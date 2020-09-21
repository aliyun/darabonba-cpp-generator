// This file is auto-generated, don't edit it. Thanks.

#include <darabonba/function.hpp>
#include <boost/throw_exception.hpp>
#include <darabonba/core.hpp>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

void Darabonba_Function::Client::hello() {
  return;
}

map<string, string> Darabonba_Function::Client::helloMap() {
  map<string, string> m = map<string, string>();
  return Darabonba::Converter::merge(new map<string, string>({
    {"key", "value"},
    {"key-1", "value-1"}
  }), new map<string, string>(m));
}

vector<map<string, string>> Darabonba_Function::Client::helloArrayMap() {
  return vector<map<string, string>>({
    new map<string, string>({
      {"key", "value"}
    })
  });
}

void Darabonba_Function::Client::helloParams(string *a, string *b) {
}

void Darabonba_Function::Client::helloInterface() {
  BOOST_THROW_EXCEPTION(std::exception('Un-implemented'));
}

