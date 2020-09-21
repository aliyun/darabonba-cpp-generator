'use strict';

const debug = require('../../lib/debug');
const CombinatorBase = require('../common/combinator');
const PackageInfo = require('./package_info');

const {
  Symbol,
} = require('../common/enum');

const {
  _avoidKeywords,
  _deepClone,
  _upperFirst,
  _convertStaticParam,
  _symbol,
  _toSnakeCase,
  _modify
} = require('../../lib/helper');
const Emitter = require('../../lib/emitter');

const {
  PropItem,
  AnnotationItem,
  FuncItem,
  ConstructItem,
  // GrammerNewObject,
  GrammerThrows,
  GrammerCatch,
  GrammerValue,
  GrammerCall,
  // GrammerExpr,
  GrammerVar,

  TypeGeneric,
  TypeDecimal,
  TypeInteger,
  TypeStream,
  TypeObject,
  TypeString,
  TypeNumber,
  TypeArray,
  TypeBytes,
  TypeBool,
  TypeItem,
  TypeVoid,
  TypeNull,
  TypeMap,
  TypeBase,

  BehaviorToMap,
} = require('../common/items');

const assert = require('assert');

function _name(name) {
  return name.split('.').map(item => _upperFirst(_avoidKeywords(item))).join('');
}

class Combinator extends CombinatorBase {
  constructor(config, imports) {
    super(config, imports);
    this.eol = ';';
    this.classNameMap = {};
    this.package = _name(this.config.name);
    this.scope = _name(this.config.scope);
    this.namespace = `${this.scope}_${this.package}`;
    this.statements = {};
    this.properties = {};
  }

  addInclude(className) {
    let realFullClassName, includeFileName, using;
    if (className.indexOf('$') > -1) {
      realFullClassName = this.coreClass(className);
      includeFileName = `<${_toSnakeCase(this.config.tea.name)}/${_toSnakeCase(this.config.tea.header)}>`;
    } else if (this.thirdPackageNamespace[className]) {
      // is third package
      let scope = _toSnakeCase(_name(this.thirdPackageScope[className]));
      let client = _toSnakeCase(_name(this.thirdPackageNamespace[className]));
      includeFileName = `<${scope}/${client}.${this.config.header_ext}>`;
      realFullClassName = `${_name(this.thirdPackageScope[className])}_${_name(this.thirdPackageNamespace[className])}::Client`;
      using = null;
    } else {
      debug.stack(className, this.thirdPackageNamespace);
    }

    if (!this.classNameMap[realFullClassName]) {
      const include = { import: realFullClassName, includeFileName, using };
      this.classNameMap[realFullClassName] = include;
      this.includeList.push(include);
    }

    return realFullClassName;
  }

  addModelInclude(modelName) {
    let realFullClassName, includeFileName, using;
    let accessPath = modelName.split('.');
    if (modelName.indexOf('$') > -1) {
      realFullClassName = this.coreClass(modelName);
      includeFileName = `<${_toSnakeCase(this.config.tea.name)}/${_toSnakeCase(this.config.tea.header)}>`;
    } else if (accessPath.length > 1 && this.thirdPackageNamespace[accessPath[0]]) {
      // is third package model
      realFullClassName = `${_name(this.thirdPackageScope[accessPath[0]])
      }_${_name(accessPath[0])
      }::${_name(accessPath.slice(1).join('.'))
      }`;
      let scope = _toSnakeCase(_name(this.thirdPackageScope[accessPath[0]]));
      let client = _toSnakeCase(_name(accessPath[0]));
      includeFileName = `<${scope}/${client}.${this.config.header_ext}>`;
      using = null;
    } else {
      // self model
      realFullClassName = _name(accessPath.join('.'));
      includeFileName = `<${_toSnakeCase(this.scope)}/${_toSnakeCase(this.package)}.${this.config.header_ext}>`;
      using = null;
    }
    if (!this.classNameMap[realFullClassName]) {
      const include = { import: realFullClassName, includeFileName, using };
      this.classNameMap[realFullClassName] = include;
      this.includeList.push(include);
    }
    return realFullClassName;
  }

  combine(objects = []) {
    if (this.config.packageInfo) {
      const packageInfo = new PackageInfo(this.config);
      packageInfo.emit(this.thirdPackageDaraMeta);
    }
    this.combineHead(objects);
    this.combineCode(objects);
  }

  combineHead(objects) {
    const models = objects.filter(obj => obj.type === 'model');
    const [client] = objects.filter(obj => obj.type === 'client');
    const outputPars = { head: '', body: '', foot: '' };

    /******************************* emit body *******************************/
    let emitter = new Emitter(this.config);
    emitter.emitln(`namespace ${this.namespace} {`);
    models.forEach(object => {
      if (object.subObject.length) {
        object.subObject.forEach(obj => this.emitClass(emitter, obj));
      }
      this.emitClass(emitter, object);
    });
    this.emitClass(emitter, client);
    emitter.emitln(`} // namespace ${this.namespace}`);
    outputPars.body = emitter.output;

    /******************************* emit head *******************************/
    emitter = new Emitter(this.config);
    if (client.topAnnotation.length > 0) {
      this.emitAnnotations(emitter, client.topAnnotation);
      emitter.emitln();
    }
    const headerName = `${this.namespace}_H_`.toUpperCase();
    emitter.emitln(`#ifndef ${headerName}`);
    emitter.emitln(`#define ${headerName}`).emitln();
    this.emitInclude(emitter);
    outputPars.head = emitter.output;

    /******************************* emit foot   *******************************/
    emitter = new Emitter(this.config);
    emitter.emitln().emitln('#endif');
    outputPars.foot = emitter.output;

    /***************************** combine output ******************************/
    const config = _deepClone(this.config);
    config.ext = '.' + this.config.header_ext;
    config.dir = `${config.dir}/include/${_toSnakeCase(this.scope)}`;
    config.filename = _avoidKeywords(_toSnakeCase(this.package));
    this.combineOutputParts(config, outputPars);
  }

  combineCode(objects) {
    const [object] = objects.filter(obj => obj.type === 'client');
    object.name = 'Client';
    const outputPars = { head: '', body: '', foot: '' };
    this.object = object;
    this.properties = {};
    object.body.filter(node => node instanceof PropItem).forEach(node => {
      this.properties[node.name] = 'pointer';
    });

    /******************************* emit body *******************************/
    let emitter = new Emitter(this.config);
    object.body.forEach(node => {
      this.statements = _deepClone(this.properties);
      if (node instanceof FuncItem) {
        this.emitFuncCode(emitter, node);
      } else if (node instanceof ConstructItem) {
        this.emitConstruct(emitter, node);
      }
    });
    outputPars.body = emitter.output;

    /******************************* emit head *******************************/
    emitter = new Emitter(this.config);
    if (object.topAnnotation.length > 0) {
      this.emitAnnotations(emitter, object.topAnnotation);
      emitter.emitln();
    }
    emitter.emitln(`#include <${_toSnakeCase(this.scope)}/${_toSnakeCase(this.package)}.${this.config.header_ext}>`);
    this.emitInclude(emitter);
    outputPars.head = emitter.output;

    /***************************** combine output ******************************/
    const config = _deepClone(this.config);
    config.ext = '.' + this.config.code_ext;
    config.dir = `${config.dir}/src/`;
    config.filename = _avoidKeywords(_toSnakeCase(this.package));
    this.combineOutputParts(config, outputPars);
  }

  emitInclude(emitter) {
    let includeFileSet = [];
    let includeList = this.includeList.concat(this.includeModelList);
    const selfInclude = `<${_toSnakeCase(this.scope)}/${_toSnakeCase(this.package)}.${this.config.header_ext}>`;

    if (includeList.length) {
      includeList.filter(item => item.includeFileName !== selfInclude).sort(function (a, b) {
        return a.includeFileName > b.includeFileName ? 1 : -1;
      }).forEach(include => {
        if (includeFileSet.indexOf(include.includeFileName) === -1) {
          emitter.emitln(`#include ${include.includeFileName}`);
          includeFileSet.push(include.includeFileName);
        }
      });
      emitter.emitln();

      includeList = includeList.filter(item => !!item.using);
      const usingSet = [];
      if (includeList.length > 0) {
        includeList.forEach(item => {
          if (usingSet.indexOf(item.using) === -1) {
            emitter.emitln(`using namespace ${item.using};`);
            usingSet.push(item.using);
          }
        });
        emitter.emitln();
      }
    }
  }

  emitClass(emitter, object) {
    /***************************** initialize include list and class name ******************************/
    this.includeList = this.includeList.concat(object.includeList);
    this.includeModelList = this.includeModelList.concat(object.includeModelList);
    const className = object.name.split('.').map(item => _upperFirst(item)).join('');

    /***************************** emit class header ******************************/
    emitter.emit(`class ${className} `);
    if (object.type === 'model') {
      emitter.emit(': public Model ');
    } else if (object.extends.length) {
      emitter.emit(`: ${object.extends[0]} `);
    }
    emitter.emitln('{');

    /***************************** emit class body ******************************/

    // emit common constructer
    let hasConstruct = false;
    if (object.type === 'model') {
      hasConstruct = true;
      this.emitModelFunc(emitter, className, object);
    } else {
      emitter.emitln('public:', this.level);
      this.levelUp();
    }

    // emit child nodes
    object.body.forEach(node => {
      if (node instanceof PropItem) {
        // emit properties
        emitter.emitln(`${this.emitType(node.type)} *${node.name}{};`, this.level);
      } else if (node instanceof AnnotationItem) {
        // emit annotation
        this.emitAnnotation(emitter, node);
      } else if (node instanceof FuncItem) {
        let modify = _modify(node.modify);
        let returnType = this.emitType(node.return[0]);
        if (modify) {
          emitter.emit(`${modify} ${returnType} ${node.name}(`, this.level);
        } else {
          emitter.emit(`${returnType} ${node.name}(`, this.level);
        }
        this.emitParams(emitter, node.params);
        emitter.emitln(');');
      } else if (node instanceof ConstructItem) {
        // emit custom constructer
        let params = '';
        if (node.params.length) {
          emitter.emit(`explicit ${className}(`, this.level);
          params = this.emitParams(emitter, node.params);
          emitter.emit(')');
        } else {
          emitter.emit(`${className}()`, this.level);
        }
        if (object.extends.length) {
          let tmp = [];
          if (!(object.extends instanceof Array)) {
            object.extends = [object.extends];
          }
          object.extends.forEach(baseClass => {
            tmp.push(baseClass);
          });
          emitter.emitln(`: ${object.extends[0]}(${params});`);
        } else {
          emitter.emitln(';');
        }
        hasConstruct = true;
      }
    });

    emitter.emitln();
    if (!hasConstruct) {
      emitter.emitln(`${className}() {};`, this.level);
    }
    let properties = object.body.filter(node => node instanceof PropItem);
    if (properties.length) {
      emitter.emitln(`~${className}() {`, this.level);
      this.levelUp();
      properties.forEach(node => {
        emitter.emitln(`delete ${node.name};`, this.level);
      });
      this.levelDown();
      emitter.emitln('};', this.level);
    } else {
      emitter.emitln(`~${className}() {};`, this.level);
    }

    this.levelDown();

    /***************************** emit class footer ******************************/
    emitter.emitln('};');
  }

  emitModelFunc(emitter, className, object) {
    // emit notes
    emitter.emitln('protected:');
    this.levelUp();
    const notes = this.resolveNotes(object.body);
    if (Object.keys(notes).length > 0) {
      this.emitNotes(emitter, notes);
    }
    this.levelDown();
    emitter.emitln('public:');
    this.levelUp();
    emitter.emitln(`${className}() {_init();};`, this.level);
    emitter.emitln(`explicit ${className}(const std::map<string, boost::any> &config) : Model(config) {_init();};`, this.level);
    emitter.emitln();

    // emit toMap&fromMap method
    let props = object.body.filter(node => node instanceof PropItem);
    this.emitToMap(emitter, props, notes);
    this.emitFromMap(emitter, className, props, notes);
  }

  emitToMap(emitter, props, notes) {
    let nameMap = {};
    if (notes['name']) {
      notes['name'].forEach(note => {
        if (note.prop !== note.value) {
          nameMap[note.prop] = note.value;
        }
      });
    }
    emitter.emitln();
    emitter.emitln('map<string, boost::any> toMap() {', this.level);
    this.levelUp();
    emitter.emitln('map<string, boost::any> res;', this.level);
    props.forEach(prop => {
      let name = typeof nameMap[prop.name] !== 'undefined' ? nameMap[prop.name] : prop.name;
      emitter.emitln(`if (nullptr != ${prop.name}) {`, this.level);
      this.levelUp();
      if (prop.type instanceof TypeArray && !(prop.type instanceof TypeBytes)) {
        if (prop.type.itemType instanceof TypeBase || prop.type.itemType instanceof TypeStream) {
          emitter.emitln(`res["${name}"] = boost::any(*${prop.name});`, this.level);
        } else {
          emitter.emitln(`res["${name}"] = boost::any(vector<boost::any>({}));`, this.level);
          emitter.emitln(`if(nullptr != ${prop.name}){`, this.level);
          this.levelUp();
          emitter.emitln(`vector<boost::any> vec_${prop.name} = boost::any_cast<vector<boost::any>>(res["${name}"])`);
          emitter.emitln(`for(auto item:*${prop.name}){`, this.level);
          this.levelUp();
          emitter.emitln(`vec_${prop.name}.push_back(boost::any(item.toMap()));`);
          this.levelDown();
          emitter.emitln('}', this.level);
          emitter.emitln(`res["${name}"] = vec_${prop.name};`, this.level);
          this.levelDown();
          emitter.emitln('}', this.level);
        }
      } else if (prop.type instanceof TypeMap) {
        if (prop.type.valType instanceof TypeBase || prop.type.itemType instanceof TypeStream) {
          emitter.emitln(`res["${name}"] = boost::any(*${prop.name});`, this.level);
        } else {
          emitter.emitln(`res["${name}"] = boost::any(map<string, boost::any>({}));`, this.level);
          emitter.emitln(`if(nullptr != ${prop.name}){`, this.level);
          this.levelUp();
          emitter.emitln(`map<string, boost::any> map_${prop.name} = boost::any_cast<map<string, boost::any>>(res["${name}"])`);
          emitter.emitln(`for(auto item:*${prop.name}){`, this.level);
          this.levelUp();
          emitter.emitln(`map_${prop.name}[item.first] = boost::any(item.second.toMap());`, this.level);
          this.levelDown();
          emitter.emitln('}', this.level);
          emitter.emitln(`res["${name}"] = map_${prop.name};`, this.level);
          this.levelDown();
          emitter.emitln('}', this.level);
        }
      } else if (prop.type instanceof TypeBase || prop.type instanceof TypeBytes || prop.type instanceof TypeStream) {
        emitter.emitln(`res["${name}"] = boost::any(*${prop.name});`, this.level);
      } else if (this.isClient(prop)) {
        // emitter.emitln(`res["${name}"] = boost::any(*${prop.name});`, this.level);
      } else {
        emitter.emitln(`res["${name}"] = nullptr != ${prop.name} ? boost::any(${prop.name}->toMap()) : boost::any(map<string,boost::any>({}));`, this.level);
      }
      this.levelDown();
      emitter.emitln('}', this.level);
    });
    emitter.emitln('return res;', this.level);
    this.levelDown();
    emitter.emitln('}', this.level);
    emitter.emitln();
  }

  emitFromMap(emitter, modelName, props, notes) {
   
  }

  emitParams(emitter, params = []) {
    let tmp = [];
    params.forEach(param => {
      tmp.push(`${this.emitType(param.type)} *${_avoidKeywords(param.key)}`);
      this.statements[param.key] = 'pointer';
    });
    let emit = new Emitter(this.config);
    let str;
    if (tmp.length > 3) {
      let curr_row_len = emitter.currRow().length - 1;
      str = tmp.join(`,${emit.eol}${' '.repeat(curr_row_len)}`);
    } else {
      str = tmp.join(', ');
    }
    if (emitter instanceof Emitter) {
      emitter.emit(str);
    }
    return str;
  }

  emitType(type) {
    if (!(type instanceof TypeItem)) {
      debug.stack('Inavalid type', type);
    }
    if (type instanceof TypeGeneric) {
      this.pushInclude('boost_any');
      return 'boost::any';
    } else if (type instanceof TypeDecimal) {
      return 'float';
    } else if (type instanceof TypeInteger) {
      return type.length > 16 ? 'long' : 'int';
    } else if (type instanceof TypeNumber) {
      return 'int';
    } else if (type instanceof TypeString) {
      this.pushInclude('iostream');
      return 'string';
    } else if (type instanceof TypeBytes) {
      this.pushInclude('vector');
      return 'vector<uint8_t>';
    } else if (type instanceof TypeArray) {
      let subType = this.emitType(type.itemType);
      this.pushInclude('vector');
      return `vector<${subType}>`;
    } else if (type instanceof TypeBool) {
      return 'bool';
    } else if (type instanceof TypeVoid) {
      return 'void';
    } else if (type instanceof TypeMap) {
      this.pushInclude('map');
      return `map<${this.emitType(type.keyType)}, ${this.emitType(type.valType)}>`;
    } else if (type instanceof TypeStream) {
      this.pushInclude('stream');
      return 'concurrency::streams::ostream';
    } else if (type instanceof TypeObject) {
      if (!type.objectName) {
        return 'class';
      }
      if (type.objectName.indexOf('$') === 0) {
        return this.addInclude(type.objectName);
      }
      return type.objectName;
    } else if (type instanceof TypeNull) {
      return 'nullptr';
    }
    debug.stack('Unsupported Type', type);
  }

  emitNotes(emitter, notes) {
    // emit _name
    emitter.emitln('void _init(){', this.level);
    this.levelUp();
    if (notes['name'] && notes['name'].length > 0) {
      emitter.emitln('_name = map<string, string>({', this.level);
      this.levelUp();
      notes['name'].forEach(note => {
        if (note.key === 'name') {
          emitter.emitln(`{"${note.prop}" , "${note.value}",`, this.level);
        }
      });
      this.levelDown();
      emitter.emitln('});', this.level);
    }

    if (notes['default'] && notes['default'].length > 0) {
      emitter.emitln('_default = {', this.level);
      this.levelUp();
      notes['default'].forEach(note => {
        if (note.key === 'default') {
          let val = note.value;
          if (note.type === 'string') {
            val = `"${val}"`;
          }
          emitter.emitln(`{"${note.prop}" , boost::any(${val})},`, this.level);
        }
      });
      this.levelDown();
      emitter.emitln('};', this.level);
    }
    this.levelDown();
    emitter.emitln('}', this.level);
  }

  emitAnnotation(emitter, annotation, level) {
    if (typeof level === 'undefined') {
      level = this.level;
    }
    if (annotation.mode === 'single') {
      emitter.emitln(`// ${annotation.content}`, level);
    } else if (annotation.mode === 'multi') {
      emitter.emitln('/**', level);
      annotation.content.forEach(c => {
        emitter.emitln(` * ${c}`, level);
      });
      emitter.emitln(' */', level);
    } else {
      debug.stack('Unsupported annotation.mode :' + annotation.mode, annotation);
    }
  }

  emitConstruct(emitter, node) {
    if (!node.params.length && !node.body.length) {
      emitter.emitln(`${this.namespace}::Client::Client(){}`, this.level);
      return;
    }
    // has super call
    const hasSuperCall = function (item) {
      if (item instanceof GrammerValue && item.type === 'call') {
        return hasSuperCall(item.value);
      }
      return item instanceof GrammerCall && item.type === 'super';
    };
    const hasSuper = node.body.some(item => hasSuperCall(item));

    // emit construct header
    emitter.emit(`${this.namespace}::Client::Client(`);
    if (node.params.length) {
      this.emitParams(emitter, node.params);
      emitter.emit(')', this.level);
      if (hasSuper) {
        let tmp = [];
        node.params.forEach(p => {
          tmp.push(p.key);
        });
        emitter.emit(` : ${this.object.extends[0]}(${tmp.join(', ')})`);
      }
    } else {
      emitter.emit(')');
    }
    const nodes = node.body.filter(node => !hasSuperCall(node));
    if (nodes.length) {
      emitter.emitln(' {');
      this.levelUp();
      node.body.filter(node => !hasSuperCall(node)).forEach(node => {
        this.grammer(emitter, node);
      });
      this.levelDown();
      emitter.emitln('};', this.level);
      emitter.emitln();
    } else {
      emitter.emitln(' {};');
    }
  }

  emitFuncCode(emitter, func) {
    this.funcReturnType = func.return[0];
    if (func.params.length) {
      emitter.emit(`${this.emitType(func.return[0])} ${this.namespace}::Client::${func.name}(`);
      this.emitParams(emitter, func.params);
      emitter.emit(')');
    } else {
      emitter.emit(`${this.emitType(func.return[0])} ${this.namespace}::Client::${func.name}()`);
    }
    emitter.emitln(' {');
    this.levelUp();
    if (this.config.manual && func.body.length === 1 && func.body[0] instanceof GrammerThrows) {
      emitter.emitln('return "";', this.level);
    } else {
      func.body.forEach(node => {
        this.grammer(emitter, node);
      });
    }
    this.levelDown();
    emitter.emitln('}', this.level);
    emitter.emitln();
  }

  /**************************************** analyze ****************************************/

  isClient(prop) {
    let client_name = prop.type.objectName;
    if (client_name.indexOf('Client') < 0) {
      return false;
    }
    let is = false;
    Object.keys(this.thirdPackageDaraMeta).forEach(key => {
      const item = this.thirdPackageDaraMeta[key];
      let namespace = `${_name(item.scope)}_${_name(item.name)}::Client`;
      if (namespace === client_name) {
        is = true;
      }
    });
    return is;
  }

  pushInclude(includeName) {
    const include = this.config.third[includeName];
    if (!this.includeList.some(item => include.import === item.import)) {
      this.includeList.push(include);
    }
  }

  resolveCallPath(paths, params = '') {
    let lastPathType = '';
    let prefix = '';
    let lastPath = '';

    paths.forEach((path, i) => {
      let pathName = typeof path.name === 'string' ? path.name.replace('@', '_') : path.name;
      if (path.type === 'parent') {
        if (paths[i + 1] && paths[i + 1].type.indexOf('static') > -1) {
          prefix += `${this.config.client.name}`;
          if (path.name) {
            prefix += '::' + pathName;
          }
        } else {
          prefix += '';
          if (path.name) {
            prefix += `${pathName}`;
          }
        }
      } else if (path.type === 'object') {
        prefix += `${_convertStaticParam(pathName)}`;
      } else if (path.type === 'object_static') {
        prefix += `${_convertStaticParam(pathName)}`;
      } else if (path.type === 'call') {
        if (lastPathType === 'object' || lastPathType === 'parent') {
          let isPointer = this.statements[lastPath] && this.statements[lastPath] === 'pointer';
          prefix += isPointer ? `->${_avoidKeywords(pathName)}(${params})` : `.${_avoidKeywords(pathName)}(${params})`;
        } else {
          prefix += `.${_avoidKeywords(pathName)}(${params})`;
        }
      } else if (path.type === 'call_static') {
        prefix += `::${_avoidKeywords(pathName)}(${params})`;
      } else if (path.type === 'prop') {
        if (lastPathType === 'object') {
          let isPointer = this.statements[lastPath] && this.statements[lastPath] === 'pointer';
          prefix += isPointer ? `->${_avoidKeywords(pathName)}` : `.${_avoidKeywords(pathName)}`;
        } else {
          prefix += `.${_avoidKeywords(pathName)}`;
        }
      } else if (path.type === 'prop_static') {
        prefix += `::${pathName}`;
      } else if (path.type === 'map') {
        prefix += `["${pathName}"]`;
      } else if (path.type === 'list') {
        prefix += `[${pathName}]`;
      } else {
        debug.stack(paths);
      }
      lastPathType = path.type;
      lastPath = path.name;
    });
    if (prefix[0] === '.') {
      prefix = prefix.slice(1);
    } else if (prefix[0] === ':') {
      prefix = prefix.slice(2);
    } else if (prefix[0] === '-') {
      prefix = prefix.slice(2);
    }
    return prefix;
  }

  resolveDataType(gram) {
    let expectedType = null;
    if (gram.dataType) {
      expectedType = gram.dataType;
    } else if (gram.type === 'call') {
      expectedType = gram.value.returnType;
    }
    if (expectedType === null) {
      debug.stack(gram);
    }
    return this.emitType(expectedType);
  }

  isPointerVar(gram) {
    if (gram instanceof GrammerValue) {
      if (gram.type === 'var' && gram.value instanceof GrammerVar) {
        if (this.statements[gram.value.name] && this.statements[gram.value.name] === 'pointer') {
          return true;
        }
      } else if (gram.type === 'call' && gram.value instanceof GrammerCall && gram.value.type === 'prop') {
        if (gram.value.path[0].type === 'parent' && gram.value.path[1].type === 'prop') {
          return true;
        }
        let obj = gram.value.path[0].name;
        if (this.statements[obj] && this.statements[obj] === 'pointer') {
          return true;
        }
        return false;
      }
    }
    return false;
  }

  /**************************************** grammer ****************************************/
  grammerVar(emitter, gram, emitType = true) {
    let name = gram.name ? gram.name : gram.key;
    if (gram.varType === 'static_class') {
      emitter.emit(`${_convertStaticParam(name)}::class`);
    } else if (gram.varType === 'var' || gram.varType === 'const') {
      if (!this.statements[name] && emitType) {
        emitter.emit(`${this.emitType(gram.type)} ${_convertStaticParam(name)}`);
      } else {
        emitter.emit(`${_convertStaticParam(name)}`);
      }
      if (!this.statements[name]) {
        this.statements[name] = gram.type;
      }
    } else {
      debug.stack(gram);
    }
  }

  emitMap(emitter, gram, layer = 0) {
    this.pushInclude('map');

    let items = [];
    let expandItems = [];
    let keyType = this.emitType(gram.dataType.keyType);
    let valType = this.emitType(gram.dataType.valType);

    if (gram.needCast) {
      emitter.emit(`${this.config.tea.converter.name}::merge(`);
    }
    items = gram.value.filter(i => !i.isExpand);
    expandItems = gram.value.filter(i => i.isExpand);
    if (!items.length && !expandItems.length) {
      emitter.emit(`map<${keyType}, ${valType}>()`);
      return;
    }

    // emit map
    if (items.length) {
      if (gram.needCast || layer !== 0) {
        emitter.emitln(`new map<${keyType}, ${valType}>({`);
      } else {
        emitter.emitln('{');
      }
      this.levelUp();
      items.forEach((item, i) => {
        if (item instanceof AnnotationItem) {
          this.emitAnnotation(emitter, item);
          return;
        }
        emitter.emit(`{"${item.key}", `, this.level);
        if (gram.dataType.valType instanceof TypeGeneric) {
          emitter.emit('boost::any(');
        }
        if (this.isPointerVar(item)) {
          emitter.emit('*');
        }
        this.grammerValue(emitter, item, layer + 1);
        if (gram.dataType.valType instanceof TypeGeneric) {
          emitter.emit(')');
        }
        if (i < items.length - 1) {
          emitter.emitln('},');
        } else {
          emitter.emitln('}');
        }
      });
      this.levelDown();
      if (gram.needCast || layer !== 0) {
        emitter.emit('})', this.level);
      } else {
        emitter.emit('}', this.level);
      }
      if (expandItems.length) {
        emitter.emit(', ');
      }
    }
    if (expandItems.length) {
      let tmp = [];
      expandItems.forEach(item => {
        let emit = new Emitter(this.config);
        if (this.isPointerVar(item)) {
          this.grammer(emit, item, false, false);
        } else {
          emit.emit(`new map<${keyType}, ${valType}>(`);
          this.grammer(emit, item, false, false);
          emit.emit(')');
        }
        tmp.push(emit.output);
      });
      emitter.emit(tmp.join(', '));
    }

    if (gram.needCast) {
      // emitter.emit('))');
      emitter.emit(')'); // close converter merge method
    }
  }

  grammerValue(emitter, gram, layer = 0) {
    if (gram instanceof AnnotationItem) {
      this.emitAnnotation(emitter, gram);
      return;
    }
    if (gram.type === 'map' || gram.type === 'model_construct_params') {
      this.emitMap(emitter, gram, layer);
    } else if (gram.type === 'string') {
      emitter.emit(`"${gram.value}"`);
    } else if (gram.type === 'null') {
      emitter.emit('nullptr');
    } else if (gram.type === 'behavior' || gram.type === 'call'
      || gram.type === 'var' || gram.type === 'instance') {
      this.grammer(emitter, gram.value, false, false);
    } else if (gram.type === 'number' || gram.type === 'param' || gram.type === 'bool') {
      emitter.emit(gram.value);
    } else if (gram.type === 'expr') {
      if (Array.isArray(gram.value)) {
        gram.value.forEach(gramItem => {
          this.grammer(emitter, gramItem, false, false);
        });
      } else {
        this.grammer(emitter, gram.value, false, false);
      }
    } else if (gram.type === 'array') {
      let itemType = this.emitType(gram.dataType.itemType);
      if (gram.value.length) {
        emitter.emitln(`vector<${itemType}>({`);
        this.levelUp();
        gram.value.forEach((item, i) => {
          if (item instanceof AnnotationItem) {
            this.emitAnnotation(emitter, item);
            return;
          }
          emitter.emit('', this.level);
          this.grammerValue(emitter, item, false, false);
          if (i < gram.value.length - 1) {
            emitter.emitln(',');
          } else {
            emitter.emitln();
          }
        });
        this.levelDown();
        emitter.emit('})', this.level);
      } else {
        emitter.emitln(`vector<${itemType}>()`);
      }
    } else if (gram.type === 'not') {
      emitter.emit(_symbol(Symbol.reverse()));
      this.grammerValue(emitter, gram.value);
    } else {
      debug.stack(gram);
    }
  }

  grammerCall(emitter, gram) {
    if (gram.type === 'sys_func' || gram.type === 'method') {
      let params = '';
      if (gram.params.length > 0) {
        let tmp = [];
        let ignoreMethod = ['isUnset', 'empty'];
        gram.params.forEach(p => {
          if (p.value instanceof BehaviorToMap && gram.type === 'sys_func' && gram.path[1].name === 'isUnset') {
            let emit = new Emitter(this.config);
            this.grammer(emit, p.value.grammer, false, false);
            tmp.push(emit.output);
          } else if (gram.type === 'sys_func' && ignoreMethod.indexOf(gram.path[1].name) > -1) {
            let emit = new Emitter(this.config);
            if (!this.isPointerVar(p)) {
              emit.emit('&');
            }
            this.grammerValue(emit, p);
            tmp.push(emit.output);
          } else if (p instanceof GrammerVar && p.type.objectName === '$Exception') {
            let emit = new Emitter(this.config);
            emit.emit('&');
            this.grammer(emit, p, false, false);
            tmp.push(`${emit.output}`);
          } else if (p instanceof GrammerValue && p.type === 'map' && p.needCast) {
            let emit = new Emitter(this.config);
            emit.emit(`${this.config.tea.converter.name}::mapPointer(`);
            this.grammerValue(emit, p);
            emit.emit(')');
            tmp.push(emit.output);
          } else if (!this.isPointerVar(p)) {
            let emit = new Emitter(this.config);
            this.grammer(emit, p, false, false);
            let dataType = this.resolveDataType(p);
            tmp.push(`new ${dataType}(${emit.output})`);
          } else {
            let emit = new Emitter(this.config);
            this.grammerValue(emit, p);
            tmp.push(emit.output);
          }
        });
        params = tmp.join(', ');
        emitter.emit(this.resolveCallPath(gram.path, params));
      } else {
        emitter.emit(this.resolveCallPath(gram.path, params));
      }
    } else if (gram.type === 'prop') {
      emitter.emit(this.resolveCallPath(gram.path));
    } else if (gram.type === 'key') {
      emitter.emit(this.resolveCallPath(gram.path));
    } else {
      debug.stack(gram);
    }
  }

  grammerExpr(emitter, gram) {
    if (gram.opt === Symbol.concat()) {
      debug.stack(gram);
    }
    if (!gram.left && !gram.right) {
      emitter.emit(` ${_symbol(gram.opt)} `);
      return;
    }
    this.grammer(emitter, gram.left, false, false);
    let symbol = _symbol(gram.opt);
    if (gram.opt === Symbol.assign()) {
      if (gram.right.type === 'null') {
        return;
      }
      emitter.emit(` ${symbol} `);
      if (this.isPointerVar(gram.left) && !this.isPointerVar(gram.right)) {
        let dataType = this.resolveDataType(gram.right);
        emitter.emit(`new ${dataType}(`);
        this.grammer(emitter, gram.right, false, false);
        emitter.emit(')');
      } else if (!this.isPointerVar(gram.left) && this.isPointerVar(gram.right)) {
        emitter.emit('*');
        this.grammer(emitter, gram.right, false, false);
      } else if (this.isPointerVar(gram.left) && this.isPointerVar(gram.right)) {
        this.grammer(emitter, gram.right, false, false);
      } else {
        this.grammer(emitter, gram.right, false, false);
      }
    } else {
      emitter.emit(` ${symbol} `);
      this.grammer(emitter, gram.right, false, false);
    }
  }

  grammerLoop(emitter, gram) {
    this.pushInclude('algorithm');
    if (gram.type === 'foreach') {
      emitter.emit('for(');
      this.grammerVar(emitter, gram.item, false, false);
      emitter.emit(' : ');
      this.grammer(emitter, gram.source, false, false);
      emitter.emitln(') {');
    }
    this.levelUp();
    gram.body.forEach(node => {
      this.grammer(emitter, node);
    });
    this.levelDown();
    emitter.emitln('}', this.level);
  }

  grammerBreak(emitter, gram) {
    emitter.emit('break');
  }

  grammerCondition(emitter, gram) {
    if (gram.type === 'elseif') {
      emitter.emit('else if');
    } else {
      emitter.emit(`${gram.type}`);
    }
    if (gram.type !== 'else') {
      emitter.emit(' (');
      let emit = new Emitter(this.config);
      gram.conditionBody.forEach(condition => {
        this.grammer(emitter, condition, false, false);
      });
      emitter.emit(`${emit.output})`);
    }

    emitter.emitln(' {');
    this.levelUp();
    gram.body.forEach(node => {
      this.grammer(emitter, node);
    });
    this.levelDown();
    emitter.emitln('}', this.level);
    if (gram.elseItem.length && gram.elseItem.length > 0) {
      gram.elseItem.forEach(e => {
        this.grammer(emitter, e);
      });
    }
  }

  grammerTryCatch(emitter, gram) {
    emitter.emitln('try {');
    this.levelUp();
    gram.body.forEach(node => {
      this.grammer(emitter, node);
    });
    this.levelDown();
    emitter.emitln('}', this.level);
    gram.catchBody.forEach(node => {
      assert.strictEqual(true, node instanceof GrammerCatch);
      this.grammerCatch(emitter, node);
    });
    if (gram.finallyBody) {
      this.grammerFinally(emitter, gram.finallyBody);
    }
  }

  grammerCatch(emitter, gram) {
    let emitterVar = new Emitter(this.config);
    this.grammerVar(emitterVar, gram.exceptions.exceptionVar, false);
    let varName = emitterVar.output;
    emitter.emit(`catch (${this.emitType(gram.exceptions.type)} &`, this.level);
    emitter.emit(varName);
    emitter.emitln(') {');
    this.levelUp();
    gram.body.forEach(childGram => {
      this.grammer(emitter, childGram);
    });
    this.levelDown();
    emitter.emitln('}', this.level);
  }

  grammerFinally(emitter, gram) {
    emitter.emitln('catch(std::exception &e) {', this.level);
    this.levelUp();
    gram.body.forEach(childGram => {
      this.grammer(emitter, childGram);
    });
    this.levelDown();
    emitter.emitln('}', this.level);
  }

  grammerContinue(emitter, gram) {
    emitter.emit('continue');
  }

  grammerThrows(emitter, gram) {
    this.pushInclude('throw_exception');
    if (gram.exception === null) {
      emitter.emit('BOOST_THROW_EXCEPTION(');
      this.grammerValue(emitter, gram.params[0]);
      emitter.emit(')');
    } else {
      if (gram.params.length > 0) {
        emitter.emit(`BOOST_THROW_EXCEPTION(${this.emitType(gram.exception)}(`);
        let isError = gram.exception instanceof TypeObject && gram.exception.objectName === '$Error';
        let dataType = this.resolveDataType(gram.params[0]);
        if (isError) {
          emitter.emit(`boost::any(${dataType}(`);
        }
        if (gram.params.length === 1) {
          this.grammerValue(emitter, gram.params[0]);
        } else {
          let tmp = [];
          gram.params.forEach(p => {
            let emit = new Emitter(this.config);
            this.grammerValue(emit, p);
            tmp.push(emit.output);
          });
          emitter.emit(tmp.join(', '));
        }
        if (isError) {
          emitter.emit('))'); // close boost::any
        }
        emitter.emit('))');
      } else {
        let msg = gram.message ? `'${gram.message}'` : '';
        emitter.emit(`BOOST_THROW_EXCEPTION(${this.emitType(gram.exception)}(${msg}))`);
      }
    }
  }

  grammerNewObject(emitter, gram) {
    let objectName = gram.name;
    emitter.emit(`${objectName}(`);
    let params;
    if (Array.isArray(gram.params)) {
      params = gram.params;
    } else {
      params = [gram.params];
    }
    if (params.length) {
      let tmp = [];
      params.forEach(p => {
        let emit = new Emitter(this.config);
        if (!this.isPointerVar(p)) {
          let dataType = this.resolveDataType(p);
          emit.emit(`new ${dataType}(`);
          this.grammer(emit, p, false, false);
          emit.emit(')');
        } else {
          this.grammer(emit, p, false, false);
        }
        tmp.push(emit.output);
      });
      emitter.emit(tmp.join(', '));
    }
    emitter.emit(')');
  }

  grammerReturn(emitter, gram) {
    if (this.funcReturnType instanceof TypeVoid) {
      emitter.emit('return');
      return;
    }
    emitter.emit('return ');
    if (gram.type === 'null') {
      this.grammerValue(emitter, new GrammerValue('null'), false, false);
    } else if (gram.type === 'grammer') {
      this.grammer(emitter, gram.expr, false, false);
    } else if (gram.type === 'string') {
      emitter.emit('string("")');
    } else {
      this.grammer(emitter, gram.expr, false, false);
    }
  }

  /**************************************** behavior ****************************************/
  behaviorTimeNow(emitter, behavior) {
    emitter.emit('0');
  }

  behaviorDoAction(emitter, behavior) {
    emitter.emit('', this.level);
    this.grammerVar(emitter, behavior.var);
    emitter.emit(`= ${this.addInclude('$Core')}::${this.config.tea.core.doAction}(`);
    let params = [];
    behavior.params.forEach(p => {
      let emit = new Emitter(this.config);
      this.grammerValue(emit, p);
      params.push(emit.output);
    });
    emitter.emit(params.join(', '));
    emitter.emitln(');');
    behavior.body.forEach(node => {
      this.grammer(emitter, node);
    });
  }

  behaviorToMap(emitter, behavior) {
    const grammer = behavior.grammer;
    if (grammer instanceof GrammerCall) {
      this.grammerCall(emitter, grammer);
    } else if (grammer instanceof GrammerVar) {
      this.grammerVar(emitter, grammer);
    } else {
      debug.stack(grammer);
    }
  }

  behaviorToModel(emitter, behavior) {
    emitter.emit('behavior.expected::fromMap(');
    this.grammer(emitter, behavior.grammer, false, false);
    emitter.emit(')');
  }

  behaviorSetMapItem(emitter, behavior) {
    let emit = new Emitter(this.config);
    this.grammerCall(emit, behavior.call);
    this.pushInclude('map');
    emitter.emit(`${emit.output}.insert(pair<string, ${this.emitType(behavior.value.dataType)}>("${behavior.key}", `, this.level);
    this.grammerValue(emitter, behavior.value);
    emitter.emitln('));');
  }

  behaviorRetry(emitter, behavior) {
    emitter.emitln(`throw ${this.addInclude('$Error')}(${this.config.request}, ${this.config.response});`, this.level);
  }

  behaviorTamplateString(emitter, behavior) {
    let tmp = [];
    this.pushInclude('cast');
    behavior.items.forEach(item => {
      let emit = new Emitter(this.config);
      if (this.isPointerVar(item)) {
        emit.emit('*');
      }
      if (item.dataType instanceof TypeString) {
        this.grammer(emit, item, false, false);
      } else if (item.dataType instanceof TypeGeneric) {
        emit.emit(`${this.config.tea.converter.name}::toString(`);
        this.grammer(emit, item, false, false);
        emit.emit(')');
      } else {
        emit.emit('boost::lexical_cast<string>(');
        this.grammer(emit, item, false, false);
        emit.emit(')');
      }
      tmp.push(emit.output);
    });
    emitter.emit(`string(${tmp.join(' + ')})`);
  }
}
module.exports = Combinator;