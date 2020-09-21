// top comment
// This file is auto-generated, don't edit it. Thanks.

#ifndef DARABONBA_COMMENT_H_
#define DARABONBA_COMMENT_H_

#include <darabonba/core.hpp>
#include <iostream>
#include <vector>

using namespace std;

namespace Darabonba_Comment {
class Test1 : public Model {
protected:
  void _init(){
    _name = map<string, string>({
      {"test" , "test",
      {"test2" , "test2",
    });
  }
public:
  Test1() {_init();};
  explicit Test1(const std::map<string, boost::any> &config) : Model(config) {_init();};


  map<string, boost::any> toMap() {
    map<string, boost::any> res;
    if (nullptr != test) {
      res["test"] = boost::any(*test);
    }
    if (nullptr != test2) {
      res["test2"] = boost::any(*test2);
    }
    return res;
  }

  string *test{};
  // model的test back comment
  string *test2{};
  // model的test2 back comment

  ~Test1() {
    delete test;
    delete test2;
  };
};
class Test2 : public Model {
protected:
  void _init(){
    _name = map<string, string>({
      {"test" , "test",
      {"test2" , "test2",
    });
  }
public:
  Test2() {_init();};
  explicit Test2(const std::map<string, boost::any> &config) : Model(config) {_init();};


  map<string, boost::any> toMap() {
    map<string, boost::any> res;
    if (nullptr != test) {
      res["test"] = boost::any(*test);
    }
    if (nullptr != test2) {
      res["test2"] = boost::any(*test2);
    }
    return res;
  }

  // model的test front comment
  string *test{};
  // model的test front comment
  string *test2{};

  ~Test2() {
    delete test;
    delete test2;
  };
};
class Test3 : public Model {
protected:
  void _init(){
    _name = map<string, string>({
      {"test" , "test",
      {"test1" , "test1",
    });
  }
public:
  Test3() {_init();};
  explicit Test3(const std::map<string, boost::any> &config) : Model(config) {_init();};


  map<string, boost::any> toMap() {
    map<string, boost::any> res;
    if (nullptr != test) {
      res["test"] = boost::any(*test);
    }
    if (nullptr != test1) {
      res["test1"] = boost::any(*test1);
    }
    return res;
  }

  // model的test front comment
  string *test{};
  // empty comment1
  // empy comment2
  string *test1{};
  // model的test back comment

  ~Test3() {
    delete test;
    delete test1;
  };
};
class Client {
public:
  // type's comment
  vector<string> *_a{};
  Client();
  void testAPI();
  void testAPI2();
  static void staticFunc();
  static void testFunc(string *str, bool *val);

  ~Client() {
    delete _a;
  };
};
} // namespace Darabonba_Comment

#endif
