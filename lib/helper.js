'use strict';

const REQUEST = 'request_';
const RESPONSE = 'response_';
const CORE = '$tea';
const fs = require('fs');
const path = require('path');

function _lowerFirst(str){
  if(!str) {
    return '';
  }
  return str[0].toLowerCase() + str.substring(1);
}

function _name(str) {
  if (str.lexeme === '__request') {
    return REQUEST;
  }

  if (str.lexeme === '__response') {
    return RESPONSE;
  }

  return str.lexeme || str.name;
}

function _upperFirst(str) {
  if(!str) {
    return '';
  }
  return str[0].toUpperCase() + str.substring(1);
}

function _subModelName(name) {
  if (!name) {
    return '';
  }
  const names = name.split('.');
  if(names.length < 2) {
    return _upperFirst(name);
  }
  let subModelName = '';
  // 处理 A.A.A 这种情况
  names.forEach(name => {
    let modelName = _upperFirst(name);
    if(modelName === subModelName) {
      subModelName = subModelName + modelName;
      return;
    }
    subModelName = modelName;
    return;
  })

  return subModelName;
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

  if (name === 'writeable') {
    return 'nullptr';
  }

  if (name === 'long' || name === 'int64' || name === 'uint64') {
    return '0L';
  }

  if (name === 'float') {
    return '0.0';
  }

  if (name === 'double') {
    return '0.0d';
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
    return 'Darabonba::Request()';
  }

  if (name === '$Model') {
    return 'Darabonba::Model()';
  }

  if (name === '$Response') {
    return 'Darabonba::Response()';
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
    return 'std::shared_ptr<Darabonba::IStream>';
  }

  if (name === 'writeable') {
    return 'std::shared_ptr<Darabonba::Http::MCurlResponseBody>';
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
    return 'std::string';
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

  if (name === '$Response') {
    return 'Darabonba::Http::MCurlResponse';
  }

  if (name === 'bytes') {
    return 'Darabonba::Bytes';
  }

  if (name === 'boolean') {
    return 'bool';
  }

  return name;
}

function _vid(vid) {
  return `_${_name(vid).substr(1)}`;
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

function _is_cpp_base_type(type) {
  const cpp_base_types = ['boolean', 'integer', 'number', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64'];
  return cpp_base_types.includes(type)
}

function _is_js_special_base_type(type) {
  const js_special_types = ['string', 'bytes'];
  return js_special_types.includes(type);
}


module.exports = {
  _name, _string, _type, _subModelName, _vid, _upperFirst, remove, _defaultValue, _lowerFirst,
  REQUEST, RESPONSE, CORE
};
