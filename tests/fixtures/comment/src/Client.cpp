#include <darabonba/Core.hpp>
#include <darabonba/test.hpp>
#include <map>
#include <darabonba/policy/Retry.hpp>
#include <darabonba/Runtime.hpp>
#include <darabonba/Exception.hpp>
using namespace std;
using json = nlohmann::json;
using namespace Darabonba::Models;
namespace Darabonba
{

/**
  Init Func
*/
Darabonba::Client::Client(){
  // string declate comment
  string str = "sss";
  // new model instance comment
  Test1 modelInstance = Test1(json({
    {"test" , "test"},
    //test declare back comment
    {"test2" , "test2"}
  }).get<map<string, string>>());
  vector<Darabonba::Json> array = vector<Darabonba::Json>()
    // array string comment
    .push_back("string")
    // array number comment
    .push_back(300);
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
      // new model instance comment
      Test1 modelInstance = Test1(json({
        // test declare front comment
        {"test" , "test"},
        // test2 declare front comment
        {"test2" , "test2"}
      }).get<map<string, string>>());
      // number declare comment
      int32_t num = 123;
      // static function call comment
      Client::staticFunc();
      _lastRequest = make_shared<Darabonba::Http::Request>(request_);
      auto futureResp_ = Darabonba::Core::doAction(request_, runtime_);
      shared_ptr<Darabonba::Http::MCurlResponse> response_ = futureResp_.get();
      _lastResponse  = response_;

      // static async function call
      Client::testFunc();
      // return comment
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

void Client::testAPI2() {
  Darabonba::RuntimeOptions runtime_(json({
    // runtime retry comment
    {"retry", true}
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
      // new model instance comment
      Test3 modelInstance = Test3();
      // boolean declare comment
      bool bool = true;
      if (bool) {
        //empty if
      } else {
      }

      // api function call comment
      testAPI();
      _lastRequest = make_shared<Darabonba::Http::Request>(request_);
      auto futureResp_ = Darabonba::Core::doAction(request_, runtime_);
      shared_ptr<Darabonba::Http::MCurlResponse> response_ = futureResp_.get();
      _lastResponse  = response_;

      // empty return comment
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

void Client::staticFunc() {
  vector<Darabonba::Json> a = vector<Darabonba::Json>();
}

/**
  testFunc
*/
void Client::testFunc() {
  // empty comment1
  // empty comment2
}
} // namespace Darabonba