// This file is auto-generated, don't edit it. Thanks.
#ifndef DARABONBA_FUNCTION_HPP_
#define DARABONBA_FUNCTION_HPP_
#include <darabonba/Core.hpp>
#include <map>
using namespace std;
using json = nlohmann::json;
namespace Darabonba
{
  class Client {
    public:
      Client() {}
      static void hello();

      static map<string, string> helloMap();

      static vector<map<string, string>> helloArrayMap();

      static void helloParams(const string &a, const string &b);

      static void helloInterface();
  };
} // namespace Darabonba
#endif
