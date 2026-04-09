// This file is auto-generated, don't edit it. Thanks.
#ifndef DARABONBA_COMMENT_HPP_
#define DARABONBA_COMMENT_HPP_
#include <darabonba/Core.hpp>
#include <darabonba/commentModel.hpp>
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

      void testAPI2();
      static void staticFunc();

      /**
        testFunc
      */
      static void testFunc();
    protected:
      vector<string> _a;
  };
} // namespace Darabonba
#endif
