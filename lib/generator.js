'use strict';

const assert = require('assert');
const fs = require('fs');
const path = require('path');
const DSL = require('@darabonba/parser');
const getBuiltin = require('./builtin');
const { Tag } = require('@darabonba/parser/lib/tag');

const REQUEST = 'request_';
const RESPONSE = 'response_';
const RUNTIME = 'runtime_';
const {
  MODEL,
  CORE,
  _dirname,
  _string,
  _name,
  _type,
  _getInclude,
  _lowerFirst,
  _defaultValue,
  _subModelName,
  _namespace,
  remove,
  _upperFirst,
  _camelCase,
  _snakeCase,
  _isBinaryOp,
  _isPointerType,
  _isBaseType,
  _avoidKeywords,
  _getGetterName,
  _isSpecialBaseType
} = require('./helper');

const Emitter = require('./emitter');
// const { type } = require('os');

function getAttr(node, attrName) {
  for (let i = 0; i < node.attrs.length; i++) {
    if (_name(node.attrs[i].attrName) === attrName) {
      return node.attrs[i].attrValue.string || node.attrs[i].attrValue.lexeme || node.attrs[i].attrValue.value;
    }
  }
}

class Visitor {
  constructor(option = {}) {
    this.option = option;
    this.header = option && option.header;
    this.baseNamespace = option && option.namespace;
    if (!this.header || !this.baseNamespace) {
      throw new Error('Darafile -> cpp -> header should not empty, please add cpp option into Darafile.example:\n' +
        '"cpp": {"header": "darabonba/core.hpp", "namespace": "DARABONBA"}');
    }

    this.pkgDir = option.pkgDir;
    this.libraries = option.libraries;
    this.outputDir = option.outputDir;
    if (option.cpp) {
      this.className = option.cpp.className || 'Client';
    }
    if(this.baseNamespace === this.className) {
      throw new Error('Please change your namespace or className, the same name will be ambiguous');
    }
    this.exec = option.exec;
    this.typedef = option.cpp.typedef || {};
    
    if (!this.outputDir) {
      throw new Error('Darafile -> cpp -> javaPackage should not empty, please add cpp option into Darafile.example:\n' +
      '"cpp": {"header": "darabonba/core.hpp", "namespace": "Darabonba::Core}');
    }

    fs.mkdirSync(this.outputDir, {
      recursive: true
    });

    this.conflictModelNameMap = {};
    this.allModleNameMap = {};

    this.srcFiles = [];

    remove(path.join(this.outputDir, 'external'));
  }

  emit(str, level){
    this.emitter.emit(str, level);
  }

  visitHeader() {
    let header = '';
    let suffix = [];
    if(this.emitter.include) {
      const headerName = this.emitter.filepath.replace('include/', '').toUpperCase().replace(/[/|.]/g, '_');

      header += '// This file is auto-generated, don\'t edit it. Thanks.\n';
      header += `#ifndef ${headerName}_\n`;
      header += `#define ${headerName}_\n`;
    }
    
    header += '#include <darabonba/Core.hpp>\n';

    [...new Set(this.headers)].map(ele =>{
      header += `#include <${ele}>\n`;
    });
    if(this.namespace) {
      this.used.push('using namespace std;');
      this.used.push('using json = nlohmann::json;');
      header += [...new Set(this.used)].sort((a, b) => a.length - b.length).join('\n') + '\n';
      this.namespace.split('::').map(namespace => {
        header += `namespace ${namespace}\n{\n`;
        suffix.push(`} // namespace ${namespace}`);
      });
    }

    this.emitter.output = header + this.emitter.output + suffix.join('\n');
    if(this.emitter.include) {
      this.emitter.output += '\n#endif\n';
    }
  }

  getInnerClient(aliasId) {
    const moduleAst = this.ast.innerDep.get(aliasId);
    const beginNotes = DSL.note.getNotes(moduleAst.notes, 0, moduleAst.moduleBody.nodes[0].tokenRange[0]);
    const clientNote = beginNotes.find(note => note.note.lexeme === '@clientName');
    if(clientNote) {
      return _string(clientNote.arg.value);
    }
    return 'Client';
  }

  saveInnerModule(ast, oriFilepath) {
    const keys = ast.innerModule.keys();
    let data = keys.next();
    const header = this.header;
    while (!data.done) {
      const aliasId = data.value;
      const moduleAst = ast.innerDep.get(aliasId);
      this.ast = ast;
      // this.modelPath = path.join(this.outputDir, this.config.package, 'models.py');
      // this.exceptionPath = path.join(this.outputDir, this.config.package, 'exceptions.py');
      const cppPath = ast.innerModule.get(aliasId);
      this.className = this.getInnerClient(aliasId);
      this.header = path.join(path.dirname(header), `${path.join(path.dirname(cppPath), _camelCase(_snakeCase(path.basename(cppPath))))}.hpp`);
      this.modelHeader = path.join(path.dirname(header), cppPath, 'models');
      this.exceptionHeader = path.join(path.dirname(header), cppPath, 'exceptions');
      this.modelDir = path.join(cppPath, 'models');
      this.exceptionDir = path.join(cppPath, 'exceptions');
      this.namespace = this.baseNamespace + '::' + _namespace(cppPath);
      const filepath = `${path.join(path.dirname(oriFilepath), path.join(path.dirname(cppPath), _camelCase(_snakeCase(path.basename(cppPath)))))}.cpp`;
      this.visitModule(moduleAst, filepath, false);
      data = keys.next();
    }
  }

  save(src = false){
    this.visitHeader();
    if(src) {
      this.visitMainExec();
    }
    this.emitter.save();
    this.used = [];
    this.headers = [];
    this.usedClass = new Map();
  }

  visit(ast, level = 0) {
    const filepath = this.option.cpp.name ? `src/${this.option.cpp.name}.cpp` : 'src/Client.cpp';
    this.builtin = getBuiltin(this);
    this.modelHeader = path.dirname(this.header) + '/models';
    this.exceptionHeader = path.dirname(this.header) + '/exceptions';
    this.modelDir = 'models';
    this.exceptionDir = 'exceptions';
    this.namespace = this.baseNamespace;
    this.visitModule(ast, filepath, level);
    this.visitCMake();
  }

  visitConflictModels(conflictModels) {
    for (let [ key ] of conflictModels) {
      let type = 'Models';
      if(key.indexOf(':') > -1) {
        const [ moduleName, modelName ] = key.split(':');
        const moudleInfo = this.imports[moduleName];
        const externEx = this.usedExternException.get(moduleName);
        if (externEx && externEx.has(modelName)) {
          type = 'Exceptions';
        }
        this.conflictModels[`${moudleInfo.namespace}::${type}::${modelName}`] = true;
        continue;
      }
      const modelName = key;
      if(this.predefined[modelName] && this.predefined[modelName].isException) {
        type = 'Exceptions';
      }
      this.conflictModels[`${this.namespace}::${type}::${modelName}`] = true;
    }
  }

  visitModule(ast, filepath, level) {
    this.ast = ast;
    this.used = [];
    this.fileBuffer = {};
    this.usedClass = new Map();
    this.moduleClass = new Map();
    this.clientName = new Map();
    ast.innerModule = new Map();
    this.predefined = ast.models;
    this.packageInfo = {};
    this.usedExternModel = ast.usedExternModel;
    this.usedExternException = ast.usedExternException;
    this.conflictModels = {};
    this.notes = ast.notes;

    this.srcFiles.push(filepath);
    if(this.overwrite(ast, filepath) === false) {
      return;
    }
    this.visitImport(ast.imports, ast.innerModule, level);
    this.visitConflictModels(ast.conflictModels);
    this.visitConflictModels(ast.sameNameModels);
    this.visitInclude(ast, level);

    this.visitSrc(ast, filepath, level);
    this.saveInnerModule(ast, filepath);
  }

  visitWhile(ast, level) {
    assert.equal(ast.type, 'while');
    this.emit('\n');
    this.emit('while (', level);
    this.visitExpr(ast.condition, level + 1);
    this.emit(') {\n');
    this.visitStmts(ast.stmts, level + 1);
    this.emit('}\n', level);
  }

  visitFor(ast, level) {
    assert.equal(ast.type, 'for');
    this.emit('for (', level);
    if(this.isIterator(ast.list.inferred)) {
      this.visitType(ast.list.inferred.valueType);
    } else {
      this.visitType(ast.list.inferred.itemType);
    }
    this.emit(` ${_name(ast.id)} : `);
    this.visitExpr(ast.list, level + 1);
    this.emit(') {\n');
    this.visitStmts(ast.stmts, level + 1);
    this.emit('}\n', level);
  }

  overwrite(ast, filepath) {
    if(!ast.moduleBody.nodes || !ast.moduleBody.nodes.length) {
      return;
    }
    const beginNotes = DSL.note.getNotes(ast.notes, 0, ast.moduleBody.nodes[0].tokenRange[0]);
    const overwirte = beginNotes.find(note => note.note.lexeme === '@overwrite');
    let targetPath = filepath;
    if(path.resolve(filepath).startsWith(path.resolve(this.outputDir))) {
      const baseDir = path.join(this.outputDir, path.sep);
      filepath = filepath.replace(baseDir, '');
    }
    targetPath = path.join(this.outputDir, filepath);
    if(overwirte && overwirte.arg.value === false && fs.existsSync(targetPath)) {
      return false;
    }
    return true;
  }

  async visitCMake() {
    const name = this.option.cpp.name || `${_snakeCase(this.option.scope)}_${_snakeCase(this.option.name)}`;
    this.visitDependencies(name);
    const CMakeTplName = this.exec ? 'CMakeLists.exec.txt' : 'CMakeLists.modern.txt';
    const version = this.version || 'master';
    let libs = '';
    let mainSubMake = 'message(STATUS "Install libraries")\n';
    // read templatefile
    let CMakeContent = fs.readFileSync(path.join(__dirname, '..', 'template', CMakeTplName), 'utf-8');
    let subCMakeContent = fs.readFileSync(path.join(__dirname, '..', 'template', 'CMakeLists.external.txt'), 'utf-8');
    let CMakeConfigContent = fs.readFileSync(path.join(__dirname, '..', 'template', 'ConfigVersion.cmake'), 'utf-8');
    let CodeCoverage = fs.readFileSync(path.join(__dirname, '..', 'template', 'CodeCoverage.cmake'), 'utf-8');

    // mkdir
    if(!fs.existsSync(path.join(this.outputDir, 'cmake'))) {
      fs.mkdirSync(path.join(this.outputDir, 'cmake'));
    }

    if(!fs.existsSync(path.join(this.outputDir, 'external'))) {
      fs.mkdirSync(path.join(this.outputDir, 'external'));
    }
    
    // cmake install config
    fs.writeFileSync(path.join(this.outputDir, 'cmake', 'CodeCoverage.cmake'), CodeCoverage);
    fs.writeFileSync(path.join(this.outputDir, 'cmake', `${name}Config.cmake.in`), CMakeConfigContent.replace(/<% name %>/g, name));
    
    // dependencies
    Object.keys(this.dependencies).map(name => {
      const cppPkg = this.dependencies[name];
      mainSubMake += `add_subdirectory(${name})\n`;
      const subDir = path.join(this.outputDir, 'external', name);
      if(!fs.existsSync(subDir)) {
        fs.mkdirSync(subDir, {recursive: true});
      }
      let content = subCMakeContent.replace(/<% name %>/g, name).replace(/<% version %>/g, version).replace(/<% link %>/g, cppPkg.gitAddress || `https://github.com/alibabacloud-sdk-cpp/${name.replace(/_/g, '-')}.git`);
      fs.writeFileSync(path.join(subDir, 'CMakeLists.txt'), content);
      // dependencies += `find_library(${name.toUpperCase().replace(/[-|.|/]/g, '-')}_LIB ${name} $\{CMAKE_CURRENT_SOURCE_DIR}/deps/lib)\n`;
      libs += `${name}\n            `;
    });
    // add core
    mainSubMake += 'add_subdirectory(darabonba_core)\n';
    const coreSubDir = path.join(this.outputDir, 'external', 'darabonba_core');
    if(!fs.existsSync(coreSubDir)) {
      fs.mkdirSync(coreSubDir);
    }
    fs.writeFileSync(path.join(this.outputDir, 'external', 'CMakeLists.txt'), mainSubMake);
    let coreSubCMake = subCMakeContent.replace(/<% name %>/g, 'darabonba_core')
      .replace(/<% version %>/g, this.option.coreVersion || 'master')
      .replace(/<% link %>/g, 'https://github.com/aliyun/tea-cpp.git');
    fs.writeFileSync(path.join(coreSubDir, 'CMakeLists.txt'), coreSubCMake);
    // main file
    CMakeContent = CMakeContent
      .replace(/<% name %>/g, name)
      .replace(/<% version %>/g, version)
      // .replace(/<% header %>/g, `include/${this.header}`)
      .replace(/<% headerDir %>/g, path.dirname(this.header))
      .replace(/<% source %>/g, this.srcFiles.join('\n        '))
      // .replace(/<% dependencies %>/g, dependencies)
      .replace(/<% LIBS %>/g, libs);
    fs.writeFileSync(path.join(this.outputDir,  'CMakeLists.txt'), CMakeContent);
  }

  visitInclude(ast, level) {
    assert.equal(ast.type, 'module');
    this.include = true;

    const subModels = Object.keys(this.predefined).filter((key) => {
      return !key.startsWith('$') && this.predefined[key].type === 'model' && key.indexOf('.') !== -1;
    }).map((key) => {
      return this.predefined[key];
    });
    
    const models = ast.moduleBody.nodes.filter((item) => {
      return item.type === 'model';
    });

    const exceptions = ast.moduleBody.nodes.filter((item) => {
      return item.type === 'exception';
    });

    this.comments = ast.comments;
   
    
    
    this.includeBefore();
    this.visitIncludeSubModels(subModels, level + 1);
    this.visitIncludeModels(models, level + 1);
    this.visitModelsIndex(models.concat(subModels), level + 1);
    

    this.visitIncludeExceptions(exceptions, level + 1);
    this.visitExceptionsIndex(exceptions, level + 1);

    this.emitter = new Emitter(this.outputDir, `include/${this.header}`);
    if(models.concat(subModels).length > 0) {
      this.headers.push(this.header.replace(/(\.h)$|(\.hpp)$/, 'Model.hpp'));
    }
    if(exceptions.length > 0) {
      this.headers.push(this.header.replace(/(\.h)$|(\.hpp)$/, 'Exception.hpp'));
    }
    this.visitIncludeClient(ast, level + 1);

    
    
    this.includeAfter();
    this.save();
    this.include = false;
  }

  getAliasName(name, aliasId) {
    let aliasName = '';
    if (!this.clientName.has(name) && name !== this.className) {
      this.clientName.set(name, aliasId);
      return aliasName;
    }
    if (aliasId) {
      aliasName = aliasId + name;
    }
    if (aliasName && !this.clientName.has(aliasName)) {
      this.clientName.set(aliasName, aliasId);
      return aliasName.replace(/-/g, '');
    }
  }

  getRealClientName(aliasId) {
    const moduleInfo = this.imports[aliasId];
    if(!moduleInfo) {
      return aliasId;
    }
    this.headers.push(moduleInfo.header);
    if(this.include) {
      const fullName = `${moduleInfo.namespace}::${moduleInfo.className}`;
      let type = '';
      if(this.includeException) {
        type = 'Exceptions::';
      }
      if(this.includeModel) {
        type = 'Models::';
      }
      return fullName.startsWith(this.namespace) ? fullName.replace(`${this.namespace}::${type}`, '') : fullName;
    }
    if(moduleInfo.aliasName) {
      this.used.push(`using ${moduleInfo.aliasName} = ${moduleInfo.namespace}::${moduleInfo.className};`);
      return moduleInfo.aliasName;
    }
    const namespaces = moduleInfo.namespace.split('::');
    if(namespaces.includes(moduleInfo.className)) {
      // deal A::B::C::B 
      this.used.push(`using namespace ${namespaces.slice(0, -1).join('::')};`);
      return namespaces.slice(-1)[0] + '::' + moduleInfo.className;
    }
    this.used.push(`using namespace ${moduleInfo.namespace};`);
    return moduleInfo.className;
  }

  getRealModelName(fullModelName) {
    const fullModelNameArr = fullModelName.split('::');
    if(fullModelName !== MODEL) {
      fullModelName = fullModelNameArr.map((m, i) => {
        return _avoidKeywords(m);
      }).join('::');
    }
    if(fullModelNameArr[fullModelNameArr.length - 2] === 'Exceptions') {
      fullModelName = fullModelName + 'Exception';
    }

    if(this.conflictModels[fullModelName]) {
      return fullModelName;
    }

    

    if(this.include) {
      let type = '';
      if(this.includeException) {
        type = 'Exceptions::';
      }
      if(this.includeModel) {
        type = 'Models::';
      }
      return fullModelName.startsWith(this.namespace) ? fullModelName.replace(`${this.namespace}::${type}`, '') : fullModelName;
    }

    
   
    let [ modelName ] = fullModelName.split('::').slice(-1);
    const existName = this.usedClass.get(modelName.toLowerCase());
    if(existName && existName !== fullModelName) {
      return fullModelName;
    }

    this.used.push(`using namespace ${fullModelName.split('::').slice(0, -1).join('::')};`);
    
    
    this.usedClass.set(modelName.toLowerCase(), fullModelName);
    return modelName;
  }

  visitIncludeExceptions(exceptions, level) {
    this.includeException = true;
    for (let i = 0; i < exceptions.length; i++) {
      const exception = exceptions[i];
      const exceptionName = exception.exceptionName.lexeme;
      const filename = path.join('include', _dirname(this.exceptionHeader), `${_camelCase(_snakeCase(exceptionName))}Exception.hpp`);
      this.emitter = new Emitter(this.outputDir, filename);
      this.emit('namespace Exceptions\n{\n');
      this.visitIncludeException(exception, 1);
      this.emit('\n', level);
      this.emit('} // namespace Exceptions\n', level);
      this.saveBuffer();
    }
    this.flushBuffer();
    this.includeException = false;
  }

  visitIncludeSubModels(subModels, level) {
    // 子模型现在会作为内部类在主模型中生成，不再需要生成独立文件
    // 保留这个方法以便兼容
    return;
  }

  visitIncludeModels(models, level){
    this.includeModel = true;
    // 用于记录文件名的映射关系：规范化名称 -> 实际使用的文件名（保持第一个model的原始大小写）
    const fileNameMap = new Map();
    
    for (let i = 0; i < models.length; i++) {
      const model = models[i];
      const modelName = model.modelName.lexeme;
      
      let filename;
      
      if(modelName.indexOf('.') > 0) {
        // 嵌套 model：如 MyModel.submodel -> MyModelSubmodel.hpp
        const normalizedName = _subModelName(modelName);
        filename = path.join('include', _dirname(this.modelHeader), `${normalizedName}.hpp`);
      } else {
        // 普通 model：完全保持原始大小写，不做任何规范化
        // 使用小写作为 key 来判断是否同名（不区分大小写）
        const canonicalKey = modelName.toLowerCase();
        
        // 如果已经有相同的 canonicalKey，使用第一次的文件名
        if (fileNameMap.has(canonicalKey)) {
          filename = fileNameMap.get(canonicalKey);
        } else {
          // 文件名完全保持 model 原始大小写
          filename = path.join('include', _dirname(this.modelHeader), `${modelName}.hpp`);
          fileNameMap.set(canonicalKey, filename);
        }
      }
      
      this.emitter = new Emitter(this.outputDir, filename);
      this.emit('namespace Models\n{\n');
      
      this.visitIncludeModel(model, 1);
      this.emit('\n');
      this.emit('} // namespace Models\n', level);
      this.saveBuffer();
    }
    this.flushBuffer();
    this.includeModel = false;
  }

  visitIncludeException(ast, level) {
    assert.equal(ast.type, 'exception');
    const exceptionName = _name(ast.exceptionName);
    this.visitAnnotation(ast.annotation, level);
    const cppClassName = `${_subModelName(exceptionName)}Exception`;
    this.emit(`class ${cppClassName} : public `, level);
    this.visitExtendOn(ast.extendOn, 'exception');
    this.emit(' {\n');
    this.emit('public:\n', level);

    // friend from_json
    this.emit(`friend void from_json(const Darabonba::Json& j, ${cppClassName}& obj) { \n`, level + 1);
    const hasFields = ast.exceptionBody.nodes && ast.exceptionBody.nodes.length > 0;
    if (!hasFields) {
      this.emit('(void)j; (void)obj; \n', level + 2);
    }
    this.visitFieldsFromJson(ast.exceptionBody, exceptionName, level + 1);
    this.emit('};\n', level + 1);

    // constructor
    this.emit(`${cppClassName}() ;\n`, level + 1);
    this.emit(`${cppClassName}(const ${cppClassName} &) = default ;\n`, level + 1);
    this.emit(`${cppClassName}(${cppClassName} &&) = default ;\n`, level + 1);
    this.emit(`${cppClassName}(const Darabonba::Json & obj)`, level + 1);
    this.visitExtendConstructor(ast.extendOn, 'exception');
    this.emit(' { from_json(obj, *this); };\n');
    // destructor
    this.emit(`virtual ~${cppClassName}() = default ;\n`, level + 1);
    // assign opeartor
    this.emit(`${cppClassName}& operator=(const ${cppClassName} &) = default ;\n`, level + 1);
    this.emit(`${cppClassName}& operator=(${cppClassName} &&) = default ;\n`, level + 1);

    this.visitIncludeExceptionFunc(ast.exceptionBody, exceptionName, level + 1);

    if(ast.exceptionBody.nodes && ast.exceptionBody.nodes.length > 0) {
      this.emit('protected:\n', level);
      this.visitIncludeField(ast.exceptionBody, exceptionName, level + 1);
    }
    this.emit('};\n', level);
  }


  visitModelsIndex(models) {
    if(models.length === 0) {
      return;
    }

    // 分析模型之间的依赖关系
    const modelDependencies = new Map(); // 存储每个模型依赖的其他模型
    const modelNames = new Set(); // 存储所有模型名称

    // 收集所有模型名称
    for (let i = 0; i < models.length; i++) {
      const model = models[i];
      let modelName = model.modelName.lexeme;
      if(modelName.indexOf('.') > 0) {
        modelName = _subModelName(modelName);
      }
      modelNames.add(modelName);
    }

    // 分析每个模型的字段依赖
    for (let i = 0; i < models.length; i++) {
      const model = models[i];
      let modelName = model.modelName.lexeme;
      if(modelName.indexOf('.') > 0) {
        modelName = _subModelName(modelName);
      }
      
      const dependencies = new Set();
      this.collectModelDependencies(model, dependencies, modelNames);
      modelDependencies.set(modelName, dependencies);
    }

    // 按依赖关系排序模型，确保在引用模型之前先包含被引用的模型
    const sortedModels = this.topologicalSort(models, modelDependencies);

    const filename = path.join('include', this.header.replace(/(.h)$|(.hpp)$/, 'Model.hpp'));
    this.emitter = new Emitter(this.outputDir, filename);
    const namespace = this.namespace;
    this.namespace = '';
    
    // 用于记录已添加的文件名（不区分大小写），避免重复添加
    const addedFiles = new Set();
    
    for (let i = 0; i < sortedModels.length; i++) {
      const model = sortedModels[i];
      let modelName = model.modelName.lexeme;
      // 跳过嵌套模型，它们已经作为内部类包含在父模型中
      if(modelName.indexOf('.') > 0) {
        continue; // 嵌套模型不需要独立的头文件
      }
      
      // 完全保持原始大小写，不做任何规范化
      const canonicalKey = modelName.toLowerCase();
      
      // 只添加第一个遇到的同名文件（不区分大小写）
      if (!addedFiles.has(canonicalKey)) {
        this.headers.push(`${this.modelHeader}/${modelName}.hpp`);
        addedFiles.add(canonicalKey);
      }
    }

    this.save();
    this.namespace = namespace;
  }

  /**
   * @brief 收集模型字段的依赖关系
   */
  collectModelDependencies(model, dependencies, modelNames) {
    if (!model.modelBody || !model.modelBody.nodes) {
      return;
    }

    for (let i = 0; i < model.modelBody.nodes.length; i++) {
      const node = model.modelBody.nodes[i];
      const value = node.fieldValue;
      
      // 检查字段类型是否引用了模型
      if (value.idType === 'model' && !value.moduleName) {
        const modelName = _subModelName(_name(value));
        if (modelNames.has(modelName)) {
          dependencies.add(modelName);
        }
      } else if (value.fieldType && value.fieldType.idType === 'model' && !value.fieldType.moduleName) {
        const modelName = _subModelName(_name(value.fieldType));
        if (modelNames.has(modelName)) {
          dependencies.add(modelName);
        }
      } else if (value.type === 'modelBody') {
        // 嵌套模型依赖于父模型
        if (modelNames.has(_name(model.modelName))) {
          dependencies.add(_name(model.modelName));
        }
      }
      
      // 递归处理数组和映射类型中的模型引用
      if (value.fieldType === 'array' && value.fieldItemType) {
        this.collectModelDependenciesInType(value.fieldItemType, dependencies, modelNames);
      } else if (value.fieldType === 'map' && value.valueType) {
        this.collectModelDependenciesInType(value.valueType, dependencies, modelNames);
      } else if (value.type === 'array' && value.subType) {
        this.collectModelDependenciesInType(value.subType, dependencies, modelNames);
      } else if (value.type === 'map' && value.valueType) {
        this.collectModelDependenciesInType(value.valueType, dependencies, modelNames);
      }
    }
  }

  collectModelDependenciesInType(type, dependencies, modelNames) {
    if (type.idType === 'model' && !type.moduleName) {
      const modelName = _subModelName(_name(type));
      if (modelNames.has(modelName)) {
        dependencies.add(modelName);
      }
    } else if (type.fieldType && type.fieldType.idType === 'model' && !type.fieldType.moduleName) {
      const modelName = _subModelName(_name(type.fieldType));
      if (modelNames.has(modelName)) {
        dependencies.add(modelName);
      }
    }
  }

  topologicalSort(models, modelDependencies) {
    const visited = new Set();
    const tempVisited = new Set();
    const result = [];
    const modelMap = new Map();

    // 创建模型映射
    for (let i = 0; i < models.length; i++) {
      const model = models[i];
      let modelName = model.modelName.lexeme;
      if(modelName.indexOf('.') > 0) {
        modelName = _subModelName(modelName);
      }
      modelMap.set(modelName, model);
    }

    // DFS遍历
    const visit = (modelName) => {
      if (tempVisited.has(modelName)) {
        // 检测到循环依赖，跳过
        return;
      }
      
      if (!visited.has(modelName)) {
        tempVisited.add(modelName);
        const dependencies = modelDependencies.get(modelName) || new Set();
        for (const dependency of dependencies) {
          visit(dependency);
        }
        tempVisited.delete(modelName);
        visited.add(modelName);
        result.push(modelMap.get(modelName));
      }
    };

    // 遍历所有模型
    for (const modelName of modelMap.keys()) {
      if (!visited.has(modelName)) {
        visit(modelName);
      }
    }

    return result;
  }

  visitExceptionsIndex(exceptions) {
    if(exceptions.length === 0) {
      return;
    }

    const filename = path.join('include', this.header.replace(/(\.h)$|(\.hpp)$/, 'Exception.hpp'));
    this.emitter = new Emitter(this.outputDir, filename);
    const namespace = this.namespace;
    this.namespace = '';
    for (let i = 0; i < exceptions.length; i++) {
      const exception = exceptions[i];
      const exceptionName = exception.exceptionName.lexeme;
      this.headers.push(`${this.exceptionHeader}/${_camelCase(_snakeCase(exceptionName))}Exception.hpp`);
    }

    this.save();
    this.namespace = namespace;
  }

  visitSrc(ast, filepath) {
    let level = 0;
    assert.equal(ast.type, 'module');
    this.emitter = new Emitter(this.outputDir, filepath);
    this.headers.push(this.header);
    const nonStaticWraps = ast.moduleBody.nodes.filter((item) => {
      return item.type === 'function' && !item.isStatic;
    });
    const apis = ast.moduleBody.nodes.filter((item) => {
      return item.type === 'api';
    });
    const init = ast.moduleBody.nodes.filter((item) => {
      return item.type === 'init';
    });
    this.comments = ast.comments;
    var extendParam = {};
    if (nonStaticWraps.length > 0 || apis.length > 0) {
      extendParam.writeConstruct = true;
    }
    
    this.noDefaultNamespace = true;
    // creat contructor
    for (let i = 0; i < init.length; i++) {
      this.emit('\n');
      this.visitConstructor(init[i], ast.extends, level);
    }

    let lastToken = 0;
    for (let i = 0; i < apis.length; i++) {
      this.emit('\n');
      const apiNotes = DSL.note.getNotes(this.notes, lastToken, apis[i].tokenRange[0]);
      const sse = apiNotes.find(note => note.note.lexeme === '@sse');
      const skip = apiNotes.find(note => note.note.lexeme === '@skip');
      lastToken = apis[i].tokenRange[1];
      if(sse && sse.arg.value) {
        continue;
      }
      if(skip && _string(skip.arg.value) === 'cpp') {
        continue;
      }
      this.visitAPI(apis[i], level);
    }
    this.emit('\n');
    const functions = ast.moduleBody.nodes.filter((item) => {
      return item.type === 'function';
    });

    for (let i = 0; i < functions.length; i++) {
      if (i !== 0) {
        this.emit('\n');
      }
      this.visitFunction(functions[i], level);
    }
    this.save(true);
  }

  saveBuffer() {
    const filepath = this.emitter.filepath;
    if(this.fileBuffer[filepath]) {
      this.fileBuffer[filepath].headers = this.headers.concat(this.fileBuffer[filepath].headers);
      this.fileBuffer[filepath].used = this.used.concat(this.fileBuffer[filepath].used);
      this.fileBuffer[filepath].emitter.output = this.emitter.output + this.fileBuffer[filepath].emitter.output;
      return;
    }

    this.fileBuffer[filepath] = {
      headers: this.headers,
      emitter: this.emitter,
      used: this.used,
    };
    this.headers = [];
    this.used = [];
    this.emitter = null;
  }

  flushBuffer() {
    Object.keys(this.fileBuffer).map(filepath => {
      this.emitter = this.fileBuffer[filepath].emitter;
      this.headers = this.fileBuffer[filepath].headers;
      this.used = this.fileBuffer[filepath].used;
      this.save();
      this.emitter = null;
      this.headers = [];
      this.used = [];
    });
    this.fileBuffer = {};
  }

  visitModels(ast, level){
    const models = ast.moduleBody.nodes.filter((item) => {
      return item.type === 'model';
    });
    for (let i = 0; i < models.length; i++) {
      const modelName = models[i].modelName.lexeme;
      const filepath = path.join('src', 'models', `${_camelCase(_snakeCase(modelName))}.cpp`);
      this.emitter = new Emitter(this.outputDir, filepath);
      this.srcFiles.push(filepath);
      this.modelBefore();
      if (this.predefined) {
        let relatedSubModels = Object.keys(this.predefined).filter((key) => {
          return key.startsWith(modelName + '.');
        }).map((key) => {
          return this.predefined[key];
        });
        for (let i = 0; i < relatedSubModels.length; i++) {
          this.visitModel(relatedSubModels[i], level);
        }
      }
      this.visitModel(models[i], level);
      this.saveBuffer();
    }
  }

  getClassNamespace(cppPath, namespace) {
    if(path.resolve(cppPath).startsWith(path.resolve(this.outputDir))) {
      const baseDir = path.join(this.outputDir, 'src', path.sep);
      cppPath = cppPath.replace(baseDir, '');
    }
    const arr = cppPath.split('/').slice(1);
    let className = namespace || this.namespace;
    arr.map(key => {
      className += '::' + _camelCase(_snakeCase(key));
    });
    
    return className;
  }
  

  visitImport(imports, innerModule, filepath) {
    this.headers = [];
    this.imports = {};
    if (imports.length === 0) {
      return;
    }
    if (!this.pkgDir) {
      throw new Error('Must specific pkgDir when have imports');
    }

    const lockPath = path.join(this.pkgDir, '.libraries.json');
    const lock = JSON.parse(fs.readFileSync(lockPath, 'utf8'));
    for (let i = 0; i < imports.length; i++) {
      const item = imports[i];
      const aliasId = item.lexeme;
      const main = item.mainModule;
      const inner = item.module;
      const moduleDir = main ? this.libraries[main] : this.libraries[aliasId];
      const innerPath = item.innerPath;
      if (!moduleDir && innerPath) {
        let cppPath = innerPath.replace(/(\.tea)$|(\.spec)$|(\.dara)$/gi, '').split('/').join(path.sep);
        const classNamespace = this.getClassNamespace(cppPath);
        const className = this.getInnerClient(aliasId, cppPath);
        const aliasName = this.getAliasName(className, aliasId);
        this.imports[aliasId] = {
          aliasName: aliasName,
          className: className,
          namespace: classNamespace,
          header: path.join(path.dirname(this.header), path.join(path.dirname(cppPath), _camelCase(_snakeCase(path.basename(cppPath))))) + '.hpp',
          modelDir: path.join(cppPath, 'models'),
          exceptionDir: path.join(cppPath, 'exceptions'),
        };

        innerModule.set(aliasId, cppPath);
        continue;
      }
      let targetPath = '';
      if (moduleDir.startsWith('./') || moduleDir.startsWith('../')) {
        targetPath = path.join(this.pkgDir, moduleDir);
      } else if (moduleDir.startsWith('/')) {
        targetPath = moduleDir;
      } else {
        targetPath = path.join(this.pkgDir, lock[moduleDir]);
      }
      const pkgPath = fs.existsSync(path.join(targetPath, 'Teafile')) ? path.join(targetPath, 'Teafile') : path.join(targetPath, 'Darafile');
      const pkg = JSON.parse(fs.readFileSync(pkgPath));
      const release = pkg.releases && pkg.releases.cpp;
      const cppPkg = pkg.cpp;
      if (!cppPkg || !cppPkg.header) {
        throw new Error(`The '${aliasId}' has no C++ supported.`);
      } else {
        cppPkg.release = release;
      }
      cppPkg.scope = pkg.scope;
      // this.headers.push(cppPkg.header);
      let modelDir= 'models';
      let exceptionDir = 'exceptions';
      let className = cppPkg.className || 'Client';
      let classNamespace = cppPkg.namespace;
      let header = cppPkg.header;
      if(inner && pkg.exports[inner]) {
        let cppPath = pkg.exports[inner];
        cppPath = cppPath.replace(/(\.tea)$|(\.spec)$|(\.dara)$/gi, '');
        modelDir = `${cppPath}Models`;
        exceptionDir = `${cppPath}Exceptions`;
        classNamespace = this.getClassNamespace(cppPath, classNamespace);
        className = cppPkg.exports && cppPkg.exports[inner];
        header = path.join(path.dirname(cppPkg.header), path.join(path.dirname(cppPath), _camelCase(_snakeCase(path.basename(cppPath))))) + '.hpp';
      }
      const aliasName = this.getAliasName(className, aliasId);
      this.imports[aliasId] = {
        aliasName: aliasName,
        className: className || 'Client',
        namespace: classNamespace,
        header: header,
        modelDir: modelDir,
        exceptionDir: exceptionDir,
      };
      
    }
  }

  visitDependencies(projectName) {
    // get all dependencies
    this.dependencies = {};
    // 如果没有指定 pkgDir，则跳过依赖分析
    if (!this.pkgDir) {
      return;
    }
    const lockPath = path.join(this.pkgDir, '.libraries.json');
    if(!fs.existsSync(lockPath)) {
      return;
    }
    // const deps = Object.keys(this.libraries).map(key => this.libraries[key]);
    const lock = JSON.parse(fs.readFileSync(lockPath, 'utf8'));
    Object.keys(lock).map(key => {
      // if(!deps.includes(key)) {
      //   return;
      // }
      
      const targetPath = path.join(this.pkgDir, lock[key]);
      const pkgPath = fs.existsSync(path.join(targetPath, 'Teafile')) ? path.join(targetPath, 'Teafile') : path.join(targetPath, 'Darafile');
      const pkg = JSON.parse(fs.readFileSync(pkgPath));
      const release = pkg.releases && pkg.releases.cpp;
      const cppPkg = pkg.cpp;
      if (!cppPkg || !cppPkg.header || !release) {
        throw new Error(`The '${pkg.scope}:${pkg.name}' has no C++ supported, if the subModule use this module cpp build will be failed.`);
      }
      const [ name, version ] = release.split(':');
      if(name === projectName || name === 'darabonba_core') {
        return;
      }
      if(!version && this.dependencies[name]) {
        return;
      }
      cppPkg.version = version;
      this.dependencies[name] = cppPkg;
    });
  }

  visitParams(ast, consts = new Map) {
    assert.equal(ast.type, 'params');
    this.emit('(');
    for (var i = 0; i < ast.params.length; i++) {
      if (i !== 0) {
        this.emit(', ');
      }
      const node = ast.params[i];
      assert.equal(node.type, 'param');
      const paramName = _avoidKeywords(_name(node.paramName));
      if(consts.get(paramName) === false) {
        this.visitType(node.paramType);
        this.emit(` &${paramName}`);
      } else {
        this.emit('const ');
        this.visitType(node.paramType);
        this.emit(` &${paramName}`);
      }
      
    }
    this.emit(')');
  }

  // getRealModelName(className) {
  //   let names = className.split('.');
  //   let name = _subModelName(className);
  //   if(names.length < 2) {
  //     return name;
  //   }
  //   for(names.splice(names.length - 1, 1);names.length > 0;names.splice(names.length - 1, 1)) {
  //     let parentClassName = _subModelName(names.join('.'));
  //     name = parentClassName + '::' + name;
  //   }
  //   return name;
  // }

  isIterator(returnType) {
    if (returnType.type === 'iterator' || returnType.type === 'asyncIterator') {
      return true;
    }
    return false;
  }

  visitType(ast, level) {
    if (ast.type === 'array') {
      this.emit('vector<');
      this.visitType(ast.subType || ast.itemType);
      this.emit('>');
    } else if (ast.type === 'moduleModel') {
      const [moduleId, ...rest] = ast.path;
      const modelName = _subModelName(rest.map((item) => item.lexeme).join('.'));
      let type = 'Models';
      const externEx = this.usedExternException.get(_name(moduleId));
      if (externEx && externEx.has(modelName)) {
        type = 'Exceptions';
      }
      const moduleInfo = this.imports[_name(moduleId)];
      this.headers.push(moduleInfo.header);
      this.emit(this.getRealModelName(`${moduleInfo.namespace}::${type}::${modelName}`));
    } else if (ast.type === 'subModel') {
      const [moduleId, ...rest] = ast.path;
      const modelName = _subModelName([moduleId.lexeme, ...rest.map((item) => {
        return item.lexeme;
      })].join('.'));
      this.emit(this.getRealModelName(`${this.namespace}::Models::${modelName}`));
    } else if (ast.type === 'moduleTypedef') {
      const [moduleId, ...rest] = ast.path;
      const type = rest.map((item) => { return item.lexeme; }).join('.');
      this.emit(this.visitTypedef(type, moduleId));
    } else if (ast.type === 'typedef' || ast.idType === 'typedef') {
      this.emit(this.visitTypedef(ast));
    } else if (ast.type === 'map') {
      if((ast.valueType.type === 'basic' && ast.valueType.name === 'any')
        || _name(ast.valueType) === 'any'){
        this.emit('json');
      } else {
        this.headers.push('map');
        this.emit('map<');
        this.visitType(ast.keyType);
        this.emit(', ');
        this.visitType(ast.valueType);
        this.emit('>');
      }
    } else if (ast.type === 'model' || ast.idType === 'model') {
      let predefined = this.predefined;
      let moduleInfo = this;
      if(ast.moduleName) {
        predefined = this.usedExternException.get(ast.moduleName);
        moduleInfo = this.imports[ast.moduleName];
      }
      
      if((!predefined || !predefined[_name(ast)]) && _name(ast).startsWith('$') && _type(_name(ast)) !== _name(ast)) {
        this.emit(this.getType(_name(ast)));
        return;
      }
      let type = 'Models';
      if (predefined && predefined[_name(ast)] && predefined[_name(ast)].isException) {
        type = 'Exceptions';
      }
      this.headers.push(moduleInfo.header);
      this.emit(this.getRealModelName(`${moduleInfo.namespace}::${type}::${_subModelName(_name(ast))}`));
    } else if (ast.type === 'module' || ast.idType === 'module') {
      this.emit('shared_ptr<');
      this.emit(this.getRealClientName(_name(ast)));
      this.emit('>');
    } else if (ast.type === 'module_instance') {
      this.emit('shared_ptr<');
      const moduleInfo = this.imports[_name(ast)];
      if(moduleInfo) {
        this.emit(this.getRealClientName(_name(ast)));
      } else if(_name(ast).startsWith('$') && this.builtin[_name(ast)]) {
        this.emit(`${this.builtin[_name(ast)].getClassName()}`);
      }
      this.emit('>');
    } else if (this.isIterator(ast)) {
      if(ast.type === 'asyncIterator') {
        this.emit('Future');
      }
      this.emit('Generator<');
      this.visitType(ast.valueType);
      this.emit('>');
    } else if (ast.type === 'entry') {
      this.emit('pair<string,');
      this.visitType(ast.valueType);
      this.emit('>');
    } else {
      const typeName = this.getType(_name(ast));
      this.emit(typeName);
    }
  }

  visitAnnotation(annotation, level) {
    if (!annotation || !annotation.value) {
      return;
    }
    let comments = DSL.comment.getFrontComments(this.comments, annotation.index);
    this.visitComments(comments, level);
    annotation.value.split('\n').forEach((line) => {
      this.emit(`${line}`, level);
      this.emit('\n');
    });
  }

  visitAPIBody(ast, level) {
    assert.equal(ast.type, 'apiBody');
    this.emit(`Darabonba::Http::Request ${REQUEST} = Darabonba::Http::Request();\n`, level);
    if (ast.stmts.stmts) {
      for (var i = 0; i < ast.stmts.stmts.length; i++) {
        this.visitStmt(ast.stmts.stmts[i], level);
      }
    }
  }

  visitRuntimeOptions(ast, level){
    this.emit('json({\n');
    for (let i = 0; i < ast.fields.length; i++) {
      const field = ast.fields[i];
      let comments = DSL.comment.getFrontComments(this.comments, field.tokenRange[0]);
      this.visitComments(comments, level);
      if (field.type === 'objectField') {
        var key = _name(field.fieldName);
        this.emit(`{"${key}", `, level);
        this.visitObjectFieldValue(field.expr, level);
        this.emit('}');
      } else {
        throw new Error('unimplemented: unknown field type in visitFieldInObject: ' + field.type);
      }
      if (i < ast.fields.length - 1) {
        this.emit(',');
      }
      this.emit('\n');
    }
    this.emit('})', level);
  }


  visitStmt(ast, level) {
    let comments = DSL.comment.getFrontComments(this.comments, ast.tokenRange[0]);
    this.visitComments(comments, level);
    if (ast.type === 'return') {
      this.visitReturn(ast, level);
    } else if (ast.type === 'yield') {
      this.visitYield(ast, level);
    } else if (ast.type === 'if') {
      this.visitIf(ast, level);
    } else if (ast.type === 'throw') {
      this.visitThrow(ast, level);
    } else if (ast.type === 'assign') {
      this.visitAssign(ast, level);
    } else if (ast.type === 'retry') {
      this.visitRetry(ast, level);
    } else if (ast.type === 'break') {
      this.emit('break;\n', level);
    } else if (ast.type === 'declare') {
      this.visitDeclare(ast, level);
    } else if (ast.type === 'while') {
      this.visitWhile(ast, level);
    } else if (ast.type === 'for') {
      this.visitFor(ast, level);
    } else if (ast.type === 'try') {
      this.visitTry(ast, level);
    } else if (ast.type === 'super') {
      // C++ deal with other way
    }else {
      this.emit('', level);
      this.visitExpr(ast, level);
      this.emit(';\n');
    }
  }

  visitTry(ast, level) {
    this.emit('try {\n', level);
    this.visitStmts(ast.tryBlock, level + 1);
    this.emit('}', level);
    if (ast.catchBlocks && ast.catchBlocks.length > 0) {
      ast.catchBlocks.forEach(catchBlock => {
        if (!catchBlock.id) {
          return;
        }
        let errorName = _avoidKeywords(_name(catchBlock.id));
        if (!catchBlock.id.type) {
          this.emit(` catch (const std::exception ${errorName}) {\n`);
        } else {
          this.emit(' catch (const ');
          this.visitType(catchBlock.id.type);
          this.emit(` ${errorName}) {\n`);
        }
        this.visitStmts(catchBlock.catchStmts, level + 1);
        this.emit('}', level);
      });
    } else if (ast.catchBlock && ast.catchBlock.stmts.length > 0) {
      let errorName = _avoidKeywords(_name(ast.catchId));
      this.emit(` catch (const std::exception ${errorName}) {\n`);
      this.visitStmts(ast.catchBlock, level + 1);
      this.emit('}\n', level);
      // this.emit(`} catch (const exception _${errorName}) {`, level);
      // this.emit('\n');
      // this.emit('json _errInfo;', level + 1);
      // this.emit('_errInfo["code"] = "Exception";', level + 1);
      // this.emit(`_errInfo["message"] = _${errorName}.what();`, level + 1);
      // this.emit(`Darabonba::Error ${errorName} = Darabonba::Error(_errInfo);\n`, level + 1);
      // this.visitStmts(ast.catchBlock, level + 1);
      // this.emit('}', level);
    }

    if (ast.finallyBlock && ast.finallyBlock.stmts.length > 0) {
      this.emit(' finally {\n');
      this.visitStmts(ast.finallyBlock, level + 1);
      this.emit('}', level);
    }
    this.emit('\n', level);
  }

  visitFieldTypeDefault(value, level, modelName, fieldName) {
    if (value.tag === Tag.TYPE || (value.tag === Tag.ID && value.type === 'basic')) {
      this.emit(`${_defaultValue(value.lexeme)}`);
    } else {
      this.visitFieldType(value, level, modelName, fieldName);
      this.emit('()');
    }
  }

  checkStream(value) {
    if (value.fieldType === 'array') {
      // basic type
      if (value.fieldItemType.tag === 8 && 
        (_type(value.fieldItemType.lexeme) === 'shared_ptr<Darabonba::IStream>' || 
        _type(value.fieldItemType.lexeme) === 'shared_ptr<Darabonba::OStream>')) {
        return true;
      } else if (value.fieldItemType.type === 'map') {
        return this.checkStreamType(value.fieldItemType);
      } else if (value.fieldItemType.fieldType === 'array') {
        return this.checkStream(value.fieldItemType);
      }
    } else if (value.fieldType === 'map') {
      return this.checkStreamType(value.valueType);
    } else if (typeof value.fieldType === 'string' && 
      (_type(value.fieldType) === 'shared_ptr<Darabonba::IStream>' || 
        _type(value.fieldType) === 'shared_ptr<Darabonba::OStream>')) {
      return true;
    } else if(value.fieldType && 
      (_type(value.fieldType.lexeme) === 'shared_ptr<Darabonba::IStream>' || 
    _type(value.fieldType.lexeme) === 'shared_ptr<Darabonba::OStream>')) {
      return true;
    }
    return false;
  }

  checkStreamType(ast) {
    if (ast.type === 'map') {
      if(ast.valueType.type === 'basic' && ast.valueType.name === 'any'){
        return false;
      }
      return this.checkStream(ast.valueType);
    } else if (ast.type === 'array') {
      return this.checkStream(ast.subType || ast.itemType);
    } else if (_type(_name(ast)) === 'shared_ptr<Darabonba::IStream>' || 
    _type(_name(ast) === 'shared_ptr<Darabonba::OStream>')) {
      return true;
    }
    return false;
  }

  visitTypedef(type, module) {
    if (module && module.idType === 'module') {
      const aliasId = _name(module);
      if (this.moduleTypedef[aliasId] && this.moduleTypedef[aliasId][type]) {
        if (this.moduleTypedef[aliasId][type].import) {
          this.imports.push({
            packageName: this.moduleTypedef[aliasId][type].import,
            className: this.moduleTypedef[aliasId][type].type,
          });
        }
        
        return this.getTypedefType(this.moduleTypedef[aliasId][type].type);
      }
    }

    if (type.idType === 'typedef' && this.typedef[type.lexeme]) {
      if (this.typedef[type.lexeme]) {
        if (this.typedef[type.lexeme].import) {
          this.imports.push({
            packageName: this.typedef[type.lexeme].import,
            className: this.typedef[type.lexeme].type,
          });
        }

        return this.getTypedefType(this.typedef[type.lexeme].type);
      }
    }
  }

  getTypedefType(type) {
    if(/\bDict\b/.test(type)) {
      this.usedTypes.push('Dict');
    }

    if(/\bList\b/.test(type)) {
      this.usedTypes.push('List');
    }

    if(/\bAny\b/.test(type)) {
      this.usedTypes.push('Any');
    }

    if(/\bBinaryIO\b/.test(type)) {
      this.usedTypes.push('BinaryIO');
    }

    return type;
  }

  isModuleType(value) {
    if (value.type === 'moduleModel' || value.type === 'module' 
      || value.idType === 'module' || (value.fieldType && value.fieldType.idType === 'module')) {
      return true;
    }
    return false;
  }

  isModelType(ast) {
    if (ast.type === 'moduleModel' || ast.type === 'subModel'
      || ast.type === 'model' || ast.idType === 'model') {
      return true;
    } 
    return false;
  }

  visitFieldType(value, level, modelName, fieldName) {
    if (value.type === 'modelBody') {
      const subModelName = _subModelName([modelName, fieldName].join('.'));
      // 判断是否是当前正在生成的模型的嵌套模型
      if (this.currentParentModel && modelName.startsWith(this.currentParentModel)) {
        // 嵌套模型 - 使用内部类名
        // 如果当前在嵌套类中，使用当前嵌套类的类名，否则使用主模型的类名
        const cppClassName = this.currentCppClassName || _subModelName(this.currentParentModel);
        let nestedClassName = _upperFirst(fieldName);
        // 如果嵌套类名与父类名相同，添加 "Item" 后缀避免C++构造函数名冲突
        if (nestedClassName === cppClassName) {
          nestedClassName = nestedClassName + 'Item';
        }
        this.emit(`${cppClassName}::${nestedClassName}`);
      } else {
        // 旧逻辑 - 使用独立类
        this.headers.push(`${this.modelHeader}/${subModelName}.hpp`);
        this.emit(this.getRealModelName(`${this.namespace}::Models::${subModelName}`));
      }
    } else if (value.type === 'array') {
      this.headers.push('vector');
      this.emit('vector<');
      this.visitFieldType(value.subType || value.itemType, level, modelName, fieldName);
      this.emit('>');
    } else if (value.fieldType === 'array') {
      this.headers.push('vector');
      this.emit('vector<');
      // 递归调用时需要传递正确的fieldName，但对于数组元素类型，使用原始的fieldName
      this.visitFieldType(value.fieldItemType, level, modelName, fieldName);
      this.emit('>');
    } else if(((value.type === 'map' || value.fieldType === 'map') && 
      _name(value.valueType) === 'any')) {
      this.emit('Darabonba::Json');
    } else if (value.fieldType === 'map') {
      this.headers.push('map');
      this.emit('map<');
      this.emit(`${_type(_name(value.keyType))}, `);
      this.visitFieldType(value.valueType, level, modelName, fieldName);
      this.emit('>');
    } else if (value.type === 'map') {
      this.headers.push('map');
      this.emit('map<');
      this.emit(`${_type(_name(value.keyType))}, `);
      this.visitFieldType(value.valueType, level, modelName, fieldName);
      this.emit('>');
    } else if (value.idType === 'model') {
      let predefined = this.predefined;
      let moduleInfo = this;
      if(value.moduleName) {
        predefined = this.usedExternException.get(value.moduleName);
        moduleInfo = this.imports[value.moduleName];
        this.headers.push(moduleInfo.header);
      }
      let type = 'Models';
      if (predefined[_name(value)] && predefined[_name(value)].isException) {
        type = 'Exceptions';
      }
      const modelName = _subModelName(_name(value));
      if(!value.moduleName) {
        this.headers.push(`${type === 'Models' ? this.modelHeader : this.exceptionHeader}/${modelName}.hpp`);
      }
      this.emit(this.getRealModelName(`${moduleInfo.namespace}::${type}::${modelName}`));
    } else if (value.tag === Tag.TYPE) {
      const type = this.getType(value.lexeme);
      this.emit(`${type}`);
    } else if (value.tag === Tag.ID) {
      this.visitType(value);
    } else if (value.type === 'moduleModel') {
      let type = 'Models';
      const [moduleId, ...models] = value.path;
      const moduleName = _name(moduleId);
      const modelName = _subModelName(models.map((item) => item.lexeme).join('.'));
      const externEx = this.usedExternException.get(moduleName);
      if (externEx && externEx.has(modelName)) {
        type = 'Exceptions';
      }
      const moduleInfo = this.imports[moduleName];
      const namespace = moduleInfo.namespace;
      this.headers.push(moduleInfo.header);
      this.emit(this.getRealModelName(`${namespace}::${type}::${modelName}`));
      
    } else if (value.type === 'subModel') {
      const [moduleId, ...rest] = value.path;
      const modelName = _subModelName([moduleId.lexeme, ...rest.map((item) => {
        return item.lexeme;
      })].join('.'));
      this.headers.push(`${this.modelHeader}/${modelName}.hpp`);
      this.emit(this.getRealModelName(`${this.namespace}::Models::${modelName}`));
    } else if (typeof value.fieldType === 'string'){
      const type = this.getType(value.fieldType);
      this.emit(type);
    } else if (value.fieldType.type === 'moduleModel') {
      let type = 'Models';
      const [moduleId, ...models] = value.fieldType.path;
      const moduleName = _name(moduleId);
      const modelName = _subModelName(models.map((item) => item.lexeme).join('.'));
      const externEx = this.usedExternException.get(moduleName);
      if (externEx && externEx.has(modelName)) {
        type = 'Exceptions';
      }
      const moduleInfo = this.imports[moduleName];
      const namespace = moduleInfo.namespace;
      this.headers.push(moduleInfo.header);
      this.emit(this.getRealModelName(`${namespace}::${type}::${modelName}`));
      
    } else if (value.fieldType.type === 'moduleTypedef') {
      const [moduleId, ...rest] = value.fieldType.path;
      const type = rest.map((item) => { return item.lexeme; }).join('.');
      this.emit(this.visitTypedef(type, moduleId));
    } else if (value.fieldType.type === 'typedef' || value.fieldType.idType === 'typedef') {
      this.emit(this.visitTypedef(value.fieldType));
    } else if (value.fieldType.type === 'subModel') {
      const [moduleId, ...rest] = value.fieldType.path;
      const modelName = _subModelName([moduleId.lexeme, ...rest.map((item) => {
        return item.lexeme;
      })].join('.'));
      this.headers.push(`${this.modelHeader}/${modelName}.hpp`);
      this.emit(this.getRealModelName(`${this.namespace}::Models::${modelName}`));
    } else if (value.fieldType.type) {
      const type = this.getType(value.fieldType.lexeme);
      this.emit(`${type}`);
    } else if (value.fieldType.idType === 'model') {
      let predefined = this.predefined;
      let moduleInfo = this;
      if(value.fieldType.moduleName) {
        predefined = this.usedExternException.get(value.fieldType.moduleName);
        moduleInfo = this.imports[value.fieldType.moduleName];
        this.headers.push(moduleInfo.header);
      }
      let type = 'Models';
      if (predefined[_name(value.fieldType)] && predefined[_name(value.fieldType)].isException) {
        type = 'Exceptions';
      }
      const modelName = _subModelName(_name(value.fieldType));
      if(!value.fieldType.moduleName) {
        this.headers.push(`${type === 'Models' ? this.modelHeader : this.exceptionHeader}/${modelName}.hpp`);
      }
      this.emit(this.getRealModelName(`${moduleInfo.namespace}::${type}::${modelName}`));
    } else if (value.fieldType.idType === 'module') {
      const moduleName = _name(value.fieldType);
      this.emit(this.getRealClientName(moduleName));
    } else if (value.fieldType.idType === 'builtin_model') {
      const type = this.getType(value.fieldType.lexeme);
      this.emit(`${this.getRealModelName(type)}`);
    } else {
      console.log(value);
      throw new Error('unknown type');
    }
  }

  visitExtendConstructor(extendOn, type = 'model') {
    if ((!extendOn && type === 'model') || (extendOn && _name(extendOn) === '$Model')) {
      return ;
    }
    this.emit(' : ');
    this.visitExtendOn(extendOn, type);
    if(!extendOn || _name(extendOn) === '$Error') {
      this.emit('(obj.value("msg", "").get<std::string>())');
      return;
    }

    this.emit('(obj)');
  }

  visitExtendOn(extendOn, type = 'model') {
    if (!extendOn) {
      type !== 'model' && this.headers.push('darabonba/Exception.hpp');
      type === 'model' ? this.emit(`${CORE}::Model`) : this.emit(`${CORE}::Exception`);
      return ;
    }

    switch(_name(extendOn)) {
    case '$Error': 
      this.headers.push('darabonba/Exception.hpp');
      this.emit(`${CORE}::Exception`);
      return;
    case '$ResponseError': 
      this.headers.push('darabonba/Exception.hpp');
      this.emit(`${CORE}::ResponseException`);
      return;
    case '$Model': 
      this.emit(`${CORE}::Model`);
      return;
    }

    let namespace = this.namespace;
    let extendType = 'Models';
    let modelName = _name(extendOn);
    if(this.predefined[modelName] && this.predefined[modelName].isException) {
      extendType = 'Exceptions';
    }
    if (extendOn.type === 'moduleModel') {
      const [moduleId, ...rest] = extendOn.path;
      extendType = 'Models';
      const externEx = this.usedExternException.get(_name(moduleId));
      if (externEx && externEx.has(modelName)) {
        extendType = 'Exceptions';
      }
      const moduleInfo = this.imports[moduleId.lexeme];
      this.headers.push(moduleInfo.header);
      namespace = moduleInfo.namespace;
      modelName = rest.map((item) => {
        return item.lexeme;
      }).join('::');
      const usedEx = this.usedExternException.get(moduleId.lexeme);
      if(usedEx && usedEx.has(modelName)) {
        extendType = 'Exceptions';
      }
    } else if (extendOn.type === 'subModel') {
      const [moduleId, ...rest] = extendOn.path;
      modelName = [moduleId.lexeme, ...rest.map((item) => {
        return item.lexeme;
      })].join('::');
    }
    this.emit(this.getRealModelName(`${namespace}::${extendType}::${modelName}`));
  }

  /**
   * @brief 收集模型中的所有嵌套模型(modelBody类型字段) - 包括所有层级的嵌套
   */
  collectNestedModels(ast, parentModelName) {
    const nestedModels = [];
    const seen = new Set(); // 防止重复
    
    if (!ast.modelBody || !ast.modelBody.nodes) {
      return nestedModels;
    }
    
    for (let i = 0; i < ast.modelBody.nodes.length; i++) {
      const node = ast.modelBody.nodes[i];
      const value = node.fieldValue;
      
      if (value.type === 'modelBody') {
        const fieldName = _name(node.fieldName);
        const nestedModelName = parentModelName + '.' + fieldName;
        
        if (seen.has(nestedModelName)) {
          continue; // 跳过重复
        }
        seen.add(nestedModelName);
        
        const nestedModel = {
          type: 'model',
          modelName: { lexeme: nestedModelName },
          modelBody: value,
          extendOn: null,
          annotation: null,
          fieldName: fieldName
        };
        // 递归收集嵌套模型的嵌套模型
        const subNested = this.collectNestedModelsRecursive(nestedModel, nestedModelName, seen);
        nestedModels.push(...subNested);
        nestedModels.push(nestedModel);
      } else if (value.type === 'array' && value.subType && value.subType.type === 'modelBody') {
        // 处理数组元素是modelBody的情况 (value.type === 'array')
        const fieldName = _name(node.fieldName);
        const nestedModelName = parentModelName + '.' + fieldName;
        
        if (seen.has(nestedModelName)) {
          continue; // 跳过重复
        }
        seen.add(nestedModelName);
        
        const nestedModel = {
          type: 'model',
          modelName: { lexeme: nestedModelName },
          modelBody: value.subType,
          extendOn: null,
          annotation: null,
          fieldName: fieldName
        };
        // 递归收集嵌套模型的嵌套模型
        const subNested = this.collectNestedModelsRecursive(nestedModel, nestedModelName, seen);
        nestedModels.push(...subNested);
        nestedModels.push(nestedModel);
      } else if (value.fieldType === 'array' && value.fieldItemType && value.fieldItemType.type === 'modelBody') {
        // 处理数组元素是modelBody的情况 (value.fieldType === 'array')
        const fieldName = _name(node.fieldName);
        const nestedModelName = parentModelName + '.' + fieldName;
        
        if (seen.has(nestedModelName)) {
          continue; // 跳过重复
        }
        seen.add(nestedModelName);
        
        const nestedModel = {
          type: 'model',
          modelName: { lexeme: nestedModelName },
          modelBody: value.fieldItemType,
          extendOn: null,
          annotation: null,
          fieldName: fieldName
        };
        // 递归收集嵌套模型的嵌套模型
        const subNested = this.collectNestedModelsRecursive(nestedModel, nestedModelName, seen);
        nestedModels.push(...subNested);
        nestedModels.push(nestedModel);
      }
    }
    
    return nestedModels;
  }

  /**
   * @brief 只收集直接的嵌套模型(一层) - 不递归
   */
  collectDirectNestedModels(ast, parentModelName) {
    const nestedModels = [];
    
    if (!ast.modelBody || !ast.modelBody.nodes) {
      return nestedModels;
    }
    
    for (let i = 0; i < ast.modelBody.nodes.length; i++) {
      const node = ast.modelBody.nodes[i];
      const value = node.fieldValue;
      
      if (value.type === 'modelBody') {
        const fieldName = _name(node.fieldName);
        const nestedModelName = parentModelName + '.' + fieldName;
        
        const nestedModel = {
          type: 'model',
          modelName: { lexeme: nestedModelName },
          modelBody: value,
          extendOn: null,
          annotation: null,
          fieldName: fieldName
        };
        nestedModels.push(nestedModel);
      } else if (value.type === 'array' && value.subType && value.subType.type === 'modelBody') {
        // 处理数组元素是modelBody的情况 (value.type === 'array')
        const fieldName = _name(node.fieldName);
        const nestedModelName = parentModelName + '.' + fieldName;
        
        const nestedModel = {
          type: 'model',
          modelName: { lexeme: nestedModelName },
          modelBody: value.subType,
          extendOn: null,
          annotation: null,
          fieldName: fieldName
        };
        nestedModels.push(nestedModel);
      } else if (value.fieldType === 'array' && value.fieldItemType && value.fieldItemType.type === 'modelBody') {
        // 处理数组元素是modelBody的情况 (value.fieldType === 'array')
        const fieldName = _name(node.fieldName);
        const nestedModelName = parentModelName + '.' + fieldName;
        
        const nestedModel = {
          type: 'model',
          modelName: { lexeme: nestedModelName },
          modelBody: value.fieldItemType,
          extendOn: null,
          annotation: null,
          fieldName: fieldName
        };
        nestedModels.push(nestedModel);
      }
    }
    
    return nestedModels;
  }

  /**
   * @brief 递归收集嵌套模型,使用共享的seen Set防止重复
   */
  collectNestedModelsRecursive(ast, parentModelName, seen) {
    const nestedModels = [];
    
    if (!ast.modelBody || !ast.modelBody.nodes) {
      return nestedModels;
    }
    
    for (let i = 0; i < ast.modelBody.nodes.length; i++) {
      const node = ast.modelBody.nodes[i];
      const value = node.fieldValue;
      
      if (value.type === 'modelBody') {
        const fieldName = _name(node.fieldName);
        const nestedModelName = parentModelName + '.' + fieldName;
        
        if (seen.has(nestedModelName)) {
          continue; // 跳过重复
        }
        seen.add(nestedModelName);
        
        const nestedModel = {
          type: 'model',
          modelName: { lexeme: nestedModelName },
          modelBody: value,
          extendOn: null,
          annotation: null,
          fieldName: fieldName
        };
        // 递归收集嵌套模型的嵌套模型
        const subNested = this.collectNestedModelsRecursive(nestedModel, nestedModelName, seen);
        nestedModels.push(...subNested);
        nestedModels.push(nestedModel);
      } else if (value.type === 'array' && value.subType && value.subType.type === 'modelBody') {
        // 处理数组元素是modelBody的情况
        const fieldName = _name(node.fieldName);
        const nestedModelName = parentModelName + '.' + fieldName;
        
        if (seen.has(nestedModelName)) {
          continue; // 跳过重复
        }
        seen.add(nestedModelName);
        
        const nestedModel = {
          type: 'model',
          modelName: { lexeme: nestedModelName },
          modelBody: value.subType,
          extendOn: null,
          annotation: null,
          fieldName: fieldName
        };
        // 递归收集嵌套模型的嵌套模型
        const subNested = this.collectNestedModelsRecursive(nestedModel, nestedModelName, seen);
        nestedModels.push(...subNested);
        nestedModels.push(nestedModel);
      } else if (value.fieldType === 'array' && value.fieldItemType && value.fieldItemType.type === 'modelBody') {
        // 处理数组元素是modelBody的情况 (value.fieldType === 'array')
        const fieldName = _name(node.fieldName);
        const nestedModelName = parentModelName + '.' + fieldName;
        
        if (seen.has(nestedModelName)) {
          continue; // 跳过重复
        }
        seen.add(nestedModelName);
        
        const nestedModel = {
          type: 'model',
          modelName: { lexeme: nestedModelName },
          modelBody: value.fieldItemType,
          extendOn: null,
          annotation: null,
          fieldName: fieldName
        };
        // 递归收集嵌套模型的嵌套模型
        const subNested = this.collectNestedModelsRecursive(nestedModel, nestedModelName, seen);
        nestedModels.push(...subNested);
        nestedModels.push(nestedModel);
      }
    }
    
    return nestedModels;
  }

  /**
   * @brief 生成嵌套模型作为内部类
   */
  visitNestedModel(ast, level, parentClassName) {
    const modelName = _name(ast.modelName);
    const fieldName = ast.fieldName;
    let cppClassName = _upperFirst(fieldName);
    
    // 如果嵌套类名与父类名相同，添加 "Item" 后缀避免C++构造函数名冲突
    if (cppClassName === parentClassName) {
      cppClassName = cppClassName + 'Item';
    }
    
    // 保存原有的currentParentModel
    const savedParentModel = this.currentParentModel;
    const savedCppClassName = this.currentCppClassName;
    
    // 设置当前嵌套模型的上下文
    this.currentParentModel = modelName;
    this.currentCppClassName = cppClassName;
    
    // 只收集直接的嵌套模型(不递归)
    const nestedModels = this.collectDirectNestedModels(ast, modelName);
    
    this.visitAnnotation(ast.annotation, level);
    this.emit(`class ${cppClassName} : public `, level);
    this.visitExtendOn(ast.extendOn, 'model');
    this.emit(' {\n');
    this.emit('public:\n', level);
    
    // friend to_json
    this.emit(`friend void to_json(Darabonba::Json& j, const ${cppClassName}& obj) { \n`, level + 1);
    this.visitFieldsToJson(ast.modelBody, level + 1);
    this.emit('};\n', level + 1);
    
    // friend from_json
    this.emit(`friend void from_json(const Darabonba::Json& j, ${cppClassName}& obj) { \n`, level + 1);
    this.visitFieldsFromJson(ast.modelBody, modelName, level + 1);
    this.emit('};\n', level + 1);

    // constructor
    this.emit(`${cppClassName}() = default ;\n`, level + 1);
    this.emit(`${cppClassName}(const ${cppClassName} &) = default ;\n`, level + 1);
    this.emit(`${cppClassName}(${cppClassName} &&) = default ;\n`, level + 1);
    this.emit(`${cppClassName}(const Darabonba::Json & obj)`, level + 1);
    this.visitExtendConstructor(ast.extendOn, 'model');
    this.emit(' { from_json(obj, *this); };\n');
    
    // destructor
    this.emit(`virtual ~${cppClassName}() = default ;\n`, level + 1);
    
    // assign operator
    this.emit(`${cppClassName}& operator=(const ${cppClassName} &) = default ;\n`, level + 1);
    this.emit(`${cppClassName}& operator=(${cppClassName} &&) = default ;\n`, level + 1);

    // validate method
    this.emit('virtual void validate() const override {\n', level + 1);
    this.visitModelValidate(ast.modelBody, modelName, level + 2);
    this.emit('};\n', level + 1);

    // fromMap method
    this.emit('virtual void fromMap(const Darabonba::Json &obj) override { from_json(obj, *this); validate(); };\n', level + 1);
    
    // toMap method
    this.emit('virtual Darabonba::Json toMap() const override { Darabonba::Json obj; to_json(obj, *this); return obj; };\n', level + 1);
    
    // 生成当前嵌套类的嵌套类（必须在方法之前生成，这样方法中可以使用嵌套类）
    if (nestedModels.length > 0) {
      // 从最深层开始生成，这样深层嵌套类先定义
      for (let i = nestedModels.length - 1; i >= 0; i--) {
        this.visitNestedModel(nestedModels[i], level + 1, cppClassName);
      }
    }
    
    // 生成字段方法（在嵌套类之后生成）
    this.visitIncludeModelFunc(ast.modelBody, modelName, level + 1);
    
    if(ast.modelBody.nodes && ast.modelBody.nodes.length > 0) {
      this.emit('protected:\n', level);
      // 使用当前嵌套类的类名作为parentClassName
      this.visitIncludeFieldForNested(ast.modelBody, modelName, level + 1, cppClassName);
    }
    
    this.emit('};\n\n', level);
    
    // 恢复原有的上下文
    this.currentParentModel = savedParentModel;
    this.currentCppClassName = savedCppClassName;
  }

  /**
   * @brief 生成 Model hpp 文件
   */
  visitIncludeModel(ast, level) {
    assert.equal(ast.type, 'model');
    const modelName = _name(ast.modelName);
    this.visitAnnotation(ast.annotation, level);
    const cppClassName = _subModelName(modelName);
    
    // 记录当前父模型名称
    this.currentParentModel = modelName;
    
    // 只收集直接的嵌套模型(不递归)
    const nestedModels = this.collectDirectNestedModels(ast, modelName);
    
    this.emit(`class ${cppClassName} : public `, level);
    this.visitExtendOn(ast.extendOn, 'model');
    this.emit(' {\n');
    this.emit('public:\n', level);
    // friend to_json
    this.emit(`friend void to_json(Darabonba::Json& j, const ${cppClassName}& obj) { \n`, level + 1);
    this.visitFieldsToJson(ast.modelBody, level + 1);
    this.emit('};\n', level + 1);
    // friend from_json
    this.emit(`friend void from_json(const Darabonba::Json& j, ${cppClassName}& obj) { \n`, level + 1);
    this.visitFieldsFromJson(ast.modelBody, modelName, level + 1);
    this.emit('};\n', level + 1);

    // constructor
    this.emit(`${cppClassName}() = default ;\n`, level + 1);
    this.emit(`${cppClassName}(const ${cppClassName} &) = default ;\n`, level + 1);
    this.emit(`${cppClassName}(${cppClassName} &&) = default ;\n`, level + 1);
    this.emit(`${cppClassName}(const Darabonba::Json & obj)`, level + 1);
    this.visitExtendConstructor(ast.extendOn, 'model');
    this.emit(' { from_json(obj, *this); };\n');
    // destructor
    this.emit(`virtual ~${cppClassName}() = default ;\n`, level + 1);
    // assign opeartor
    this.emit(`${cppClassName}& operator=(const ${cppClassName} &) = default ;\n`, level + 1);
    this.emit(`${cppClassName}& operator=(${cppClassName} &&) = default ;\n`, level + 1);

    // validate method - validates field constraints like required, maxLength, pattern etc.
    this.emit('virtual void validate() const override {\n', level + 1);
    this.visitModelValidate(ast.modelBody, modelName, level + 2);
    this.emit('};\n', level + 1);

    // fromMap method
    this.emit('virtual void fromMap(const Darabonba::Json &obj) override { from_json(obj, *this); validate(); };\n', level + 1);
    // toMap method
    this.emit('virtual Darabonba::Json toMap() const override { Darabonba::Json obj; to_json(obj, *this); return obj; };\n', level + 1);

    // this.emit(`class ${_subModelName(modelName)} : public Darabonba::Model {\n`, level);
    // this.emit('public:\n', level);
    // this.emit(`${_subModelName(modelName)}() {}\n`, level + 1);
    // this.emit(`${_subModelName(modelName)}(const json &map);\n`, level + 1);
    // this.visitIncludeSubModel(modelName, level);
    // this.emit(`friend void to_json(json& j, const ${_subModelName(modelName)}& p){ \n`, level + 1);
    // this.visitFieldsToJson(ast.modelBody, level + 1);
    // this.emit('}\n', level + 1);
    // this.emit(`friend void from_json(const json& j, ${_subModelName(modelName)}& p){ \n`, level + 1);
    // this.visitModelFromJson(ast.modelBody, modelName, level + 1);
    // this.emit('}\n', level + 1);
    // this.emit('json toMap();\n', level + 1);
    // this.emit('void validate(const json &map);\n', level + 1);
    // 先生成嵌套模型作为内部类（必须在方法之前生成，这样方法中可以使用嵌套类）
    if (nestedModels.length > 0) {
      // 从最深层开始生成，这样深层嵌套类先定义
      for (let i = nestedModels.length - 1; i >= 0; i--) {
        this.visitNestedModel(nestedModels[i], level + 1, cppClassName);
      }
    }
    
    // 生成字段方法（在嵌套类之后生成）
    this.visitIncludeModelFunc(ast.modelBody, modelName, level + 1);
    // this.emit(`~${_subModelName(modelName)}() = default ;\n`, level + 1);
    if(ast.modelBody.nodes && ast.modelBody.nodes.length > 0) {
      this.emit('protected:\n', level);
      this.visitIncludeFieldForMain(ast.modelBody, modelName, level + 1, cppClassName);
    }
    this.emit('};\n', level);
    
    // 清除当前父模型名称
    this.currentParentModel = null;
    
    // this.visitBuildMethod(ast, level + 1);
    // this.createGetSetMethod(ast.modelBody, level + 1, modelName);
  }

  /**
   * @brief 生成 Model cpp 文件
   */
  visitModel(ast, level) {
    assert.equal(ast.type, 'model');
    // const modelName = _name(ast.modelName);
    // this.emit(`${this.getRealModelName(modelName)}::${this.getRealModelName(modelName)}() : Darabonba::Model() {\n`, level);
    // this.emit('validate(map);\n', level + 1);
    // this.emit('from_json(map, *this);\n', level + 1);
    // this.emit('}\n\n', level);
    // this.emit(`void ${this.getRealModelName(modelName)}::validate() {\n`, level);
    // this.visitModelValidate(ast.modelBody, modelName, level);
    // this.emit('}\n\n', level);
    // this.emit(`Json ${this.getRealModelName(modelName)}::toMap() {\n`, level);
    // this.emit('Json map;\n', level + 1);
    // this.emit('to_json(map, *this);\n', level + 1);
    // this.emit('return map;\n', level + 1);
    // this.emit('}\n\n', level);
    // this.visitModelFunc(ast.modelBody, modelName, level);
  }

  visitFieldsToJson(ast, level) {
    for (let i = 0; i < ast.nodes.length; i++) {
      const node = ast.nodes[i];
      const value = node.fieldValue;
      const realName = getAttr(node, 'name') || _name(node.fieldName);
      const attrName = _name(node.fieldName);
     
      
      if((value.fieldType && (value.fieldType.idType === 'module' || value.fieldType === 'bytes'))) {
        this.emit(`DARABONBA_TO_JSON(${realName}, ${attrName}_);\n`, level + 1);
      } else if((value.fieldType && (value.fieldType === 'any' || value.fieldType.type === 'any'))
       || ((value.type === 'map' || value.fieldType === 'map') && _name(value.valueType) === 'any')) {
        this.emit(`DARABONBA_ANY_TO_JSON(${realName}, ${attrName}_);\n`, level + 1);
      } else if(this.checkStream(value)) {
        // bytes 类型不是 shared_ptr，使用 DARABONBA_TO_JSON
        this.emit(`// ${attrName}_ is stream\n`, level + 1);
      } else {
        this.emit(`DARABONBA_PTR_TO_JSON(${realName}, ${attrName}_);\n`, level + 1);
      }
      // this.emit(`if(p._${_name(node.fieldName)}){\n`, level + 1);
      // this.emit(`j["${realName}"] = *(p._${_name(node.fieldName)});\n`, level + 2);
      // this.emit('}\n\n', level + 1);
    }
  }

  
  visitFieldsFromJson(ast, modelName, level) {
    for (let i = 0; i < ast.nodes.length; i++) {
      const node = ast.nodes[i];
      const value = node.fieldValue;
      const realName = getAttr(node, 'name') || _name(node.fieldName);
      const attrName = _name(node.fieldName);
      // bytes 等类型不是 shared_ptr，使用 DARABONBA_FROM_JSON
      if((value.fieldType && (value.fieldType.idType === 'module' || value.fieldType === 'bytes'))) {
        this.emit(`DARABONBA_FROM_JSON(${realName}, ${attrName}_);\n`, level + 1);
      } else if((value.fieldType && (value.fieldType === 'any' || value.fieldType.type === 'any'))
       || ((value.type === 'map' || value.fieldType === 'map') && _name(value.valueType) === 'any')) {
        this.emit(`DARABONBA_ANY_FROM_JSON(${realName}, ${attrName}_);\n`, level + 1);
      } else if(this.checkStream(value)) {
        
        this.emit(`// ${attrName}_ is stream\n`, level + 1);
      } 
      else {
        this.emit(`DARABONBA_PTR_FROM_JSON(${realName}, ${attrName}_);\n`, level + 1);
      }
      // this.emit(`DARABONBA_JSON_FROM(${realName}, ${_name(node.fieldName)}, `, level + 1);
      // // this type used in marco, so the ',' should be replace to marco DARABONBA_COMMA
      // const emitFunc = this.emit;
      // this.emit = function(str, level) {
      //   str = str && str.replace(/,/g, ' DARABONBA_COMMA ');
      //   this.emitter.emit(str, level);
      // };
      // this.visitFieldType(value, level, modelName);
      // this.emit = emitFunc;
      // this.emit(')\n');
    }
  }

  /**
   * @brief 
   */
  visitModelFunc(ast, modelName, level){ 
    for (let i = 0; i < ast.nodes.length; i++) {
      const node = ast.nodes[i];
      const value = node.fieldValue;
      // get方法
      this.emit('', level);
      this.visitFieldType(value, level, modelName, _name(node.fieldName));
      this.emit(` ${this.getRealModelName(modelName)}::${this.avoidReserveName(_name(node.fieldName))}() const {\n`);
      this.emit(`if(_${_name(node.fieldName)}) { \n`, level + 1);
      this.emit(`return *_${_name(node.fieldName)};\n`, level + 2);
      this.emit('}\n', level + 1);
      this.emit('return ', level + 1);
      this.visitFieldTypeDefault(value, node, modelName, _name(node.fieldName));
      this.emit(';\n');
      this.emit('}\n\n', level);

      // set方法
      this.emit('void ', level);
      this.emit(`${this.getRealModelName(modelName)}::set${_upperFirst(_name(node.fieldName))}(`);
      this.visitFieldType(value, level, modelName, _name(node.fieldName));
      this.emit(` ${_name(node.fieldName)}){\n`);
      this.emit(`_${_name(node.fieldName)} = make_shared<`, level + 1);
      this.visitFieldType(value, level, modelName, _name(node.fieldName));
      this.emit(`> (${_name(node.fieldName)});\n`);
      this.emit('}\n\n', level);
    }
  }

  visitModelValidate(ast, modelName, level) {
    for (let i = 0; i < ast.nodes.length; i++) {
      const node = ast.nodes[i];
      const attrName = _name(node.fieldName);
      const pattern = getAttr(node, 'pattern') || '';
      const maxLength = getAttr(node, 'maxLength') || 0;
      const minLength = getAttr(node, 'minLength') || 0;
      const maximum = getAttr(node, 'maximum') || 0;
      const minimum = getAttr(node, 'minimum') || 0;
      const required = node.required || false;
      if (required || maxLength > 0 || minLength > 0 || maximum > 0 || pattern !== '') {
        if (required) {
          this.emit(`DARABONBA_VALIDATE_REQUIRED(${attrName}_);\n`, level + 1);
        }
        if (pattern !== '') {
          this.emit(`DARABONBA_VALIDATE_PATTERN(${attrName}_, "${pattern}");\n`, level + 1);
        }
        if (maxLength > 0 && maxLength <= 2147483647) {
          this.emit(`DARABONBA_VALIDATE_MAX_LENGTH(${attrName}_, ${maxLength});\n`, level + 1);
        }
        if (minLength > 0 && minLength <= 2147483647) {
          this.emit(`DARABONBA_VALIDATE_MIN_LENGTH(${attrName}_, ${minLength});\n`, level + 1);
        }
        // 不能超过JS中最大安全整数
        if (maximum > 0 && maximum <= Number.MAX_SAFE_INTEGER) {
          this.emit(`DARABONBA_VALIDATE_MAXIMUM(${attrName}_, ${maximum});\n`, level + 1);
        }
        // 不能超过JS中最大安全整数
        if (minimum > 0 && minimum <= Number.MAX_SAFE_INTEGER) {
          this.emit(`DARABONBA_VALIDATE_MINIMUM(${attrName}_, ${minimum});\n`, level + 1);
        }
      }
    }
  }

  avoidReserveName(name) {
    const reserves = [
      'float', 'int', 'double', 'public', 'private', 'class',
    ];
  
    if (reserves.includes(name)) {
      return `${name}_`;
    }
  
    return name;
  }

  visitIncludeExceptionFunc(ast, exceptionName, level) {
    for (let i = 0; i < ast.nodes.length; i++) {
      const node = ast.nodes[i];
      const value = node.fieldValue;

      const attrName = _avoidKeywords(_name(node.fieldName));
      const attrGetName = _avoidKeywords(attrName);
      // get method
      this.emit('inline ', level);
      
      if(value.fieldType && _isBaseType(value.fieldType)) {
        this.visitFieldType(value, level, exceptionName, attrName);
        this.emit(` ${attrGetName}() const { DARABONBA_PTR_GET_DEFAULT(${attrName}_, ${_defaultValue(value.fieldType)}) };\n`);
      } else if(this.isModuleType(value)) {
        this.emit('shared_ptr<');
        this.visitFieldType(value, level, exceptionName, attrName);
        this.emit(`> ${attrGetName}() const { DARABONBA_GET(${attrName}_) };\n`);
      } else if(value.fieldType && _isSpecialBaseType(value.fieldType)) {
        this.emit('const ');
        this.visitFieldType(value, level, exceptionName, attrName);
        this.emit(` & ${attrGetName}() const { DARABONBA_PTR_GET_DEFAULT(${attrName}_, ${_defaultValue(value.fieldType)}) };\n`);
        this.emit('inline ', level);
        this.visitFieldType(value, level, exceptionName, attrName);
        this.emit(` & ${attrGetName}() { DARABONBA_PTR_GET_DEFAULT(${attrName}_, ${_defaultValue(value.fieldType)}) };\n`);
      } else if((value.fieldType && (value.fieldType === 'any' || value.fieldType.type === 'any'))
       || ((value.type === 'map' || value.fieldType === 'map') && _name(value.valueType) === 'any')) {
        this.emit(`const Darabonba::Json & ${attrGetName}() const { DARABONBA_GET(${attrName}_) };\n`, level);
        this.emit(`inline Darabonba::Json & ${attrGetName}() { DARABONBA_GET(${attrName}_) };\n`, level);
      } else {
        this.emit('const ');
        this.visitFieldType(value, level, exceptionName, attrName);
        this.emit(` & ${attrGetName}() const { DARABONBA_PTR_GET_CONST(${attrName}_, `);
        this.visitFieldType(value, level, exceptionName, attrName);
        this.emit(') };\n');
        this.emit('inline ', level);
        this.visitFieldType(value, level, exceptionName, attrName);
        this.emit(` ${attrGetName}() { DARABONBA_PTR_GET(${attrName}_, `);
        this.visitFieldType(value, level, exceptionName, attrName);
        this.emit(') };\n');
      }
    }
  }

  visitIncludeModelFunc(ast, modelName, level) {
    // empty method
    // 当模型为空时，返回true
    if (ast.nodes.length === 0) {
      this.emit('virtual bool empty() const override { return true; };\n', level);
      return;
    }
    const emptyChecks = ast.nodes.map((node, index) => {
      const fieldName = _name(node.fieldName);
      const value = node.fieldValue;
      let check;
      if (value.fieldType && value.fieldType === 'bytes') {
        // bytes 类型使用 .empty()
        check = `this->${fieldName}_.empty()`;
      } else {
        check = `this->${fieldName}_ == nullptr`;
      }
      return check + (index % 5 === 0 && index !== ast.nodes.length - 1 ? '\n       ' : '');
    });
    this.emit(`virtual bool empty() const override { return ${emptyChecks.join(' && ')}; };\n`, level);

    // 使用当前类名，如果是嵌套模型则使用currentCppClassName
    const cppClassName = this.currentCppClassName || _subModelName(modelName);
    
    for (let i = 0; i < ast.nodes.length; i++) {
      const node = ast.nodes[i];
      const value = node.fieldValue;

      const attrName = _name(node.fieldName);
      // Field helper methods for ${attrName}
      this.emit(`// ${attrName} Field Functions \n`, level);
      // has method
      this.emit('', level);
      if(value.fieldType && value.fieldType === 'bytes') {
        // bytes 类型使用 .empty() 判断
        this.emit(`bool has${_upperFirst(attrName)}() const { return !this->${attrName}_.empty();};\n`);
      } else {
        this.emit(`bool has${_upperFirst(attrName)}() const { return this->${attrName}_ != nullptr;};\n`);
      }

      // null method
      if(value.fieldType && value.fieldType === 'bytes') {
        // bytes 类型使用 .clear() 清空
        this.emit(`void delete${_upperFirst(attrName)}() { this->${attrName}_.clear();};
`, level);
      } else {
        this.emit(`void delete${_upperFirst(attrName)}() { this->${attrName}_ = nullptr;};
`, level);
      }

      // 如果字段名以 'has' 开头，getter方法名使用get前缀避免与has方法冲突
      // 所有字段都使用 get 前缀
      const getterName = _getGetterName(attrName);
      let setterParamName = attrName;
      
      // 对于嵌套模型类型的字段，setter 参数名首字母小写避免与类名冲突
      const isNestedModel = value.type === 'modelBody' || 
                           (value.type === 'array' && value.subType && value.subType.type === 'modelBody') ||
                           (value.fieldType === 'array' && value.fieldItemType && value.fieldItemType.type === 'modelBody');
      
      if (isNestedModel) {
        setterParamName = attrName.charAt(0).toLowerCase() + attrName.slice(1);
      }
      
      // 处理C++关键字转义
      setterParamName = _avoidKeywords(setterParamName);
      // get method
      this.emit('inline ', level);
      if(value.fieldType && _isBaseType(value.fieldType)) {
        this.visitFieldType(value, level, modelName, attrName);
        this.emit(` ${getterName}() const { DARABONBA_PTR_GET_DEFAULT(${attrName}_, ${_defaultValue(value.fieldType)}) };\n`);
      } else if(this.isModuleType(value)) {
        this.emit('shared_ptr<');
        this.visitFieldType(value, level, modelName, attrName);
        this.emit('>');
        this.emit(` ${getterName}() const { DARABONBA_GET(${attrName}_) };\n`);
      } else if(value.fieldType && _isPointerType(value.fieldType)) {
        this.visitFieldType(value, level, modelName, attrName);
        this.emit(` ${getterName}() const { DARABONBA_GET(${attrName}_) };\n`);
      } else if(value.fieldType && _isSpecialBaseType(value.fieldType)) {
        this.emit('const ');
        this.visitFieldType(value, level, modelName, attrName);
        this.emit(` & ${getterName}() const { DARABONBA_PTR_GET_DEFAULT(${attrName}_, ${_defaultValue(value.fieldType)}) };\n`);
        this.emit('inline ', level);
        this.visitFieldType(value, level, modelName, attrName);
        this.emit(` & ${getterName}() { DARABONBA_PTR_GET_DEFAULT(${attrName}_, ${_defaultValue(value.fieldType)}) };\n`);
      } else if((value.fieldType && (value.fieldType === 'any' || value.fieldType.type === 'any'))
       || ((value.type === 'map' || value.fieldType === 'map') && _name(value.valueType) === 'any')) {
        this.emit(`const Darabonba::Json & ${getterName}() const { DARABONBA_GET(${attrName}_) };\n`, level);
        this.emit(`Darabonba::Json & ${getterName}() { DARABONBA_GET(${attrName}_) };\n`, level);
      } else {
        this.emit('const ');
        this.visitFieldType(value, level, modelName, attrName);
        this.emit(` & ${getterName}() const { DARABONBA_PTR_GET_CONST(${attrName}_, `);
        this.visitFieldType(value, level, modelName, attrName);
        this.emit(') };\n');
        this.emit('inline ', level);
        this.visitFieldType(value, level, modelName, attrName);
        this.emit(` ${getterName}() { DARABONBA_PTR_GET(${attrName}_, `);
        this.visitFieldType(value, level, modelName, attrName);
        this.emit(') };\n');
      }

      // set method
      this.emit('inline ', level);
      if(value.fieldType && _isBaseType(value.fieldType)) {
        this.emit(`${cppClassName}& set${_upperFirst(attrName)}(`);
        this.visitFieldType(value, level, modelName, attrName);
        this.emit(` ${setterParamName}) { DARABONBA_PTR_SET_VALUE(${attrName}_, ${setterParamName}) };\n`);
      }  else if(this.isModuleType(value)) {
        this.emit(`${cppClassName}& set${_upperFirst(attrName)}(shared_ptr<`);
        this.visitFieldType(value, level, modelName, attrName);
        this.emit(`> ${setterParamName}) { DARABONBA_SET_RVALUE(${attrName}_, ${setterParamName}) };\n`);
      } else if(value.fieldType && _isPointerType(value.fieldType)) {
        this.emit(`${cppClassName}& set${_upperFirst(attrName)}(`);
        this.visitFieldType(value, level, modelName, attrName);
        this.emit(` ${setterParamName}) { DARABONBA_SET_VALUE(${attrName}_, ${setterParamName}) };\n`);
      } else if(value.fieldType && _isSpecialBaseType(value.fieldType)) {
        this.emit(`${cppClassName}& set${_upperFirst(attrName)}(const `);
        this.visitFieldType(value, level, modelName, attrName);
        this.emit(` & ${setterParamName}) { DARABONBA_PTR_SET_VALUE(${attrName}_, ${setterParamName}) };\n`);
        this.emit(`inline ${cppClassName}& set${_upperFirst(attrName)}(`, level);
        this.visitFieldType(value, level, modelName, attrName);
        this.emit(` && ${setterParamName}) { DARABONBA_PTR_SET_RVALUE(${attrName}_, ${setterParamName}) };\n`);
      } else if((value.fieldType && (value.fieldType === 'any' || value.fieldType.type === 'any'))
       || ((value.type === 'map' || value.fieldType === 'map') && _name(value.valueType) === 'any')) {
        this.emit(`${cppClassName}& set${_upperFirst(attrName)}(const `);
        this.visitFieldType(value, level, modelName, attrName);
        this.emit(` & ${setterParamName}) { DARABONBA_SET_VALUE(${attrName}_, ${setterParamName}) };\n`);
        this.emit(`inline ${cppClassName}& set${_upperFirst(attrName)}(`, level);
        this.visitFieldType(value, level, modelName, attrName);
        this.emit(` && ${setterParamName}) { DARABONBA_SET_RVALUE(${attrName}_, ${setterParamName}) };\n`);
      } else {
        this.emit(`${cppClassName}& set${_upperFirst(attrName)}(const `);
        this.visitFieldType(value, level, modelName, attrName);
        this.emit(` & ${setterParamName}) { DARABONBA_PTR_SET_VALUE(${attrName}_, ${setterParamName}) };\n`);
        this.emit(`inline ${cppClassName}& set${_upperFirst(attrName)}(`, level);
        this.visitFieldType(value, level, modelName, attrName);
        this.emit(` && ${setterParamName}) { DARABONBA_PTR_SET_RVALUE(${attrName}_, ${setterParamName}) };\n`);
      }

      this.emit('\n\n');
    }

    // for (let i = 0; i < ast.nodes.length; i++) {
    //   const node = ast.nodes[i];
    //   const value = node.fieldValue;
    //   // get方法
    //   this.emit('', level);
    //   this.visitFieldType(value, level, modelName);
    //   this.emit(` ${this.avoidReserveName(_name(node.fieldName))}() const;\n`);
    //   // set方法
    //   this.emit('void ', level);
    //   this.emit(`set${_upperFirst(_name(node.fieldName))}(`);
    //   this.visitFieldType(value, level, modelName);
    //   this.emit(` ${_name(node.fieldName)});\n`);
    // }
  }

  visitIncludeField(ast, modelName, level) {
    let node;
    for (let i = 0; i < ast.nodes.length; i++) {
      node = ast.nodes[i];
      let comments = DSL.comment.getFrontComments(this.comments, node.tokenRange[0]);
      this.visitComments(comments, level);
      const value = node.fieldValue;
      const description = getAttr(node, 'description');
      if (description) {
        let descriptions = description.split('\n');
        for (let j = 0; j < descriptions.length; j++) {
          this.emit(`// ${descriptions[j]}\n`, level);
        }
      }
      const attrName = _name(node.fieldName);
      // Note: Field default values are handled through shared_ptr initialization
      // All fields use {} for consistent modern C++ style
      if((value.fieldType && (value.fieldType === 'any' || value.fieldType.type === 'any'))
       || ((value.type === 'map' || value.fieldType === 'map') && _name(value.valueType) === 'any')) {
        this.emit(`Darabonba::Json ${attrName}_ {};\n`, level);
      } else if(value.fieldType && _isPointerType(value.fieldType)) {
        this.emit('', level);
        this.visitFieldType(value, level, modelName, attrName);
        this.emit(` ${attrName}_ {};\n`);
      } else {
        this.emit('shared_ptr<', level);
        this.visitFieldType(value, level, modelName, attrName);
        this.emit(`> ${attrName}_ {};\n`);
      }
    }
  }

  /**
   * @brief 为主模型生成字段定义，嵌套模型引用内部类
   */
  visitIncludeFieldForMain(ast, modelName, level, parentClassName) {
    let node;
    for (let i = 0; i < ast.nodes.length; i++) {
      node = ast.nodes[i];
      let comments = DSL.comment.getFrontComments(this.comments, node.tokenRange[0]);
      this.visitComments(comments, level);
      const value = node.fieldValue;
      const description = getAttr(node, 'description');
      if (description) {
        let descriptions = description.split('\n');
        for (let j = 0; j < descriptions.length; j++) {
          this.emit(`// ${descriptions[j]}\n`, level);
        }
      }
      const attrName = _name(node.fieldName);

      if((value.fieldType && (value.fieldType === 'any' || value.fieldType.type === 'any'))
       || ((value.type === 'map' || value.fieldType === 'map') && _name(value.valueType) === 'any')) {
        this.emit(`Darabonba::Json ${attrName}_ {};\n`, level);
      } else if(value.fieldType && _isPointerType(value.fieldType)) {
        this.emit('', level);
        this.visitFieldTypeForNested(value, level, modelName, attrName, parentClassName);
        this.emit(` ${attrName}_ {};\n`);
      } else {
        this.emit('shared_ptr<', level);
        this.visitFieldTypeForNested(value, level, modelName, attrName, parentClassName);
        this.emit(`> ${attrName}_ {};\n`);
      }
    }
  }

  /**
   * @brief 为嵌套模型生成字段定义，嵌套模型引用内部类
   */
  visitIncludeFieldForNested(ast, modelName, level, parentClassName) {
    let node;
    for (let i = 0; i < ast.nodes.length; i++) {
      node = ast.nodes[i];
      let comments = DSL.comment.getFrontComments(this.comments, node.tokenRange[0]);
      this.visitComments(comments, level);
      const value = node.fieldValue;
      const description = getAttr(node, 'description');
      if (description) {
        let descriptions = description.split('\n');
        for (let j = 0; j < descriptions.length; j++) {
          this.emit(`// ${descriptions[j]}\n`, level);
        }
      }
      const attrName = _name(node.fieldName);

      if((value.fieldType && (value.fieldType === 'any' || value.fieldType.type === 'any'))
       || ((value.type === 'map' || value.fieldType === 'map') && _name(value.valueType) === 'any')) {
        this.emit(`Darabonba::Json ${attrName}_ {};\n`, level);
      } else if(value.fieldType && _isPointerType(value.fieldType)) {
        this.emit('', level);
        this.visitFieldTypeForNested(value, level, modelName, attrName, parentClassName);
        this.emit(` ${attrName}_ {};\n`);
      } else {
        this.emit('shared_ptr<', level);
        this.visitFieldTypeForNested(value, level, modelName, attrName, parentClassName);
        this.emit(`> ${attrName}_ {};\n`);
      }
    }
  }

  /**
   * @brief 生成字段类型，嵌套模型使用内部类名
   */
  visitFieldTypeForNested(value, level, modelName, fieldName, parentClassName) {
    if (value.type === 'modelBody') {
      // 使用父类的内部类
      let nestedClassName = _upperFirst(fieldName);
      // 如果嵌套类名与父类名相同，添加 "Item" 后缀避免C++构造函数名冲突
      if (nestedClassName === parentClassName) {
        nestedClassName = nestedClassName + 'Item';
      }
      this.emit(`${parentClassName}::${nestedClassName}`);
    } else if (value.type === 'array') {
      this.headers.push('vector');
      this.emit('vector<');
      this.visitFieldTypeForNested(value.subType || value.itemType, level, modelName, fieldName, parentClassName);
      this.emit('>');
    } else if (value.fieldType === 'array') {
      this.headers.push('vector');
      this.emit('vector<');
      this.visitFieldTypeForNested(value.fieldItemType, level, modelName, fieldName, parentClassName);
      this.emit('>');
    } else if(((value.type === 'map' || value.fieldType === 'map') && 
      _name(value.valueType) === 'any')) {
      this.emit('Darabonba::Json');
    } else if (value.fieldType === 'map') {
      this.headers.push('map');
      this.emit('map<');
      this.emit(`${_type(_name(value.keyType))}, `);
      this.visitFieldTypeForNested(value.valueType, level, modelName, fieldName, parentClassName);
      this.emit('>');
    } else if (value.type === 'map') {
      this.headers.push('map');
      this.emit('map<');
      this.emit(`${_type(_name(value.keyType))}, `);
      this.visitFieldTypeForNested(value.valueType, level, modelName, fieldName, parentClassName);
      this.emit('>');
    } else {
      // 其他类型使用原有逻辑
      this.visitFieldType(value, level, modelName, fieldName);
    }
  }

  visitObjectFieldValue(ast, level) {
    this.visitExpr(ast, level);
  }

  visitObjectField(ast, level) {
    let comments = DSL.comment.getFrontComments(this.comments, ast.tokenRange[0]);
    this.visitComments(comments, level);
    if (ast.type === 'objectField') {
      var key = _name(ast.fieldName) || _string(ast.fieldName);
      this.emit(`{"${key}" , `, level);
      this.visitObjectFieldValue(ast.expr, level);
      this.emit('}');
    } else {
      throw new Error('unimplemented: unknown object field type in visitObjectField: ' + ast.type);
    }
  }

  visitObject(ast, level, getType=true) {
    assert.equal(ast.type, 'object');
    if (ast.fields.length === 0) {
      this.emit('{}');
      return;
    }
    var hasExpandField = false;
    var hasNotExpandField = false;
    for (let i = 0; i < ast.fields.length; i++) {
      const field = ast.fields[i];
      if (field.type === 'expandField') {
        hasExpandField = true;
        break;
      } else {
        hasNotExpandField = true;
      }
    }

    if (!hasExpandField) {
      this.emit('json({\n');
      for (let i = 0; i < ast.fields.length; i++) {
        this.visitObjectField(ast.fields[i], level + 1);
        if (i < ast.fields.length - 1) {
          this.emit(',');
        }
        this.emit('\n');
      }
      this.emit('})', level);
      if(ast.inferred && getType) {
        this.visitObjectType(ast.inferred);
      }
      return;
    }

    var all = [];
    // 分段
    var current = [];
    for (let i = 0; i < ast.fields.length; i++) {
      const field = ast.fields[i];
      if (field.type === 'objectField') {
        current.push(field);
      } else {
        if (current.length > 0) {
          all.push(current);
        }
        all.push(field);
        current = [];
      }
    }

    if (current.length > 0) {
      all.push(current);
    }

    this.emit('Darabonba::Core::merge(');
    var hasExpandFieldBuildMap = false;
    if (hasExpandField && hasNotExpandField) {
      hasExpandFieldBuildMap = true;
      this.emit('json({\n');
    }

    for (let i = 0; i < all.length; i++) {
      const item = all[i];
      if (Array.isArray(item)) {
        for (var j = 0; j < item.length; j++) {
          this.visitObjectField(item[j], level + 2);
          if (item[j + 1]) {
            this.emit(',\n');
          } else {
            this.emit('\n');
          }
        }
      } else {

        this.emit('', i === 0 ? 0 : level + 1);
        this.visitExpr(item.expr, level);
        if (all[i + 1]) {
          this.emit(',');
        }
        this.emit('\n');
      }
      if (hasExpandFieldBuildMap) {
        this.emit('})', level + 1);
        if (all[i + 1]) {
          this.emit(',\n');
        } else {
          this.emit('\n');
        }
        hasExpandFieldBuildMap = false;
      }
    }
    this.emit(')', level);
    if(ast.inferred && getType) {
      this.visitObjectType(ast.inferred);
    }
  }

  visitObjectType(ast) {
    if (ast.type === 'map') {
      if(ast.valueType.type === 'basic' && ast.valueType.name === 'any'){
        return;
      } 
    } else if(_type(ast.lexeme || ast.name) === 'any'){
      return;
    }
    this.emit('.get<');
    this.visitType(ast);
    this.emit('>()');
  }

  visitCall(ast, level) {
    assert.equal(ast.type, 'call');
    if (ast.left.type === 'method_call') {
      this.visitMethodCall(ast, level);
    } else if (ast.left.type === 'instance_call') {
      this.visitInstanceCall(ast, level);
    } else if (ast.left.type === 'static_call') {
      this.visitStaticCall(ast, level);
    } else {
      throw new Error('unimplemented: unknown call type in visitCall: ' + ast.left.type);
    }
  }

  visitArgs(args, level){
    this.emit('(');
    for (let i = 0; i < args.length; i++) {
      const expr = args[i];
      if (expr.needCast) {
        // this.emit('Darabonba::toMap(');
        this.visitExpr(expr, level);
        this.emit('.toMap()');
      } else {
        this.visitExpr(expr, level);
      }
      if (i !== args.length - 1) {
        this.emit(', ');
      }
    }
    this.emit(')');
  }

  visitBuiltinStaticCall(ast, level) {
    const moduleName = _name(ast.left.id);

    const builtiner = this.builtin[moduleName];
    if (!builtiner) {
      throw new Error('un-implemented');
    }
    const func = _name(ast.left.propertyPath[0]);
    builtiner[func](ast.args, level);
  }

  visitStaticCall(ast, level) {
    assert.equal(ast.left.type, 'static_call');
    if (ast.left.id.type === 'builtin_module') {
      this.visitBuiltinStaticCall(ast, level);
      return;
    }
  
    var className = this.getRealClientName(_name(ast.left.id));

    this.emit(`${className}::${_name(ast.left.propertyPath[0])}`);
    this.visitArgs(ast.args, level);
  }

  visitInstanceCall(ast, level) {
    assert.equal(ast.left.type, 'instance_call');
    const method = _name(ast.left.propertyPath[0]);
    if (ast.builtinModule && this.builtin[ast.builtinModule] && this.builtin[ast.builtinModule][method]) {
      this.builtin[ast.builtinModule][method](ast, level);
    } else if(ast.builtinModule === '$ModelInstance') {
      var id = _name(ast.left.id);
      this.emit(`${id}.${method}`);
      this.visitArgs(ast.args, level);
    } else {
      id = _name(ast.left.id);
      if (id.indexOf('@') > -1) {
        id = `_${_lowerFirst(id.substr(1))}`;
      }
      this.emit(`${id}->${method}`);
      this.visitArgs(ast.args, level);
    }
  }

  visitMethodCall(ast, level) {
    assert.equal(ast.left.type, 'method_call');
    const name = _name(ast.left.id);
    const functionName = _avoidKeywords(name);
    if (name.startsWith('$') && this.builtin[name]) {
      const method = name.replace('$', '');
      this.builtin[name][method](ast.args, level);
      return;
    } else if (ast.isStatic) {
      this.emit(`${this.className}::${functionName}`);
    } else {
      this.emit(`${functionName}`);
    }
    this.visitArgs(ast.args, level);
  }

  visitPropertyAssign(ast, level) {
    assert.ok(ast.left.type === 'property_access' || ast.left.type === 'property');
    var expr = _name(ast.left.id);
    var current = ast.left.id.inferred;
    let last = ast.left.propertyPath[ast.left.propertyPath.length - 1];
    for (let i = 0; i < ast.left.propertyPath.length - 1; i++) {
      let name = _name(ast.left.propertyPath[i]);
      if(expr === RESPONSE) {
        expr += `->${name}()`;
      }else if(current.type === 'model'){
        const getterName =  _getGetterName(name);
        expr += `.${getterName}()`;
      }else {
        expr += `.at("${name}")`;
      }
      current = ast.left.propertyPathTypes[i];
    }

    let name = _upperFirst(_name(last));
    let needClose = false;
    if(expr === RESPONSE) {
      needClose = true;
      expr += `->set${name}(`;
    }
    else if(current.type === 'model'){
      needClose = true;
      if(ast.expr.type === 'null') {
        expr += `.delete${name}()`;
        this.emit(expr);
        return;
      }
      expr += `.set${name}(`;
    } else {
      expr += `["${_name(last)}"] = `;
    }
    
    this.emit(expr);
    if (ast.expr.needToReadable) {
      this.headers.push('darabonba/Stream.hpp');
      this.emit('Darabonba::Stream::toReadable(');
    }
    this.visitExpr(ast.expr, level);
    if (ast.expr.needToReadable) {
      this.emit(')');
    }
    if(needClose) {
      this.emit(')');
    }
    this.emit(';\n');
    
  }

  visitPropertyIsNull(ast) {
    assert.ok(ast.type === 'property_access' || ast.type === 'property');
    var expr = _name(ast.id);
    var current = ast.id.inferred;
    if(expr === RESPONSE || expr === REQUEST) {
      this.emit(`${CORE}::isNull(`);
      this.visitExpr(ast);
      this.emit(')');
      return;
    }
    const lastIndex = ast.propertyPath.length - 1;
    for (var i = 0; i < lastIndex; i++) {
      let name = _name(ast.propertyPath[i]);
      if(current.type === 'model'){
        // 所有 getter 方法都使用 get 前缀
        const getterName = _getGetterName(name);
        expr += `.${_avoidKeywords(getterName)}()`;
      } else if(current.type === 'map' && current.valueType.name === 'any') {
        expr += `["${name}"]`;
      } else {
        expr += `.at("${name}")`;
      }
      current = ast.propertyPathTypes[i];
    }

    let lastName = _name(ast.propertyPath[lastIndex]);
    if(current.type === 'model'){
      this.emit(`!${expr}.has${_upperFirst(lastName)}()`);
    } else if(current.type === 'map' && current.valueType.name === 'any') {
      this.emit(`!${expr}.contains("${lastName}")`);
    } else {
      this.emit(`${CORE}::isNull(${expr}["${lastName}"])`);
    }

    
  }

  visitPropertyAccess(ast) {
    assert.ok(ast.type === 'property_access' || ast.type === 'property');
    var expr = _name(ast.id);
    var current = ast.id.inferred;
    // 检查是否是 response_ (shared_ptr 类型)
    const isResponsePtr = (expr === RESPONSE);
    for (var i = 0; i < ast.propertyPath.length; i++) {
      var name = _name(ast.propertyPath[i]);
      const hasSpecialChars = /[-.]/.test(name);
      // 只有在第一次循环时才检查初始类型，之后根据 current.type 决定
      if(current.type === 'model'){
        const getterName = _getGetterName(name);
        if (hasSpecialChars) {
          // response_ 是 shared_ptr，使用 ->
          const accessor = isResponsePtr && i === 0 ? '->' : '.';
          expr += `${accessor}()["${name}"]`;
        } else {
          // response_ 是 shared_ptr，使用 ->
          const accessor = isResponsePtr && i === 0 ? '->' : '.';
          expr += `${accessor}${_avoidKeywords(getterName)}()`;
        }
      } else if(current.type === 'map' && current.valueType.name === 'any') {
        expr += `["${name}"]`;
      } else {
        expr += `.at("${name}")`;
      }
      current = ast.propertyPathTypes[i];
    }

    this.emit(expr);
  }

  emitNumber(ast, level) {
    this.emit(ast.value.value, level);
    if (ast.value.type === 'long') {
      this.emit('L');
    }
    if (ast.value.type === 'float') {
      this.emit('f');
    }
  }

  checkEmpty(elements, index) {
    return elements[index + 1] 
    && elements[index + 1].type === 'element' 
    && elements[index + 1].value.string === '';
  }

  visitIsNull(ast, level) {
    if (ast.type === 'property_access') {
      this.visitPropertyIsNull(ast, level);
    } else if (ast.type === 'string') {
      this.emit(`"${ast.value.string.replace(new RegExp('"', 'g'), '\\"')}"`);
    } else if (ast.type === 'variable' && this.isModelType(ast.inferred)) {
      var id = _name(ast.id);
      this.emit(`${id}.empty()`);
    } else if (ast.type === 'construct_model') {
      this.visitConstructModel(ast, level);
      this.emit('.empty()');
    } else {
      this.emit(`${CORE}::isNull`);
      this.visitArgs([ast]);
    }
  }

  visitExpr(ast, level) {
    if (ast.type === 'boolean') {
      this.emit(`${ast.value}`);
    } else if (ast.type === 'property_access') {
      this.visitPropertyAccess(ast, level);
    } else if (ast.type === 'string') {
      this.emit(`"${ast.value.string.replace(new RegExp('"', 'g'), '\\"')}"`);
    } else if (ast.type === 'null') {
      this.emit('nullptr');
    } else if (ast.type === 'number') {
      this.emitNumber(ast);
    } else if (ast.type === 'object') {
      this.visitObject(ast, level);
    } else if (ast.type === 'variable') {
      var id = _name(ast.id);
      if (id === '__response') {
        this.emit(RESPONSE);
      } else if (id === '__request') {
        this.emit(REQUEST);
      } else if (ast.inferred && ast.inferred.name === 'class') {
        // class type in C++ need to be fixed by manual
        this.emit('nullptr');
      } else {
        this.emit(id);
      }
    } else if (ast.type === 'virtualVariable') {
      const vid = `_${_name(ast.vid).substr(1)}`;
      this.emit(`${vid}`);
    } else if (ast.type === 'template_string') {
      this.emit('DARA_STRING_TEMPLATE(');
      for (var i = 0; i < ast.elements.length; i++) {
        var item = ast.elements[i];
        if (item.type === 'element') {
          if(!_string(item.value) && i !== 0) {
            continue;
          }
          if(i !== 0) {
            this.emit(' , ');
          }
          this.emit(`"${_string(item.value)}"`);
        } else if (item.type === 'expr') {
          this.emit(' , ');
          if(_isBinaryOp(item.expr.type)) {
            this.emit('(');
          }
          this.visitExpr(item.expr, level);
          if(_isBinaryOp(item.expr.type)) {
            this.emit(')');
          }
        } else {
          throw new Error('unimplemented: unknown template element type in visitExpr');
        }
      }
      this.emit(')');
    } else if (ast.type === 'call') {
      this.visitCall(ast, level);
    } else if (ast.type === 'construct') {
      this.visitConstruct(ast, level);
    } else if (ast.type === 'array') {
      this.visitArray(ast, level);
    } else if (ast.type === 'and') {
      this.visitExpr(ast.left, level);
      this.emit(' && ');
      this.visitExpr(ast.right, level);
    } else if (ast.type === 'or') {
      this.visitExpr(ast.left, level);
      this.emit(' || ');
      this.visitExpr(ast.right, level);
    } else if (ast.type === 'null') {
      this.emit('null');
    } else if (ast.type === 'group') {
      this.emit('(');
      this.visitExpr(ast.expr, level);
      this.emit(')');
    } else if (_isBinaryOp(ast.type)) {
      this.visitExpr(ast.left, level);
      if (ast.type === 'or') {
        this.emit(' || ');
      } else if (ast.type === 'add') {
        this.emit(' + ');
      } else if (ast.type === 'subtract') {
        this.emit(' - ');
      } else if (ast.type === 'div') {
        this.emit(' / ');
      } else if (ast.type === 'multi') {
        this.emit(' * ');
      } else if (ast.type === 'and') {
        this.emit(' && ');
      } else if (ast.type === 'lte') {
        this.emit(' <= ');
      } else if (ast.type === 'lt') {
        this.emit(' < ');
      } else if (ast.type === 'gte') {
        this.emit(' >= ');
      } else if (ast.type === 'gt') {
        this.emit(' > ');
      } else if (ast.type === 'neq') {
        this.emit(' != ');
      } else if (ast.type === 'eq') {
        this.emit(' == ');
      }
      this.visitExpr(ast.right, level);
    } else if (ast.type === 'decrement') {
      if (ast.position === 'front') {
        this.emit('--');
      }
      this.visitExpr(ast.expr, level);
      if (ast.position === 'backend') {
        this.emit('--');
      }
    } else if (ast.type === 'increment') {
      if (ast.position === 'front') {
        this.emit('++');
      }
      this.visitExpr(ast.expr, level);
      if (ast.position === 'backend') {
        this.emit('++');
      }
    } else if (ast.type === 'not') {
      this.emit('!');
      this.visitExpr(ast.expr, level);
    } else if (ast.type === 'construct_model') {
      this.visitConstructModel(ast, level);
    } else if (ast.type === 'super') {
      //C++ 中需要特殊处理了，这里直接过滤
    } else if (ast.type === 'map_access') {
      this.visitMapAccess(ast);
    } else if (ast.type === 'array_access') {
      this.visitArrayAccess(ast);
    } else {
      throw new Error('unimplemented: unknown expression type in visitObjectFieldValue: ' + ast.type);
    }
  }

  visitMapAccess(ast, level, assign = false) {
    assert.equal(ast.type, 'map_access');
    let expr = _name(ast.id);
    if (ast.id.tag === DSL.Tag.Tag.VID) {
      expr = `_${expr.substr(1)}`;
    }
    if (ast.propertyPath && ast.propertyPath.length) {
      var current = ast.id.inferred;
      for (var i = 0; i < ast.propertyPath.length; i++) {
        var name = _name(ast.propertyPath[i]);
        if (current.type === 'model') {
          // 所有 getter 方法都使用 get 前缀
          const getterName = _getGetterName(name);
          expr += `.${getterName}()`;
        } else if(current.type === 'map' && current.valueType.name === 'any') {
          expr += `["${name}"]`;
        } else {
          expr += `.at("${name}")`;
        }
        current = ast.propertyPathTypes[i];
      }
    }

    if(assign) {
      this.emit(`${expr}[`, level);
      this.visitExpr(ast.accessKey, level);
      this.emit(']');
      return;
    }
    this.emit(`${expr}.at(`, level);
    this.visitExpr(ast.accessKey, level);
    this.emit(')');
  }


  visitArrayAccess(ast, level) {
    assert.equal(ast.type, 'array_access');
    let expr = _name(ast.id);
    if (ast.id.tag === DSL.Tag.Tag.VID) {
      expr = `_${expr.substr(1)}`;
    }
    if (ast.propertyPath && ast.propertyPath.length) {
      var current = ast.id.inferred;
      for (var i = 0; i < ast.propertyPath.length; i++) {
        var name = _name(ast.propertyPath[i]);
        if (current.type === 'model' || expr === REQUEST) {
          const getterName =  _getGetterName(name);
          expr += `.${getterName}()`;
        } else if(current.type === 'map' && current.valueType.name === 'any') {
          expr += `["${name}"]`;
        } else {
          expr += `.at("${name}")`;
        }
        current = ast.propertyPathTypes[i];
      }
    }
    this.emit(`${expr}.at(`, level);
    this.visitExpr(ast.accessKey, level);
    this.emit(')');
  }


  visitConstruct(ast, level) {
    assert.equal(ast.type, 'construct');
    const aliasId = _name(ast.aliasId);
    if(this.builtin[aliasId]) {
      const type = this.builtin[aliasId].getClassName();
      this.emit(`make_shared<${type}>`);
    } else {
      this.emit(`make_shared<${this.getRealClientName(aliasId)}>`);
    }

    this.visitArgs(ast.args, level);
  }

  visitArray(ast, level) {
    assert.equal(ast.type, 'array');
    this.emit('vector<');
    this.visitType(ast.inferred.itemType);
    this.emit('>()');
    
    if (ast.items.length === 0) {
      return;
    }
    this.emit('\n');
    for (let i = 0; i < ast.items.length; i++) {
      const item = ast.items[i];
      var comments = DSL.comment.getFrontComments(this.comments, item.tokenRange[0]);
      this.visitComments(comments, level + 1);
      this.emit('.push_back(', level + 1);
      this.visitExpr(item, level + 1);
      this.emit(')');
      if (i < ast.items.length - 1) {
        this.emit('\n');
      }
    }
  }

  visitConstructModel(ast, level) {
    assert.equal(ast.type, 'construct_model');

    if (ast.aliasId.isModule) {
      let type = 'Models';
      let moduleName = _name(ast.aliasId);
      const moduleInfo = this.imports[moduleName];
      let modelName = _subModelName(ast.propertyPath.map((item) => {
        return item.lexeme;
      }).join('.'));
      const externEx = this.usedExternException.get(moduleName);
      if (externEx && externEx.has(modelName)) {
        type = 'Exceptions';
      }
      this.headers.push(moduleInfo.header);
      this.emit(this.getRealModelName(`${moduleInfo.namespace}::${type}::${modelName}`));
    }

    if (ast.aliasId.isModel) {
      let mainModelName = _name(ast.aliasId);
      mainModelName = _subModelName([mainModelName, ...ast.propertyPath.map((item) => {
        return item.lexeme;
      })].join('.'));
      if(mainModelName === _type(mainModelName)) {
        let type = 'Models';
        if(this.predefined[mainModelName] && this.predefined[mainModelName].isException) {
          type = 'Exceptions';
        }
        this.emit(this.getRealModelName(`${this.namespace}::${type}::${mainModelName}`));
      } else {
        this.emit(this.getRealModelName(this.getType(mainModelName)));
      }
    }


    if (ast.object && ast.object.fields && ast.object.fields.length > 0) {
      this.emit('(');
      this.visitObject(ast.object, level);
      this.emit(')');
      return;
    }
    this.emit('()');

  }

  visitReturn(ast, level) {
    assert.equal(ast.type, 'return');
    this.emit('return ', level);
    if (!ast.expr) {
      this.emit(';\n');
      return;
    }
    if (ast.needCast) {
      this.emit('json(');
    }

    this.visitExpr(ast.expr, level);

    if (ast.needCast) {
      this.emit(').get<');
      this.visitType(ast.expectedType);
      this.emit('>()');
    }

    this.emit(';\n');
  }

  visitYield(ast, level) {
    assert.equal(ast.type, 'yield');
    if (!ast.expr) {
      this.emit('return;\n');
      return;
    }
    this.visitType(ast.expr.inferred);
    this.emit(' __retrun = ', level);
    if (ast.needCast) {
      this.emit('json(');
    }

    this.visitExpr(ast.expr, level);

    if (ast.needCast) {
      this.emit(').get<');
      this.visitType(ast.expectedType);
      this.emit('>()');
    }

    this.emit(';\n');
    const retType = this.isAsyncFunction ? 'Darabonba::FutureGenerator' : 'Darabonba::Generator';
    this.emit(`return ${retType}<`);
    this.visitType(ast.expr.inferred);
    this.emit('>(__retrun);\n');
  }

  visitRetry(ast, level) {
    assert.equal(ast.type, 'retry');
    this.emit('throw new Darabonba::UnretryableError();\n', level);
  }

  visitIf(ast, level) {
    assert.equal(ast.type, 'if');
    this.emit('if (', level);
    this.visitExpr(ast.condition, level + 1);
    this.emit(') {\n');
    this.visitStmts(ast.stmts, level + 1);
    this.emit('}', level);
    if (ast.elseIfs) {
      for (let i = 0; i < ast.elseIfs.length; i++) {
        const branch = ast.elseIfs[i];
        this.emit(' else if (');
        this.visitExpr(branch.condition, level + 1);
        this.emit(') {\n');
        this.visitStmts(branch.stmts, level + 1);
        this.emit('}', level);
      }
    }

    if (ast.elseStmts) {
      this.emit(' else {\n');
      for (let i = 0; i < ast.elseStmts.stmts.length; i++) {
        this.visitStmt(ast.elseStmts.stmts[i], level + 1);
      }
      this.emit('}', level);
    }

    this.emit('\n');
    this.emit('\n');
  }

  visitThrow(ast, level) {
    this.emit('throw ', level);
    if (ast.expr.type === 'construct_model') {
      this.visitConstructModel(ast.expr, level);
      this.emit(';\n');
    } else {
      this.emit('Darabonba::Exception(', level);
      this.visitObject(ast.expr, level, false);
      this.emit(');\n');
    }
  }

  visitAssign(ast, level) {
    if (ast.left.type === 'property_assign' || ast.left.type === 'property') {
      this.emit('', level);
      this.visitPropertyAssign(ast, level);
      return;
    } else if (ast.left.type === 'virtualVariable') { // vid
      this.emit(`this->_${_name(ast.left.vid).substr(1)}`, level);
    } else if (ast.left.type === 'variable') {
      this.emit(`${_name(ast.left.id)}`, level);
    } else if (ast.left.type === 'map_access') {
      this.visitMapAccess(ast.left, level, true);
    } else if (ast.left.type === 'array_access') {
      this.visitArrayAccess(ast.left, level);
    } else {
      throw new Error('unimplemented: unknown assignment left-hand side type in visitAssign: ' + ast.left.type);
    }

    this.emit(' = ');

    if(ast.expr.type === 'null') {
      // empty deal
      this.visitType(ast.left.inferred);
      this.emit('();\n');
      return;
    }
      
    if (ast.expr.needToReadable) {
      this.headers.push('darabonba/Stream.hpp');
      this.emit('Darabonba::Stream::toReadable(');
    }
    this.visitExpr(ast.expr, level);
    if (ast.expr.needToReadable) {
      this.emit(')');
    }
    this.emit(';\n');
  }

  visitDeclare(ast, level) {
    var id = _name(ast.id);
    this.emit('', level);
    
    // 检查是否是基础类型初始化为 null
    const inferredType = ast.expr.inferred;
    const isNullValue = ast.expr.type === 'null';
    
    // 判断是否为基础类型
    let isBaseType = false;
    let typeName = null;
    if (inferredType) {
      if (inferredType.type === 'basic') {
        typeName = inferredType.name;
        isBaseType = _isBaseType(typeName);
      } else if (typeof inferredType === 'string') {
        typeName = inferredType;
        isBaseType = _isBaseType(typeName);
      }
    }
    
    if (isBaseType && isNullValue) {
      // 基础类型不能赋值为 nullptr，使用默认值
      this.visitType(inferredType);
      this.emit(` ${id} = `);
      this.emit(_defaultValue(typeName));
    } else {
      this.visitType(ast.expr.inferred);
      this.emit(` ${id} = `);
      this.visitExpr(ast.expr, level);
    }
    this.emit(';\n');
  }

  visitComments(comments, level) {
    comments.forEach(comment => {
      this.emit(`${comment.value}`, level);
      this.emit('\n');
    });
  }

  visitStmts(ast, level) {
    assert.equal(ast.type, 'stmts');
    let node;
    for (var i = 0; i < ast.stmts.length; i++) {
      node = ast.stmts[i];
      this.visitStmt(node, level);
    }
    if (node) {
      //find the last node's back comment
      let comments = DSL.comment.getBackComments(this.comments, node.tokenRange[1]);
      this.visitComments(comments, level);
    }

    if (ast.stmts.length === 0) {
      //empty block's comment
      let comments = DSL.comment.getBetweenComments(this.comments, ast.tokenRange[0], ast.tokenRange[1]);
      this.visitComments(comments, level);
    }
  }

  visitReturnBody(ast, level) {
    assert.equal(ast.type, 'returnBody');
    this.emit('\n');
    this.visitStmts(ast.stmts, level);
  }

  visitFunctionBody(ast, level) {
    assert.equal(ast.type, 'functionBody');
    this.visitStmts(ast.stmts, level);
  }

  visitMainExec(){
    let level = 0;
    if(!this.exec) {
      return;
    }
    if(!this.mainExec) {
      throw new Error('exec function must have static main function');
    }

    this.emit('\nint main(int argc, char *argv[]){\n');
    this.emit('vector<string> params;\n', level + 1);
    this.emit('if(argc > 0) {\n', level + 1);
    this.emit('params.assign(argv + 1, argv + argc);\n', level + 2);
    this.emit('}\n', level + 1);
    this.emit(`${this.namespace}::main(params);\n`, level + 1);
    this.emit('return 0;\n', level + 1);
    this.emit('}\n', level);
  }

  visitFunction(ast, level) {
    if (_name(ast.functionName) === 'main' && this.exec) {
      this.mainExec = true;
    }
    this.isAsyncFunction = ast.isAsync;
    this.visitAnnotation(ast.annotation, level);
    this.emit('', level);
    this.visitType(ast.returnType);
    this.emit(` ${this.className}::${_name(ast.functionName)}`);
    this.visitParams(ast.params, ast.consts);
    this.emit(' {');
    if (ast.functionBody) {
      this.emit('\n');
      this.visitFunctionBody(ast.functionBody, level + 1);
    }
    this.emit('}\n', level);
    this.isAsyncFunction = false;
  }

  visitIncludeFunciton(ast, level) {
    if (_name(ast.functionName) === 'main' && this.exec) {
      if (!ast.params.params || ast.params.params.length === 0) {
        throw new Error('static function main must have a argument');
      }
      return;
    }
    this.visitAnnotation(ast.annotation, level);
    this.emit('', level);
    if (ast.isStatic) {
      this.emit('static ');
    }
    this.visitType(ast.returnType);
    this.emit(` ${_name(ast.functionName)}`);
    this.visitParams(ast.params, ast.consts);
    this.emit(';\n');
  }

  visitIncludeType(ast, level) {
    this.emit('', level);
    this.visitType(ast.value);
    this.emit(` _${_name(ast.vid).substr(1)};`);
  }

  defaultConstructor(ast, level) {
    var className = this.className;
    this.emit(`${className}()`, level + 1);
    if(ast.extends) {
      this.emit(`: ${this.getRealClientName(_name(ast.extends))} `);
    }
    this.emit(' {}\n');
  }

  includeConstructor(ast, level) {
    var className = this.className;
    this.visitAnnotation(ast.annotation, level);
    this.emit(`${className}`, level + 1);

    this.emit('(');
    for (var i = 0; i < ast.params.params.length; i++) {
      if (i !== 0) {
        this.emit(', ');
      }
      const node = ast.params.params[i];
      assert.equal(node.type, 'param');
      const paramName = _name(node.paramName);
      this.visitType(node.paramType);
      this.emit(` &${paramName}`);
    }
    this.emit(')');
    // this.visitParams(ast.params, ast.consts);
    this.emit(';\n');
    if(!ast.params.length) {
      this.needDefaultConstructor = false;
    }
  }

  visitConstructor(ast, extendsClass, level) {
    var className = this.className;
    this.visitAnnotation(ast.annotation, level);
    this.emit(`${this.namespace}::${className}::${className}`, level);
    this.emit('(');
    for (var i = 0; i < ast.params.params.length; i++) {
      if (i !== 0) {
        this.emit(', ');
      }
      const node = ast.params.params[i];
      assert.equal(node.type, 'param');
      const paramName = _name(node.paramName);
      this.visitType(node.paramType);
      this.emit(` &${paramName}`);
    }
    this.emit(')');
    if (ast.initBody) {
      this.visitSuper(ast.initBody.stmts, extendsClass);
      this.emit('{\n');
      this.visitStmts(ast.initBody, level + 1);
    } else {
      this.emit('{\n');
    }
    this.emit('}\n\n', level);
  }

  visitSuper(stmts, extendsClass) {
    const [ superStmt ] = stmts.filter(stmt => {
      if(stmt.type === 'super') {
        return true;
      }
      return false;
    });
    if(!superStmt) {
      return;
    }
    this.emit(`: ${this.getRealClientName(_name(extendsClass))}`);
    this.visitArgs(superStmt.args);
  }

  visitAPI(ast, level) {
    // if (ast.annotation) {
    //   this.emit(`${ _anno(ast.annotation.value) } \n`, level);
    // }
    var className = this.className;
    this.isAsyncFunction = true;
    this.emit('', level);
    this.visitType(ast.returnType, this.namespace);
    this.emit(` ${className}::${_name(ast.apiName)}`);
    this.visitParams(ast.params, ast.consts);
    this.emit(' {\n');
    // for (var i = 0; i < ast.params.params.length; i++) {
    //   const param = ast.params.params[i];
    //   if (_name(param.paramType) && !DSL.util.isBasicType(_name(param.paramType)) && param.paramName.lexeme !== 'client') {
    //     this.emit(`validate(${param.paramName.lexeme}, "${param.paramName.lexeme}");\n`, level + 1);
    //   }
    // }
    let baseLevel = ast.runtimeBody ? level + 2 : level;
    // api level
    if (ast.runtimeBody) {
      this.visitRuntimeBefore(ast.runtimeBody, level + 1);
    } else {
      this.emit(`Darabonba::RuntimeOptions ${RUNTIME}(json({}));\n\n`, level);
    }
    this.visitAPIBody(ast.apiBody, baseLevel + 1);
    if (ast.runtimeBody) {
      this.emit(`_lastRequest = make_shared<Darabonba::Http::Request>(${REQUEST});\n`, baseLevel + 1);
    }

    this.emit(`auto futureResp_ = Darabonba::Core::doAction(${REQUEST}, ${RUNTIME}`, baseLevel + 1);
    this.emit(');\n');

    this.emit(`shared_ptr<Darabonba::Http::MCurlResponse> ${RESPONSE} = futureResp_.get();\n`, baseLevel + 1);
    if (ast.runtimeBody) {
      this.emit(`_lastResponse  = ${RESPONSE};\n`, baseLevel + 1);
    }

    if (ast.returns) {
      this.visitReturnBody(ast.returns, baseLevel + 1);
    }

    if (ast.runtimeBody) {
      this.visitRuntimeAfter(ast.runtimeBody, level + 1);
    }

    this.emit('}\n', level);
    this.isAsyncFunction = false;
  }

  visitIncludeAPI(ast, level) {
    this.emit('', level);
    this.visitType(ast.returnType);
    this.emit(` ${_name(ast.apiName)}`);
    this.visitParams(ast.params, ast.consts);
    this.emit(';\n');
  }


  visitRuntimeBefore(ast, level) {
    assert.equal(ast.type, 'object');
    this.headers.push('darabonba/policy/Retry.hpp');
    this.headers.push('darabonba/Runtime.hpp');
    this.headers.push('darabonba/Exception.hpp');
    let comments = DSL.comment.getFrontComments(this.comments, ast.tokenRange[0]);
    this.visitComments(comments, level + 1);
    
    this.emit(`Darabonba::RuntimeOptions ${RUNTIME}(`, level);
    this.visitRuntimeOptions(ast, level + 1);
    this.emit(');\n');
    this.emit('\n');
    this.emit('shared_ptr<Darabonba::Http::Request> _lastRequest = nullptr;\n', level);
    this.emit('shared_ptr<Darabonba::Http::MCurlResponse> _lastResponse = nullptr;\n', level);
    this.emit('int _retriesAttempted = 0;\n', level);
    this.emit('Darabonba::Policy::RetryPolicyContext _context = json({\n', level);
    this.emit('{"retriesAttempted" , _retriesAttempted}\n', level + 1);
    this.emit('});\n', level);
    this.emit(`while (Darabonba::allowRetry(${RUNTIME}.getRetryOptions(), _context)) {\n`, level);
    this.emit('if (_retriesAttempted > 0) {\n', level + 1);
    this.emit(`int _backoffTime = Darabonba::getBackoffTime(${RUNTIME}.getRetryOptions(), _context);\n`, level + 2);
    this.emit('if (_backoffTime > 0) {\n', level + 2);
    this.emit('Darabonba::sleep(_backoffTime);\n', level + 3);
    this.emit('}\n', level + 2);
    this.emit('}\n', level + 1);
    this.emit('_retriesAttempted++;\n', level + 1);
    this.emit('try {\n', level + 1);
  }

  visitRuntimeAfter(ast, level) {
    this.emit('} catch (const Darabonba::DaraException& ex) {\n', level + 1);
    this.emit('_context = Darabonba::Policy::RetryPolicyContext(json({\n', level + 2);
    this.emit('{"retriesAttempted" , _retriesAttempted},\n', level + 3);
    this.emit('{"lastRequest" , _lastRequest},\n', level + 3);
    this.emit('{"lastResponse" , _lastResponse},\n', level + 3);
    this.emit('{"exception" , ex},\n', level + 3);
    this.emit('}));\n', level + 2);
    this.emit('continue;\n', level + 2);
    this.emit('}\n', level + 1);
    this.emit('}\n', level);
    this.emit('\n');
    this.emit('throw Darabonba::UnretryableException(_context);\n', level);
  }

  includeBefore() {
    remove(path.join(this.outputDir, 'include', this.modelHeader));
    remove(path.join(this.outputDir, 'include', this.exceptionHeader));
  }

  includeAfter() {
    // Note: Custom JSON serializers for shared_ptr types can be added here if needed
    // Example implementation commented out below for reference:
    // namespace nlohmann {
    //   template <>
    //   struct adl_serializer<std::shared_ptr<AlibabaCloud::Credential::Client>> {
    //     static void to_json(json &j, const std::shared_ptr<AlibabaCloud::Credential::Client> client) {
    //       j = reinterpret_cast<uintptr_t>(client.get());
    //     }

    //     static std::shared_ptr<AlibabaCloud::Credential::Client> from_json(const json &j) {
    //       if (!j.is_null()) {
    //         AlibabaCloud::Credential::Client *ptr = reinterpret_cast<AlibabaCloud::Credential::Client *>(j.get<uintptr_t>());
    //         return std::shared_ptr<AlibabaCloud::Credential::Client>(ptr);
    //       }
    //       return nullptr;
    //     }
    //   };
    // }
  }

  modelBefore() {
    this.emit(`// This file is auto-generated, don't edit it. Thanks.
#include <${this.header}>

using namespace std;
using json = nlohmann::json;
using namespace ${this.namespace};\n
`);
  }

  visitIncludeClient(ast, level) {

    const types = ast.moduleBody.nodes.filter((item) => {
      return item.type === 'type';
    });
    
    const init = ast.moduleBody.nodes.filter((item) => {
      return item.type === 'init';
    });

    const apis = ast.moduleBody.nodes.filter((item) => {
      return item.type === 'api';
    });

    this.emit(`class ${this.className}`, level);
    if (ast.extends) {
      this.emit(` : public ${this.getRealClientName(_name(ast.extends))}`);
    }
    this.emit(' {\n');
    this.emit('public:\n', level + 1);
    // creat contructor
    this.needDefaultConstructor = true;
    for (let i = 0; i < init.length; i++) {
      this.emit('\n');
      this.includeConstructor(init[i], level + 1);
    }
    if(this.needDefaultConstructor) {
      this.defaultConstructor(ast, level + 1);
    }

    let lastToken = 0;
    for (let i = 0; i < apis.length; i++) {
      this.emit('\n');
      const apiNotes = DSL.note.getNotes(this.notes, lastToken, apis[i].tokenRange[0]);
      const sse = apiNotes.find(note => note.note.lexeme === '@sse');
      const skip = apiNotes.find(note => note.note.lexeme === '@skip');
      lastToken = apis[i].tokenRange[1];
      if(sse && sse.arg.value) {
        continue;
      }
      if(skip && _string(skip.arg.value) === 'cpp') {
        continue;
      }
      this.visitIncludeAPI(apis[i], level + 2);
    
    }
    const functions = ast.moduleBody.nodes.filter((item) => {
      return item.type === 'function';
    });

    for (let i = 0; i < functions.length; i++) {
      if (i !== 0) {
        this.emit('\n');
      }
      this.visitIncludeFunciton(functions[i], level + 2);
    }
    if(types && types.length >0){
      this.emit('protected:', level + 1);
      // creat class field
      for (let i = 0; i < types.length; i++) {
        this.emit('\n');
        this.visitIncludeType(types[i], level + 2);
        this.emit('\n');
      }
    }

    this.emit('};\n', level);
  }

  getType(type) {
    const info = _getInclude(type);
    if(info) {
      this.headers.push(info.header);
    }
    return _type(type);
  }

  typeRelover(type, module) {
    // Reserved for future type resolution logic
    // Currently type resolution is handled inline in visitType methods
  }

}

module.exports = Visitor;
