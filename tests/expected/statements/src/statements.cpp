// This file is auto-generated, don't edit it. Thanks.

#include <darabonba/statements.hpp>
#include <algorithm>
#include <boost/any.hpp>
#include <boost/throw_exception.hpp>
#include <darabonba/core.hpp>
#include <iostream>
#include <map>

using namespace std;

using namespace Darabonba_Statements;

Darabonba_Statements::Client::Client(){}
void Darabonba_Statements::Client::hello() {
  shared_ptr<Darabonba::Request> request_ = make_shared<Darabonba::Request>();
  request_->method = "GET";
  request_->pathname = "/";
  request_->headers = {
    {"host", "www.test.com"}
  };
  if (true) {
    request_->headers.insert(pair<string, string>("host", "www.test2.com"));
  }
  shared_ptr<Darabonba::Request> _lastRequest = request_;
  shared_ptr<Darabonba::Response> response_ = make_shared<Darabonba::Response>(Darabonba::Core::doAction(request_));
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
  for(auto item : vector<boost::any>()) {
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

