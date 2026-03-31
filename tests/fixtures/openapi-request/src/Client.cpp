#include <darabonba/Core.hpp>
#include <darabonba/core.hpp>
#include <map>
using namespace std;
using json = nlohmann::json;
using namespace DARABONBA::Models;
namespace DARABONBA
{

DARABONBA::Client::Client(){
}


void Client::testOpenApiRequest(const OpenApiRequest &request) {
Darabonba::RuntimeOptions runtime_(json({}));

  Darabonba::Http::Request request_ = Darabonba::Http::Request();
  OpenApiRequest req(request.getQuery(), request.getBody());
  Params params = Params(json({
    {"action" , "TestAction"},
    {"version" , "2024-01-01"}
  }).get<map<string, string>>());
  auto futureResp_ = Darabonba::Core::doAction(request_, runtime_);
  shared_ptr<Darabonba::Http::MCurlResponse> response_ = futureResp_.get();
}

map<string, string> Client::query(const Darabonba::Json &query) {}
} // namespace DARABONBA