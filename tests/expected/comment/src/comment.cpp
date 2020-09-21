// top comment
// This file is auto-generated, don't edit it. Thanks.

#include <darabonba/comment.hpp>
#include <boost/any.hpp>
#include <boost/throw_exception.hpp>
#include <darabonba/core.hpp>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

Darabonba_Comment::Client::Client() {
  // string declate comment
  string str = "sss";
  // new model instance comment
  Test1 modelInstance = Test1(new map<string, string>({
    {"test", "test"},
    // test declare back comment
    {"test2", "test2"},
    // test2 declare back comment
  }));
  vector<boost::any> array = vector<boost::any>({
    // array string comment
    "string",
    // array number comment
    300
  });
};

void Darabonba_Comment::Client::testAPI() {
  map<string, boost::any> runtime_ = {
    // empty runtime comment
    // another runtime comment
  };
  Darabonba::Request _lastRequest;
  std::exception _lastException;
  int _now = 0;
  int _retryTimes = 0;
  while (Darabonba::Core::allowRetry(new boost::any(runtime_["retry"]), new int(_retryTimes), new int(_now))) {
    if (_retryTimes > 0) {
      int _backoffTime = Darabonba::Core::getBackoffTime(new boost::any(runtime_["backoff"]), new int(_retryTimes));
      if (_backoffTime > 0) {
        Darabonba::Core::sleep(new int(_backoffTime));
      }
    }
    _retryTimes = _retryTimes + 1;
    try {
      Darabonba::Request request_ = Darabonba::Request();
      // new model instance comment
      Test1 modelInstance = Test1(new map<string, string>({
        // test declare front comment
        {"test", "test"},
        // test2 declare front comment
        {"test2", "test2"}
      }));
      // number declare comment
      int num = 123;
      // static function call comment
      Client::staticFunc();
      _lastRequest = request_;
      Darabonba::Response response_= Darabonba::Core::doAction(request_, runtime_);
      // static async function call
      Client::testFunc(new string("test"), new bool(true));
      // return comment
      return;
    }
    catch (std::exception &e) {
      if (Darabonba::Core::isRetryable(&e)) {
        _lastException = e;
        continue;
      }
      BOOST_THROW_EXCEPTION(e);
    }
  }
  BOOST_THROW_EXCEPTION(Darabonba::UnretryableError(_lastRequest, _lastException));
}

void Darabonba_Comment::Client::testAPI2() {
  map<string, boost::any> runtime_ = {
    // runtime retry comment
    {"retry", true},
    // runtime back comment one
    // runtime back comment two
  };
  Darabonba::Request _lastRequest;
  std::exception _lastException;
  int _now = 0;
  int _retryTimes = 0;
  while (Darabonba::Core::allowRetry(new boost::any(runtime_["retry"]), new int(_retryTimes), new int(_now))) {
    if (_retryTimes > 0) {
      int _backoffTime = Darabonba::Core::getBackoffTime(new boost::any(runtime_["backoff"]), new int(_retryTimes));
      if (_backoffTime > 0) {
        Darabonba::Core::sleep(new int(_backoffTime));
      }
    }
    _retryTimes = _retryTimes + 1;
    try {
      Darabonba::Request request_ = Darabonba::Request();
      // new model instance comment
      Test3 modelInstance = Test3(new map<string, boost::any>({
        // empty model
      }));
      // boolean declare comment
      bool bool_ = true;
      if (bool_) {
        // empty if
      }
      else {
        // empty else
      }
      // api function call comment
      testAPI();
      _lastRequest = request_;
      Darabonba::Response response_= Darabonba::Core::doAction(request_, runtime_);
      // empty return comment
      // back comment
    }
    catch (std::exception &e) {
      if (Darabonba::Core::isRetryable(&e)) {
        _lastException = e;
        continue;
      }
      BOOST_THROW_EXCEPTION(e);
    }
  }
  BOOST_THROW_EXCEPTION(Darabonba::UnretryableError(_lastRequest, _lastException));
}

void Darabonba_Comment::Client::staticFunc() {
  vector<boost::any> a = vector<boost::any>({
    // empty annotation comment
  });
}

void Darabonba_Comment::Client::testFunc(string *str, bool *val) {
  // empty comment1
  // empty comment2
}

