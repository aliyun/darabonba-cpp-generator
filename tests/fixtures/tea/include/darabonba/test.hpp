// This file is auto-generated, don't edit it. Thanks.
#ifndef DARABONBA_TEST_HPP_
#define DARABONBA_TEST_HPP_
#include <darabonba/Core.hpp>
#include <darabonba/source.hpp>
using namespace std;
using json = nlohmann::json;
namespace Darabonba
{
  class Client {
    public:

      Client(vector<string> &id, string &str);
      static void Sample(const shared_ptr<Test::Source> &client);
    protected:
      vector<string> _id;

      string _str;
  };
} // namespace Darabonba
#endif
