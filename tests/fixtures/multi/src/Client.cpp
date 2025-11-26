#include <darabonba/Core.hpp>
#include <darabonba/test.hpp>
#include <darabonba/model/User.hpp>
#include <darabonba/lib/Util.hpp>
#include <darabonba/Api.hpp>
using namespace std;
using json = nlohmann::json;
using namespace Darabonba::Lib;
using APIClient = Darabonba::Api::Client;
using namespace Darabonba::Model::User::Models;
namespace Darabonba
{

Darabonba::Client::Client(){
  this->_user = Info(json({
    {"name" , "test"},
    {"age" , 124},
    {"maxAttemp" , 3},
    {"autoretry" , true}
  }));
}


FutrueGenerator<string> Client::test3() {
  Generator<string> it = Util::Util::test1();
  for (string test : it) {
string     __retrun = test;
return Darbaonba::FutureGenerator<string>(__retrun);
  }
}

int64_t Client::test4() {
  shared_ptr<APIClient> api = make_shared<APIClient>();
  int64_t status = api->test3();
  return status;
}
} // namespace Darabonba