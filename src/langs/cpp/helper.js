'use strict';

const debug = require('../../lib/debug');
const config = require('./config');

const {
  _camelCase,
  _isBasicType
} = require('../../lib/helper');

const symbolMap = {
  'ASSIGN': '=',
  'EQ': '==',
  'NOT': '!=',
  'AND': '&&',
  'OR': '||',
  'PLUS': '+',
  'SUB': '-',
  'MULTI': '*',
  'DIV': '/',
  'POWER': '^',
  'GREATER': '>',
  'GREATER_EQ': '>=',
  'LESS': '<',
  'LESS_EQ': '<=',
  'REVERSE': '!',
  'CONCAT': '+'
};

function _symbol(str) {
  if (symbolMap[str]) {
    return symbolMap[str];
  }
  debug.stack(str);
}

const exceptionMap = {
  'BASE': 'TeaException.Error',
};

function _exception(str) {
  if (exceptionMap[str]) {
    return exceptionMap[str];
  }
  return str;
}

function _avoidReserveName(str) {
  if (config.keywords.indexOf(str.toLowerCase()) > -1) {
    return str + '_';
  }
  return str;
}

function _name(str) {
  return _avoidReserveName(_camelCase(str, '-'));
}

const modifyOrder = [
  'OPEN',
  'INTERNAL',
  'PRIVATE',
  'PUBLIC',
  'FILE_PRIVATE',
];

const modifyMap = {
  'OPEN': 'open',
  'INTERNAL': 'internal',
  'PRIVATE': 'private',
  'PUBLIC': 'public',
  'FILE_PRIVATE': 'fileprivate',
};

function _modify(modify) {
  if (Array.isArray(modify)) {
    return modify.filter((m) => modifyOrder.indexOf(m) > -1)
      .map((m) => _modify(m)).sort(function (a, b) {
        return modifyOrder.indexOf(a.toUpperCase()) - modifyOrder.indexOf(b.toUpperCase());
      }).join(' ');
  }
  return modifyMap[modify];
}

const typeMap = {
  'boolean': 'Bool',
  'number': 'Int',
  'integer': 'Int',
  'any': '[String:Any]',
  'int32': 'Int32',
  'uint32': 'UInt32',
  'int16': 'Int',
  'object': '[String:AnyObject]',
  'string': 'String',
  'array': '[String:Any]',
  'long': 'Int64'
};

function _type(type) {
  let t = type instanceof Object ? type.lexeme : type;
  if (t[0] === '$') {
    t = t.replace('$', 'Tea');
  }
  if (typeMap[t]) {
    return typeMap[t];
  }
  return t;
}

const defaultValueMap = {
  'boolean': 'true',
  'number': '0',
  'integer': '0',
  'any': 'nil',
  'int32': '0',
  'int16': '0',
  'object': 'nil',
  'string': '""',
  'long': '0',
  'array': '[String:NSObject]()',
  'map': '[String:Any]()',
  'readable': 'Data',
  'float': '0'
};

function _default(type) {
  if (type.lexeme) {
    type = type.lexeme;
  }
  if (defaultValueMap[type]) {
    return defaultValueMap[type];
  }
  if (_isBasicType(type)) {
    debug.stack(type);
  }
  return 'nil';
}

function _convertStaticParam(param) {
  if (param === '__response') {
    param = config.response;
  } else if (param === '__request') {
    param = config.request;
  }
  return param;
}

module.exports = {
  _symbol,
  _exception,
  _name,
  _modify,
  _type,
  _convertStaticParam,
  _default,
  _avoidReserveName
};
