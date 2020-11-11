// This file is auto-generated, don't edit it. Thanks.

#include <darabonba/import.hpp>
#include <boost/any.hpp>
#include <boost/throw_exception.hpp>
#include <darabonba/core.hpp>
#include <darabonba/source.hpp>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

using namespace Darabonba_Import;

Darabonba_Import::Client::Client(const shared_ptr<vector<string>>& id, const shared_ptr<string>& str) {
  _id = id;
  _str = str;
  BOOST_THROW_EXCEPTION(Darabonba::Error(map<string, string>({
    {"code", "SomeError"},
    {"messge", "ErrorMessage"}
  })));
};

void Darabonba_Import::Client::Sample(shared_ptr<Darabonba_Source::Client> client) {
  shared_ptr<Darabonba_Source::RuntimeObject> runtime = make_shared<Darabonba_Source::RuntimeObject>();
  shared_ptr<Darabonba_Source::Request> request = make_shared<Darabonba_Source::Request>(map<string, boost::any>({
    {"accesskey", boost::any(string("accesskey"))},
    {"region", boost::any(string("region"))}
  }));
  client->print(runtime);
}

