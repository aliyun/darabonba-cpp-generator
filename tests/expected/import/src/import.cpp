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

Darabonba_Import::Client::Client(shared_ptr<vector<string>> id, shared_ptr<string> str) {
  _id = id;
  _str = str;
  BOOST_THROW_EXCEPTION(Darabonba::Error(map<string, string>({
    {"code", "SomeError"},
    {"messge", "ErrorMessage"}
  })));
};

void Darabonba_Import::Client::Sample(shared_ptr<Darabonba_Source::Client> client) {
  Darabonba_Source::RuntimeObject runtime = Darabonba_Source::RuntimeObject(shared_ptr<map<string, boost::any>>(new map<string, boost::any>(map<string, boost::any>())));
  Darabonba_Source::Request request = Darabonba_Source::Request(shared_ptr<map<string, string>>(new map<string, string>({
    {"accesskey", "accesskey"},
    {"region", "region"}
  })));
  client->print(shared_ptr<Darabonba_Source::RuntimeObject>(new Darabonba_Source::RuntimeObject(runtime)));
}

