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
  shared_ptr<string> str = make_shared<string>("sss");
  // new model instance comment
  shared_ptr<Test1> modelInstance = make_shared<Test1>(map<string, boost::any>({
    {"test", boost::any(string("test"))},
    // test declare back comment
    {"test2", boost::any(string("test2"))},
    // test2 declare back comment
  }));
  shared_ptr<vector<boost::any>> array = make_shared<vector<boost::any>>(vector<boost::any>({
    // array string comment
    "string",
    // array number comment
    300
  }));
};

void Darabonba_Comment::Client::testAPI() {
  shared_ptr<map<string, boost::any>> runtime_ = make_shared<map<string, boost::any>>(map<string, boost::any>({
    // empty runtime comment
    // another runtime comment
  })
);
  shared_ptr<Darabonba::Request> _lastRequest;
  shared_ptr<std::exception> _lastException;
  shared_ptr<int> _now = make_shared<int>(0);
  shared_ptr<int> _retryTimes = make_shared<int>(0);
  while (Darabonba::Core::allowRetry(make_shared<boost::any>((*runtime_)["retry"]), _retryTimes, _now)) {
    if (*_retryTimes > 0) {
      shared_ptr<int> _backoffTime = make_shared<int>(Darabonba::Core::getBackoffTime(make_shared<boost::any>((*runtime_)["backoff"]), _retryTimes));
      if (*_backoffTime > 0) {
        Darabonba::Core::sleep(_backoffTime);
      }
    }
    _retryTimes = make_shared<int>(*_retryTimes + 1);
    try {
      shared_ptr<Darabonba::Request> request_ = make_shared<Darabonba::Request>();
      // new model instance comment
      shared_ptr<Test1> modelInstance = make_shared<Test1>(map<string, boost::any>({
        // test declare front comment
        {"test", boost::any(string("test"))},
        // test2 declare front comment
        {"test2", boost::any(string("test2"))}
      }));
      // number declare comment
      shared_ptr<int> num = make_shared<int>(123);
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
        _lastException = make_shared<std::exception>(e);
        continue;
      }
      BOOST_THROW_EXCEPTION(e);
    }
  }
  BOOST_THROW_EXCEPTION(Darabonba::UnretryableError(_lastRequest, _lastException));
}

void Darabonba_Comment::Client::testAPI2() {
  shared_ptr<map<string, boost::any>> runtime_ = make_shared<map<string, bool>>(map<string, bool>({
    // runtime retry comment
    {"retry", true},
    // runtime back comment one
    // runtime back comment two
  })
);
  shared_ptr<Darabonba::Request> _lastRequest;
  shared_ptr<std::exception> _lastException;
  shared_ptr<int> _now = make_shared<int>(0);
  shared_ptr<int> _retryTimes = make_shared<int>(0);
  while (Darabonba::Core::allowRetry(make_shared<boost::any>((*runtime_)["retry"]), _retryTimes, _now)) {
    if (*_retryTimes > 0) {
      shared_ptr<int> _backoffTime = make_shared<int>(Darabonba::Core::getBackoffTime(make_shared<boost::any>((*runtime_)["backoff"]), _retryTimes));
      if (*_backoffTime > 0) {
        Darabonba::Core::sleep(_backoffTime);
      }
    }
    _retryTimes = make_shared<int>(*_retryTimes + 1);
    try {
      shared_ptr<Darabonba::Request> request_ = make_shared<Darabonba::Request>();
      // new model instance comment
      shared_ptr<Test3> modelInstance = make_shared<Test3>(map<string, boost::any>({
        // empty model
      }));
      // boolean declare comment
      shared_ptr<bool> bool_ = make_shared<bool>(true);
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
        _lastException = make_shared<std::exception>(e);
        continue;
      }
      BOOST_THROW_EXCEPTION(e);
    }
  }
  BOOST_THROW_EXCEPTION(Darabonba::UnretryableError(_lastRequest, _lastException));
}

void Darabonba_Comment::Client::staticFunc() {
  shared_ptr<vector<boost::any>> a = make_shared<vector<boost::any>>(vector<boost::any>({
    // empty annotation comment
  }));
}

void Darabonba_Comment::Client::testFunc(shared_ptr<string> str, shared_ptr<bool> val) {
  // empty comment1
  // empty comment2
}

