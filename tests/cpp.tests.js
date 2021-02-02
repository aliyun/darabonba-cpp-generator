'use strict';

// const mm = require('mm');
// const expect = require('chai').expect;
require('mocha-sinon');
const path = require('path');
const fs = require('fs');
const assert = require('assert');

const DSL = require('@darabonba/parser');

const Generator = require('../src/generator');

const lang = 'cpp';

const expectedDir = path.join(__dirname, 'expected/');
const fixturesDir = path.join(__dirname, 'fixtures/');
const outputDir = path.join(__dirname, '../', 'output/tests/');

const extCode = '.cpp';
const extHead = '.hpp';

function check(moduleName, expectedFiles = [], options = {}) {
  const mainFilePath = path.join(fixturesDir, moduleName, 'main.dara');
  const moduleOutputDir = path.join(outputDir, moduleName);
  const prefixDir = path.join(fixturesDir, moduleName);
  const pkgContent = fs.readFileSync(
    fs.existsSync(path.join(prefixDir, 'Darafile')) ? path.join(prefixDir, 'Darafile') : path.join(prefixDir, 'Teafile'), 'utf8');
  const pkgInfo = JSON.parse(pkgContent);
  const config = {
    outputDir: moduleOutputDir,
    pkgDir: path.join(fixturesDir, moduleName),
    ...pkgInfo,
    ...options
  };
  const generator = new Generator(config, lang);

  const dsl = fs.readFileSync(mainFilePath, 'utf8');
  const ast = DSL.parse(dsl, mainFilePath);
  generator.visit(ast);
  expectedFiles.forEach(element => {
    const outputFilePath = path.join(outputDir, moduleName, element);
    const expectedFilePath = path.join(expectedDir, moduleName, element);
    const expected = fs.readFileSync(expectedFilePath, 'utf8');
    assert.deepStrictEqual(fs.readFileSync(outputFilePath, 'utf8'), expected);
  });
}

describe('C++ Generator', function () {
  it('add annotation should ok', function () {
    check('annotation', [
      `src/annotation${extCode}`,
      `include/darabonba/annotation${extHead}`
    ]);
  });

  it('api should ok', function () {
    check('api', [
      `src/api${extCode}`,
      `include/darabonba/api${extHead}`
    ]);
  });

  it('add comments should ok', function () {
    check('comment', [
      `src/comment${extCode}`,
      `include/darabonba/comment${extHead}`
    ]);
  });

  it('complex should ok', function () {
    check('complex', [
      `src/complex${extCode}`,
      `include/darabonba/complex${extHead}`
    ]);
  });

  it('const should ok', function () {
    check('const', [
      `src/const${extCode}`,
      `include/darabonba/const${extHead}`
    ]);
  });

  it('empty should ok', function () {
    check('empty', [
      `src/empty${extCode}`,
      `include/darabonba/empty${extHead}`
    ]);
  });

  it('function should ok', function () {
    check('function', [
      `src/function${extCode}`,
      `include/darabonba/function${extHead}`
    ]);
  });

  it('import should ok', function () {
    check('import', [
      `src/import${extCode}`,
      `include/darabonba/import${extHead}`
    ]);
  });

  it('map should ok', function () {
    check('map', [
      `src/map${extCode}`,
      `include/darabonba/map${extHead}`
    ]);
  });

  it('model should ok', function () {
    check('model', [
      `src/model${extCode}`,
      `include/darabonba/model${extHead}`
    ]);
  });

  it('statements should ok', function () {
    check('statements', [
      `src/statements${extCode}`,
      `include/darabonba/statements${extHead}`
    ]);
  });

  it('super should ok', function () {
    check('super', [
      `src/super${extCode}`,
      `include/darabonba/super${extHead}`
    ]);
  });

  it('exec should ok', function () {
    check('exec', [
      'src/exec.cpp'
    ]);
  });

  it('alias should ok', function () {
    check('alias', [
      `src/alias${extCode}`,
      `include/darabonba/alias${extHead}`
    ]);
  });

  it('package should ok', function () {
    check('package', [
      'CMakeLists.txt',
      'src/package.cpp',
      'include/darabonba/package.hpp',
      'external/CMakeLists.txt',
      'external/darabonba_core/CMakeLists.txt',
      '.gitignore',
      'scripts/build.sh',
      'scripts/codecov.sh',
      'scripts/format.sh',
      'scripts/install.sh',
      'scripts/run_ut.sh',
    ], {
      withTest: 1
    });
  });
});

const PackageInfo = require('../src/langs/cpp/package_info');
const pack = new PackageInfo();
describe('C++ Generator generate package files should ok', function () {
  beforeEach(function () {
    this.sinon.stub(pack, 'renderAuto');
  });
  it('package generateFiles', function () {
    pack.config = {
      dir: '',
      packageInfo: {
        files: {
          'readme': {
            tmpl: path.join(__dirname, '../README.md'),
            path: 'README.md',
          }
        }
      }
    };
    pack.generateFiles();
  });
});
