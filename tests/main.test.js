'use strict';

const path = require('path');
const fs = require('fs');
const assert = require('assert');

const DSL = require('@darabonba/parser');

let Generator = require('../lib/generator');
// const { release } = require('os');

function check(mainFilePath, outputDir, expectedDir, pkgInfo = {}) {
  // 将 cpp 配置展开到顶层
  const config = {
    outputDir,
    ...pkgInfo,
    header: pkgInfo.cpp && pkgInfo.cpp.header,
    namespace: pkgInfo.cpp && pkgInfo.cpp.namespace,
    release: pkgInfo.releases
  };
  
  const generator = new Generator(config);

  const dsl = fs.readFileSync(mainFilePath, 'utf8');
  const ast = DSL.parse(dsl, mainFilePath);
  generator.visit(ast);
  
  // 递归比对所有生成的文件（只比对 src 和 include 目录）
  function compareDir(relPath = '') {
    const actualDir = path.join(outputDir, relPath);
    const expectDir = path.join(expectedDir, relPath);
    
    if (!fs.existsSync(expectDir)) {
      // 如果期望目录不存在，跳过（允许只比对部分文件）
      return;
    }
    
    const expectFiles = fs.readdirSync(expectDir);
    
    for (const file of expectFiles) {
      const expectPath = path.join(expectDir, file);
      const actualPath = path.join(actualDir, file);
      const stat = fs.statSync(expectPath);
      
      if (stat.isDirectory()) {
        // 只比对 src 和 include 目录
        if (relPath === '' && file !== 'src' && file !== 'include') {
          continue;
        }
        // 递归比对子目录
        compareDir(path.join(relPath, file));
      } else {
        // 文件层面，只在 src 和 include 目录下比对
        if (relPath.startsWith('src') || relPath.startsWith('include')) {
          // 比对文件内容
          const expected = fs.readFileSync(expectPath, 'utf8');
          const actual = fs.readFileSync(actualPath, 'utf8');
          assert.deepStrictEqual(actual, expected, `File mismatch: ${path.join(relPath, file)}`);
        }
      }
    }
  }
  
  compareDir();
}

describe('new Generator', function() {
  it('must pass in outputDir', function () {
    assert.throws(function () {
      new Generator({});
    }, function(err) {
      assert.deepStrictEqual(err.message, 'Darafile -> cpp -> header should not empty, please add cpp option into Darafile.example:\n' +
      '"cpp": {"header": "darabonba/core.hpp", "namespace": "DARABONBA"}');
      return true;
    });
  });

  it('empty module should ok', function () {
    const outputDir = path.join(__dirname, 'output/empty');
    const mainFilePath = path.join(__dirname, 'fixtures/empty/main.dara');
    const pkgContent = fs.readFileSync(path.join(__dirname, 'fixtures/empty/Darafile'), 'utf8');
    const pkg = JSON.parse(pkgContent);
    check(mainFilePath, outputDir, path.join(__dirname, 'fixtures/empty'), {
      pkgDir: path.join(__dirname, 'fixtures/empty'),
      ...pkg
    });
  });

  it('one model should ok', function () {
    const outputDir = path.join(__dirname, 'output/model');
    const mainFilePath = path.join(__dirname, 'fixtures/model/main.dara');
    const pkgContent = fs.readFileSync(path.join(__dirname, 'fixtures/model/Darafile'), 'utf8');
    const pkg = JSON.parse(pkgContent);
    check(mainFilePath, outputDir, path.join(__dirname, 'fixtures/model'), {
      pkgDir: path.join(__dirname, 'fixtures/model'),
      ...pkg
    });
  });

  it('one api should ok', function () {
    const outputDir = path.join(__dirname, 'output/api');
    const mainFilePath = path.join(__dirname, 'fixtures/api/main.dara');
    const pkgContent = fs.readFileSync(path.join(__dirname, 'fixtures/api/Darafile'), 'utf8');
    const pkg = JSON.parse(pkgContent);
    check(mainFilePath, outputDir, path.join(__dirname, 'fixtures/api'), {
      pkgDir: path.join(__dirname, 'fixtures/api'),
      ...pkg
    });
  });

  it('alias should ok', function () {
    const outputDir = path.join(__dirname, 'output/alias');
    const mainFilePath = path.join(__dirname, 'fixtures/alias/main.dara');
    const pkgContent = fs.readFileSync(path.join(__dirname, 'fixtures/alias/Darafile'), 'utf8');
    const pkg = JSON.parse(pkgContent);
    check(mainFilePath, outputDir, path.join(__dirname, 'fixtures/alias'), {
      pkgDir: path.join(__dirname, 'fixtures/alias'),
      ...pkg
    });
  });

  it('builtin should ok', function () {
    const outputDir = path.join(__dirname, 'output/builtin');
    const mainFilePath = path.join(__dirname, 'fixtures/builtin/main.dara');
    const pkgContent = fs.readFileSync(path.join(__dirname, 'fixtures/builtin/Darafile'), 'utf8');
    const pkg = JSON.parse(pkgContent);
    check(mainFilePath, outputDir, path.join(__dirname, 'fixtures/builtin'), {
      pkgDir: path.join(__dirname, 'fixtures/builtin'),
      ...pkg
    });
  });

  it('one function should ok', function () {
    const outputDir = path.join(__dirname, 'output/function');
    const mainFilePath = path.join(__dirname, 'fixtures/function/main.dara');
    const pkgContent = fs.readFileSync(path.join(__dirname, 'fixtures/function/Darafile'), 'utf8');
    const pkg = JSON.parse(pkgContent);
    check(mainFilePath, outputDir, path.join(__dirname, 'fixtures/function'), {
      pkgDir: path.join(__dirname, 'fixtures/function'),
      ...pkg
    });
  });

  it('const should ok', function () {
    const outputDir = path.join(__dirname, 'output/const');
    const mainFilePath = path.join(__dirname, 'fixtures/const/main.dara');
    const pkgContent = fs.readFileSync(path.join(__dirname, 'fixtures/const/Darafile'), 'utf8');
    const pkg = JSON.parse(pkgContent);
    check(mainFilePath, outputDir, path.join(__dirname, 'fixtures/const'), {
      pkgDir: path.join(__dirname, 'fixtures/const'),
      ...pkg
    });
  });

  it('statements should ok', function () {
    const outputDir = path.join(__dirname, 'output/statements');
    const mainFilePath = path.join(__dirname, 'fixtures/statements/main.dara');
    const pkgContent = fs.readFileSync(path.join(__dirname, 'fixtures/statements/Darafile'), 'utf8');
    const pkg = JSON.parse(pkgContent);
    check(mainFilePath, outputDir, path.join(__dirname, 'fixtures/statements'), {
      pkgDir: path.join(__dirname, 'fixtures/statements'),
      ...pkg
    });
  });

  it('import should ok', function () {
    const outputDir = path.join(__dirname, 'output/import');
    const mainFilePath = path.join(__dirname, 'fixtures/import/main.dara');
    const pkgContent = fs.readFileSync(path.join(__dirname, 'fixtures/import/Darafile'), 'utf8');
    const pkg = JSON.parse(pkgContent);
    check(mainFilePath, outputDir, path.join(__dirname, 'fixtures/import'), {
      pkgDir: path.join(__dirname, 'fixtures/import'),
      ...pkg
    });
  });

  it('complex should ok', function () {
    const outputDir = path.join(__dirname, 'output/complex');
    const mainFilePath = path.join(__dirname, 'fixtures/complex/main.dara');
    const pkgContent = fs.readFileSync(path.join(__dirname, 'fixtures/complex/Darafile'), 'utf8');
    const pkg = JSON.parse(pkgContent);
    check(mainFilePath, outputDir, path.join(__dirname, 'fixtures/complex'), {
      pkgDir: path.join(__dirname, 'fixtures/complex'),
      ...pkg
    });
  });

  it('add annotation should ok', function () {
    const outputDir = path.join(__dirname, 'output/annotation');
    const mainFilePath = path.join(__dirname, 'fixtures/annotation/main.dara');
    const pkgContent = fs.readFileSync(path.join(__dirname, 'fixtures/annotation/Darafile'), 'utf8');
    const pkg = JSON.parse(pkgContent);
    check(mainFilePath, outputDir, path.join(__dirname, 'fixtures/annotation'), {
      pkgDir: path.join(__dirname, 'fixtures/annotation'),
      ...pkg
    });
  });

  it('add comments should ok', function () {
    const outputDir = path.join(__dirname, 'output/comment');
    const mainFilePath = path.join(__dirname, 'fixtures/comment/main.dara');
    const pkgContent = fs.readFileSync(path.join(__dirname, 'fixtures/comment/Darafile'), 'utf8');
    const pkg = JSON.parse(pkgContent);
    check(mainFilePath, outputDir, path.join(__dirname, 'fixtures/comment'), {
      pkgDir: path.join(__dirname, 'fixtures/comment'),
      ...pkg
    });
  });

  it('multi should ok', function () {
    const outputDir = path.join(__dirname, 'output/multi');
    const mainFilePath = path.join(__dirname, 'fixtures/multi/main.dara');
    const pkgContent = fs.readFileSync(path.join(__dirname, 'fixtures/multi/Darafile'), 'utf8');
    const pkg = JSON.parse(pkgContent);
    check(mainFilePath, outputDir, path.join(__dirname, 'fixtures/multi'), {
      pkgDir: path.join(__dirname, 'fixtures/multi'),
      ...pkg
    });
  });

  it('tea should ok', function () {
    const outputDir = path.join(__dirname, 'output/tea');
    const mainFilePath = path.join(__dirname, 'fixtures/tea/main.tea');
    const pkgContent = fs.readFileSync(path.join(__dirname, 'fixtures/tea/Teafile'), 'utf8');
    const pkg = JSON.parse(pkgContent);
    check(mainFilePath, outputDir, path.join(__dirname, 'fixtures/tea'), {
      pkgDir: path.join(__dirname, 'fixtures/tea'),
      ...pkg
    });
  });

  it('nested model and field conflict should ok', function () {
    const outputDir = path.join(__dirname, 'output/nested');
    const mainFilePath = path.join(__dirname, 'fixtures/nested/main.dara');
    const pkgContent = fs.readFileSync(path.join(__dirname, 'fixtures/nested/Darafile'), 'utf8');
    const pkg = JSON.parse(pkgContent);
    check(mainFilePath, outputDir, path.join(__dirname, 'fixtures/nested'), {
      pkgDir: path.join(__dirname, 'fixtures/nested'),
      ...pkg
    });
  });
});
