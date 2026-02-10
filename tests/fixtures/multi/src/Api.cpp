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

  std::exception_ptr _lastExceptionPtr;
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
      request_.setProtocol("https");
      request_.setMethod("DELETE");
      request_.setPathname("/");
      request_.setHeaders(json({
        {"host" , "test.aliyun.com"},
        {"accept" , "application/json"}
      }).get<map<string, string>>());
      request_.setQuery(Util::Util::getQuery());
      auto futureResp_ = Darabonba::Core::doAction(request_, runtime_);
      shared_ptr<Darabonba::Http::MCurlResponse> response_ = futureResp_.get();

      return response_->getStatusCode();
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

} // namespace Darabonba
} // namespace Api