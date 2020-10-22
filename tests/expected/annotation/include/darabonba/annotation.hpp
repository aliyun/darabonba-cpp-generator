// This file is auto-generated, don't edit it. Thanks.

#ifndef DARABONBA_ANNOTATION_H_
#define DARABONBA_ANNOTATION_H_

#include <boost/throw_exception.hpp>
#include <darabonba/core.hpp>
#include <iostream>

using namespace std;

namespace Darabonba_Annotation {
class Test : public Darabonba::Model {
public:
  Test() {}
  explicit Test(const std::map<string, boost::any> &config) : Darabonba::Model(config) {
    fromMap(config);
  };

  void validate() override {
    if (!test) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("test is required.")));
    }
  }

  map<string, boost::any> toMap() override {
    map<string, boost::any> res;
    if (test) {
      res["test"] = boost::any(*test);
    }
    return res;
  }

  void fromMap(map<string, boost::any> m) override {
    if (m.find("test") != m.end()) {
      test = make_shared<string>(boost::any_cast<string>(m["test"]));
    }
  }

  shared_ptr<string> test{};

  ~Test() {};
};
class Client {
public:
  shared_ptr<string> _a{};
  Client();
  void testAPI();
  static void testFunc();

  ~Client() {};
};
} // namespace Darabonba_Annotation

#endif
