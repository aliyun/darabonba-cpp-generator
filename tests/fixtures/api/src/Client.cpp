#include <darabonba/Core.hpp>
#include <darabonba/test.hpp>
#include <map>
#include <darabonba/policy/Retry.hpp>
#include <darabonba/Runtime.hpp>
#include <darabonba/Exception.hpp>
using namespace std;
using json = nlohmann::json;
namespace Darabonba
{

Darabonba::Client::Client(){
}


void Client::hello() {
Darabonba::RuntimeOptions runtime_(json({}));

  Darabonba::Http::Request request_ = Darabonba::Http::Request();
  request_.setMethod("GET");
  request_.setPathname("/");
  request_.setHeaders(json({
    {"host" , "www.test.com"},
    {"Cookie" , "test"}
  }).get<map<string, string>>());
  auto futureResp_ = Darabonba::Core::doAction(request_, runtime_);
  shared_ptr<Darabonba::Http::MCurlResponse> response_ = futureResp_.get();

  return ;
}

void Client::helloRuntime() {
  Darabonba::RuntimeOptions runtime_(json({
    }));

  shared_ptr<Darabonba::Http::Request> _lastRequest = nullptr;
  shared_ptr<Darabonba::Http::MCurlResponse> _lastResponse = nullptr;
  Darabonba::Exception _lastException;
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
      request_.setMethod("GET");
      request_.setPathname("/");
      request_.setHeaders(json({
        {"host" , "www.test.com"},
        {"Cookie" , "test"}
      }).get<map<string, string>>());
      _lastRequest = make_shared<Darabonba::Http::Request>(request_);
      auto futureResp_ = Darabonba::Core::doAction(request_, runtime_);
      shared_ptr<Darabonba::Http::MCurlResponse> response_ = futureResp_.get();
      _lastResponse  = response_;

      return ;
    } catch (const Darabonba::Exception& ex) {
      _context = Darabonba::Policy::RetryPolicyContext(json({
        {"retriesAttempted" , _retriesAttempted},
        {"lastRequest" , _lastRequest},
        {"lastResponse" , _lastResponse},
        {"exception" , ex},
      }));
      continue;
    }
  }

  throw *_context.getException();
}

} // namespace Darabonba