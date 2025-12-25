'use strict';

const path = require('path');
const fs = require('fs');
const DSL = require('@darabonba/parser');
const Generator = require('../lib/generator');

// 生成器配置和测试用例列表
const testCases = [
  {
    name: 'empty',
    mainFile: 'main.dara',
    configFile: 'Darafile'
  },
  {
    name: 'model',
    mainFile: 'main.dara',
    configFile: 'Darafile'
  },
  {
    name: 'api',
    mainFile: 'main.dara',
    configFile: 'Darafile'
  },
  {
    name: 'alias',
    mainFile: 'main.dara',
    configFile: 'Darafile'
  },
  {
    name: 'builtin',
    mainFile: 'main.dara',
    configFile: 'Darafile'
  },
  {
    name: 'function',
    mainFile: 'main.dara',
    configFile: 'Darafile'
  },
  {
    name: 'const',
    mainFile: 'main.dara',
    configFile: 'Darafile'
  },
  {
    name: 'statements',
    mainFile: 'main.dara',
    configFile: 'Darafile'
  },
  {
    name: 'import',
    mainFile: 'main.dara',
    configFile: 'Darafile'
  },
  {
    name: 'complex',
    mainFile: 'main.dara',
    configFile: 'Darafile'
  },
  {
    name: 'annotation',
    mainFile: 'main.dara',
    configFile: 'Darafile'
  },
  {
    name: 'comment',
    mainFile: 'main.dara',
    configFile: 'Darafile'
  },
  {
    name: 'multi',
    mainFile: 'main.dara',
    configFile: 'Darafile'
  },
  {
    name: 'tea',
    mainFile: 'main.tea',
    configFile: 'Teafile'
  },
  {
    name: 'nested',
    mainFile: 'main.dara',
    configFile: 'Darafile'
  }
  // exceptions测试用例需要复杂的依赖配置，暂时跳过
  // {
  //   name: 'exceptions',
  //   mainFile: 'main.dara',
  //   configFile: 'Darafile'
  // }
];

function generateFixture(testCase) {
  const fixtureDir = path.join(__dirname, 'fixtures', testCase.name);
  const mainFilePath = path.join(fixtureDir, testCase.mainFile);
  const outputDir = path.join(__dirname, 'temp-output', testCase.name);

  console.log(`生成 ${testCase.name} 的参考文件...`);

  // 读取配置
  const configPath = path.join(fixtureDir, testCase.configFile);
  const configContent = fs.readFileSync(configPath, 'utf8');
  const pkg = JSON.parse(configContent);
  
  // 将 cpp 配置展开到顶层
  const config = {
    outputDir,
    pkgDir: fixtureDir,
    ...pkg,
    header: pkg.cpp && pkg.cpp.header,
    namespace: pkg.cpp && pkg.cpp.namespace,
    release: pkg.releases
  };

  // 生成代码
  const generator = new Generator(config);

  const dsl = fs.readFileSync(mainFilePath, 'utf8');
  const ast = DSL.parse(dsl, mainFilePath);
  generator.visit(ast);

  // 复制生成的文件到 fixtures（排除 external 和 cmake 目录）
  function copyFiles(srcDir, destDir, relPath = '') {
    const srcPath = path.join(srcDir, relPath);
    const destPath = path.join(destDir, relPath);
    
    if (!fs.existsSync(srcPath)) {
      return;
    }
    
    const files = fs.readdirSync(srcPath);
    
    for (const file of files) {
      // 跳过 external 和 cmake 目录
      if (relPath === '' && (file === 'external' || file === 'cmake' || file === 'CMakeLists.txt')) {
        continue;
      }
      
      const srcFile = path.join(srcPath, file);
      const destFile = path.join(destPath, file);
      const stat = fs.statSync(srcFile);
      
      if (stat.isDirectory()) {
        if (!fs.existsSync(destFile)) {
          fs.mkdirSync(destFile, { recursive: true });
        }
        copyFiles(srcDir, destDir, path.join(relPath, file));
      } else {
        if (!fs.existsSync(path.dirname(destFile))) {
          fs.mkdirSync(path.dirname(destFile), { recursive: true });
        }
        fs.copyFileSync(srcFile, destFile);
      }
    }
  }
  
  copyFiles(outputDir, fixtureDir);
  console.log(`✓ ${testCase.name} 完成`);
}

// 生成所有参考文件
testCases.forEach(generateFixture);

console.log('\n所有参考文件生成完成!');
