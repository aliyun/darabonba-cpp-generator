#include <darabonba/Core.hpp>
#include <darabonba/test.hpp>
#include <map>
using namespace std;
using json = nlohmann::json;
namespace Darabonba
{

void Client::hello() {
  return ;
}

map<string, string> Client::helloMap() {
  map<string, string> m = {};
  return Darabonba::Core::merge(json({
      {"key" , "value"},
      {"key-1" , "value-1"},
      {"key-2" , "value-2"},
      {"\"\"" , "value-3"}
    }),
    m
  ).get<map<string, string>>();
}

vector<map<string, string>> Client::helloArrayMap() {
  return vector<map<string, string>>()
    .push_back(json({
      {"key" , "value"}
    }).get<map<string, string>>());
}

void Client::helloParams(const string &a, const string &b) {
}

void Client::helloInterface() {}
} // namespace Darabonba