'use strict';

const CORE = 'Darabonba';
const fs = require('fs');
const path = require('path');

const builtinModels = [
  '$Request', '$Response', '$Error', '$SSEEvent', '$Model',
  '$RuntimeOptions', '$ExtendsParameters', '$RetryOptions',
  '$ResponseError', '$FileField'
];

const keywords = [
  'alignas', 'alignof', 'and', 'and_eq', 'asm',
  'atomic_cancel', 'atomic_commit', 'atomic_noexcept', 'auto', 'bitand',
  'bitor', 'bool', 'break', 'case', 'catch',
  'char', 'char8_t', 'char16_t', 'char32_t', 'class',
  'compl', 'concept', 'const', 'consteval', 'constexpr',
  'constinit', 'const_cast', 'continue', 'co_await', 'co_return',
  'co_yield', 'decltype', 'default', 'delete', 'do',
  'double', 'dynamic_cast', 'else', 'enum', 'explicit',
  'export', 'extern', 'false', 'float', 'for',
  'friend', 'goto', 'if', 'inline', 'int',
  'long', 'mutable', 'namespace', 'new', 'noexcept', 'map',
  'not', 'not_eq', 'nullptr', 'operator', 'or', 'vector',
  'or_eq', 'private', 'protected', 'public', 'reflexpr',
  'register', 'reinterpret_cast', 'requires', 'return', 'short',
  'signed', 'sizeof', 'static', 'static_assert', 'static_cast',
  'struct', 'switch', 'synchronized', 'template', 'this',
  'thread_local', 'throw', 'true', 'try', 'typedef',
  'typeid', 'typename', 'union', 'unsigned', 'using',
  'virtual', 'void', 'volatile', 'wchar_t', 'while',
  'xor', 'xor_eq'
];

const REQUEST = 'Darabonba::Http::Request';
const RESPONSE = 'Darabonba::Http::MCurlResponse';
const MODEL = 'Darabonba::Model';
function _lowerFirst(str){
  if(!str) {
    return '';
  }
  return str[0].toLowerCase() + str.substring(1);
}

function _isBuiltinModel(name){ 
  return builtinModels.includes(name);
}

const builtinInclude = {
  DaraStream: {
    header: 'darabonba/Stream.hpp',
    className: 'Darabonba::Stream',
  },
  DaraLogger: {
    header: 'darabonba/Logger.hpp',
    className: 'Darabonba::Logger',
  },
  DaraXML: {
    header: 'darabonba/XML.hpp',
    className: 'Darabonba::XML',
  },
  DaraURL: {
    header: 'darabonba/http/URL.hpp',
    className: 'Darabonba::Http::URL',
  },
  DaraForm: {
    header: 'darabonba/http/Form.hpp',
    className: 'Darabonba::Http::Form',
  },
  DaraNumber: {
    header: 'darabonba/Number.hpp',
    className: 'Darabonba::Number',
  },
  DaraFile: {
    header: 'darabonba/File.hpp',
    className: 'Darabonba::File',
  },
  DaraBytes: {
    header: 'darabonba/encode/Encoder.hpp',
    className: 'Darabonba::Encode::Encoder',
  },
  DaraDate: {
    header: 'darabonba/Date.hpp',
    className: 'Darabonba::Date',
  },
  DaraCore: {
    header: 'darabonba/Core.hpp',
    className: 'Darabonba::Core',
  },
  DaraRequest: {
    header: 'darabonba/http/Request.hpp',
    className: 'Darabonba::Http::Request',
  },
  DaraResponse: {
    header: 'darabonba/http/MCurlResponse.hpp',
    className: 'Darabonba::Http::MCurlResponse',
  },
  DaraModel: {
    header: 'darabonba/Model.hpp',
    className: 'Darabonba::Model',
  },
  RuntimeOptions: {
    header: 'darabonba/Runtime.hpp',
    className: 'Darabonba::RuntimeOptions',
  },
  DaraException: {
    header: 'darabonba/Exception.hpp',
    className: 'Darabonba::Exception',
  },
  UnretryableException: {
    header: 'darabonba/Exceptions.hpp',
    className: 'Darabonba::UnretryableException',
  },
  ResponseException: {
    header: 'darabonba/Exceptions.hpp',
    className: 'Darabonba::ResponseException',
  },
  RetryPolicyContext: {
    header: 'darabonba/policy/Retry.hpp',
    className: 'Darabonba::Policy::RetryPolicyContext',
  },
  RetryOptions: {
    header: 'darabonba/policy/Retry.hpp',
    className: 'Darabonba::Policy::RetryOptions',
  },
  SSEEvent: {
    header: 'darabonba/http/SSEEvent.hpp',
    className: 'Darabonba::Http::SSEEvent',
  },
  FileField: {
    header: 'darabonba/http/FileField.hpp',
    className: 'Darabonba::Http::FileField',
  },
  ExtendsParameters: {
    header: 'darabonba/Runtime.hpp',
    className: 'Darabonba::ExtendsParameters',
  },
  DaraEnv: {
    header: 'darabonba/Env.hpp',
    className: 'Darabonba::Env',
  },
  DaraJSON: {
    header: 'darabonba/JSON.hpp',
    className: 'Darabonba::JSON',
  },
  DaraString: {
    header: 'darabonba/String.hpp',
    className: 'Darabonba::String',
  },
  DaraArray: {
    header: 'darabonba/Array.hpp',
    className: 'Darabonba::Array',
  },
  DaraMap: {
    header: 'darabonba/Map.hpp',
    className: 'Darabonba::Map',
  },
  DaraEntry: {},
};

function _getInclude(type) {
  if (builtinInclude[type]) {
    return builtinInclude[type];
  }

  let tmpName = type.replace('$', '');
  if(builtinInclude[tmpName]) {
    return builtinInclude[tmpName];
  }

  if(builtinInclude[`Dara${tmpName}`]) {
    return builtinInclude[`Dara${tmpName}`];
  }
}

function _name(str) {
  if (str.lexeme === '__request') {
    return 'request_';
  }

  if (str.lexeme === '__response') {
    return 'response_';
  }

  return str.lexeme || str.name;
}

function _avoidKeywords(str) {
  if (keywords.indexOf(str) > -1) {
    return '_' + str;
  }
  return str;
}


function _upperFirst(str) {
  if(!str) {
    return '';
  }
  return str[0].toUpperCase() + str.substring(1);
}

function _snakeCase(str) {
  if (!str) {
    return '';
  }

  // 在大写字母前添加下划线，但避免在字符串开头添加
  // 处理连续大写字母的情况，如 MoMValues -> mo_m_values
  let result = '';
  for (let i = 0; i < str.length; i++) {
    const char = str[i];
    // 如果是大写字母
    if (char >= 'A' && char <= 'Z') {
      // 如果不是第一个字符，且前一个字符不是下划线，则添加下划线
      if (i > 0 && str[i-1] !== '_' && (str[i-1] < 'A' || str[i-1] > 'Z')) {
        result += '_';
      }
      // 如果是连续大写字母中的最后一个大写字母，且后面跟着小写字母，则在前面添加下划线
      else if (i > 0 && i < str.length - 1 && 
               (str[i-1] >= 'A' && str[i-1] <= 'Z') && 
               (str[i+1] >= 'a' && str[i+1] <= 'z')) {
        result += '_';
      }
      result += char.toLowerCase();
    } else {
      result += char;
    }
  }
  
  return result;
}

function _camelCase(str, split = '_') {
  // 先将字符串中的下划线拆分
  if (str.indexOf(split) > -1) {
    let tmp = str.split(split);
    tmp = tmp.map((s, i) => {
      // 如果是第一个单词则不处理，其他单词首字母大写
      return _upperFirst(s);
    });
    str = tmp.join('');
  } else {
    // 如果没有下划线，对整个字符串首字母大写
    str = _upperFirst(str);
  }
  
  return str;
}


function _subModelName(name) {
  return name.split('.').map((name) => _upperFirst(name)).join('');
}

function _string(str) {
  if (str.string === '""') {
    return '\\"\\"';
  }
  return str.string.replace(/([^\\])"|^"/g, '$1\\"');
}

function _defaultValue(name){
  if (name === 'integer' || name === 'number' ||
    name === 'int8' || name === 'uint8' ||
    name === 'int16' || name === 'uint16' ||
    name === 'int32' || name === 'uint32') {
    return '0';
  }

  if (name === 'readable') {
    return 'nullptr';
  }

  if (name === 'writable') {
    return 'nullptr';
  }

  if (name === 'long' || name === 'int64' || name === 'uint64') {
    return '0L';
  }

  if (name === 'float') {
    return '0.0';
  }

  if (name === 'double') {
    return '0.0';
  }

  if (name === 'object') {
    return 'R"({})"_json';
  }

  if (name === 'string') {
    return '""';
  }

  if (name === 'any') {
    return '""';
  }

  if (name === '$Request') {
    return 'Darabonba::Http::Request()';
  }

  if (name === '$Model') {
    return 'Darabonba::Model()';
  }

  if (name === '$Response') {
    return 'shared_ptr<Darabonba::Http::MCurlResponse>()';
  }

  if (name === 'bytes') {
    return '{}';
  }

  if (name === 'boolean') {
    return 'false';
  }

  console.log(name);
  throw new Error('unimpelemented');
}


function _type(name) {
  if(!name) {
    return;
  }

  if (name === 'null') {
    return 'nullptr';
  }

  if (name === 'number') {
    return 'int64_t';
  }
  
  if(name === 'int8') {
    return 'int8_t';
  }

  if(name === 'uint16') {
    return 'uint16_t';
  }

  if(name === 'int8') {
    return 'int8_t';
  }

  if(name === 'uint16') {
    return 'uint16_t';
  }

  if (name === 'integer' || name === 'int32') {
    return 'int32_t';
  }

  if (name === 'uint32') {
    return 'uint32_t';
  }

  if (name === 'readable') {
    return 'shared_ptr<Darabonba::IStream>';
  }

  if (name === 'writable') {
    return 'shared_ptr<Darabonba::OStream>';
  }

  if (name === 'long' || name === 'int64') {
    return 'int64_t';
  }

  if (name === 'uint64') {
    return 'uint64_t';
  }

  if (name === 'float') {
    return 'float';
  }

  if (name === 'double') {
    return 'double';
  }

  if (name === 'object') {
    return 'Darabonba::Json';
  }

  if (name === 'string') {
    return 'string';
  }

  if (name === 'any') {
    return 'Darabonba::Json';
  }

  if (name === '$Request') {
    return 'Darabonba::Http::Request';
  }

  if (name === '$Model') {
    return 'Darabonba::Model';
  }

  if (name === '$Error') {
    return 'Darabonba::Exception';
  }

  if (name === '$ResponseError') {
    return 'Darabonba::ResponseException';
  }

  if (name === 'bytes') {
    return 'Darabonba::Bytes';
  }

  if (name === 'boolean') {
    return 'bool';
  }

  let tmpName = name.replace('$', '');
  if(builtinInclude[tmpName]) {
    return builtinInclude[tmpName].className;
  }

  if(builtinInclude[`Dara${tmpName}`]) {
    return builtinInclude[`Dara${tmpName}`].className;
  }

  return name;
}

function _vid(vid) {
  return `_${_name(vid).substr(1)}`;
}

function _namespace(name) {
  if(name.startsWith('./') || name.startsWith('../')) {
    name = name.split('/').slice(1).join('/');
  }
  return name.replace(/(\.h)$|(\.hpp)$/, '').split(path.sep).map(ele => _upperFirst(ele)).join('::');
}

function remove(...filesPath) {
  filesPath.forEach(filePath => {
    if (fs.existsSync(filePath)) {
      if (fs.statSync(filePath).isDirectory()) {
        const files = fs.readdirSync(filePath);
        files.forEach((file, index) => {
          let curPath = path.join(filePath, file);
          if (fs.statSync(curPath).isDirectory()) {
            remove(curPath);
          } else {
            fs.unlinkSync(curPath);
          }
        });
        fs.rmdirSync(filePath);
      } else {
        fs.unlinkSync(filePath);
      }
    }
  });
}

function _isBaseType(type) {
  type = typeof type === 'string' ? type : type.type;
  const cppBaseTypes = ['boolean', 'integer', 'number', 'float', 'double','int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64', 'string', 'long'];
  return cppBaseTypes.includes(type);
}

function _isPointerType(type) {
  type = typeof type === 'string' ? type : type.type;
  const pointerType = ['bytes', 'readable', 'writable'].concat(builtinModels);
  return !!pointerType.includes(type);
}

function _isSpecialBaseType(type) {
  type = typeof type === 'string' ? type : type.type;
  const specialTypes = ['string', 'bytes'];
  return specialTypes.includes(type);
}

function _dirname(header) {
  return header.split('/').join(path.sep);
}

function _isBinaryOp(type) {
  const op = [
    'or', 'eq', 'neq',
    'gt', 'gte', 'lt',
    'lte', 'add', 'subtract',
    'div', 'multi', 'and'
  ];
  return op.includes(type);
}

module.exports = {
  _name, _string, _type, _subModelName, _vid, _upperFirst, remove, _defaultValue, _lowerFirst,
  REQUEST, RESPONSE, CORE, _isBaseType, _isSpecialBaseType, _isPointerType, _isBinaryOp, _snakeCase,
  _camelCase, _isBuiltinModel, MODEL, _avoidKeywords, _getInclude, _namespace, _dirname
};
