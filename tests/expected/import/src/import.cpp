// This file is auto-generated, don't edit it. Thanks.

#include <darabonba/import.hpp>
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
  Darabonba_Source::RuntimeObject runtime;
  Darabonba_Source::Request request(map<string, string>({
    {"accesskey", "accesskey"},
    {"region", "region"}
  }));
  client->print(make_shared<Darabonba_Source::RuntimeObject>(runtime));
}

