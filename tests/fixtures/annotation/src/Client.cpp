#include <darabonba/Core.hpp>
#include <darabonba/annotation.hpp>
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

  std::exception_ptr _lastExceptionPtr;
  int _retriesAttempted = 0;
  Darabonba::Policy::RetryPolicyContext _context = json({
    {"retriesAttempted" , _retriesAttempted}
  });
  while (Darabonba::shouldRetry(runtime_.getRetryOptions(), _context)) {
    if (_retriesAttempted > 0) {
      int _backoffTime = Darabonba::getBackoffTime(runtime_.getRetryOptions(), _context);
      if (_backoffTime > 0) {
        Darabonba::sleep(_backoffTime);
      }
    }
    _retriesAttempted++;
    try {
      Darabonba::Http::Request request_ = Darabonba::Http::Request();
      auto futureResp_ = Darabonba::Core::doAction(request_, runtime_);
      shared_ptr<Darabonba::Http::MCurlResponse> response_ = futureResp_.get();

      return ;
    } catch (const Darabonba::DaraException& ex) {
      _lastExceptionPtr = std::current_exception();
      _context = Darabonba::Policy::RetryPolicyContext(json({
        {"retriesAttempted" , _retriesAttempted},
        {"exception" , ex},
      }));
      continue;
    }
  }

  std::rethrow_exception(_lastExceptionPtr);
}

/**
  testFunc
*/
void Client::testFunc() {
}
} // namespace Darabonba