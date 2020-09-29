// This file is auto-generated, don't edit it. Thanks.

#include <darabonba/annotation.hpp>
#include <boost/any.hpp>
#include <boost/throw_exception.hpp>
#include <darabonba/core.hpp>
#include <iostream>
#include <map>

using namespace std;

Darabonba_Annotation::Client::Client(){}
void Darabonba_Annotation::Client::testAPI() {
  map<string, boost::any> runtime_ = map<string, boost::any>();
  Darabonba::Request _lastRequest;
  std::exception _lastException;
  int _now = 0;
  int _retryTimes = 0;
  while (Darabonba::Core::allowRetry(shared_ptr<boost::any>(new boost::any(runtime_["retry"])), shared_ptr<int>(new int(_retryTimes)), shared_ptr<int>(new int(_now)))) {
    if (_retryTimes > 0) {
      int _backoffTime = Darabonba::Core::getBackoffTime(shared_ptr<boost::any>(new boost::any(runtime_["backoff"])), shared_ptr<int>(new int(_retryTimes)));
      if (_backoffTime > 0) {
        Darabonba::Core::sleep(shared_ptr<int>(new int(_backoffTime)));
      }
    }
    _retryTimes = _retryTimes + 1;
    try {
      Darabonba::Request request_ = Darabonba::Request();
      _lastRequest = request_;
      Darabonba::Response response_= Darabonba::Core::doAction(request_, runtime_);
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

void Darabonba_Annotation::Client::testFunc() {
}

