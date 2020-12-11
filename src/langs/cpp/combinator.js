'use strict';

const debug = require('../../lib/debug');
const CombinatorBase = require('../common/combinator');
const PackageInfo = require('./package_info');

const {
  Symbol,
} = require('../common/enum');

const {
  is,
  _symbol,
  _modify,
  _contain,
  _deepClone,
  _upperFirst,
  _toSnakeCase,
  _avoidKeywords,
  _camelCase,
  _name
} = require('../../lib/helper');
const Emitter = require('../../lib/emitter');

const {
  PropItem,
  AnnotationItem,

  GrammerNewObject,
  GrammerThrows,
  GrammerCatch,
  GrammerValue,
  GrammerCall,
  GrammerVar,

  BehaviorToMap,

  TypeItem,
  TypeMap,
  TypeString,
  TypeGeneric,
  BehaviorTamplateString
} = require('../common/items');

const assert = require('assert');

function _names(notes) {
  let nameMap = {};
  if (notes['name']) {
    notes['name'].forEach(note => {
      if (note.prop !== note.value) {
        nameMap[note.prop] = note.value;
      }
    });
  }
  return nameMap;
}

function _needRecur(prop_type) {
  if (is.undefined(prop_type) || !is.tree(prop_type)) {
    return false;
  }
  let itemType = prop_type.itemType ? prop_type.itemType : prop_type.valType;
  if (is.undefined(itemType)) {
    return false;
  }
  if (is.tree(itemType)) {
    return _needRecur.call(this, itemType);
  }
  if (is.object(itemType) && !this.isClient(itemType)) {
    return true;
  }
  return false;
}

var statements = {};

class Combinator extends CombinatorBase {
  constructor(config, imports) {
    super(config, imports);
    this.eol = ';';
    this.classNameMap = {};
    this.package = _upperFirst(_camelCase(_name(this.config.name)));
    this.scope = _upperFirst(_camelCase(_name(this.config.scope)));
    this.namespace = `${this.scope}_${this.package}`;
    this.properties = {};
  }

  addInclude(className) {
    let realFullClassName, includeFileName, using;
    if (_contain(className, '$')) {
      realFullClassName = this.coreClass(className);
      includeFileName = `<${_toSnakeCase(this.config.tea.name)}/${_toSnakeCase(this.config.tea.header)}>`;
    } else if (this.thirdPackageNamespace[className]) {
      // is third package
      let scope = _toSnakeCase(_name(this.thirdPackageScope[className]));
      let client = _toSnakeCase(_name(this.thirdPackageNamespace[className]));
      includeFileName = `<${scope}/${client}.${this.config.header_ext}>`;
      realFullClassName = `${_upperFirst(_name(this.thirdPackageScope[className]))}_${_upperFirst(_name(this.thirdPackageNamespace[className]))}::Client`;
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
    if (_contain(modelName, '$')) {
      realFullClassName = this.coreClass(modelName);
      includeFileName = `<${_toSnakeCase(this.config.tea.name)}/${_toSnakeCase(this.config.tea.header)}>`;
    } else if (accessPath.length > 1 && this.thirdPackageNamespace[accessPath[0]]) {
      // is third package model
      realFullClassName = `${_upperFirst(_name(this.thirdPackageScope[accessPath[0]]))
      }_${_upperFirst(_name(this.thirdPackageNamespace[accessPath[0]]))
      }::${_name(accessPath.slice(1).join('.'))
      }`;
      let scope = _toSnakeCase(_name(this.thirdPackageScope[accessPath[0]]));
      let client = _toSnakeCase(_name(this.thirdPackageNamespace[accessPath[0]]));
      includeFileName = `<${scope}/${client}.${this.config.header_ext}>`;
      using = null;
    } else if (accessPath.length === 1 && this.thirdPackageNamespace[accessPath[0]]) {
      realFullClassName = `${_upperFirst(_name(this.thirdPackageScope[accessPath[0]]))
      }_${_upperFirst(_name(this.thirdPackageNamespace[accessPath[0]]))
      }::Client`;
      let scope = _toSnakeCase(_name(this.thirdPackageScope[accessPath[0]]));
      let client = _toSnakeCase(_name(this.thirdPackageNamespace[accessPath[0]]));
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
    if (this.config.packageInfo || this.config.exec) {
      const packageInfo = new PackageInfo(this.config);
      packageInfo.emit(this.thirdPackageDaraMeta, this.libraries, objects);
    }
    if (this.config.exec) {
      this.combineCode(objects);
    } else {
      this.combineHead(objects);
      this.combineCode(objects);
    }
  }

  combineHead(objects) {
    const models = objects.filter(obj => obj.type === 'model');
    const [client] = objects.filter(obj => obj.type === 'client');
    const outputPars = { head: '', body: '', foot: '' };

    /******************************* emit body *******************************/
    let emitter = new Emitter(this.config);
    emitter.emitln(`namespace ${this.namespace} {`);
    this.definedModels = [];
    const self = this;
    // Fix the problem when used before definition
    const findUndefinedModel = function (type) {
      if (is.object(type)) {
        let objectName = this.resolveName(type.objectName);
        if (!_contain(this.definedModels, objectName)) {
          const [obj] = models.filter(node => node.name === objectName);
          if (obj) {
            obj.body.filter(node => is.prop(node)).forEach(item => {
              findUndefinedModel.call(self, item.type);
            });
            this.emitModel(emitter, obj);
          }
        }
      } else if (is.array(type)) {
        findUndefinedModel.call(self, type.itemType);
      } else if (is.map(type)) {
        findUndefinedModel.call(self, type.valType);
      }
    };
    models.forEach(model => {
      if (_contain(this.definedModels, model.name)) {
        return;
      }
      model.body.filter(node => is.prop(node)).forEach(item => {
        findUndefinedModel.call(self, item.type);
      });
      this.emitModel(emitter, model);
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
    config.filename = _toSnakeCase(this.package);
    this.combineOutputParts(config, outputPars);
  }

  combineCode(objects) {
    const [object] = objects.filter(obj => obj.type === 'client');
    object.name = 'Client';
    const outputPars = { head: '', body: '', foot: '' };
    this.object = object;
    this.properties = {};
    object.body.filter(node => is.prop(node)).forEach(node => {
      this.properties[node.name] = { type: node.type, pointer: true };
    });

    /******************************* emit body *******************************/
    let emitter = new Emitter(this.config);
    object.body.forEach(node => {
      statements = _deepClone(this.properties);
      if (is.func(node)) {
        this.emitFuncCode(emitter, node);
      } else if (is.construct(node)) {
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
    if (!this.config.exec) {
      emitter.emitln(`#include <${_toSnakeCase(this.scope)}/${_toSnakeCase(this.package)}.${this.config.header_ext}>`);
      this.emitInclude(emitter);
      emitter.emitln(`using namespace ${this.namespace};`).emitln();
    } else {
      this.emitInclude(emitter);
    }

    outputPars.head = emitter.output;

    /***************************** combine output ******************************/
    const config = _deepClone(this.config);
    config.ext = '.' + this.config.code_ext;
    config.dir = `${config.dir}/src/`;
    config.filename = _toSnakeCase(this.package);
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
        if (!_contain(includeFileSet, include.includeFileName)) {
          emitter.emitln(`#include ${include.includeFileName}`);
          includeFileSet.push(include.includeFileName);
        }
      });
      emitter.emitln();

      includeList = includeList.filter(item => !!item.using);
      const usingSet = [];
      if (includeList.length > 0) {
        includeList.forEach(item => {
          if (!_contain(usingSet, item.using)) {
            emitter.emitln(`using namespace ${item.using};`);
            usingSet.push(item.using);
          }
        });
        emitter.emitln();
      }
    }
  }

  emitModel(emitter, model) {
    if (_contain(this.definedModels, model.name)) {
      return;
    }
    this.definedModels.push(model.name);
    if (model.subObject.length) {
      model.subObject.forEach(obj => this.emitClass(emitter, obj));
    }
    this.emitClass(emitter, model);
  }

  emitClass(emitter, object) {
    /***************************** initialize include list and class name ******************************/
    this.includeList = this.includeList.concat(object.includeList);
    this.includeModelList = this.includeModelList.concat(object.includeModelList);
    const className = object.name.split('.').map(item => _upperFirst(item)).join('');

    /***************************** emit class header ******************************/
    emitter.emit(`class ${className} `);
    if (object.type === 'model') {
      emitter.emit(`: public ${this.config.tea.model.name} `);
    } else if (object.extends.length) {
      emitter.emit(`: ${this.resolveName(object.extends[0])} `);
    }
    emitter.emitln('{');

    /***************************** emit class body ******************************/

    // emit common constructer
    let hasConstruct = false;
    if (object.type === 'model') {
      hasConstruct = true;
    }
    emitter.emitln('public:', this.level);
    this.levelUp();

    // emit child nodes
    object.body.forEach(node => {
      if (is.prop(node)) {
        // emit properties
        emitter.emitln(`shared_ptr<${this.emitType(node.type)}> ${_avoidKeywords(node.name)}{};`, this.level);
      } else if (is.annotation(node)) {
        // emit annotation
        this.emitAnnotation(emitter, node);
      } else if (is.func(node)) {
        let modify = _modify(node.modify);
        let returnType = this.emitType(node.return[0], true);
        let func_name = _avoidKeywords(node.name);
        if (modify) {
          emitter.emit(`${modify} ${returnType} ${func_name}(`, this.level);
        } else {
          emitter.emit(`${returnType} ${func_name}(`, this.level);
        }
        this.emitParams(emitter, node.params);
        emitter.emitln(');');
      } else if (is.construct(node)) {
        // emit custom constructer
        if (node.params.length) {
          emitter.emit(`explicit ${className}(`, this.level);
          let tmp = [];
          node.params.forEach(param => {
            tmp.push(`const shared_ptr<${this.emitType(param.type, true)}>& ${_avoidKeywords(param.key)}`);
            this.addStatement(param.key, param.type, true);
          });
          let emit = new Emitter(this.config);
          let str;
          if (tmp.length > 3) {
            let curr_row_len = emitter.currRow().length;
            str = tmp.join(`,${emit.eol}${' '.repeat(curr_row_len)}`);
          } else {
            str = tmp.join(', ');
          }
          emitter.emit(str);
          emitter.emit(')');
        } else {
          emitter.emit(`${className}()`, this.level);
        }
        emitter.emitln(';');
        hasConstruct = true;
      }
    });

    if (object.type === 'model') {
      emitter.emitln();
      this.emitModelFunc(emitter, className, object);
    }
    emitter.emitln();
    if (!hasConstruct) {
      emitter.emitln(`${className}() {};`, this.level);
    }
    emitter.emitln(`virtual ~${className}() = default;`, this.level);

    this.levelDown();

    /***************************** emit class footer ******************************/
    emitter.emitln('};');
  }

  emitModelFunc(emitter, className, object) {
    const notes = this.resolveNotes(object.body);
    emitter.emitln(`${className}() {}`, this.level);
    emitter.emitln();
    emitter.emitln(`explicit ${className}(const std::map<string, boost::any> &config) : ${this.config.tea.model.name}(config) {`, this.level);
    this.levelUp();
    emitter.emits(this.level,
      'fromMap(config);'
    );
    this.levelDown();
    emitter.emitln('};', this.level);
    emitter.emitln();

    // emit toMap&fromMap method
    let props = object.body.filter(node => is.prop(node));
    this.emitValidate(emitter, props);
    this.emitToMap(emitter, props, notes);
    this.emitFromMap(emitter, props, notes);
  }

  emitValidate(emitter, props) {
    let emit = new Emitter(this.config);
    let validateNoteKeys = [
      'required',
      'maximum',
      'minimum',
      'maxLength',
      'minLength',
      // 'format',
      // 'enum',
      'pattern',
      // 'maxItems'
    ];
    this.levelUp();
    props.forEach(prop => {
      prop.notes.forEach(note => {
        if (_contain(validateNoteKeys, note.key)) {
          let val = note.value;
          if (note.type === 'string') {
            val = `"${val}"`;
          }
          if (note.key === 'pattern') {
            val = val.split('\\').join('\\\\');
          }
          if (note.key === 'required' && note.value === true) {
            emit.emitln(`if (!${_avoidKeywords(note.prop)}) {`, this.level);
            this.pushInclude('throw_exception', this.level);
            this.levelUp();
            emit.emitln(`BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("${prop.name} is required.")));`, this.level);
            this.levelDown();
            emit.emitln('}', this.level);
          } else if (note.key === 'maximum' || note.key === 'minimum') {
            let opt = note.key === 'maximum' ? '>' : '<';
            emit.emitln(`if (${_avoidKeywords(note.prop)} && *${_avoidKeywords(note.prop)} ${opt} ${val}) {`, this.level);
            this.pushInclude('throw_exception', this.level);
            this.levelUp();
            emit.emitln(`BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("${prop.name} is required.")));`, this.level);
            this.levelDown();
            emit.emitln('}', this.level);
          } else if (note.key === 'pattern') {
            if (is.string(prop.type)) {
              emit.emitln(`${this.addInclude('$Model')}::validatePattern("${_avoidKeywords(note.prop)}", ${_avoidKeywords(note.prop)}, ${val});`, this.level);
            } else {
              debug.warning(`Only supported string for validate pattern. ${prop.getParent().name}::${prop.name} type is ${this.emitType(prop.type)}.`);
            }
          } else {
            emit.emitln(`${this.addInclude('$Model')}::validate${_upperFirst(note.key)}("${_avoidKeywords(note.prop)}", ${_avoidKeywords(note.prop)}, ${val});`, this.level);
          }
        }
      });
    });
    this.levelDown();
    if (emit.output) {
      emitter.emitln('void validate() override {', this.level);
      emitter.emit(emit.output);
      emitter.emitln('}', this.level);
    } else {
      emitter.emitln('void validate() override {}', this.level);
    }
    emitter.emitln();
  }

  emitMakeShared(type, data, need_cast = false) {
    let type_str = typeof (type) === 'string' ? type : this.emitType(type);
    if (type_str === 'nullptr') {
      return 'nullptr';
    }
    let data_str;
    if (typeof (data) === 'string') {
      data_str = data;
    } else {
      const emit = new Emitter(this.config);
      this.grammer(emit, data, false, false);
      data_str = emit.output;
    }
    if (need_cast) {
      return `make_shared<${type_str}>(boost::any_cast<${type_str}>(${data_str}))`;
    }
    return `make_shared<${type_str}>(${data_str})`;
  }

  emitToMapProp(emitter, prefix = 'res', prop, layer = 1, parent_type) {
    let var_name = '';
    let isProp = layer === 1 && !this.isClient(prop);
    if (isProp) {
      var_name = `*${_avoidKeywords(prop.name)}`;
      emitter.emitln(`if (${_avoidKeywords(prop.name)}) {`, this.level);
      this.levelUp();
    } else {
      var_name = _avoidKeywords(prop.name);
    }
    if (_needRecur.call(this, prop.type)) {
      // item type is array or map
      const p = new PropItem();
      p.type = is.array(prop.type) ? prop.type.itemType : prop.type.valType;
      let pre = '';
      let temp = '';
      if (is.array(prop.type)) {
        p.name = `item${layer}`;
        temp = `temp${layer}`;
        pre = `${temp}`;
      } else {
        p.name = `item${layer}.second`;
        temp = `temp${layer}`;
        pre = `${temp}[item${layer}.first]`;
      }
      let temp_type = is.array(prop.type) ? 'vector<boost::any>' : 'map<string, boost::any>';
      emitter.emitln(`${temp_type} ${temp};`, this.level);
      emitter.emitln(`for(auto item${layer}:${var_name}){`, this.level);
      this.levelUp();
      this.emitToMapProp(emitter, pre, p, layer + 1, prop.type);
      this.levelDown();
      emitter.emitln('}', this.level);
      if (is.array(prop.type)) {
        emitter.emitln(`${prefix} = boost::any(${temp});`, this.level);
      } else {
        emitter.emitln(`${prefix} = boost::any(${temp});`, this.level);
      }
    } else if (is.object(prop.type)) {
      // type is model
      if (!this.isClient(prop)) {
        // is not client
        if (layer === 1) {
          emitter.emitln(`${prefix} = ${_avoidKeywords(prop.name)} ? boost::any(${_avoidKeywords(prop.name)}->toMap()) : boost::any(map<string,boost::any>({}));`, this.level);
        } else {
          if (is.array(parent_type)) {
            emitter.emitln(`${prefix}.push_back(boost::any(${_avoidKeywords(prop.name)}.toMap()));`, this.level);
          } else {
            emitter.emitln(`${prefix} = boost::any(${_avoidKeywords(prop.name)}.toMap());`, this.level);
          }
        }
      } else {
        debug.warning('sub item type is client : ' + prefix);
      }
    } else if (is.base(prop.type)) {
      // is base type
      emitter.emitln(`${prefix} = boost::any(${var_name});`, this.level);
    } else {
      debug.warning('unsupported type toMap()', prop);
    }
    if (isProp) {
      this.levelDown();
      emitter.emitln('}', this.level);
    }
  }

  emitToMap(emitter, props, notes) {
    let nameMap = _names(notes);
    emitter.emitln('map<string, boost::any> toMap() override {', this.level);
    this.levelUp();
    emitter.emitln('map<string, boost::any> res;', this.level);
    props.forEach(prop => {
      let name = typeof nameMap[prop.name] !== 'undefined' ? nameMap[prop.name] : prop.name;
      this.emitToMapProp(emitter, `res["${name}"]`, prop);
    });
    emitter.emitln('return res;', this.level);
    this.levelDown();
    emitter.emitln('}', this.level);
    emitter.emitln();
  }

  emitFromMapItem(emitter, target, type, source, parent_type = null, layer = 1) {
    if (is.array(type)) {
      emitter.emitln(`vector<${this.emitType(type.itemType)}> toVec${layer};`, this.level);
      emitter.emitln(`if (typeid(vector<boost::any>) == ${source}.type()) {`, this.level);
      this.levelUp();
      emitter.emitln(`vector<boost::any> vec${layer} = boost::any_cast<vector<boost::any>>(${source});`, this.level);
      emitter.emitln(`for (auto item:vec${layer}) {`, this.level);
      this.levelUp();
      this.emitFromMapItem(emitter, ` toVec${layer}`, type.itemType, 'item', type, layer + 1);
      this.levelDown();
      emitter.emitln('}', this.level);
      this.levelDown();
      emitter.emitln('}', this.level);
      if (layer === 1) {
        emitter.emitln(`${target} = ${this.emitMakeShared(type, `toVec${layer}`)};`, this.level);
      } else {
        emitter.emitln(`${target} = toVec${layer};`, this.level);
      }
    } else if (is.map(type)) {
      emitter.emitln(`map<${this.emitType(type.keyType)}, ${this.emitType(type.valType)}> map${layer} = boost::any_cast<map<${this.emitType(type.keyType)}, ${this.emitType(type.valType)}>>(${source});`, this.level);
      emitter.emitln(`map<${this.emitType(type.keyType)}, ${this.emitType(type.valType)}> toMap${layer};`, this.level);
      emitter.emitln(`for (auto item:map${layer}) {`, this.level);
      this.levelUp();
      this.emitFromMapItem(emitter, ` toMap${layer}[item.first]`, type.valType, 'item.second', type, layer + 1);
      this.levelDown();
      emitter.emitln('}', this.level);
      if (layer === 1) {
        emitter.emitln(`${target} = ${this.emitMakeShared(type, `toMap${layer}`)};`, this.level);
      } else {
        emitter.emitln(`${target} = toMap${layer};`, this.level);
      }
    } else if (is.stream(type)) {
      if (is.array(parent_type)) {
        emitter.emitln(`${target}.push_back(boost::any_cast<${this.addInclude('$Stream')}>(${source}));`, this.level);
      } else if (layer === 1) {
        emitter.emitln(`${target} = ${this.emitMakeShared(this.addInclude('$Stream'), source, true)};`, this.level);
      } else {
        emitter.emitln(`${target} = boost::any_cast<${this.addInclude('$Stream')}>(${source});`, this.level);
      }
    } else if (is.base(type)) {
      if (is.array(parent_type)) {
        emitter.emitln(`${target}.push_back(boost::any_cast<${this.emitType(type)}>(${source}));`, this.level);
      } else if (layer === 1) {
        emitter.emitln(`${target} = ${this.emitMakeShared(type, source, true)};`, this.level);
      } else {
        emitter.emitln(`${target} = ${source};`, this.level);
      }
    } else if (is.object(type)) {
      if (is.array(parent_type)) {
        if (layer === 1) {
          emitter.emitln(`${target}->push_back(${source});`, this.level);
        } else {
          emitter.emitln(`${target}.push_back(${source});`, this.level);
        }
      } else if (layer === 1) {
        emitter.emitln(`${target} = ${this.emitMakeShared(type, source)};`, this.level);
      } else {
        emitter.emitln(`${target} = ${this.emitType(type)}(${source});`, this.level);
      }
    } else {
      debug.stack(target, type, source);
    }
  }

  emitFromMapProp(emitter, name, prop, realkey, layer = 1, parent_type = null) {
    const isProp = realkey.indexOf('expect') !== 0 && !this.isClient(prop);
    if (isProp) {
      emitter.emitln(`if (m.find("${realkey}") != m.end() && !m["${realkey}"].empty()) {`, this.level);
      this.levelUp();
    }

    if (_needRecur.call(this, prop.type)) {
      // item type is array or map
      const p = new PropItem();
      p.type = is.array(prop.type) ? prop.type.itemType : prop.type.valType;
      let nextName = '';
      let nextExpectName = '';
      let expectName = `expect${layer}`;
      if (is.array(prop.type)) {
        p.name = `item${layer}`;
        p.parent = prop.type;
        nextName = `item${layer}`;
        nextExpectName = `${expectName}`;
      } else {
        p.name = `item${layer}.second`;
        nextName = `item${layer}.second`;
        nextExpectName = `${expectName}[item.first]`;
      }
      let temp_type = is.array(prop.type) ? 'vector<boost::any>' : 'map<string, boost::any>';
      let expected_type = this.emitType(prop.type);
      emitter.emitln(`if (typeid(${temp_type}) == ${name}.type()) {`, this.level);
      this.levelUp();
      emitter.emitln(`${expected_type} ${expectName};`, this.level);
      emitter.emitln(`for(auto item${layer}:boost::any_cast<${temp_type}>(${name})){`, this.level);
      this.levelUp();
      this.emitFromMapProp(emitter, nextName, p, nextExpectName, layer + 1, prop.type);
      this.levelDown();
      emitter.emitln('}', this.level);
      if (prop.parent && is.array(prop.parent)) {
        if (layer === 1) {
          emitter.emitln(`${realkey}.push_back(${this.emitMakeShared(prop.type, expectName)};`, this.level);
        } else {
          emitter.emitln(`${realkey}.push_back(${expectName});`, this.level);
        }
      } else {
        if (layer === 1) {
          emitter.emitln(`${_avoidKeywords(prop.name)} = ${this.emitMakeShared(prop.type, expectName)};`, this.level);
        } else {
          if (is.array(parent_type)) {
            emitter.emitln(`${realkey}.push_back(${expectName});`, this.level);
          } else {
            emitter.emitln(`${realkey} = ${expectName};`, this.level);
          }
        }
      }
      this.levelDown();
      emitter.emitln('}', this.level);
    } else if (is.object(prop.type)) {
      if (!this.isClient(prop)) {
        // type is model
        let var_name = `model${layer}`;
        emitter.emitln(`if (typeid(map<string, boost::any>) == ${name}.type()) {`, this.level);
        this.levelUp();
        emitter.emitln(`${this.emitType(prop.type)} ${var_name};`, this.level);
        emitter.emitln(`${var_name}.fromMap(boost::any_cast<map<string, boost::any>>(${name}));`, this.level);
        if (isProp) {
          this.emitFromMapItem(emitter, _avoidKeywords(prop.name), prop.type, var_name, parent_type, layer);
        } else {
          if (is.array(parent_type)) {
            emitter.emitln(`${realkey}.push_back(${var_name});`, this.level);
          } else {
            emitter.emitln(`${realkey} = ${var_name};`, this.level);
          }
        }
        this.levelDown();
        emitter.emitln('}', this.level);
      } else {
        // type is client
        debug.warning('sub item type is client : ' + prop.name);
      }
    } else if (is.base(prop.type)) {
      if (isProp) {
        this.emitFromMapItem(emitter, _avoidKeywords(prop.name), prop.type, name);
      } else {
        this.emitFromMapItem(emitter, realkey, prop.type, name, parent_type, layer);
      }
    } else {
      debug.warning('unsupported type fromMap()', prop);
    }
    if (isProp) {
      this.levelDown();
      emitter.emitln('}', this.level);
    }
  }

  emitFromMap(emitter, props, notes) {
    let nameMap = _names(notes);
    emitter.emitln('void fromMap(map<string, boost::any> m) override {', this.level);
    this.levelUp();
    props.forEach(prop => {
      let name = typeof nameMap[prop.name] !== 'undefined' ? nameMap[prop.name] : prop.name;
      this.emitFromMapProp(emitter, `m["${name}"]`, prop, name);
    });
    this.levelDown();
    emitter.emitln('}', this.level);
    emitter.emitln();
  }

  emitParams(emitter, params = []) {
    let tmp = [];
    params.forEach(param => {
      if (is.any(param.type)) {
        tmp.push(`const boost::any &${_avoidKeywords(param.key)}`);
        this.addStatement(param.key, param.type, false);
      } else {
        tmp.push(`shared_ptr<${this.emitType(param.type)}> ${_avoidKeywords(param.key)}`);
        this.addStatement(param.key, param.type, true);
      }
    });
    let emit = new Emitter(this.config);
    let str;
    if (tmp.length > 3) {
      let curr_row_len = emitter.currRow().length;
      str = tmp.join(`,${emit.eol}${' '.repeat(curr_row_len)}`);
    } else {
      str = tmp.join(', ');
    }
    if (emitter instanceof Emitter) {
      emitter.emit(str);
    }
    return str;
  }

  emitType(type, autoPtr = false) {
    if (!is.type(type)) {
      debug.stack('Inavalid type', type);
    }
    let type_str = null;
    if (is.any(type)) {
      this.pushInclude('boost_any');
      type_str = 'boost::any';
    } else if (is.decimal(type)) {
      type_str = 'double';
    } else if (is.integer(type)) {
      type_str = type.length > 16 ? 'long' : 'int';
    } else if (is.number(type)) {
      type_str = 'int';
    } else if (is.string(type)) {
      this.pushInclude('iostream');
      type_str = 'string';
    } else if (is.bytes(type)) {
      this.pushInclude('vector');
      type_str = 'vector<uint8_t>';
    } else if (is.array(type)) {
      let subType = this.emitType(type.itemType);
      this.pushInclude('vector');
      type_str = `vector<${subType}>`;
    } else if (is.bool(type)) {
      type_str = 'bool';
    } else if (is.void(type)) {
      type_str = 'void';
    } else if (is.map(type)) {
      this.pushInclude('map');
      type_str = `map<${this.emitType(type.keyType)}, ${this.emitType(type.valType)}>`;
    } else if (is.stream(type)) {
      type_str = this.addInclude('$Stream');
    } else if (is.object(type)) {
      type_str = !type.objectName ? 'void' : this.resolveName(type.objectName);
    } else if (is.null(type)) {
      type_str = 'nullptr';
    }
    if (type_str === null) {
      debug.stack('Unsupported Type', type);
    }
    if (autoPtr && this.isPointerType(type)) {
      type_str = `shared_ptr<${type_str}>`;
    }
    return type_str;
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
      let tmp = [];
      node.params.forEach(param => {
        tmp.push(`const shared_ptr<${this.emitType(param.type)}>& ${_avoidKeywords(param.key)}`);
        this.addStatement(param.key, param.type, true);
      });
      let emit = new Emitter(this.config);
      let str;
      if (tmp.length > 3) {
        let curr_row_len = emitter.currRow().length;
        str = tmp.join(`,${emit.eol}${' '.repeat(curr_row_len)}`);
      } else {
        str = tmp.join(', ');
      }
      if (emitter instanceof Emitter) {
        emitter.emit(str);
      }
      emitter.emit(')', this.level);
      if (hasSuper) {
        let tmp = [];
        node.params.forEach(p => {
          tmp.push(p.key);
        });
        emitter.emit(` : ${this.resolveName(this.object.extends[0])}(${tmp.join(', ')})`);
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
    let func_name = _avoidKeywords(func.name);
    if (this.config.exec) {
      emitter.emitln(`int ${func_name}(int argc, char *argv[]) {`);
      this.levelUp();
      emitter.emitln('argv++;', this.level);
    } else {
      if (func.params.length) {
        emitter.emit(`${this.emitType(func.return[0], true)} ${this.namespace}::Client::${func_name}(`);
        this.emitParams(emitter, func.params);
        emitter.emit(')');
      } else {
        emitter.emit(`${this.emitType(func.return[0], true)} ${this.namespace}::Client::${func_name}()`);
      }
      emitter.emitln(' {');
      this.levelUp();
    }

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
    let client_name = prop.objectName ? prop.objectName : prop.type.objectName;
    client_name = this.resolveName(client_name);
    if (client_name && client_name.indexOf('Client') < 0) {
      return false;
    }
    let is = false;
    Object.keys(this.thirdPackageDaraMeta).forEach(key => {
      const item = this.thirdPackageDaraMeta[key];
      let namespace = `${_upperFirst(_name(item.scope))}_${_upperFirst(_name(item.name))}::Client`;
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

  isPointerPath(lastPathIndex, paths) {
    const lastPath = paths[lastPathIndex];
    if (lastPath.type === 'object') {
      let name = _name(lastPath.name);
      return this.isPtrStatement(name);
    } else if (lastPath.type === 'parent') {
      return true;
    }
    if (lastPath.type === 'prop') {
      if (lastPathIndex > 0) {
        let parentPath = paths[lastPathIndex - 1];
        if (parentPath.type === 'object') {
          let parentType = this.getStatementType(_name(parentPath.name));
          if (parentType.objectName === '$Request' || parentType.objectName === '$Response') {
            if (lastPath.name === 'body') {
              return true;
            }
            return false;
          }
        }
      }
      return true;
    }
    return false;
  }

  isUnsetMethod(gram) {
    return gram.type === 'sys_func'
      && gram.path[0].name === '^Util'
      && gram.path[1].name === 'isUnset';
  }

  useTmplMethod(gram) {
    const useTmplMethods = ['isUnset', 'toArray'];
    return gram.type === 'sys_func'
      && gram.path[0].name === '^Util'
      && _contain(useTmplMethods, gram.path[1].name);
  }

  resolveCallPath(paths, params = '', gram) {
    let prefix = '';
    let lastPathIndex = -1;

    paths.forEach((path, i) => {
      let pathName = typeof path.name === 'string' ? path.name.replace('@', '_') : `${path.name}`;
      pathName = _name(pathName);
      if (path.type === 'parent') {
        if (paths[i + 1] && _contain(paths[i + 1].type, 'static')) {
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
      } else if (path.type === 'object' || path.type === 'object_static') {
        prefix += this.resolveName(pathName);
      } else if (path.type === 'call') {
        let isPointer = this.isPointerPath(lastPathIndex, paths);
        prefix += isPointer ? `->${pathName}(${params})` : `.${pathName}(${params})`;
      } else if (path.type === 'call_static') {
        if (this.useTmplMethod(gram)) {
          prefix += `::${pathName}<${this.emitType(gram.params[0].dataType)}>(${params})`;
        } else {
          prefix += `::${pathName}(${params})`;
        }
      } else if (path.type === 'prop') {
        let isPointer = this.isPointerPath(lastPathIndex, paths);
        prefix += isPointer ? `->${pathName}` : `.${pathName}`;
      } else if (path.type === 'prop_static') {
        prefix += `::${pathName}`;
      } else if (path.type === 'map') {
        let isPointer = this.isPointerPath(lastPathIndex, paths);
        let path_name;
        if (path.isVar) {
          let varIsPointer = this.isPtrStatement(pathName);
          if (varIsPointer) {
            path_name = `*${pathName}`;
          } else {
            path_name = pathName;
          }
        } else {
          path_name = `"${pathName}"`;
        }
        if (isPointer) {
          prefix = `(*${prefix})[${path_name}]`;
        } else {
          prefix += `[${path_name}]`;
        }
      } else if (path.type === 'list') {
        let isPointer = this.isPointerPath(lastPathIndex, paths);
        let path_name = pathName;
        if (path.isVar) {
          let varIsPointer = this.isPtrStatement(pathName);
          if (varIsPointer) {
            path_name = `*${pathName}`;
          } else {
            path_name = pathName;
          }
        }
        if (isPointer) {
          prefix = `(*${prefix})[${path_name}]`;
        } else {
          prefix += `[${path_name}]`;
        }
      } else {
        debug.stack(paths);
      }
      lastPathIndex = i;
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
    if (gram.returnType) {
      expectedType = gram.returnType;
    } else if (gram.dataType) {
      expectedType = gram.dataType;
    } else if (gram.type instanceof TypeItem) {
      expectedType = gram.type;
    } else if (gram.type === 'call') {
      expectedType = gram.value.returnType;
    }
    if (expectedType === null) {
      return null;
    }
    return this.emitType(expectedType);
  }

  resolveName(name, _avoidKeywords = true) {
    name = super.resolveName(name, _avoidKeywords);
    if (_contain(name, '.')) {
      name = name.split('.').map(s => _upperFirst(s)).join('');
    }
    return name;
  }

  isPointerType(type) {
    if (is.stream(type)) {
      return true;
    }
    return false;
  }

  isPointerVar(gram, ignore_to_map = false) {
    if (gram instanceof GrammerValue) {
      if (gram.type === 'null') {
        return false;
      }
    }
    let grammerVar;
    if (gram instanceof GrammerVar) {
      grammerVar = gram;
    }
    if (gram instanceof GrammerValue) {
      if (gram.type === 'var' && gram.value instanceof GrammerVar) {
        grammerVar = gram.value;
      } else if (gram.type === 'call' && gram.value instanceof GrammerCall) {
        grammerVar = gram.value;
      } else if (ignore_to_map && gram.type === 'behavior' && gram.value instanceof BehaviorToMap) {
        grammerVar = gram.value.grammer;
      }
    }
    if (grammerVar && grammerVar instanceof GrammerVar) {
      let name = grammerVar.name ? _name(grammerVar.name) : '';
      if (this.isPtrStatement(name)) {
        return true;
      }
    } else if (grammerVar instanceof GrammerCall) {
      return this.isPointerPath(grammerVar.path.length - 1, grammerVar.path);
    }
    return false;
  }

  addStatement(name, type, pointer = null) {
    if (null === pointer) {
      pointer = this.isPointerType(type);
    }
    statements[name] = { type, pointer };
  }

  isPtrStatement(name) {
    return statements[name] && statements[name].pointer;
  }

  hasStatement(name) {
    return !statements[name] ? false : true;
  }

  getStatementType(name) {
    if (!statements[name]) {
      debug.stack('Undefined statement!', name, statements);
    }
    return statements[name].type;
  }

  /**************************************** grammer ****************************************/
  grammerVar(emitter, gram, emitType = true) {
    let name = gram.name ? gram.name : gram.key;
    name = _name(name);
    if (gram.varType === 'static_class') {
      emitter.emit(`${name}::class`);
    } else if (gram.varType === 'var' || gram.varType === 'const') {
      if (!this.hasStatement(name) && emitType) {
        emitter.emit(`shared_ptr<${this.emitType(gram.type)}> ${name}`);
        this.addStatement(name, gram.type, true);
      } else {
        emitter.emit(`${name}`);
      }
      if (!this.hasStatement(name)) {
        this.addStatement(name, gram.type);
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

    if (!Array.isArray(gram.value) && !(gram.value instanceof GrammerValue)) {
      this.grammer(emitter, gram.value, false, false);
      return;
    }
    items = gram.value.filter(i => !i.isExpand);
    expandItems = gram.value.filter(i => i.isExpand);

    if (!items.length && !expandItems.length) {
      emitter.emit(`map<${keyType}, ${valType}>()`);
      return;
    }
    let needCast = gram.needCast;
    if (needCast) {
      this.pushInclude('darabonba_core');
      emitter.emit(`${this.config.tea.converter.name}::merge(`);
    }
    if (!items.length && expandItems.length) {
      emitter.emit(`map<${keyType}, ${valType}>(), `);
    }

    // emit map
    if (items.length) {
      if (gram.needCast || layer !== 0) {
        emitter.emitln(`map<${keyType}, ${valType}>({`);
      } else {
        if (this.exprIsAssignToPtr) {
          emitter.emitln(`map<${keyType}, ${valType}>({`);
        } else {
          emitter.emitln('{');
        }
      }
      this.levelUp();
      items.forEach((item, i) => {
        if (item instanceof AnnotationItem) {
          this.emitAnnotation(emitter, item);
          return;
        }
        emitter.emit(`{"${item.key}", `, this.level);
        let isAny = is.any(gram.dataType.valType);
        if (this.isPointerVar(item)) {
          let emit = new Emitter(this.config);
          this.grammerValue(emit, item, layer + 1);
          let emitItem = emit.output;
          if (isAny) {
            emitter.emit(`!${emitItem} ? boost::any() : boost::any(*${emitItem})`);
          } else {
            emitter.emit(`!${emitItem} ? ${this.emitType(gram.dataType.valType)}() : *${emitItem}`);
          }
        } else {
          if (isAny) {
            if (is.any(item.dataType)) {
              this.grammerValue(emitter, item, layer + 1);
            } else {
              emitter.emit('boost::any(');
              if (is.string(item.dataType)) {
                if (item.type === 'behavior' && item.value instanceof BehaviorTamplateString) {
                  this.grammerValue(emitter, item, layer + 1);
                } else {
                  emitter.emit('string(');
                  this.grammerValue(emitter, item, layer + 1);
                  emitter.emit(')');
                }
              } else {
                this.grammerValue(emitter, item, layer + 1);
              }
              emitter.emit(')');
            }
          } else {
            this.grammerValue(emitter, item, layer + 1);
          }
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
        if (this.exprIsAssignToPtr) {
          emitter.emitln('})', this.level);
        } else {
          emitter.emit('}', this.level);
        }
      }
      if (expandItems.length) {
        emitter.emit(', ');
      }
    }
    if (expandItems.length) {
      let tmp = [];
      expandItems.forEach(item => {
        let emit = new Emitter(this.config);
        let needConvertMap = is.map(item.dataType) && is.any(gram.dataType.valType) && !is.any(item.dataType.valType);
        if (needConvertMap) {
          emit.emit(`${this.config.tea.converter.name}::toGenericMap(`);
        }
        if (this.isPointerVar(item)) {
          let varEmit = new Emitter(this.config);
          this.grammer(varEmit, item, false, false);
          let var_name = varEmit.output;
          let type_name = this.resolveDataType(item);
          if (is.object(item.dataType)) {
            type_name = `map<${keyType}, ${valType}>`;
          }
          emit.emit(`!${var_name} ? ${type_name}() : ${is.object(item.dataType) ? `${var_name}.toMap()` : `*${var_name}`}`);
        } else if (item.type === 'var') {
          this.grammer(emit, item, false, false);
        } else if (item.type === 'call') {
          this.grammer(emit, item, false, false);
        } else {
          emit.emit(`map<${keyType}, ${valType}>(`);
          this.grammer(emit, item, false, false);
          emit.emit(')');
        }
        if (needConvertMap) {
          emit.emit(')');
        }
        tmp.push(emit.output);
      });
      emitter.emit(tmp.join(', '));
    }

    if (needCast) {
      // emitter.emit('))');
      emitter.emit(')'); // close converter merge method
    }
  }

  grammerValue(emitter, gram, layer = 0) {
    if (is.annotation(gram)) {
      this.emitAnnotation(emitter, gram);
      return;
    }
    if (gram.type === 'map' || gram.type === 'model_construct_params') {
      if (gram.type === 'model_construct_params' && this.emitType(gram.dataType) !== 'map<string, boost::any>') {
        gram.dataType = new TypeMap(
          new TypeString(), new TypeGeneric()
        );
      }
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
        emitter.emit(`vector<${itemType}>()`);
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
        gram.params.forEach(p => {
          let emit = new Emitter(this.config);
          let isUnsetMethod = this.isUnsetMethod(gram);
          if (p.value instanceof BehaviorToMap && gram.type === 'sys_func' && isUnsetMethod) {
            let isPointer = this.isPointerVar(p, true);
            if (!isPointer) {
              emit.emit(this.emitMakeShared(p.dataType, p.value.grammer));
            } else {
              this.grammer(emit, p.value.grammer, false, false);
            }
            tmp.push(emit.output);
          } else if (p.value instanceof BehaviorToMap && gram.type === 'sys_func') {
            tmp.push(this.emitMakeShared('map<string, boost::any>', p));
          } else if (gram.type === 'sys_func' && isUnsetMethod) {
            this.grammer(emit, p, false, false);
            tmp.push(emit.output);
          } else if (gram.type === 'sys_func') {
            if (!this.isPointerVar(p)) {
              emit.emit(this.emitMakeShared(p.dataType, p));
            } else {
              this.grammer(emit, p, false, false);
            }
            tmp.push(emit.output);
          } else if (p instanceof GrammerVar && p.type.objectName === '$Exception') {
            this.grammer(emit, p, false, false);
            tmp.push(`${emit.output}`);
          } else if (p instanceof GrammerValue && p.type === 'map' && p.needCast) {
            this.pushInclude('darabonba_core');
            emit.emit(`${this.config.tea.converter.name}::mapPointer(`);
            this.grammerValue(emit, p);
            emit.emit(')');
            tmp.push(emit.output);
          } else if (p.type === 'var' && is.object(p.value.type) && p.value.varType === 'static_class') {
            tmp.push('nullptr');
          } else if (p.type === 'param') {
            if (this.isPtrStatement(p.value)) {
              tmp.push(p.value);
            } else {
              tmp.push(this.emitMakeShared(p.dataType, p.value));
            }
          } else if (!this.isPointerVar(p)) {
            this.grammer(emit, p, false, false);
            let dataType = this.resolveDataType(p);
            if (is.stream(p.dataType)) {
              tmp.push(emit.output);
            } else if (p.type === 'behavior' && p.value instanceof BehaviorToMap) {
              tmp.push(this.emitMakeShared('map<string, boost::any>', emit.output));
            } else if (!this.isPointerVar(p)) {
              tmp.push(this.emitMakeShared(dataType, emit.output));
            } else {
              tmp.push(emit.output);
            }
          } else {
            this.grammerValue(emit, p);
            tmp.push(emit.output);
          }
        });
        params = tmp.join(', ');
        emitter.emit(this.resolveCallPath(gram.path, params, gram));
      } else {
        emitter.emit(this.resolveCallPath(gram.path, params, gram));
      }
    } else if (gram.type === 'prop') {
      emitter.emit(this.resolveCallPath(gram.path, '', gram));
    } else if (gram.type === 'key') {
      emitter.emit(this.resolveCallPath(gram.path, '', gram));
    } else {
      debug.stack(gram);
    }
  }

  grammerExpr(emitter, gram) {
    if (gram.opt === Symbol.concat()) {
      // implement by behaviorTamplateString
      debug.stack(gram);
    }
    this.exprIsAssignToPtr = this.isPointerVar(gram.left);
    if (!gram.left && !gram.right) {
      // only emit symbol
      emitter.emit(` ${_symbol(gram.opt)} `);
      this.exprIsAssignToPtr = null;
      return;
    }
    // emit left of expr
    if (gram.opt !== Symbol.assign() && this.exprIsAssignToPtr) {
      emitter.emit('*');
    }
    this.grammer(emitter, gram.left, false, false);

    if (gram.right.type === 'null') {
      // not emit symbol&right if right of expr is null
      this.exprIsAssignToPtr = null;
      if (gram.left instanceof GrammerVar) { return; }
    }

    // emit right of expr
    if (gram.opt === Symbol.assign()) {
      let isNewObject = false;
      let right = null;
      if (gram.right instanceof GrammerValue && gram.right.type === 'instance' && gram.right.value instanceof GrammerNewObject) {
        isNewObject = true;
        right = gram.right.value;
      } else if (gram.right instanceof GrammerNewObject) {
        isNewObject = true;
        right = gram.right;
      }
      if (isNewObject) {
        this.exprIsAssignToPtr = this.isPointerVar(gram.left);
        // is new object
        if (this.isPointerVar(gram.left)) {
          // new object to ptr property
          emitter.emit(` ${_symbol(gram.opt)} `); // emit symbol of expr
          this.grammerNewObject(emitter, right, true, true);
          this.exprIsAssignToPtr = null;
          return;
        }
        this.grammerNewObject(emitter, right, false);
        this.exprIsAssignToPtr = null;
        return;
      }
      emitter.emit(` ${_symbol(gram.opt)} `); // emit symbol of expr
      let toStream = false;
      if (gram.left instanceof GrammerValue && gram.left.type === 'call' && gram.left.value.path[1].name === 'body') {
        const k = gram.left.value.path.map(item => item.name).join('.');
        toStream = k === '__request.body' && is.string(gram.right.dataType);
      }
      if (toStream) {
        emitter.emit(`${this.config.tea.converter.name}::toStream(`);
      }

      if (!toStream && this.isPointerVar(gram.left) && !this.isPointerVar(gram.right)) {
        let dataType = this.resolveDataType(gram.right);
        if (dataType === null) {
          dataType = this.resolveDataType(gram.left);
        }
        if (this.isPointerType(gram.right.dataType)) {
          this.grammer(emitter, gram.right, false, false);
        } else {
          this.exprIsAssignToPtr = this.isPointerVar(gram.left);
          emitter.emit(this.emitMakeShared(dataType, gram.right));
        }
      } else if (!this.isPointerVar(gram.left) && this.isPointerVar(gram.right)) {
        emitter.emit('*');
        this.grammer(emitter, gram.right, false, false);
      } else if (this.isPointerVar(gram.left) && this.isPointerVar(gram.right)) {
        if (toStream) {
          emitter.emit('*');
        }
        this.grammer(emitter, gram.right, false, false);
      } else {
        this.grammer(emitter, gram.right, false, false);
      }
      if (toStream) {
        emitter.emit(')');
      }
      this.exprIsAssignToPtr = null;
      return;
    }
    emitter.emit(` ${_symbol(gram.opt)} `); // emit symbol of expr
    this.grammer(emitter, gram.right, false, false);
    this.exprIsAssignToPtr = null;
  }

  grammerLoop(emitter, gram) {
    this.pushInclude('algorithm');
    if (gram.type === 'foreach') {
      emitter.emit('for(auto ');
      this.grammerVar(emitter, gram.item, false, false);
      emitter.emit(' : ');
      if (this.isPointerVar(gram.source)) {
        emitter.emit('*');
      }
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
    this.addStatement(varName, gram.exceptions.type, false);
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
    emitter.emit('BOOST_THROW_EXCEPTION(');
    // emit exception_begin
    if (gram.exception) {
      let isException = is.object(gram.exception) && gram.exception.objectName === '$Exception';
      if (isException) {
        emitter.emit('std::runtime_error(');
      } else {
        emitter.emit(`${this.emitType(gram.exception)}(`);
      }
    }

    // emit exception_body
    if (!gram.params.length) {
      let msg = gram.message ? `"${gram.message}"` : '';
      emitter.emit(msg);
    } else if (gram.params.length === 1) {
      let isError = is.object(gram.exception) && gram.exception.objectName === '$Error';
      if (isError) {
        let dataType = this.resolveDataType(gram.params[0]);
        emitter.emit(`${dataType}(`);
        this.grammerValue(emitter, gram.params[0]);
        emitter.emit(')');
      } else {
        this.grammerValue(emitter, gram.params[0]);
      }
    } else {
      let tmp = [];
      gram.params.forEach(p => {
        let emit = new Emitter(this.config);
        this.grammerValue(emit, p);
        tmp.push(emit.output);
      });
      emitter.emit(tmp.join(', '));
    }

    // emit exception_end
    if (gram.exception) {
      emitter.emit(')');
    }

    emitter.emit(')'); // close BOOST_THROW_EXCEPTION
  }

  grammerNewObject(emitter, gram, isAssign = true, isPtrParam = false) {
    let objectName = gram.name;
    if (!this.exprIsAssignToPtr && isAssign) {
      emitter.emit(`${this.resolveName(objectName)}(`);
    } else if (isAssign) {
      emitter.emit(`make_shared<${this.resolveName(objectName)}>(`);
    }
    let tmp = [];
    let params;
    if (Array.isArray(gram.params)) {
      params = gram.params;
    } else {
      params = [gram.params];
    }
    if (params.length) {
      params.forEach(p => {
        if (p instanceof GrammerValue && p.type === 'model_construct_params' && !p.value.length) {
          return;
        } else if (p instanceof GrammerValue && p.type === 'model_construct_params') {
          isPtrParam = false;
        }
        let emit = new Emitter(this.config);
        if (isPtrParam && !this.isPointerVar(p)) {
          emit.emit(this.emitMakeShared(p.dataType ? p.dataType : p.type, p));
        } else {
          this.grammerValue(emit, p, false, false);
        }
        tmp.push(emit.output);
      });
      // emitter.emit(tmp.join(', '));
    }
    if (isAssign) {
      emitter.emit(tmp.join(', '));
      emitter.emit(')');
    } else if (tmp.length) {
      emitter.emit('(');
      emitter.emit(tmp.join(', '));
      emitter.emit(')');
    }
  }

  grammerReturn(emitter, gram) {
    if (is.void(this.funcReturnType)) {
      emitter.emit('return');
      return;
    }
    emitter.emit('return ');
    if (gram.type === 'null') {
      this.grammerValue(emitter, new GrammerValue('null'), false, false);
    } else if (gram.type === 'grammer') {
      let returnPointer = this.isPointerType(this.funcReturnType);
      if (this.isPointerVar(gram.expr) && !returnPointer) {
        emitter.emit('*');
      }
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
    emitter.emit(` = make_shared<${this.addInclude('$Response')}>(${this.addInclude('$Core')}::${this.config.tea.core.doAction}(`);
    let params = [];
    behavior.params.forEach(p => {
      let emit = new Emitter(this.config);
      if (this.isPointerVar(p)) {
        emit.emit('*');
      }
      this.grammerValue(emit, p);
      params.push(emit.output);
    });
    emitter.emit(params.join(', '));
    emitter.emitln('));');
    behavior.body.forEach(node => {
      this.grammer(emitter, node);
    });
  }

  behaviorToMap(emitter, behavior) {
    const grammer = behavior.grammer;
    if (grammer instanceof GrammerCall) {
      grammer.path.push({
        type: 'call',
        name: 'toMap'
      });
      this.grammerCall(emitter, grammer);
    } else if (grammer instanceof GrammerVar) {
      const grammerCall = new GrammerCall('method');
      grammerCall.path.push({
        type: 'object',
        name: grammer.name
      });
      grammerCall.path.push({
        type: 'call',
        name: 'toMap'
      });
      this.grammerCall(emitter, grammerCall);
    } else {
      debug.stack(grammer);
    }
  }

  behaviorToModel(emitter, behavior) {
    emitter.emit(`${behavior.expected}(`);
    let type = this.resolveDataType(behavior.grammer);
    if (type === 'map<string, string>') {
      emitter.emit(`${this.config.tea.converter.name}::toGenericMap(`);
      this.grammer(emitter, behavior.grammer, false, false);
      emitter.emit(')');
    } else {
      behavior.grammer.type = 'model_construct_params';
      this.grammer(emitter, behavior.grammer, false, false);
    }
    emitter.emit(')');
  }

  behaviorSetMapItem(emitter, behavior) {
    let emit = new Emitter(this.config);
    this.grammerCall(emit, behavior.call);
    this.pushInclude('map');
    let paths = behavior.call.path;
    if (this.isPointerPath(paths.length - 1, paths)) {
      emitter.emit(`${emit.output}->insert(pair<string, ${this.emitType(behavior.value.dataType)}>("${behavior.key}", `, this.level);
    } else {
      emitter.emit(`${emit.output}.insert(pair<string, ${this.emitType(behavior.value.dataType)}>("${behavior.key}", `, this.level);
    }
    if (this.isPointerVar(behavior.value)) {
      emitter.emit('*');
    }
    this.grammerValue(emitter, behavior.value);
    emitter.emitln('));');
  }

  behaviorRetry(emitter, behavior) {
    emitter.emitln(`throw ${this.addInclude('$Error')}(${this.config.request}, ${this.config.response});`, this.level);
  }

  behaviorTamplateString(emitter, behavior) {
    let tmp = [];
    behavior.items.forEach(item => {
      let emit = new Emitter(this.config);
      if (this.isPointerVar(item)) {
        emit.emit('*');
      }
      if (is.string(item.dataType)) {
        this.grammer(emit, item, false, false);
      } else if (is.any(item.dataType)) {
        this.pushInclude('darabonba_core');
        emit.emit(`${this.config.tea.converter.name}::toString(`);
        this.grammer(emit, item, false, false);
        emit.emit(')');
      } else {
        this.pushInclude('cast');
        emit.emit('boost::lexical_cast<string>(');
        this.grammer(emit, item, false, false);
        emit.emit(')');
      }
      tmp.push(emit.output);
    });
    emitter.emit(`${tmp.filter(s => s !== '""').map(s => `string(${s})`).join(' + ')}`);
  }
}
module.exports = Combinator;