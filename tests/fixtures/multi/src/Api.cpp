#include <darabonba/Core.hpp>
#include <darabonba/Api.hpp>
#include <darabonba/policy/Retry.hpp>
#include <darabonba/Runtime.hpp>
#include <darabonba/Exception.hpp>
#include <map>
#include <darabonba/lib/Util.hpp>
using namespace std;
using json = nlohmann::json;
using namespace Darabonba::Api::Lib;
namespace Darabonba
{
namespace Api
{

Darabonba::Api::Client::Client(){
}


int64_t Client::test3() {
  Darabonba::RuntimeOptions runtime_(json({
    {"timeouted", "retry"}
    }));

  shared_ptr<Darabonba::Http::Request> _lastRequest = nullptr;
  shared_ptr<Darabonba::Http::MCurlResponse> _lastResponse = nullptr;
  Darabonba::Exception _lastException;
  int _retriesAttempted = 0;
  Darabonba::Policy::RetryPolicyContext _context = json({
    {"retriesAttempted" , _retriesAttempted}
  });
  while (Darabonba::allowRetry(runtime_.retryOptions(), _context)) {
    if (_retriesAttempted > 0) {
      int _backoffTime = Darabonba::getBackoffTime(runtime_.retryOptions(), _context);
      if (_backoffTime > 0) {
        Darabonba::sleep(_backoffTime);
      }
    }
    _retriesAttempted++;
    try {
      Darabonba::Http::Request request_ = Darabonba::Http::Request();
      request_.setProtocol("https");
      request_.setMethod("DELETE");
      request_.setPathname("/");
      request_.setHeaders(json({
        {"host" , "test.aliyun.com"},
        {"accept" , "application/json"}
      }).get<map<string, string>>());
      request_.setQuery(Util::Util::getQuery());
      _lastRequest = make_shared<Darabonba::Http::Request>(request_);
      auto futureResp_ = Darabonba::Core::doAction(request_, runtime_);
      shared_ptr<Darabonba::Http::MCurlResponse> response_ = futureResp_.get();
      _lastResponse  = response_;

      return response_->statusCode();
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

  throw *_context.exception();
}

} // namespace Darabonba
} // namespace Api