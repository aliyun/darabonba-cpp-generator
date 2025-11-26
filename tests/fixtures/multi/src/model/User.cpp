#include <darabonba/Core.hpp>
#include <darabonba/model/User.hpp>
#include <darabonba/Util.hpp>
#include <darabonba/lib/Util.hpp>
using namespace std;
using json = nlohmann::json;
using namespace DaraUtil::Util;
using UtilUtil = Darabonba::Model::User::Lib::Util::Util;
namespace Darabonba
{
namespace Model
{
namespace User
{

FutrueGenerator<string> Client::test() {
  Client::test();
  Generator<string> it = UtilUtil::test1();
  for (string test : it) {
string     __retrun = test;
return Darbaonba::FutureGenerator<string>(__retrun);
  }
}
} // namespace Darabonba
} // namespace Model
} // namespace User