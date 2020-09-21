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

Darabonba_Import::Client::Client(vector<string> *id, string *str) {
  _id = id;
  _str = str;
  BOOST_THROW_EXCEPTION(Darabonba::Error(boost::any(map<string, string>({
    {"code", "SomeError"},
    {"messge", "ErrorMessage"}
  }))));
};

void Darabonba_Import::Client::Sample(Darabonba_Source::Client *client) {
  Darabonba_Source::RuntimeObject runtime = Darabonba_Source::RuntimeObject(new map<string, boost::any>(map<string, boost::any>()));
  Darabonba_Source::Request request = Darabonba_Source::Request(new map<string, string>({
    {"accesskey", "accesskey"},
    {"region", "region"}
  }));
  client->print(new Darabonba_Source::RuntimeObject(runtime));
}

