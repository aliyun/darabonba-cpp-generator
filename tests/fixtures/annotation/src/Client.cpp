#include <darabonba/Core.hpp>
#include <darabonba/test.hpp>
#include <darabonba/policy/Retry.hpp>
#include <darabonba/Runtime.hpp>
#include <darabonba/Exception.hpp>
using namespace std;
using json = nlohmann::json;
namespace Darabonba
{

/**
  Init Func
*/
Darabonba::Client::Client(){
}


void Client::testAPI() {
  Darabonba::RuntimeOptions runtime_(json({
    }));

  shared_ptr<Darabonba::Http::Request> _lastRequest = nullptr;
  shared_ptr<Darabonba::Http::MCurlResponse> _lastResponse = nullptr;
  int _retriesAttempted = 0;
  Darabonba::Policy::RetryPolicyContext _context = json({
    {"retriesAttempted" , _retriesAttempted}
  });
  while (Darabonba::allowRetry(runtime_.getRetryOptions(), _context)) {
    if (_retriesAttempted > 0) {
      int _backoffTime = Darabonba::getBackoffTime(runtime_.getRetryOptions(), _context);
      if (_backoffTime > 0) {
        Darabonba::sleep(_backoffTime);
      }
    }
    _retriesAttempted++;
    try {
      Darabonba::Http::Request request_ = Darabonba::Http::Request();
      _lastRequest = make_shared<Darabonba::Http::Request>(request_);
      auto futureResp_ = Darabonba::Core::doAction(request_, runtime_);
      shared_ptr<Darabonba::Http::MCurlResponse> response_ = futureResp_.get();
      _lastResponse  = response_;

      return ;
    } catch (const Darabonba::DaraException& ex) {
      _context = Darabonba::Policy::RetryPolicyContext(json({
        {"retriesAttempted" , _retriesAttempted},
        {"lastRequest" , _lastRequest},
        {"lastResponse" , _lastResponse},
        {"exception" , ex},
      }));
      continue;
    }
  }

  throw Darabonba::UnretryableException(_context);
}

/**
  testFunc
*/
void Client::testFunc() {
}
} // namespace Darabonba