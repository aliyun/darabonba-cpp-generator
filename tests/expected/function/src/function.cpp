// This file is auto-generated, don't edit it. Thanks.

#include <darabonba/function.hpp>
#include <boost/throw_exception.hpp>
#include <darabonba/core.hpp>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

using namespace Darabonba_Function;

void Darabonba_Function::Client::hello() {
  return;
}

map<string, string> Darabonba_Function::Client::helloMap() {
  map<string, string> m = map<string, string>();
  return Darabonba::Converter::merge(map<string, string>({
    {"key", "value"},
    {"key-1", "value-1"}
  }), m);
}

vector<map<string, string>> Darabonba_Function::Client::helloArrayMap() {
  return vector<map<string, string>>({
    map<string, string>({
      {"key", "value"}
    })
  });
}

void Darabonba_Function::Client::helloParams(shared_ptr<string> a, shared_ptr<string> b) {
}

void Darabonba_Function::Client::helloInterface() {
  BOOST_THROW_EXCEPTION(std::runtime_error("Un-implemented"));
}

