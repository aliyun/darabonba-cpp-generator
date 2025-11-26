#include <darabonba/Core.hpp>
#include <darabonba/test.hpp>
#include <darabonba/source.hpp>
#include <darabonba/local.hpp>
#include <map>
using namespace std;
using namespace Test;
using json = nlohmann::json;
namespace Darabonba
{

Darabonba::Client::Client(vector<string> &id, string &str){
  this->_id = id;
  this->_STR = str;
}


void Client::Sample(const shared_ptr<Source> &client) {
  Test::Models::RuntimeObject runtime = Test::Models::RuntimeObject();
  Test::Models::Request request = Test::Models::Request(json({
    {"accesskey" , "accesskey"},
    {"region" , "region"}
  }).get<map<string, string>>());
  client->print(runtime);
}
} // namespace Darabonba