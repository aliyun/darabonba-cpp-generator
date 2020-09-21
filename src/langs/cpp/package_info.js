'use strict';

const path = require('path');
const os = require('os');
const fs = require('fs');
// const debug = require('../../lib/debug');
const BasePackageInfo = require('../common/package_info');
const { _toSnakeCase, _deepClone, _upperFirst, _avoidKeywords } = require('../../lib/helper');

class PackageInfo extends BasePackageInfo {
  emit(requirePackage) {
    const config = _deepClone(this.config);
    let outputDir = config.dir;
    let project_name = `${_toSnakeCase(config.scope)}_${_toSnakeCase(config.name)}`;

    // generate scripts
    let scripts = ['build.sh', 'format.sh', 'install.sh'];
    scripts.forEach(item => {
      let tmpl_path = path.join(__dirname, `./files/scripts/${item}.tmpl`);
      let output_path = path.join(outputDir, `scripts/${item}`);
      this.renderAuto(tmpl_path, output_path, {});
    });

    let tmp = [];
    let param_import = '';
    if (config.libraries) {
      Object.keys(config.libraries).forEach((key) => {
        const item = config.libraries[key];
        let [scope, package_name] = item.split(':');
        let cpp_project_name = `${_toSnakeCase(scope)}_${_toSnakeCase(package_name)}`;
        tmp.push(cpp_project_name);
      });
      param_import = tmp.join(' ');
    }

    // generate CMakeLists.txt
    if (config.withTest) {
      this.renderAuto(
        path.join(__dirname, './files/CMakeLists.txt.test.tmpl'),
        path.join(outputDir, 'CMakeLists.txt'), {
          param_scope: _toSnakeCase(config.scope),
          param_package: _avoidKeywords(_toSnakeCase(config.name)),
          param_import: param_import
        }
      );
      // generate tests/main.cpp
      let tests_main_path = path.join(outputDir, 'tests/main.cpp');
      if (!fs.existsSync(tests_main_path)) {
        this.renderAuto(
          path.join(__dirname, './files/tests.main.cpp.tmpl'),
          tests_main_path, {}
        );
      }
      // generate scripts/run_ut.sh
      this.renderAuto(
        path.join(__dirname, './files/scripts/run_ut.sh.tmpl'),
        path.join(outputDir, 'scripts/run_ut.sh'), {
          package: project_name
        }
      );
      // generate scripts/codecov.sh
      this.renderAuto(
        path.join(__dirname, './files/scripts/codecov.sh.tmpl'),
        path.join(outputDir, 'scripts/codecov.sh'), {
          package: project_name
        }
      );
      // generate external/googletest
      let targetPath = path.join(outputDir, 'external/googletest');
      if (!fs.existsSync(path.dirname(targetPath))) {
        fs.mkdirSync(path.dirname(targetPath), {
          recursive: true
        });
      }
      // fs.writeFileSync(path.join(outputDir, 'external/CMakeLists.txt'), `message(STATUS "Install libraries for development")${os.EOL}add_subdirectory(googletest)${os.EOL}`);
      this.renderAuto(
        path.join(__dirname, './files/CMakeLists.txt.googletest.tmpl'),
        path.join(outputDir, 'external/googletest/CMakeLists.txt'), {}
      );
      this.renderAuto(
        path.join(__dirname, './files/CMakeLists.txt.in.googletest.tmpl'),
        path.join(outputDir, 'external/googletest/CMakeLists.txt.in'), {}
      );
      this.renderAuto(
        path.join(__dirname, './files/CodeCoverage.cmake.tmpl'),
        path.join(outputDir, 'cmake/CodeCoverage.cmake'), {}
      );
    } else {
      this.renderAuto(
        path.join(__dirname, './files/CMakeLists.txt.tmpl'),
        path.join(outputDir, 'CMakeLists.txt'), {
          param_scope: _toSnakeCase(config.scope),
          param_package: _avoidKeywords(_toSnakeCase(config.name)),
          param_import: param_import
        }
      );
    }

    // generate CMake.in
    this.renderAuto(
      path.join(__dirname, './files/cmake.in'),
      path.join(outputDir, `cmake/${project_name}Config.cmake.in`), {
        param_scope: _toSnakeCase(config.scope),
        param_package: _avoidKeywords(_toSnakeCase(config.name)),
        param_import: param_import
      }
    );

    // generate external/CMakeLists.txt
    let tmpl_path = path.join(__dirname, './files/CMakeLists.txt.external.libraries.tmpl');
    let keys = Object.keys(requirePackage);
    let libraries = '';
    if (keys.length > 0) {
      Object.keys(requirePackage).forEach(key => {
        const item = requirePackage[key];
        const package_name = `${_toSnakeCase(item.scope)}_${_toSnakeCase(item.name)}`;
        // let git_link = '';
        let git_tag = 'master';
        let git_scope = item.scope;
        let git_project = item.name;
        if (item.cpp && item.cpp.packageInfo && item.cpp.packageInfo.git) {
          if (item.cpp.packageInfo.git.scope) {
            git_scope = item.cpp.packageInfo.git.scope;
          }
          if (item.cpp.packageInfo.git.project) {
            git_project = item.cpp.packageInfo.git.project;
          }
        }
        let git_link = `https://github.com/${git_scope}/${git_project}.git`;
        if (item.releases && item.releases.cpp) {
          const [git_repo, tag] = item.releases.cpp.split(':');
          git_tag = tag;
          git_link = `https://github.com/${git_repo}.git`;
        }
        this.renderAuto(
          tmpl_path,
          path.join(outputDir, `external/${package_name}/CMakeLists.txt`), {
            package_name: package_name,
            git_link: git_link,
            git_tag: git_tag,
            project_name: project_name
          }
        );
        libraries += `add_subdirectory(${package_name})${os.EOL}`;
      });
    }
    this.renderAuto(
      path.join(__dirname, './files/CMakeLists.txt.external.tmpl'),
      path.join(outputDir, 'external/CMakeLists.txt'), {
        libraries: libraries,
        libraries_dev: config.withTest ? 'add_subdirectory(googletest)' : ''
      }
    );

    // generate other files
    let git_scope = config.scope;
    let git_project = config.name;
    if (config.packageInfo && config.packageInfo.git && config.packageInfo.git.scope) {
      if (config.packageInfo.git.scope) {
        git_scope = config.packageInfo.git.scope;
      }
      if (config.packageInfo.git.project) {
        git_project = config.packageInfo.git.project;
      }
    }

    if (config.packageInfo.files) {
      Object.keys(config.packageInfo.files).forEach((key) => {
        let tmpl_path = config.packageInfo.files[key].tmpl;
        let output_path = path.join(outputDir, config.packageInfo.files[key].path);
        this.renderAuto(
          tmpl_path,
          output_path, {
            scope: _upperFirst(config.scope),
            name: config.name,
            git_scope: git_scope,
            git_project: git_project,
            project_name: `${_toSnakeCase(config.scope)}_${_toSnakeCase(config.name)}`
          }
        );
      });
    }

    // generate git ignore file
    this.renderAuto(
      path.join(__dirname, './files/gitignore.tmpl'),
      path.join(outputDir, '.gitignore'), {}
    );
  }
}

module.exports = PackageInfo;