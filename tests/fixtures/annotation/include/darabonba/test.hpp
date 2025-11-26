// This file is auto-generated, don't edit it. Thanks.
#ifndef DARABONBA_TEST_HPP_
#define DARABONBA_TEST_HPP_
#include <darabonba/Core.hpp>
#include <darabonba/testModel.hpp>
using namespace std;
using json = nlohmann::json;
namespace Darabonba
{
  class Client {
    public:

    /**
      Init Func
    */
      Client();

      void testAPI();
      /**
        testFunc
      */
      static void testFunc();
    protected:
      string _a;
  };
} // namespace Darabonba
#endif
