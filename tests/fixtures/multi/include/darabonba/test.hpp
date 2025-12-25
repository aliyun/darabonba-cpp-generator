// This file is auto-generated, don't edit it. Thanks.
#ifndef DARABONBA_TEST_HPP_
#define DARABONBA_TEST_HPP_
#include <darabonba/Core.hpp>
#include <darabonba/testModel.hpp>
#include <darabonba/testException.hpp>
#include <darabonba/model/User.hpp>
using namespace std;
using json = nlohmann::json;
namespace Darabonba
{
  class Client {
    public:

      Client();
      FutureGenerator<string> test3();

      int64_t test4();
    protected:
      Model::User::Models::Info _user;
  };
} // namespace Darabonba
#endif
