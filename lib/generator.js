'use strict';

const assert = require('assert');
const fs = require('fs');
const path = require('path');
const DSL = require('@darabonba/parser');
const types = require('./types')

const REQUEST = 'request_';
const RESPONSE = 'response_';
const RUNTIME = 'runtime_';
const {
  _name,
  _type,
  _lowerFirst,
  _defaultValue,
  _subModelName,
  remove,
  _upperFirst
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
    this.namespace = option && option.namespace;
    if (!this.header || !this.namespace) {
      throw new Error('Darafile -> cpp -> header should not empty, please add cpp option into Darafile.example:\n' +
        '"cpp": {"header": "darabonba/core.hpp", "namespace": "DARABONBA"}');
    }

    this.pkgDir = option.pkgDir;
    this.libraries = option.libraries;
    this.outputDir = option.outputDir;
    if (option.cpp) {
      this.className = option.cpp.className || 'Client';
    }
    if(this.namespace === this.className) {
      throw new Error('Please change your namespace or className, the same name will be ambiguous');
    }
    this.exec = option.exec;
    this.typedef = option.cpp.typedef || {};
    
    if (!this.outputDir) {
      throw new Error('Darafile -> cpp -> javaPackage should not empty, please add cpp option into Darafile.example:\n' +
      '"cpp": {"header": "darabonba/core.hpp", "namespace": "DARABONBA}');
    }

    fs.mkdirSync(this.outputDir, {
      recursive: true
    });

    this.conflictModelNameMap = {};
    this.allModleNameMap = {};

    remove(path.join(this.outputDir, 'src/models/'));
  }

  emit(str, level){
    this.emitter.emit(str, level);
  }

  save(){
    this.emitter.save();
  }

  visit(ast, level = 0) {
    this.usedExternModel = ast.usedExternModel;
    this.conflictModels = ast.conflictModels;
    this.visitInclude(ast, level);
    this.srcFiles = [];
    this.visitModels(ast, level);
    this.visitSrc(ast, level);
    this.visitCMake();
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
    this.visitType(ast.list.inferred.itemType);
    this.emit(` ${_name(ast.id)} : `);
    this.visitExpr(ast.list, level + 1);
    this.emit(') {\n');
    this.visitStmts(ast.stmts, level + 1);
    this.emit('}\n', level);
  }

  async visitCMake() {
    this.visitDependencies();
    const CMakeTplName = this.exec ? 'CMakeLists.exec.txt' : 'CMakeLists.shared.txt';
    const name = this.option.cpp.name || `${this.option.scope}_${this.option.name}`;
    const version = this.version || '1.0.0';
    let dependencies = '';
    let libs = '';
    let win32Libs = '';
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
    this.dependencies.map(cppPkg => {
      const release = cppPkg.release;
      const [name, version] = release.split(':');
      mainSubMake += `add_subdirectory(${name})\n`;
      const subDir = path.join(this.outputDir, 'external', name);
      if(!fs.existsSync(subDir)) {
        fs.mkdirSync(subDir, {recursive: true});
      }
      let content = subCMakeContent.replace(/<% name %>/g, name).replace(/<% version %>/g, version).replace(/<% scope %>/g, cppPkg.scope);
      fs.writeFileSync(path.join(subDir, 'CMakeLists.txt'), content);
      // console.log(name);
      dependencies += `find_library(${name.toUpperCase().replace(/[-|.|/]/g, '-')}_LIB ${name} $\{CMAKE_CURRENT_SOURCE_DIR}/deps/lib)\n`;
      libs += `$\{${name.toUpperCase().replace(/[-|.|/]/g, '-')}_LIB}\n`;
      win32Libs += `${name} $\{CMAKE_CURRENT_SOURCE_DIR}/deps/lib/lib${name}.lib\n`;
    });
    // add core
    mainSubMake += 'add_subdirectory(darabonba_core)\n';
    const coreSubDir = path.join(this.outputDir, 'external', 'darabonba_core');
    if(!fs.existsSync(coreSubDir)) {
      fs.mkdirSync(coreSubDir);
    }
    fs.writeFileSync(path.join(this.outputDir, 'external', 'CMakeLists.txt'), mainSubMake);
    let coreSubCMake = subCMakeContent.replace(/<% name %>/g, 'darabonba_core').replace(/<% version %>/g, this.option.coreVersion || 'latest').replace(/<% scope %>/g, 'darabonba');
    fs.writeFileSync(path.join(coreSubDir, 'CMakeLists.txt'), coreSubCMake);
    // main file
    CMakeContent = CMakeContent
      .replace(/<% name %>/g, name)
      .replace(/<% version %>/g, version)
      .replace(/<% header %>/g, `include/${this.header}`)
      .replace(/<% headerDir %>/g, path.dirname(this.header))
      .replace(/<% source %>/g, this.srcFiles.join('\n        '))
      .replace(/<% dependencies %>/g, dependencies)
      .replace(/<% LIBS %>/g, libs)
      .replace(/<% WIN32_LIBS %>/g, win32Libs);
    fs.writeFileSync(path.join(this.outputDir,  'CMakeLists.txt'), CMakeContent);
  }

  visitInclude(ast, level) {
    assert.equal(ast.type, 'module');
    this.emitter = new Emitter(this.outputDir, `include/${this.header}`);

    const nonStaticWraps = ast.moduleBody.nodes.filter((item) => {
      return item.type === 'function' && !item.isStatic;
    });
    const apis = ast.moduleBody.nodes.filter((item) => {
      return item.type === 'api';
    });
    const models = ast.moduleBody.nodes.filter((item) => {
      return item.type === 'model';
    });
    const types = ast.moduleBody.nodes.filter((item) => {
      return item.type === 'type';
    });
    const init = ast.moduleBody.nodes.filter((item) => {
      return item.type === 'init';
    });
    this.comments = ast.comments;
    var extendParam = {};
    if (nonStaticWraps.length > 0 || apis.length > 0) {
      extendParam.writeConstruct = true;
    }
    if (models.length > 0) {
      extendParam.writeImport = true;
    }
    this.predefined = ast.models;
    this.visitImport(ast.imports, ast.usedExternModel, level);
    
    this.includeBefore();
    this.visitIncludeModels(models, level + 1);
    

    // models definition
    var extendsClass;
    if (ast.extends) {
      var extendsName = _name(ast.extends);
      extendsClass = {};
      extendsClass.className = this.imports[extendsName].className || 'Client';
      extendsClass.namespace = this.imports[extendsName].namespace;
    }
    this.includeApiBefore(extendsClass, level + 1);

    
    this.emit('public:\n', level + 1);
    // creat contructor
    this.needDefaultConstructor = true;
    for (let i = 0; i < init.length; i++) {
      this.emit('\n');
      this.includeConstructor(init[i], level + 1);
    }
    if(this.needDefaultConstructor) {
      this.defaultConstructor(extendsClass, level + 1);
    }

    for (let i = 0; i < apis.length; i++) {
      this.emit('\n');

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
      this.emit('private:', level + 1);
      // creat class field
      for (let i = 0; i < types.length; i++) {
        this.emit('\n');
        this.visitIncludeType(types[i], level + 2);
        this.emit('\n');
      }
    }

    this.emit('};\n', level + 1);
    this.includeAfter();
    this.save();
  }

  visitIncludeModels(models, level){
    for (let i = 0; i < models.length; i++) {
      // const modelName = models[i].modelName.lexeme;
      this.visitIncludeModel(models[i], 1);
      this.emit('\n\n', level);
    }
  }

  visitSrc(ast) {
    let level = 0;
    assert.equal(ast.type, 'module');
    const filePath = this.option.cpp.name ? `src/${this.option.cpp.name}.cpp` : 'src/Client.cpp';
    this.emitter = new Emitter(this.outputDir, filePath);
    this.srcFiles.push(filePath);

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
    
    this.srcBefore();
    this.noDefaultNamespace = true;
    var extendsClass;
    if (ast.extends) {
      var extendsName = _name(ast.extends);
      extendsClass = {};
      extendsClass.className = this.imports[extendsName].className || 'Client';
      extendsClass.namespace = this.imports[extendsName].namespace;
    }
    // creat contructor
    for (let i = 0; i < init.length; i++) {
      this.emit('\n');
      this.visitConstructor(init[i], extendsClass, level);
    }

    // this.apiBefore(extendsClass, level + 1);

    
    for (let i = 0; i < apis.length; i++) {
      this.emit('\n');
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
    this.visitMainExec();
    this.save();
  }

  visitModels(ast, level){
    const models = ast.moduleBody.nodes.filter((item) => {
      return item.type === 'model';
    });
    for (let i = 0; i < models.length; i++) {
      const modelName = models[i].modelName.lexeme;
      this.emitter = new Emitter(this.outputDir, `src/models/${_upperFirst(modelName)}.cpp`);
      this.srcFiles.push(`src/models/${_upperFirst(modelName)}.cpp`);
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
      this.save();
    }
  }

  visitImport(imports) {
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
      const moduleDir = this.libraries[aliasId];
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
      this.headers.push(cppPkg.header);
      this.imports[aliasId] = cppPkg;
    }
  }

  visitDependencies() {
    // get all dependencies
    this.dependencies = [];
    const lockPath = path.join(this.pkgDir, '.libraries.json');
    if(!fs.existsSync(lockPath)) {
      return;
    }
    const lock = JSON.parse(fs.readFileSync(lockPath, 'utf8'));
    Object.keys(lock).map(key => {
      const targetPath = path.join(this.pkgDir, lock[key]);
      const pkgPath = fs.existsSync(path.join(targetPath, 'Teafile')) ? path.join(targetPath, 'Teafile') : path.join(targetPath, 'Darafile');
      const pkg = JSON.parse(fs.readFileSync(pkgPath));
      const release = pkg.releases && pkg.releases.cpp;
      const cppPkg = pkg.cpp;
      if (!cppPkg || !cppPkg.header || !release) {
        console.warn(`The '${pkg.scope}:${pkg.name}'  has no C++ supported, if the subModule use this module cpp build will be failed.`);
      } else {
        cppPkg.release = release;
      }
      cppPkg.scope = pkg.scope;
      this.dependencies.push(cppPkg);
    });
  }

  visitParams(ast) {
    assert.equal(ast.type, 'params');
    this.emit('(');
    for (var i = 0; i < ast.params.length; i++) {
      if (i !== 0) {
        this.emit(', ');
      }
      const node = ast.params[i];
      assert.equal(node.type, 'param');
      this.visitType(node.paramType);
      this.emit(` &${_name(node.paramName)}`);
    }
    this.emit(')');
  }

  getSubFieldClassName(className, hasModel) {
    if (className.indexOf('.') > 0) {
      let names = className.split('.');
      let name = _subModelName(className);
      if (hasModel) {
        for(names.splice(names.length - 1, 1);names.length > 0;names.splice(names.length - 1, 1)) {
          let parentClassName = _subModelName(names.join('.'));
          name = parentClassName + '::' + name;
        }
      }
      return name;
    }
    return className;
  }

  getSubModelClassName(className) {
    let names = className.split('.');
    let name = _subModelName(className);
    if(names.length < 2) {
      return name;
    }
    for(names.splice(names.length - 1, 1);names.length > 0;names.splice(names.length - 1, 1)) {
      let parentClassName = _subModelName(names.join('.'));
      name = parentClassName + '::' + name;
    }
    return name;
  }

  visitType(ast) {
    if (ast.type === 'map') {
      if(ast.valueType.type === 'basic' && ast.valueType.name === 'any'){
        this.emit('json');
      } else {
        this.emit('map<');
        this.visitType(ast.keyType);
        this.emit(', ');
        this.visitType(ast.valueType);
        this.emit('>');
      }
    } else if (ast.type === 'array') {
      this.emit('vector<');
      this.visitType(ast.subType || ast.itemType);
      this.emit('>');
    } else if (ast.type === 'model') {
      if (ast.moduleName) {
        this.emit(`${this.imports[ast.moduleName].namespace}::`);
      }else if(this.noDefaultNamespace) {
        this.emit(`${this.namespace}::`);
      }
      this.emit(`${_type(this.getSubFieldClassName(ast.name))}`);
    } else if (ast.type === 'subModel') {
      let className = '';
      for (let i = 0; i < ast.path.length; i++) {
        const item = ast.path[i];
        if (i > 0) {
          className += '.';
        }
        className += item.lexeme;
      }
      let resultName = this.getSubModelClassName(className);
      this.emit(resultName);
    } else if (ast.type === 'moduleModel') {
      const [moduleId, ...rest] = ast.path;
      let pathName = rest.map((item) => {
        return item.lexeme;
      }).join('.');
      let subModelName = this.getSubModelClassName(pathName);
      var moduleName = moduleId.lexeme;
      let namespace = `${this.imports[moduleName].namespace}`;
      this.emit(`${namespace}::${subModelName}`);
    } else if (ast.idType === 'typedef') {
      this.emit(this.typeRelover(ast));
    } else if (ast.type === 'moduleTypedef') {
      for (let i = 1; i < ast.path.length; i++) {
        this.emit(this.typeRelover(ast.path[i], ast.path[0]));
      }
    } else if (ast.type === 'basic') {
      this.emit(_type(ast.name));
    } else if (this.predefined && this.predefined[`module:${_name(ast)}`]) {
      const importInfo = this.imports[_name(ast)];
      const className = importInfo.className || 'Client';
      this.emit(`${importInfo.namespace}::${className}`);
    } else if (ast.idType === 'module') {
      const importInfo = this.imports[_name(ast)];
      const className = this.imports[ast.lexeme].className || 'Client';

      this.emit(`${importInfo.namespace}::${className}`);
    } else if (ast.idType === 'model') {
      if(this.noDefaultNamespace) {
        this.emit(`${this.namespace}::`);
      }
      const modelMap = `${_name(ast)}`;
      this.emit(modelMap);
    } else if (ast.type === 'module_instance') {
      const importInfo = this.imports[_name(ast)];
      let className = importInfo.className || 'Client';
      this.emit(`${importInfo.namespace}::${className}`);
    } else {
      this.emit(_type(ast.lexeme || ast.name));
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
    this.emit(`Darabonba::Request ${REQUEST} = Darabonba::Request();\n`, level);
    if (ast.stmts.stmts) {
      for (var i = 0; i < ast.stmts.stmts.length; i++) {
        this.visitStmt(ast.stmts.stmts[i], level);
      }
    }
  }

  visitRuntimeOptions(ast, level){
    this.emit('R"({\n');
    for (let i = 0; i < ast.fields.length; i++) {
      const field = ast.fields[i];
      let comments = DSL.comment.getFrontComments(this.comments, field.tokenRange[0]);
      this.visitComments(comments, level);
      if (field.type === 'objectField') {
        var key = _name(field.fieldName);
        this.emit(`"${key}" : `, level);
        this.visitObjectFieldValue(field.expr, level);
        this.emit('}');
      } else {
        throw new Error('unimpelemented');
      }
      if (i < ast.fields.length - 1) {
        this.emit(',');
      }
      this.emit('\n');
    }
    this.emit('})"__json', level);
  }

  visitRuntimeBefore(ast, level) {
    assert.equal(ast.type, 'object');
    let comments = DSL.comment.getFrontComments(this.comments, ast.tokenRange[0]);
    this.visitComments(comments, level + 1);
    this.emit(`Darabonba::RuntimeOptions ${RUNTIME}(`, level);
    this.visitRuntimeOptions(ast, level);
    this.emit(');\n');
    this.emit('\n');
    this.emit('Darabonba::Request _lastRequest;\n', level);
    this.emit('Error _lastException;\n', level);
    this.emit('int _retryTimes = 0;\n', level);
    this.emit(`while (Darabonba::allowRetry(${RUNTIME}.autoretry(), _retryTimes)) {\n`, level);
    this.emit('if (_retryTimes > 0) {\n', level + 1);
    this.emit(`int backoffTime = Darabonba::getBackoffTime(${RUNTIME}.backoffPeriod(), _retryTimes);\n`, level + 2);
    this.emit('if (backoffTime > 0) {\n', level + 2);
    this.emit('Darabonba::Core::sleep(backoffTime);\n', level + 3);
    this.emit('}\n', level + 2);
    this.emit('}\n', level + 1);
    this.emit('_retryTimes = _retryTimes + 1;\n', level + 1);
    this.emit('try {\n', level + 1);
  }

  visitStmt(ast, level) {
    let comments = DSL.comment.getFrontComments(this.comments, ast.tokenRange[0]);
    this.visitComments(comments, level);
    if (ast.type === 'return') {
      this.visitReturn(ast, level);
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
    if (ast.catchBlock && ast.catchBlock.stmts.length > 0) {
      let errorName = _name(ast.catchId);
      this.emit(` catch (Darabonba::Error ${errorName}) {\n`);
      this.visitStmts(ast.catchBlock, level + 1);
      this.emit(`} catch (exception _${errorName}) {`, level);
      this.emit('\n');
      this.emit('json _errInfo;', level + 1);
      this.emit('_errInfo["code"] = "Exception";', level + 1);
      this.emit(`_errInfo["message"] = _${errorName}.what();`, level + 1);
      this.emit(`Darabonba::Error ${errorName} = Darabonba::Error(_errInfo);\n`, level + 1);
      this.visitStmts(ast.catchBlock, level + 1);
      this.emit('}', level);
    }

    if (ast.finallyBlock && ast.finallyBlock.stmts.length > 0) {
      this.emit(' finally {\n');
      this.visitStmts(ast.finallyBlock, level + 1);
      this.emit('}', level);
    }
    this.emit('\n', level);
  }

  visitFieldTypeDefault(value, node, modelName) {
    if (value.fieldType === 'array') {
      // basic type
      this.emit('vector<');
      if (value.fieldItemType.tag === 8) {
        this.emit(`${_type(value.fieldItemType.lexeme)}`);
      } else if (value.fieldItemType.type === 'map') {
        this.visitType(value.fieldItemType);
      } else if (value.fieldItemType.fieldType === 'array') {
        this.visitFieldType(value.fieldItemType, node, modelName);
      } else {
        if (node.fieldValue.itemType) {
          this.emit(_subModelName(node.fieldValue.itemType));
        } else if (value.fieldItemType) {
          this.emit(`${_name(value.fieldItemType)}`);
        } else {
          this.emit(`${_name(node.fieldValue.fieldItemType)}`);
        }
      }
      this.emit('>()');
    } else if (value.fieldType === 'map') {
      this.emit(`map<${_type(value.keyType.lexeme)}, `);
      if (value.valueType.type) {
        this.visitType(value.valueType);
      } else {
        this.emit(`${_type(value.valueType.lexeme)}`);
      }
      this.emit('>()');
    } else if (typeof value.fieldType === 'string') {
      this.emit(`${_defaultValue(value.fieldType)}`);
    } else if (value.fieldType) {
      if (value.fieldType.idType && value.fieldType.idType === 'module') {
        const namespace = this.imports[`${_type(value.fieldType.lexeme)}`].namespace;
        const className = this.imports[`${_type(value.fieldType.lexeme)}`].className || 'Client';
        this.emit(`${namespace}::${className}()`);
      } else if (value.fieldType.idType && value.fieldType.idType === 'typedef') {
        this.emit(this.typeRelover(value.fieldType));
      } else if (value.fieldType.type && value.fieldType.type === 'moduleModel') {
        const namespace = this.imports[_name(value.fieldType.path[0])].namespace;
        this.emit(`${namespace}::${_name(value.fieldType.path[1])}()`);
      } else if (value.fieldType.type && value.fieldType.type === 'moduleTypedef') {
        for (let i = 1; i < value.fieldType.path.length; i++) {
          this.emit(this.typeRelover(value.fieldType.path[i], value.fieldType.path[0]));
        }
      } else {
        this.emit(`${_type(value.fieldType.lexeme)}`);
      }
    } else {
      this.emit(`${_subModelName([modelName, _name(node.fieldName)].join('.'))}()`);
    }
  }

  checkStream(value) {
    if (value.fieldType === 'array') {
      // basic type
      if (value.fieldItemType.tag === 8 && (_type(value.fieldItemType.lexeme) || '').includes('stream')) {
        return true;
      } else if (value.fieldItemType.type === 'map') {
        return this.checkStreamType(value.fieldItemType);
      } else if (value.fieldItemType.fieldType === 'array') {
        return this.checkStream(value.fieldItemType);
      }
    } else if (value.fieldType === 'map') {
      return this.checkStreamType(value.valueType);
    } else if (typeof value.fieldType === 'string' && (_type(value.fieldType) || '').includes('stream')) {
      return true;
    } else if((_type(value.fieldType.lexeme) || '').includes('stream')){
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
    } else if ((_type(ast.lexeme || ast.name) || '').includes('stream')) {
      return true;
    }
    return false;
  }

  visitFieldType(value, node, modelName) {
    if (value.fieldType === 'array') {
      // basic type
      this.emit('vector<');
      if (value.fieldItemType.tag === 8) {
        this.emit(`${_type(value.fieldItemType.lexeme)}`);
      } else if (value.fieldItemType.type === 'map') {
        this.visitType(value.fieldItemType);
      } else if (value.fieldItemType.fieldType === 'array') {
        this.visitFieldType(value.fieldItemType, node, modelName);
      } else {
        if (node.fieldValue.itemType) {
          this.emit(this.getSubModelClassName(node.fieldValue.itemType));
        } else if (value.fieldItemType) {
          this.emit(`${_name(value.fieldItemType)}`);
        } else {
          this.emit(`${_name(node.fieldValue.fieldItemType)}`);
        }
      }
      this.emit('>');
    } else if (value.fieldType === 'map') {
      this.emit(`map<${_type(value.keyType.lexeme)}, `);
      this.visitType(value.valueType);
      this.emit('>');
    } else if (typeof value.fieldType === 'string') {
      this.emit(`${_type(value.fieldType)}`);
    } else if (value.fieldType) {
      if (value.fieldType.idType && value.fieldType.idType === 'module') {
        const namespace = this.imports[`${_type(value.fieldType.lexeme)}`].namespace;
        const className = this.imports[`${_type(value.fieldType.lexeme)}`].className || 'Client';
        this.emit(`${namespace}::${className}`);
      } else if (value.fieldType.idType && value.fieldType.idType === 'typedef') {
        this.emit(this.typeRelover(value.fieldType));
      } else if (value.fieldType.type && value.fieldType.type === 'moduleModel') {
        const namespace = this.imports[_name(value.fieldType.path[0])].namespace;
        this.emit(`${namespace}::${_name(value.fieldType.path[1])}`);
      } else if (value.fieldType.type && value.fieldType.type === 'moduleTypedef') {
        for (let i = 1; i < value.fieldType.path.length; i++) {
          this.emit(this.typeRelover(value.fieldType.path[i], value.fieldType.path[0]));
        }
      } else {
        this.emit(`${_type(value.fieldType.lexeme)}`);
      }
    } else {
      this.emit(this.getSubModelClassName([modelName, _name(node.fieldName)].join('.')));
    }
  }

  /**
   * @brief 生成 Model hpp 文件
   */
  visitIncludeModel(ast, level) {
    assert.equal(ast.type, 'model');
    const modelName = _name(ast.modelName);
    this.visitAnnotation(ast.annotation, level);
    const cppClassName = _subModelName(modelName);
    this.emit(`class ${cppClassName} : public Darabonba::Model {\n`, level);
    this.emit('public:\n', level);
    // friend to_json
    this.emit(`friend void to_json(Darabonba::Json& j, const ${cppClassName}& obj) { \n`, level + 1);
    this.visitModelToJson(ast.modelBody, level + 1);
    this.emit('}\n', level + 1);
    // friend from_json
    this.emit(`friend void from_json(const Darabonba::Json& j, ${cppClassName}& obj) { \n`, level + 1);
    this.visitModelFromJson(ast.modelBody, modelName, level + 1);
    this.emit('}\n', level + 1);

    // constructor
    this.emit(`${cppClassName}() = default\n`, level + 1);
    this.emit(`${cppClassName}(const ${cppClassName} &) = default\n`, level + 1);
    this.emit(`${cppClassName}(${cppClassName} &&) = default\n`, level + 1);
    this.emit(`${cppClassName}(const Darabonba::Json & obj) { from_json(obj, *this); }\n`, level + 1);
    // destructor
    this.emit(`virtual ~${cppClassName}() = default\n`, level + 1);
    // assign opeartor
    this.emit(`${cppClassName}& operator=(const ${cppClassName} &) = default\n`, level + 1);
    this.emit(`${cppClassName}& operator=(${cppClassName} &&) = default\n`, level + 1);

    // validate method
    this.emit('virtual void validate() overriede {\n', level + 1);
    this.visitModelValidate(ast.modelBody, modelName, level + 2);
    // TODO something with validate
    this.emit('}\n', level + 1);

    // fromMap method
    this.emit(`virtual void fromMap(const Darabonba::Json &obj) override { from_json(obj, *this); validate(); }\n`, level + 1)
    // toMap method
    this.emit(`virtual Darabonba::Json toMap(const Darabonba::Json &obj) override { Darabonba::Json obj; to_json(obj, *this); return obj; }\n`, level + 1);

    // this.emit(`class ${_subModelName(modelName)} : public Darabonba::Model {\n`, level);
    // this.emit('public:\n', level);
    // this.emit(`${_subModelName(modelName)}() {}\n`, level + 1);
    // this.emit(`${_subModelName(modelName)}(const json &map);\n`, level + 1);
    // this.visitIncludeSubModel(modelName, level);
    // this.emit(`friend void to_json(json& j, const ${_subModelName(modelName)}& p){ \n`, level + 1);
    // this.visitModelToJson(ast.modelBody, level + 1);
    // this.emit('}\n', level + 1);
    // this.emit(`friend void from_json(const json& j, ${_subModelName(modelName)}& p){ \n`, level + 1);
    // this.visitModelFromJson(ast.modelBody, modelName, level + 1);
    // this.emit('}\n', level + 1);
    // this.emit('json toMap();\n', level + 1);
    // this.emit('void validate(const json &map);\n', level + 1);
    this.visitIncludeModelFunc(ast.modelBody, modelName, level + 1);
    // this.emit(`~${_subModelName(modelName)}() = default;\n`, level + 1);
    if(ast.modelBody.nodes && ast.modelBody.nodes.length > 0) {
      this.emit('protected:\n', level);
      this.visitIncludeModelField(ast.modelBody, modelName, level + 1);
    }
    this.emit('};\n', level);
    
    // this.visitBuildMethod(ast, level + 1);
    // this.createGetSetMethod(ast.modelBody, level + 1, modelName);
  }

  visitIncludeSubModel(modelName, level) {
    if (this.predefined) {
      let relatedSubModels = Object.keys(this.predefined).filter((key) => {
        return key.startsWith(modelName + '.');
      }).map((key) => {
        return this.predefined[key];
      });
      for (let i = 0; i < relatedSubModels.length; i++) {
        this.emit('\n\n');
        this.visitIncludeModel(relatedSubModels[i], level + 1);
      }
    }
  }

  /**
   * @brief 生成 Model cpp 文件
   */
  visitModel(ast, level) {
    assert.equal(ast.type, 'model');
    // const modelName = _name(ast.modelName);
    // this.emit(`${this.getSubModelClassName(modelName)}::${this.getSubModelClassName(modelName)}() : Darabonba::Model() {\n`, level);
    // this.emit('validate(map);\n', level + 1);
    // this.emit('from_json(map, *this);\n', level + 1);
    // this.emit('}\n\n', level);
    // this.emit(`void ${this.getSubModelClassName(modelName)}::validate() {\n`, level);
    // this.visitModelValidate(ast.modelBody, modelName, level);
    // this.emit('}\n\n', level);
    // this.emit(`Json ${this.getSubModelClassName(modelName)}::toMap() {\n`, level);
    // this.emit('Json map;\n', level + 1);
    // this.emit('to_json(map, *this);\n', level + 1);
    // this.emit('return map;\n', level + 1);
    // this.emit('}\n\n', level);
    // this.visitModelFunc(ast.modelBody, modelName, level);
  }

  visitModelToJson(ast, level) {
    for (let i = 0; i < ast.nodes.length; i++) {
      const node = ast.nodes[i];
      const value = node.fieldValue;
      const realName = getAttr(node, 'name') || _name(node.fieldName);
      if(this.checkStream(value)) {
        this.emit(`if(p._${_name(node.fieldName)}){\n`, level + 1);
        this.emit(`j["${realName}"] = (int64_t)p._${_name(node.fieldName)}.get();\n`, level + 2);
        this.emit('}\n\n', level + 1);
        continue;
      }
      const attrName = _name(node.fieldName);
    
      if(types.isAny(value.fieldType)) {
        this.emit(`DARABONBA_ANY_TO_JSON(${realName}, ${attrName}_);\n`, level + 1);
      } else {
        this.emit(`DARABONBA_PTR_TO_JSON(${realName}, ${attrName}_);\n`, level + 1);
      }
      // this.emit(`if(p._${_name(node.fieldName)}){\n`, level + 1);
      // this.emit(`j["${realName}"] = *(p._${_name(node.fieldName)});\n`, level + 2);
      // this.emit('}\n\n', level + 1);
    }
  }

  
  visitModelFromJson(ast, modelName, level) {
    for (let i = 0; i < ast.nodes.length; i++) {
      const node = ast.nodes[i];
      const value = node.fieldValue;
      const realName = getAttr(node, 'name') || _name(node.fieldName);
      if(this.checkStream(value)) {
        this.emit(`if(j.find("${realName}") != j.end()){\n`, level + 1);
        this.emit(`if(j["${realName}"].is_null()) {\n`, level + 2);
        this.emit(`p._${_name(node.fieldName)} = nullptr;\n`, level + 3);
        this.emit('} else {\n', level + 2);
        this.emit(`p._${_name(node.fieldName)} = shared_ptr<`, level + 3);
        this.visitFieldType(value, node, modelName);
        this.emit('>((');
        this.visitFieldType(value, node, modelName);
        this.emit(`*)j["${realName}"].get<int64_t>());\n`);
        this.emit('}\n', level + 2);
        this.emit('}\n', level + 1);
        continue;
      }
      const attrName = _name(node.fieldName);
    
      if(types.isAny(value.fieldType)) {
        this.emit(`DARABONBA_ANY_FROM_JSON(${realName}, ${attrName}_);\n`, level + 1);
      } else {
        this.emit(`DARABONBA_PTR_FOMR_JSON(${realName}, ${attrName}_);\n`, level + 1);
      }
      // this.emit(`DARABONBA_JSON_FROM(${realName}, ${_name(node.fieldName)}, `, level + 1);
      // // this type used in marco, so the ',' should be replace to marco DARABONBA_COMMA
      // const emitFunc = this.emit;
      // this.emit = function(str, level) {
      //   str = str && str.replace(/,/g, ' DARABONBA_COMMA ');
      //   this.emitter.emit(str, level);
      // };
      // this.visitFieldType(value, node, modelName);
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
      this.visitFieldType(value, node, modelName);
      this.emit(` ${this.getSubModelClassName(modelName)}::${this.avoidReserveName(_name(node.fieldName))}() const {\n`);
      this.emit(`if(_${_name(node.fieldName)}) { \n`, level + 1);
      this.emit(`return *_${_name(node.fieldName)};\n`, level + 2);
      this.emit('}\n', level + 1);
      this.emit('return ', level + 1);
      this.visitFieldTypeDefault(value, node, modelName);
      this.emit(';\n');
      this.emit('}\n\n', level);

      // set方法
      this.emit('void ', level);
      this.emit(`${this.getSubModelClassName(modelName)}::set${_upperFirst(_name(node.fieldName))}(`);
      this.visitFieldType(value, node, modelName);
      this.emit(` ${_name(node.fieldName)}){\n`);
      this.emit(`_${_name(node.fieldName)} = make_shared<`, level + 1);
      this.visitFieldType(value, node, modelName);
      this.emit(`> (${_name(node.fieldName)});\n`);
      this.emit('}\n\n', level);
    }
  }

  visitModelValidate(ast, modelName, level) {
    for (let i = 0; i < ast.nodes.length; i++) {
      const node = ast.nodes[i];
      const value = node.fieldValue;
      const attrName = _name(node.fieldName);
      const realName = getAttr(node, 'name') || _name(node.fieldName);
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

  visitIncludeModelFunc(ast, modelName, level) {
    // empty method
    this.emit(`virtual bool empty() const override { ${ast.nodes.map(node => "this->" + _name(node.fieldName) + "_ != nullptr").join(" && ")}; }\n`, level);

    for (let i = 0; i < ast.nodes.length; i++) {
      const node = ast.nodes[i];
      const value = node.fieldValue;

      const cppClassName = _subModelName(modelName);
      const attrName = _name(node.fieldName);
      // TODO 应该使用 this.visitFieldType
      const cppType = types.cppType(value.fieldType);

      // has method
      this.emit('', level);
      this.emit(`bool has${_upperFirst(attrName)}() { return this->${attrName}_ != nullptr;}\n`, level);

      // get method
      this.emit('', level);
      if(types.isCppBasicType(value.fieldType)) {
        this.emit(`${cppType} ${attrName}() const { DARABONBA_PTR_GET_DEFAULT(${attrName}_, ${types.defaultValue(value.fieldType)}); }\n`, level);
      } else if(types.isPointer(value.fieldType)) {
        this.emit(`${cppType} ${attrName}() const { DARABONBA_GET(${attrName}_); }\n`, level);
      } else if(types.isJsUnmodifiableType(value.fieldType)) {
        this.emit(`const ${cppType} & ${attrName}() const { DARABONBA_PTR_GET_DEFAULT(${attrName}_, ${types.defaultValue(value.fieldType)}); }\n`, level);
        this.emit(`${cppType} & ${attrName}() { DARABONBA_PTR_GET_DEFAULT(${attrName}_, ${types.defaultValue(value.fieldType)}); }\n`, level);
      } else if(types.isAny(value.fieldType)) {
        this.emit(`const Darabonaba::Json & ${attrName}() const { DARABONBA_GET(${attrName}_); }\n`, level);
        this.emit(`Darabonba::Json & ${attrName}() { DARABONBA_GET(${attrName}_); }\n`, level);
      } else {
        this.emit(`const ${cppType} & ${attrName}() const { DARABONBA_PTR_GET(${attrName}_); }\n`, level);
        this.emit(`${cppType} & ${attrName}() { DARABONBA_PTR_GET(${attrName}_); }\n`, level);
      }

      // set method
      this.emit('', level);
      if(types.isCppBasicType(value.fieldType)) {
        this.emit(`${cppClassName}& set${_upperFirst(attrName)}(${cppType} ${attrName}) { DARABONBA_PTR_SET_VALUE(${attrName}_, ${attrName}); }\n`, level);
      } else if(types.isPointer(value.fieldType)) {
        this.emit(`${cppClassName}& set${_upperFirst(attrName)}(${cppType} ${attrName}) { DARABONBA_SET_VALUE(${attrName}_, ${attrName}); }\n`, level);
      } else if(types.isJsUnmodifiableType(value.fieldType)) {
        this.emit(`${cppClassName}& set${_upperFirst(attrName)}(const ${cppType}) & ${attrName}) { DARABONBA_PTR_SET_VALUE(${attrName}_, ${attrName}); }\n`, level);
        this.emit(`${cppClassName}$ set${_upperFirst(attrName)}(${cppType} && ${attrName}) { DARABONBA_PTR_SET_RVALUE(${attrName}_, ${attrName}); }\n`, level);
      } else if(types.isAny(value.fieldType)) {
        this.emit(`${cppClassName}& set${_upperFirst(attrName)}(const ${cppType} & ${attrName}) { DARABONBA_SET_VALUE(${attrName}_, ${attrName}); }\n`, level);
        this.emit(`${cppClassName}& set${_upperFirst(attrName)}(${cppType} & ${attrName}) { DARABONBA_SET_RVALUE(${attrName}_, ${attrName}); }\n`, level);
      } else {
        this.emit(`${cppClassName}& set${_upperFirst(attrName)}(const ${cppType} & ${attrName}) { DARABONBA_PTR_SET_VALUE(${attrName}_, ${attrName}); }\n`, level);
        this.emit(`${cppClassName}& set${_upperFirst(attrName)}(${cppType} && ${attrName}) { DARABONBA_PTR_SET_RVALUE(${attrName}_, ${attrName}); }\n`, level);
      }
    }

    // for (let i = 0; i < ast.nodes.length; i++) {
    //   const node = ast.nodes[i];
    //   const value = node.fieldValue;
    //   // get方法
    //   this.emit('', level);
    //   this.visitFieldType(value, node, modelName);
    //   this.emit(` ${this.avoidReserveName(_name(node.fieldName))}() const;\n`);
    //   // set方法
    //   this.emit('void ', level);
    //   this.emit(`set${_upperFirst(_name(node.fieldName))}(`);
    //   this.visitFieldType(value, node, modelName);
    //   this.emit(` ${_name(node.fieldName)});\n`);
    // }
  }

  visitIncludeModelField(ast, modelName, level) {
    assert.equal(ast.type, 'modelBody');
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
      // TODO 应该使用 this.visitFieldType
      const cppType = types.cppType(value.fieldType);

      // TODO 这里应该判断是否有默认值
      if(types.isAny(value.fieldType)) {
        this.emit(`Darabonba::Json ${attrName}_ = nullptr;\n`, level);
      } else {
        this.emit(`std::shared_ptr<${cppType}> ${attrName}_ = nullptr;\n`, level);
      }
    }
  }

  visitObjectFieldValue(ast, level) {
    this.visitExpr(ast, level);
  }

  visitObjectField(ast, level) {
    let comments = DSL.comment.getFrontComments(this.comments, ast.tokenRange[0]);
    this.visitComments(comments, level);
    if (ast.type === 'objectField') {
      var key = _name(ast.fieldName);
      this.emit(`{"${key}" , `, level);
      this.visitObjectFieldValue(ast.expr, level);
      this.emit('}');
    } else {
      throw new Error('unimpelemented');
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
        this.emit('', level + 1);
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
      throw new Error('unimplemented');
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

  visitStaticCall(ast, level) {
    assert.equal(ast.left.type, 'static_call');
    const importInfo = this.imports[ast.left.id.lexeme];
    var className = importInfo.className || 'Client';
    this.emit(`${importInfo.namespace}::${className}::${_name(ast.left.propertyPath[0])}`);
    this.visitArgs(ast.args, level);
  }

  visitInstanceCall(ast, level) {
    assert.equal(ast.left.type, 'instance_call');
    const method = ast.left.propertyPath[0];
    var id = _name(ast.left.id);
    if (id.indexOf('@') > -1) {
      id = `_${_lowerFirst(id.substr(1))}`;
    }
    this.emit(`${id}.${_name(method)}`);
    this.visitArgs(ast.args, level);
  }

  visitMethodCall(ast, level) {
    assert.equal(ast.left.type, 'method_call');
    if (ast.isStatic) {
      var className = this.className;
      this.emit(`${className}::${_name(ast.left.id)}`);
    } else {
      this.emit(`${_name(ast.left.id)}`);
    }
    this.visitArgs(ast.args, level);
  }

  visitPropertyAssign(ast) {
    assert.ok(ast.left.type === 'property_access' || ast.left.type === 'property');
    var expr = _name(ast.left.id);
    var current = ast.left.id.inferred;
    let last = ast.left.propertyPath[ast.left.propertyPath.length - 1];
    for (let i = 0; i < ast.left.propertyPath.length - 1; i++) {
      let name = _name(ast.left.propertyPath[i]);
      if(expr === RESPONSE) {
        expr += `->${name}()`;
      }else if(current.type === 'model' || expr === REQUEST){
        expr += `.${name}()`;
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
    }else if(expr === `${REQUEST}.query()`) {
      // deal _request.query.xx
      needClose = true;
      expr = `${REQUEST}.addQuery("${_name(last)}", `;
    }else if(expr === `${REQUEST}.headers()`) {
      // deal _request.headers.xx
      needClose = true;
      expr = `${REQUEST}.addHeader("${_name(last)}", `;
    }else if(current.type === 'model'|| expr === REQUEST){
      needClose = true;
      expr += `.set${name}(`;
    }else {
      expr += `.at("${_name(last)}") = `;
    }
    
    this.emit(expr);
    if (ast.expr.needToReadable) {
      this.emit('stringstream(');
    }
    this.visitExpr(ast.expr);
    if (ast.expr.needToReadable) {
      this.emit(')');
    }
    if(needClose) {
      this.emit(')');
    }
    this.emit(';\n');
    
  }

  visitPropertyAccess(ast) {
    assert.ok(ast.type === 'property_access' || ast.type === 'property');
    var expr = _name(ast.id);
    var current = ast.id.inferred;
    for (var i = 0; i < ast.propertyPath.length; i++) {
      var name = _name(ast.propertyPath[i]);
      if(expr === RESPONSE) {
        expr += `->${name}()`;
      }else if(current.type === 'model' || expr === REQUEST){
        expr += `.${name}()`;
      }else {
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
      this.emit('(ostringstream(');
      for (let i = 0; i < ast.elements.length; i++) {
        var item = ast.elements[i];
        if (item.type === 'element') {
          if(item.value.string || i === 0) {
            this.emit('"');
            this.emit(item.value.string);
            this.emit('"');
          }
          if(i === 0) {
            this.emit(', ios_base::ate)');
          }
        } else if (item.type === 'expr') {
          if(i === 0) {
            this.emit('"", ios_base::ate) << ');
          }
          if (item.expr.type === 'property_access' && _name(item.expr.id) === '__module') {
            var value = this.__module;
            for (let i = 0; i < item.expr.propertyPath.length; i++) {
              value = value[_name(item.expr.propertyPath[i])];
            }
            this.emit('"');
            this.emit(value);
            this.emit('"');
          } else {
            this.visitExpr(item.expr, level);
          }
        } else {
          throw new Error('unimpelemented');
        }
        if (i < ast.elements.length - 1 && !this.checkEmpty(ast.elements, i)) {
          this.emit(' << ');
        }
      }
      this.emit(').str()');
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
    } else if (ast.type === 'not') {
      this.emit('!');
      this.visitExpr(ast.expr, level);
    } else if (ast.type === 'construct_model') {
      this.visitConstructModel(ast, level);
    } else if (ast.type === 'super') {
      //C++ 中需要特殊处理了，这里直接过滤
    } else if (ast.type === 'map_access') {
      this.visitMapAccess(ast, true);
    } else if (ast.type === 'array_access') {
      this.visitArrayAccess(ast);
    } else {
      throw new Error('unimpelemented');
    }
  }

  visitMapAccess(ast, level) {
    assert.equal(ast.type, 'map_access');
    let expr = _name(ast.id);
    if (ast.id.tag === DSL.Tag.Tag.VID) {
      expr = `_${expr.substr(1)}`;
    }
    if (ast.propertyPath && ast.propertyPath.length) {
      var current = ast.id.inferred;
      for (var i = 0; i < ast.propertyPath.length; i++) {
        var name = _name(ast.propertyPath[i]);
        if (current.type === 'model' || expr === REQUEST) {
          expr += `.${name}()`;
        } else {
          expr += `.at("${name}")`;
        }
        current = ast.propertyPathTypes[i];
      }
    }

    this.emit(`${expr}[`, level);
    this.visitExpr(ast.accessKey, level);
    this.emit(']');
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
          expr += `.${name}()`;
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
    const importInfo = this.imports[ast.inferred.name];
    let className = importInfo.className || 'Client';
    let namespace = importInfo.namespace;
    this.emit(`${namespace}::${className}`);
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
    if (ast.object && ast.object.fields && ast.object.fields.length > 0 && !this.exec) {
      this.visitType(ast.inferred);
      this.emit('(');
      this.visitObject(ast.object, level);
      this.emit(')');
      return;
    }
    this.emit('new ');
    this.visitType(ast.inferred);
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
    this.emit('throw Darabonba::Error(', level);
    this.visitObject(ast.expr, level, false);
    this.emit(');\n');
  }

  visitAssign(ast, level) {
    if (ast.left.type === 'property_assign' || ast.left.type === 'property') {
      this.emit('', level);
      this.visitPropertyAssign(ast);
      return;
    } else if (ast.left.type === 'virtualVariable') { // vid
      this.emit(`this->_${_name(ast.left.vid).substr(1)}`, level);
    } else if (ast.left.type === 'variable') {
      this.emit(`${_name(ast.left.id)}`, level);
    } else if (ast.left.type === 'map_access') {
      this.visitMapAccess(ast.left, level);
    } else if (ast.left.type === 'array_access') {
      this.visitArrayAccess(ast.left, level);
    } else {
      throw new Error('unimpelemented');
    }

    this.emit(' = ');
    if (ast.expr.needToReadable) {
      this.emit('stringstream(');
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
    this.visitType(ast.expr.inferred);
    this.emit(` ${id} = `);
    this.visitExpr(ast.expr, level);
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
    const ast = this.mainExec;
    if (!ast.params.params || ast.params.params.length === 0) {
      throw new Error('main function main must have [ string ] argument');
    }

    this.emit('int main(int argc, char *argv[]){\n');
    if (_name(ast.functionName) === 'main') {
      const args = _name(ast.params.params[0].paramName);
      this.emit(`vector<string> ${args};\n`, level + 1);
      this.emit('if(argc > 0) {\n', level + 1);
      this.emit(`${args}.assign(argv + 1, argv + argc);\n`, level + 2);
      this.emit('}\n', level + 1);
    }
    if (ast.functionBody) {
      this.visitFunctionBody(ast.functionBody, level + 1);
    }
    this.emit('}\n', level);
  }

  visitFunction(ast, level) {
    if (_name(ast.functionName) === 'main' && this.exec) {
      this.mainExec = ast;
      return;
    }
    this.visitAnnotation(ast.annotation, level);
    this.emit('', level);
    this.visitType(ast.returnType);
    this.emit(` ${this.namespace}::${this.className}::${_name(ast.functionName)}`);
    this.visitParams(ast.params, level);
    this.emit(' {');
    if (ast.functionBody) {
      this.emit('\n');
      this.visitFunctionBody(ast.functionBody, level + 1);
    }
    this.emit('}\n', level);
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
    this.visitParams(ast.params, level);
    this.emit(';\n');
  }

  visitIncludeType(ast, level) {
    this.emit('', level);
    this.visitType(ast.value);
    this.emit(` _${_name(ast.vid).substr(1)};`);
  }

  defaultConstructor(extendsClass, level) {
    var className = this.className;
    this.emit(`${className}()`, level + 1);
    if(extendsClass) {
      this.emit(`: ${extendsClass.namespace}::${extendsClass.className} `);
    }
    this.emit(' {}\n');
  }

  includeConstructor(ast, level) {
    var className = this.className;
    this.visitAnnotation(ast.annotation, level);
    this.emit(`${className}`, level + 1);
    this.visitParams(ast.params);
    this.emit(';\n');
    if(!ast.params.length) {
      this.needDefaultConstructor = false;
    }
  }

  visitConstructor(ast, extendsClass, level) {
    var className = this.className;
    this.visitAnnotation(ast.annotation, level);
    this.emit(`${this.namespace}::${className}::${className}`, level);
    this.visitParams(ast.params);
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
    this.emit(`: ${extendsClass.namespace}::${extendsClass.className}`);
    this.visitArgs(superStmt.args);
  }

  visitAPI(ast, level) {
    // if (ast.annotation) {
    //   this.emit(`${ _anno(ast.annotation.value) } \n`, level);
    // }
    var className = this.className;
    this.emit('', level);
    this.visitType(ast.returnType, this.namespace);
    this.emit(` ${this.namespace}::${className}::${_name(ast.apiName)}`);
    this.visitParams(ast.params, level);
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
    }
    this.visitAPIBody(ast.apiBody, baseLevel + 1);
    if (ast.runtimeBody) {
      this.emit(`_lastRequest = ${REQUEST};\n`, baseLevel + 1);
    }

    this.emit(`shared_ptr<Darabonba::Response> ${RESPONSE} = Darabonba::Core::doAction(${REQUEST}`, baseLevel + 1);
    if (ast.runtimeBody) {
      this.emit(`, ${RUNTIME}`);
    }
    this.emit(');\n');

    if (ast.returns) {
      this.visitReturnBody(ast.returns, baseLevel + 1);
    }

    if (ast.runtimeBody) {
      this.visitRuntimeAfter(ast.runtimeBody, level + 1);
    }

    this.emit('}\n', level);
  }

  visitIncludeAPI(ast, level) {
    this.emit('', level);
    this.visitType(ast.returnType);
    this.emit(` ${_name(ast.apiName)}`);
    this.visitParams(ast.params);
    this.emit(';\n');
  }

  visitRuntimeAfter(ast, level) {
    this.emit('} catch (RetryableError e) {\n', level + 1);
    // this.emit('if (Darabonba::isRetryable(e)) {\n', level + 2);
    this.emit('_lastException = e;\n', level + 2);
    this.emit('continue;\n', level + 2);
    this.emit('}\n', level + 2);
    // if (!this.NoException) {
    // this.emit('throw e;\n', level + 2);
    // } else {
      // this.emit('if (e instanceof TeaException) {\n', level + 2);
      // this.emit('throw e;\n', level + 3);
      // this.emit('}\n', level + 2);
      // this.emit(`json _errInfo;`, level + 2);
      // this.emit(`_errInfo["code"] = "Exception";`, level + 2);
      // this.emit(`_errInfo["message"] = _${errorName}.what();`, level + 2);
      // this.emit(`Darabonba::Error ${errorName} = Darabonba::Error(_errInfo);\n`, level + 2);
    // }
    this.emit('}\n', level + 1);
    this.emit('}\n', level);
    this.emit('throw Darabonba::UnretryableError(_lastRequest, _lastException);\n', level);
  }

  includeBefore() {
    this.emit('// This file is auto-generated, don\'t edit it. Thanks.\n', 0);
    this.emit(`#ifndef ${this.header.toUpperCase().replace(/[/|.]/g, '_')}_H_\n`, 0);
    this.emit(`#define ${this.header.toUpperCase().replace(/[/|.]/g, '_')}_H_\n`, 0);
    this.emit('#include <darabonba/core.hpp>\n', 0);
    this.headers.map(header =>{
      this.emit(`#include <${header}>\n`, 0);
    });
    this.emit('using namespace std;\n');
    this.emit('using json = nlohmann::json;\n');
    this.emit(`namespace ${this.namespace} {\n`);
  }

  srcBefore() {
    this.emit(`// This file is auto-generated, don't edit it. Thanks.
#include <${this.header}>

using namespace std;
using json = nlohmann::json;
`);
  }

  includeAfter() {
    this.emit('}\n');
    this.emit('#endif\n', 0);
  }

  modelBefore() {
    this.emit(`// This file is auto-generated, don't edit it. Thanks.
#include <${this.header}>

using namespace std;
using json = nlohmann::json;
using namespace ${this.namespace};\n
`);
  }

  includeApiBefore(extendsClass, level) {
    this.emit(`class ${this.className}`, level);
    if (extendsClass) {
      this.emit(` : public ${extendsClass.className}`);
    }
    this.emit(' {\n');
  }

  typeRelover(type, module) {
    //TODO
  }

}

module.exports = Visitor;
