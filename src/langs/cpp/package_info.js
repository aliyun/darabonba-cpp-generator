'use strict';

const path = require('path');
const os = require('os');
const fs = require('fs');
// const debug = require('../../lib/debug');
const BasePackageInfo = require('../common/package_info');
const { _toSnakeCase, _upperFirst, _avoidKeywords } = require('../../lib/helper');

class PackageInfo extends BasePackageInfo {
  emit(requirePackage) {
    this.requirePackage = requirePackage;
    this.project_name = `${_toSnakeCase(this.config.scope)}_${_toSnakeCase(this.config.name)}`;
    this.imports = [];

    // generate external
    this.generateExternal();

    // generate other files
    this.generateFiles();

    // generate shell scripts
    this.generateScripts();

    // generate files in cmake dir
    this.generateCMakeDir();

    // generate main files : CMakeLists.tx | tests/main.cpp
    this.generateMainFiles();
  }

  resolveGitInfo(config) {
    let git_scope = '';
    let git_project = '';
    let git_link = '';
    let git_tag = 'master';
    const package_name = `${_toSnakeCase(config.scope)}_${_toSnakeCase(config.name)}`;
    const package_info = config.packageInfo ? config.packageInfo : config.cpp.packageInfo;
    if (package_info.git && package_info.git.scope) {
      if (package_info.git.scope) {
        git_scope = package_info.git.scope;
      }
      if (package_info.git.project) {
        git_project = package_info.git.project;
      }
      if (config.releases && config.releases.cpp) {
        const [git_repo, tag] = config.releases.cpp.split(':');
        git_link = `https://github.com/${git_repo}.git`;
        git_tag = tag;
      } else {
        git_link = `https://github.com/${git_scope}/${git_project}.git`;
      }
    }
    return { package_name, git_scope, git_project, git_link, git_tag };
  }

  generateFiles() {
    const { git_scope, git_project } = this.resolveGitInfo(this.config);
    if (this.config.packageInfo.files) {
      Object.keys(this.config.packageInfo.files).forEach((key) => {
        let tmpl_path = this.config.packageInfo.files[key].tmpl;
        let output_path = path.join(this.config.dir, this.config.packageInfo.files[key].path);
        this.renderAuto(
          tmpl_path,
          output_path, {
            scope: _upperFirst(this.config.scope),
            name: this.config.name,
            git_scope: git_scope,
            git_project: git_project,
            project_name: `${_toSnakeCase(this.config.scope)}_${_toSnakeCase(this.config.name)}`
          }
        );
      });
    }

    // generate git ignore file
    this.renderAuto(
      path.join(__dirname, './files/gitignore.tmpl'),
      path.join(this.config.dir, '.gitignore'), {}
    );
  }

  generateMainFiles() {
    let param_scope = _toSnakeCase(this.config.scope);
    let param_package = _avoidKeywords(_toSnakeCase(this.config.name));
    let template = fs.readFileSync(path.join(__dirname, './files/main/CMakeLists.txt.tmpl'), 'utf-8');
    if (this.config.withTest) {
      let tests_main_path = path.join(this.config.dir, 'tests/main.cpp');
      if (!fs.existsSync(tests_main_path)) {
        this.renderAuto(
          path.join(__dirname, './files/main/tests.main.cpp.tmpl'),
          tests_main_path, {}
        );
      }
      template = this.render(template, {
        with_test: this.render(fs.readFileSync(path.join(__dirname, './files/main/with_test.CMakeLists.txt.tmpl'), 'utf-8'), {
          param_scope,
          param_package,
        }),
        param_import: this.imports.join(' ')
      });
    } else {
      template = this.render(template, { with_test: '' });
    }
    this.renderContent(
      template,
      path.join(this.config.dir, 'CMakeLists.txt'), {
        param_scope,
        param_package,
        param_import: this.imports.join(' ')
      }
    );
  }

  generateScripts() {
    // generate scripts
    let scripts = ['build.sh', 'format.sh', 'install.sh'];
    if (this.config.withTest) {
      scripts.push('codecov.sh');
      scripts.push('run_ut.sh');
    }
    scripts.forEach(item => {
      let tmpl_path = path.join(__dirname, `./files/scripts/${item}.tmpl`);
      let output_path = path.join(this.config.dir, `scripts/${item}`);
      this.renderAuto(tmpl_path, output_path, {
        project_name: this.project_name
      });
    });
  }

  generateCMakeDir() {
    // generate CMake.in
    this.renderAuto(
      path.join(__dirname, './files/cmake/cmake.in'),
      path.join(this.config.dir, `cmake/${this.project_name}Config.cmake.in`), {
        param_scope: _toSnakeCase(this.config.scope),
        param_package: _avoidKeywords(_toSnakeCase(this.config.name)),
        param_import: this.imports.join(' ')
      }
    );
    if (this.config.withTest) {
      this.renderAuto(
        path.join(__dirname, './files/cmake/CodeCoverage.cmake.tmpl'),
        path.join(this.config.dir, 'cmake/CodeCoverage.cmake'), {}
      );
    }
  }

  generateExternal() {
    // generate external/CMakeLists.txt
    let tmpl_path = path.join(__dirname, './files/external/CMakeLists.txt.tmpl');
    let keys = Object.keys(this.requirePackage);
    let libraries = '';
    if (keys.length > 0) {
      Object.keys(this.requirePackage).forEach(key => {
        const item = this.requirePackage[key];
        const { package_name, git_link, git_tag } = this.resolveGitInfo(item);
        this.renderAuto(
          tmpl_path,
          path.join(this.config.dir, `external/${package_name}/CMakeLists.txt`), {
            package_name: package_name,
            git_link: git_link,
            git_tag: git_tag,
            project_name: this.project_name
          }
        );
        libraries += `add_subdirectory(${package_name})${os.EOL}`;
        this.imports.push(package_name);
      });
    }
    this.renderContent(
      'message(STATUS "Install libraries")\n${libraries}${libraries_dev}',
      path.join(this.config.dir, 'external/CMakeLists.txt'), {
        libraries: libraries,
        libraries_dev: this.config.withTest ? 'if (ENABLE_UNIT_TESTS)\n  add_subdirectory(googletest)\nendif()\n' : ''
      }
    );
    if (this.config.withTest) {
      this.renderAuto(
        path.join(__dirname, './files/external/googletest.CMakeLists.txt.tmpl'),
        path.join(this.config.dir, 'external/googletest/CMakeLists.txt'), {}
      );
      this.renderAuto(
        path.join(__dirname, './files/external/googletest.CMakeLists.txt.in.tmpl'),
        path.join(this.config.dir, 'external/googletest/CMakeLists.txt.in'), {}
      );
    }
  }
}
module.exports = PackageInfo;