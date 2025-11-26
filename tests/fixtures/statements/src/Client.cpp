#include <darabonba/Core.hpp>
#include <darabonba/test.hpp>
#include <map>
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
    {"host" , "www.test.com"}
  }).get<map<string, string>>());
  if (true) {
    request_.addHeader("host", "www.test2.com");
  }

  auto futureResp_ = Darabonba::Core::doAction(request_, runtime_);
  shared_ptr<Darabonba::Http::MCurlResponse> response_ = futureResp_.get();

  if (true) {
    throw new Darabonba::UnretryableError();
  } else {
    true;
  }

  Client::helloIf();
  !false;
  string a = nullptr;
  a = "string";
  return ;
}

void Client::helloIf() {
  if (true) {
  }

  if (true) {
  } else if (true) {
  } else {
  }

}

void Client::helloThrow() {
  throw   Darabonba::Exception({});
}

void Client::helloForBreak() {
  for (Darabonba::Json item : vector<Darabonba::Json>()) {
    break;
  }
}

void Client::helloWhile() {

  while (true) {
    break;
  }
}

void Client::helloDeclare() {
  string hello = "world";
  string helloNull = nullptr;
  hello = "\"hehe\":\"\"";
}
} // namespace Darabonba