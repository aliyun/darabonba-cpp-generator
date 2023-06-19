'use strict';
const fs = require('fs');
const path = require('path');

class Emitter {
  constructor(outputDir, filepath) {
    this.outputDir = outputDir;
    this.filepath = filepath;
    this.output = '';
    this.config = {
      indent: '  '
    };
  }

  emit(str, level) {
    this.output += this.config.indent.repeat(level) + str;
  }

  save() {
    const targetPath = path.join(this.outputDir, this.filepath);
    fs.mkdirSync(path.dirname(targetPath), {
      recursive: true
    });

    fs.writeFileSync(targetPath, this.output);
    this.output = '';
  }
}

module.exports = Emitter;
