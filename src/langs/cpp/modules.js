'use strict';

const Emitter = require('../../lib/emitter');

function param(param_gram) {
  let emit = new Emitter(this.config);
  this.grammer(emit, param_gram, false, false);
  let res = emit.output;
  if (this.isPointerVar(param_gram)) {
    res = '*' + res;
  }
  return res;
}

function parse(emitter, gram) {
  const method_name = gram.path[1].name;
  const map = {
    'parseInt': 'stoi',
    'parseLong': 'stol',
    'parseFloat': 'stod',
    'parseDouble': 'stod',
    'itol': 'itol',
    'ltoi': 'ltoi',
  };
  emitter.emit(`std::${map[method_name]}(${param.call(this, gram.params[0])})`);
}

function binary_operation(emitter, gram) {
  const a = param.call(this, gram.params[0]);
  const b = param.call(this, gram.params[1]);
  const method_name = gram.path[1].name;
  const map = {
    'add': '+',
    'sub': '-',
    'mul': '*',
    'div': '/',
    'gt': '>',
    'gte': '>=',
    'lt': '<',
    'lte': '<='
  };
  emitter.emit(`${a} ${map[method_name]} ${b}`);
}

module.exports = {
  parse,
  binary_operation,
};
