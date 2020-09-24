// This file is auto-generated, don't edit it. Thanks.

#ifndef DARABONBA_ANNOTATION_H_
#define DARABONBA_ANNOTATION_H_

#include <darabonba/core.hpp>
#include <iostream>

using namespace std;

namespace Darabonba_Annotation {
class Test : public Darabonba::Model {
protected:
  void _init(){
    _name = map<string, string>({
      {"test" , "test"},
    });
  }
public:
  Test() {_init();};
  explicit Test(const std::map<string, boost::any> &config) : Darabonba::Model(config) {_init();};


  map<string, boost::any> toMap() {
    map<string, boost::any> res;
    if (nullptr != test) {
      res["test"] = boost::any(*test);
    }
    return res;
  }

  string *test{};

  ~Test() {
    delete test;
    test = nullptr;
  };
};
class Client {
public:
  string *_a{};
  Client();
  void testAPI();
  static void testFunc();

  ~Client() {
    delete _a;
    _a = nullptr;
  };
};
} // namespace Darabonba_Annotation

#endif
