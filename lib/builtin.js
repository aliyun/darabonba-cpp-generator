'use strict';
const DSL = require('@darabonba/parser');
const  { _vid, _name, _string, CORE, _getInclude } = require('./helper');

const types = [
  'integer', 'int8', 'int16', 'int32', 
  'int64', 'long', 'ulong', 'string',
  'uint8', 'uint16', 'uint32', 'uint64',
  'number', 'float', 'double', 'boolean',
  'bytes', 'readable', 'writable', 'object', 'any'
];

const integers = [
  'integer', 'int8', 'int16', 'int32', 
  'int64', 'long', 'ulong',
  'uint8', 'uint16', 'uint32', 'uint64'
];

const floats = ['float', 'double'];

class Builtin {
  constructor(generator, module = '', methods = []){
    this.generator = generator;
    this._moduleInfo = _getInclude(module);
    this.module = this._moduleInfo.className;

    methods.forEach(method => {
      this[method] = function(args, level) {
        this.generator.headers.push(this._moduleInfo.header);
        this.generator.emit(`${this.module}::${method}`);
        this.generator.visitArgs(args, level);
      };
    });
  }

  

  getInstanceName(ast) {
    if (ast.left.id.tag === DSL.Tag.Tag.VID) {
      this.generator.emit(`this->${_vid(ast.left.id)}`);
    } else {
      this.generator.emit(`${_name(ast.left.id)}`);
    }
  }

  getClassName(){
    this.generator.headers.push(this._moduleInfo.header);
    return this.module;
  }
}

class Env extends Builtin {
  constructor(generator){
    const methods = [];
    super(generator, 'DaraEnv', methods);
  }

  get(args){
    const key = args[0];
    this.generator.emit('std::getenv(');
    this.generator.visitExpr(key);
    this.generator.emit(')');
  }

  set(args){
    this.generator.emit('Darabonba::Env::setEnv');
    this.generator.visitArgs(args);
  }
}

class Logger extends Builtin {
  constructor(generator){
    const methods = ['log', 'info', 'debug', 'error', 'warning'];
    super(generator, 'DaraLogger', methods);
    methods.forEach(method => {
      this[method] = function(args, level) {
        this.generator.headers.push(this._moduleInfo.header);
        this.generator.used.push('using DaraLogger = Darabonba::Logger;');
        this.generator.emit(`DaraLogger::${method}`);
        this.generator.visitArgs(args, level);
      };
    });
  }
}

class XML extends Builtin {
  constructor(generator){
    const methods = ['parseXml', 'toXML'];
    super(generator, 'DaraXML', methods);
  }
}

class URL extends Builtin {
  constructor(generator){
    const methods = ['parse', 'urlEncode', 'pathEncode'];
    super(generator, 'DaraURL', methods);
  }

  percentEncode(args, level) {
    this.generator.headers.push('darabonba/encode/Encoder.hpp');
    this.generator.emit('Darabonba::Encode::Encoder::percentEncode');
    this.generator.visitArgs(args, level);
  }
}

class Stream extends Builtin {
  constructor(generator){
    const methods = ['readAsBytes', 'readAsJSON', 'readAsString', 'readAsSSE'];
    super(generator, 'DaraStream', methods);
  }
}

class Number extends Builtin {
  constructor(generator){
    const methods = ['random'];
    super(generator, 'DaraNumber', methods);

  }

  floor(args) {
    const key = args[0];
    this.generator.headers.push('cmath');
    this.generator.emit('std::floor(');
    this.generator.visitExpr(key);
    this.generator.emit(')');
  }

  round(args) {
    const key = args[0];
    this.generator.headers.push('cmath');
    this.generator.emit('std::round(');
    this.generator.visitExpr(key);
    this.generator.emit(')');
  }

  min(args) {
    this.generator.headers.push('cmath');
    this.generator.emit('std::min');
    this.generator.visitArgs(args);
  }

  max(args) {
    this.generator.headers.push('cmath');
    this.generator.emit('std::max');
    this.generator.visitArgs(args);
  }

  parseInt(ast) {
    this.generator.emit(`${this.getClassName()}::parseInt(`);
    this.getInstanceName(ast);
    this.generator.emit(')');
  }

  parseLong(ast) {
    this.generator.emit(`${this.getClassName()}::parseLong(`);
    this.getInstanceName(ast);
    this.generator.emit(')');
  }

  parseFloat(ast) {
    this.generator.emit(`${this.getClassName()}::parseFloat(`);
    this.getInstanceName(ast);
    this.generator.emit(')');
  }

  parseDouble(ast) {
    this.generator.emit(`${this.getClassName()}::parseDouble(`);
    this.getInstanceName(ast);
    this.generator.emit(')');
  }

  itol(ast) {
    this.generator.emit(`${this.getClassName()}::itol(`);
    this.getInstanceName(ast);
    this.generator.emit(')');
  }

  ltoi(ast) {
    this.generator.emit(`${this.getClassName()}::ltoi(`);
    this.getInstanceName(ast);
    this.generator.emit(')');
  }
}

class JSON extends Builtin {
  constructor(generator){
    const methods = [];
    super(generator, 'DaraJSON', methods);
  }

  parseJSON(args) {
    this.generator.emit('json::parse');
    this.generator.visitArgs(args);
  }

  stringify(args) {
    const expr = args[0];
    let needCast = true;
    if(expr.inferred) {
      if (expr.inferred.type === 'map') {
        if(expr.inferred.valueType.type === 'basic' && expr.inferred.valueType.name === 'any'){
          needCast = false;
        } 
      } else if((expr.inferred.type || expr.inferred.name) === 'any'){
        needCast = false;
      }
    }
    if(needCast) {
      this.generator.emit('json(');
    }
    this.generator.visitExpr(expr);
    if(needCast) {
      this.generator.emit(')');
    }
    this.generator.emit('.dump()');
  }

}

class Form extends Builtin {
  constructor(generator){
    const methods = ['toFormString', 'getBoundary', 'toFileForm'];
    super(generator, 'DaraForm', methods);
  }
}

class File extends Builtin {
  constructor(generator){
    const methods = ['createReadStream', 'createWriteStream', 'exists'];
    super(generator, 'DaraFile', methods);
  }
}

class Date extends Builtin {
  constructor(generator){
    const methods = [];
    super(generator, 'DaraDate', methods);
  }
}

class Bytes extends Builtin {
  constructor(generator){
    const methods = [];
    super(generator, 'DaraBytes', methods);
  }

  from(args, level){
    this.generator.headers.push('darabonba/Bytes.hpp');
    this.generator.emit('Darabonba::BytesUtil::from');
    this.generator.visitArgs(args);
  }

  toString(ast, level){ 
    this.generator.emit(`${this.module}::toString(`);
    this.getInstanceName(ast);
    this.generator.emit(')');
  }

  toHex(ast, level){ 
    this.generator.emit(`${this.module}::hexEncode(`);
    this.getInstanceName(ast);
    this.generator.emit(')');
  }

  toBase64(ast, level){ 
    this.generator.emit(`${this.module}::base64EncodeToString(`);
    this.getInstanceName(ast);
    this.generator.emit(')');
  }

  toJSON(ast, level) {
    this.toString(ast, level);
  }

  length(ast){ 
    this.getInstanceName(ast);
    this.generator.emit('.size()');
  }
}


class Converter {
  constructor(generator){
    this.generator = generator;
    integers.forEach(type => {
      this[type] = function(args) {
        const expr = args[0];
        generator.headers.push('darabonba/Convert.hpp');
        generator.emit(`${CORE}::Convert::${type}Val(`);
        generator.visitExpr(expr);
        generator.emit(')');
      };
    });

    floats.forEach(type => {
      this[type] = function(args) {
        generator.headers.push('darabonba/Convert.hpp');
        const expr = args[0];
        generator.emit(`${CORE}::Convert::${type}Val(`);
        generator.visitExpr(expr);
        generator.emit(')');
      };
    });
  }

  string(args) {
    const expr = args[0];
    this.generator.headers.push('darabonba/Convert.hpp');
    this.generator.emit(`${CORE}::Convert::stringVal(`);
    this.generator.visitExpr(expr);
    this.generator.emit(')');
  }

  number(args) {
    const expr = args[0];
    this.generator.headers.push('darabonba/Convert.hpp');
    this.generator.emit(`${CORE}::Convert::int64Val(`);
    this.generator.visitExpr(expr);
    this.generator.emit(')');
  }

  boolean(args) {
    const expr = args[0];
    this.generator.headers.push('darabonba/Convert.hpp');
    this.generator.emit(`${CORE}::Convert::boolVal(`);
    this.generator.visitExpr(expr);
    this.generator.emit(')');
  }

  bytes(args) {
    const expr = args[0];
    this.generator.headers.push('darabonba/Bytes.hpp');
    this.generator.emit(`${CORE}::BytesUtil::toBytes(`);
    this.generator.visitExpr(expr);
    this.generator.emit(')');
  }

  any(args){
    const expr = args[0];
    this.generator.emit('json(');
    this.generator.visitExpr(expr);
    this.generator.emit(')');
  }

  object(args){
    const expr = args[0];
    let needCast = true;
    if(expr.inferred) {
      if (expr.inferred.type === 'map') {
        if(expr.inferred.valueType.type === 'basic' && expr.inferred.valueType.name === 'any'){
          needCast = false;
        } 
      } else if((expr.inferred.type || expr.inferred.name) === 'any'){
        needCast = false;
      }
    }
    if(needCast) {
      this.generator.emit('json(');
    }
    this.generator.visitExpr(expr);
    if(needCast) {
      this.generator.emit(')');
    }
  }

  readable(args){
    const expr = args[0];
    const steamInfo = _getInclude('DaraStream');
    this.generator.headers.push(steamInfo.header);
    this.generator.emit(`${steamInfo.className}::toReadable(`);
    this.generator.visitExpr(expr);
    this.generator.emit(')');
  }

  writable(args){
    const expr = args[0];
    const steamInfo = _getInclude('DaraStream');
    this.generator.headers.push(steamInfo.header);
    this.generator.emit(`${steamInfo.className}::toWritable(`);
    this.generator.visitExpr(expr);
    this.generator.emit(')');
  }
}

class Func {
  constructor(generator){
    this.generator = generator;
    ['sleep'].forEach(method => {
      this[method] = function(args) {
        generator.emit(`${CORE}::${method}`);
        generator.visitArgs(args);
      };
    });
  }

  isNull(args) {
    const expr = args[0];
    this.generator.visitIsNull(expr);
  }

  default(args){
    this.generator.emit(`${CORE}::defaultVal`);
    this.generator.visitArgs(args);
  }

  equal(args){
    this.generator.visitExpr(args[0]);
    this.generator.emit(' == ');
    this.generator.visitExpr(args[1]);
  }

}

class String extends Builtin {

  constructor(generator){
    const methods = [];
    super(generator, 'DaraString', methods);
  }
  replace(ast) {
    const args = ast.args;
    this.generator.emit(`${CORE}::String::replace(`);
    this.getInstanceName(ast);
    this.generator.emit(', ');
    this.generator.visitExpr(args[0]);
    this.generator.emit(', ');
    this.generator.visitExpr(args[1]);
    this.generator.emit(')');
  }

  contains(ast) {
    const args = ast.args;
    this.generator.emit(`${CORE}::String::contains(`);
    this.getInstanceName(ast);
    this.generator.emit(', ');
    this.generator.visitExpr(args[0]);
    this.generator.emit(')');
  }

  split(ast) {
    const args = ast.args;
    this.generator.emit(`${CORE}::String::split(`);
    this.getInstanceName(ast);
    this.generator.emit(', ');
    this.generator.visitExpr(args[0]);
    this.generator.emit(')');
  }


  length(ast) {
    this.getInstanceName(ast);
    this.generator.emit('.size()');
  }

  hasPrefix(ast) {
    const args = ast.args;
    this.generator.emit(`${CORE}::String::hasPrefix(`);
    this.getInstanceName(ast);
    this.generator.emit(', ');
    this.generator.visitExpr(args[0]);
    this.generator.emit(')');
  }

  hasSuffix(ast) {
    const args = ast.args;
    this.generator.emit(`${CORE}::String::hasSuffix(`);
    this.getInstanceName(ast);
    this.generator.emit(', ');
    this.generator.visitExpr(args[0]);
    this.generator.emit(')');
  }

  index(ast, level) {
    const args = ast.args;
    this.generator.emit(`${CORE}::String::index(`);
    this.getInstanceName(ast);
    this.generator.emit(', ');
    this.generator.visitExpr(args[0]);
    this.generator.emit(')');
  }

  subString(ast, level) {
    const args = ast.args;
    this.generator.emit(`${CORE}::String::subString(`);
    this.getInstanceName(ast);
    this.generator.emit(', ');
    this.generator.visitExpr(args[0]);
    this.generator.emit(')');
  }

  toLower(ast) {
    this.generator.emit(`${CORE}::String::toLower(`);
    this.getInstanceName(ast);
    this.generator.emit(')');
  }

  toUpper(ast) {
    this.generator.emit(`${CORE}::String::toUpper(`);
    this.getInstanceName(ast);
    this.generator.emit(')');
  }

  trim(ast) {
    this.generator.emit(`${CORE}::String::trim(`);
    this.getInstanceName(ast);
    this.generator.emit(')');
  }

  equals(ast) {
    this.getInstanceName(ast);
    const args = ast.args;
    const expr = args[0];
    this.generator.emit(' == ');
    this.generator.visitExpr(expr);

  }

  empty(ast) {
    this.getInstanceName(ast);
    this.generator.emit('.empty()');
  }

  toBytes(ast) {
    this.generator.emit(`${CORE}::BytesUtil::toBytes(`);
    this.getInstanceName(ast);
    this.generator.emit(')');
  }

  parseInt(ast) {
    this.generator.emit('std::stoi(');
    this.getInstanceName(ast);
    this.generator.emit(')');
  }

  parseLong(ast) {
    this.generator.emit('std::stol(');
    this.getInstanceName(ast);
    this.generator.emit(')');
  }

  parseFloat(ast) {
    this.generator.emit('std::stof(');
    this.getInstanceName(ast);
    this.generator.emit(')');
  }

  parseDouble(ast) {
    this.generator.emit('std::stod(');
    this.getInstanceName(ast);
    this.generator.emit(')');
  }
}

class Array extends Builtin {
  constructor(generator){
    const methods = [];
    super(generator, 'DaraArray', methods);
  }

  contains(ast) {
    const args = ast.args;
    this.generator.emit(`${CORE}::Array::contains(`);
    this.getInstanceName(ast);
    this.generator.emit(', ');
    this.generator.visitExpr(args[0]);
    this.generator.emit(')');
  }

  join(ast) {
    const args = ast.args;
    this.generator.emit(`${CORE}::Array::join(`);
    this.getInstanceName(ast);
    this.generator.emit(', ');
    this.generator.visitExpr(args[0]);
    this.generator.emit(')');
  }

  length(ast) {
    this.getInstanceName(ast);
    this.generator.emit('.size()');
  }

  index(ast, level) {
    const args = ast.args;
    this.generator.emit(`${CORE}::Array::index(`);
    this.getInstanceName(ast);
    this.generator.emit(', ');
    this.generator.visitExpr(args[0]);
    this.generator.emit(')');
  }

  get(ast, level) {
    this.getInstanceName(ast);
    const args = ast.args;
    this.generator.emit('[');
    const expr = args[0];
    this.generator.visitExpr(expr, level);
    this.generator.emit(']');
  }

  sort(ast) {
    const order = _string(ast.args[0].value);
    this.generator.emit(`${CORE}::Array::${order.toLowerCase()}Sort(`);
    this.getInstanceName(ast);
    this.generator.emit(')');
  }

  append(ast) {
    const position = ast.args[1];
    const value = ast.args[0];
    this.getInstanceName(ast);
    this.generator.emit('.insert(');
    this.getInstanceName(ast);
    this.generator.emit('.begin() + ');
    this.generator.visitExpr(position);
    this.generator.emit(', ');
    this.generator.visitExpr(value);
    this.generator.emit(')');
  }

  remove(ast) {
    this.getInstanceName(ast);
    const value = ast.args[0];
    this.generator.emit('.erase(std::remove(');
    this.getInstanceName(ast);
    this.generator.emit('.begin(), ');
    this.getInstanceName(ast);
    this.generator.emit('.end(), ');
    this.generator.visitExpr(value);
    this.generator.emit('), ');
    this.getInstanceName(ast);
    this.generator.emit('.end())');
  }
}

class Map extends Builtin {

  constructor(generator){
    const methods = [];
    super(generator, 'DaraMap', methods);
  }

  length(ast) {
    this.getInstanceName(ast);
    this.generator.emit('.size()');
  }

  keySet(ast) {
    this.generator.emit(`${CORE}::Map::keySet(`);
    this.getInstanceName(ast);
    this.generator.emit(')');
  }

  entries(ast) {
    this.generator.emit(`${CORE}::Map::entries(`);
    this.getInstanceName(ast);
    this.generator.emit(')');
  }

  toJSON(ast) {
    this.generator.emit(`${CORE}::JSON::stringify(`);
    this.getInstanceName(ast);
    this.generator.emit(')');
  }

  merge(ast) {
    this.generator.emit(`${CORE}::CORE::merge(`);
    this.getInstanceName(ast);
    this.generator.emit(' , ');
    this.generator.visitExpr(ast.args[0]);
    this.generator.emit(')');
  }
}

class Entry extends Builtin {
  constructor(generator){
    const methods = [];
    super(generator, 'DaraEntry', methods);
  }

  key(ast) {
    this.getInstanceName(ast);
    this.generator.emit('.first');
  }

  value(ast) {
    this.getInstanceName(ast);
    this.generator.emit('.second');
  }
}

module.exports = (generator) => {
  const builtin = {};
  builtin['$Env'] = new Env(generator);
  builtin['$Logger'] = new Logger(generator);
  builtin['$XML'] = new XML(generator);
  builtin['$URL'] = new URL(generator);
  builtin['$Stream'] = new Stream(generator);
  builtin['$Number'] = new Number(generator);
  builtin['$JSON'] = new JSON(generator);
  builtin['$Form'] = new Form(generator);
  builtin['$File'] = new File(generator);
  builtin['$Bytes'] = new Bytes(generator);
  const converter = new Converter(generator);
  types.map(type => {
    builtin[`$${type}`] = converter;
  });

  const func = new Func(generator);
  builtin['$isNull'] = func;
  builtin['$sleep'] = func;
  builtin['$default'] = func;
  builtin['$equal'] = func;

  builtin['$String'] = new String(generator);
  builtin['$Array'] = new Array(generator);
  builtin['$Date'] = new Date(generator);
  builtin['$Map'] = new Map(generator);
  builtin['$Entry'] = new Entry(generator);

  return builtin;
};