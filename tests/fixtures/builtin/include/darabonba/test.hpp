// This file is auto-generated, don't edit it. Thanks.
#ifndef DARABONBA_TEST_HPP_
#define DARABONBA_TEST_HPP_
#include <darabonba/Core.hpp>
using namespace std;
using json = nlohmann::json;
namespace Darabonba
{
  class Client {
    public:
      Client() {}
      static void arrayTest(const vector<string> &args);

      static void bytesTest(const vector<string> &args);

      static void dateTest(const vector<string> &args);

      static void envTest(const vector<string> &args);

      static void fileTest(const vector<string> &args);

      static void formTest(const vector<string> &args);

      static void jsonTest(const vector<string> &args);

      static void logerTest(const vector<string> &args);

      static void mapTestCase(const vector<string> &args);

      static void numberTest(const vector<string> &args);

      static void streamTest(const vector<string> &args);

      static void stringTest(const vector<string> &args);

      static void urlTest(const vector<string> &args);

      static void xmlTest(const vector<string> &args);

      static Darabonba::Json returnAny();

      static void main(const vector<string> &args);
  };
} // namespace Darabonba
#endif
