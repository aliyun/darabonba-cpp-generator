// This file is auto-generated, don't edit it. Thanks.

#include <darabonba/statements.hpp>
#include <algorithm>
#include <boost/any.hpp>
#include <boost/throw_exception.hpp>
#include <darabonba/core.hpp>
#include <iostream>
#include <map>

using namespace std;

Darabonba_Statements::Client::Client(){}
void Darabonba_Statements::Client::hello() {
  Darabonba::Request request_ = Darabonba::Request();
  request_.method = "GET";
  request_.pathname = "/";
  request_.headers = {
    {"host", "www.test.com"}
  };
  if (true) {
    request_.headers.insert(pair<string, string>("host", "www.test2.com"));
  }
  Darabonba::Request _lastRequest = request_;
  Darabonba::Response response_= Darabonba::Core::doAction(request_);
  if (true) {
    throw Darabonba::Error(request_, response_);
  }
  else {
    true;
  }
  Client::helloIf();
  !false;
  string a;
  a = "string";
  return;
}

void Darabonba_Statements::Client::helloIf() {
  if (true) {
  }
  if (true) {
  }
  else if (true) {
  }
  else {
  }
}

void Darabonba_Statements::Client::helloThrow() {
  BOOST_THROW_EXCEPTION(Darabonba::Error(map<string, boost::any>(map<string, boost::any>())));
}

void Darabonba_Statements::Client::helloForBreak() {
  for(item : vector<boost::any>()
) {
    break;
  }
}

void Darabonba_Statements::Client::helloWhile() {
  while (true) {
    break;
  }
}

void Darabonba_Statements::Client::helloDeclare() {
  string hello = "world";
  string helloNull;
  hello = "hehe";
}

