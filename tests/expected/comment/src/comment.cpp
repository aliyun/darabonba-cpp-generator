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

using namespace Darabonba_Comment;

Darabonba_Comment::Client::Client() {
  // string declate comment
  string str = "sss";
  // new model instance comment
  shared_ptr<Test1> modelInstance = make_shared<Test1>(map<string, string>({
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
  shared_ptr<Darabonba::Request> _lastRequest;
  std::exception _lastException;
  int _now = 0;
  int _retryTimes = 0;
  while (Darabonba::Core::allowRetry(make_shared<boost::any>(runtime_["retry"]), make_shared<int>(_retryTimes), make_shared<int>(_now))) {
    if (_retryTimes > 0) {
      int _backoffTime = Darabonba::Core::getBackoffTime(make_shared<boost::any>(runtime_["backoff"]), make_shared<int>(_retryTimes));
      if (_backoffTime > 0) {
        Darabonba::Core::sleep(make_shared<int>(_backoffTime));
      }
    }
    _retryTimes = _retryTimes + 1;
    try {
      shared_ptr<Darabonba::Request> request_ = make_shared<Darabonba::Request>();
      // new model instance comment
      shared_ptr<Test1> modelInstance = make_shared<Test1>(map<string, string>({
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
      shared_ptr<Darabonba::Response> response_ = make_shared<Darabonba::Response>(Darabonba::Core::doAction(request_, runtime_));
      // static async function call
      Client::testFunc(make_shared<string>("test"), make_shared<bool>(true));
      // return comment
      return;
    }
    catch (std::exception &e) {
      if (Darabonba::Core::isRetryable(e)) {
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
  shared_ptr<Darabonba::Request> _lastRequest;
  std::exception _lastException;
  int _now = 0;
  int _retryTimes = 0;
  while (Darabonba::Core::allowRetry(make_shared<boost::any>(runtime_["retry"]), make_shared<int>(_retryTimes), make_shared<int>(_now))) {
    if (_retryTimes > 0) {
      int _backoffTime = Darabonba::Core::getBackoffTime(make_shared<boost::any>(runtime_["backoff"]), make_shared<int>(_retryTimes));
      if (_backoffTime > 0) {
        Darabonba::Core::sleep(make_shared<int>(_backoffTime));
      }
    }
    _retryTimes = _retryTimes + 1;
    try {
      shared_ptr<Darabonba::Request> request_ = make_shared<Darabonba::Request>();
      // new model instance comment
      shared_ptr<Test3> modelInstance = make_shared<Test3>(map<string, boost::any>({
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
      shared_ptr<Darabonba::Response> response_ = make_shared<Darabonba::Response>(Darabonba::Core::doAction(request_, runtime_));
      // empty return comment
      // back comment
    }
    catch (std::exception &e) {
      if (Darabonba::Core::isRetryable(e)) {
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

void Darabonba_Comment::Client::testFunc(shared_ptr<string> str, shared_ptr<bool> val) {
  // empty comment1
  // empty comment2
}

