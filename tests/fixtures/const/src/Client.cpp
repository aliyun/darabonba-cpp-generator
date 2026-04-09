#include <darabonba/Core.hpp>
#include <darabonba/const.hpp>
using namespace std;
using json = nlohmann::json;
namespace Darabonba
{

string Client::hello() {
  return DARA_STRING_TEMPLATE("Hello " , "World!");
}
} // namespace Darabonba