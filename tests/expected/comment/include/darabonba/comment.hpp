// top comment
// This file is auto-generated, don't edit it. Thanks.

#ifndef DARABONBA_COMMENT_H_
#define DARABONBA_COMMENT_H_

#include <boost/throw_exception.hpp>
#include <darabonba/core.hpp>
#include <iostream>
#include <vector>

using namespace std;

namespace Darabonba_Comment {
class Test1 : public Darabonba::Model {
public:
  Test1() {}
  explicit Test1(const std::map<string, boost::any> &config) : Darabonba::Model(config) {
    fromMap(config);
  };

  void validate() override {
    if (!test) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("test is required.")));
    }
    if (!test2) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("test2 is required.")));
    }
  }

  map<string, boost::any> toMap() override {
    map<string, boost::any> res;
    if (test) {
      res["test"] = boost::any(*test);
    }
    if (test2) {
      res["test2"] = boost::any(*test2);
    }
    return res;
  }

  void fromMap(map<string, boost::any> m) override {
    if (m.find("test") != m.end()) {
      test = make_shared<string>(boost::any_cast<string>(m["test"]));
    }
    if (m.find("test2") != m.end()) {
      test2 = make_shared<string>(boost::any_cast<string>(m["test2"]));
    }
  }

  shared_ptr<string> test{};
  // model的test back comment
  shared_ptr<string> test2{};
  // model的test2 back comment

  ~Test1() {};
};
class Test2 : public Darabonba::Model {
public:
  Test2() {}
  explicit Test2(const std::map<string, boost::any> &config) : Darabonba::Model(config) {
    fromMap(config);
  };

  void validate() override {
    if (!test) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("test is required.")));
    }
    if (!test2) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("test2 is required.")));
    }
  }

  map<string, boost::any> toMap() override {
    map<string, boost::any> res;
    if (test) {
      res["test"] = boost::any(*test);
    }
    if (test2) {
      res["test2"] = boost::any(*test2);
    }
    return res;
  }

  void fromMap(map<string, boost::any> m) override {
    if (m.find("test") != m.end()) {
      test = make_shared<string>(boost::any_cast<string>(m["test"]));
    }
    if (m.find("test2") != m.end()) {
      test2 = make_shared<string>(boost::any_cast<string>(m["test2"]));
    }
  }

  // model的test front comment
  shared_ptr<string> test{};
  // model的test front comment
  shared_ptr<string> test2{};

  ~Test2() {};
};
class Test3 : public Darabonba::Model {
public:
  Test3() {}
  explicit Test3(const std::map<string, boost::any> &config) : Darabonba::Model(config) {
    fromMap(config);
  };

  void validate() override {
    if (!test) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("test is required.")));
    }
    if (!test1) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("test1 is required.")));
    }
  }

  map<string, boost::any> toMap() override {
    map<string, boost::any> res;
    if (test) {
      res["test"] = boost::any(*test);
    }
    if (test1) {
      res["test1"] = boost::any(*test1);
    }
    return res;
  }

  void fromMap(map<string, boost::any> m) override {
    if (m.find("test") != m.end()) {
      test = make_shared<string>(boost::any_cast<string>(m["test"]));
    }
    if (m.find("test1") != m.end()) {
      test1 = make_shared<string>(boost::any_cast<string>(m["test1"]));
    }
  }

  // model的test front comment
  shared_ptr<string> test{};
  // empty comment1
  // empy comment2
  shared_ptr<string> test1{};
  // model的test back comment

  ~Test3() {};
};
class Client {
public:
  // type's comment
  shared_ptr<vector<string>> _a{};
  Client();
  void testAPI();
  void testAPI2();
  static void staticFunc();
  static void testFunc(shared_ptr<string> str, shared_ptr<bool> val);

  ~Client() {};
};
} // namespace Darabonba_Comment

#endif
