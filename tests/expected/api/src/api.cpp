// This file is auto-generated, don't edit it. Thanks.

#include <darabonba/api.hpp>
#include <boost/any.hpp>
#include <boost/throw_exception.hpp>
#include <darabonba/core.hpp>
#include <iostream>
#include <map>

using namespace std;

Darabonba_Api::Client::Client(){}
void Darabonba_Api::Client::hello() {
  Darabonba::Request request_ = Darabonba::Request();
  request_.method = "GET";
  request_.pathname = "/";
  request_.headers = {
    {"host", "www.test.com"}
  };
  Darabonba::Request _lastRequest = request_;
  Darabonba::Response response_= Darabonba::Core::doAction(request_);
  return;
}

void Darabonba_Api::Client::helloRuntime() {
  map<string, boost::any> runtime_ = map<string, boost::any>();
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
      request_.method = "GET";
      request_.pathname = "/";
      request_.headers = {
        {"host", "www.test.com"}
      };
      _lastRequest = request_;
      Darabonba::Response response_= Darabonba::Core::doAction(request_, runtime_);
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

