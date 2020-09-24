// This file is auto-generated, don't edit it. Thanks.

#include <darabonba/complex.hpp>
#include <boost/any.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include <cpprest/streams.h>
#include <darabonba/core.hpp>
#include <darabonba/import.hpp>
#include <darabonba/source.hpp>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

Darabonba_Complex::Client::Client(Darabonba_Source::Config *config) : Darabonba_Import::Client(config) {
  _configs[0] = *config;
};

Darabonba_Source::RuntimeObject Darabonba_Complex::Client::complex1(ComplexRequest *request, Darabonba_Import::Client *client) {
  request->validate();
  map<string, boost::any> runtime_ = {
    {"timeouted", "retry"}
  };
  Darabonba::Request _lastRequest;
  std::exception _lastException;
  int _now = 0;
  int _retryTimes = 0;
  while (Darabonba::Core::allowRetry(new boost::any(runtime_["retry"]), new int(_retryTimes), new int(_now))) {
    if (_retryTimes > 0) {
      int _backoffTime = Darabonba::Core::getBackoffTime(new boost::any(runtime_["backoff"]), new int(_retryTimes));
      if (_backoffTime > 0) {
        Darabonba::Core::sleep(new int(_backoffTime));
      }
    }
    _retryTimes = _retryTimes + 1;
    try {
      Darabonba::Request request_ = Darabonba::Request();
      string name = "complex";
      map<string, string> mapVal = {
        {"test", "ok"}
      };
      string version = string("/" + "2019-01-08" + "" + *_pathname + "");
      string mapAccess = _API["version"];
      request_.protocol = *_protocol;
      request_.port = 80;
      request_.method = "GET";
      request_.pathname = string("/" + *_pathname + "");
      request_.query = Darabonba_Import::Client::query(Darabonba::Converter::mapPointer(Darabonba::Converter::merge(map<string, boost::any>({
        {"date", boost::any("2019")},
        {"access", boost::any(mapAccess)},
        {"test", boost::any(mapVal["test"])}
      }), *request->header)));
      request_.body = Darabonba_Import::Client::body();
      _lastRequest = request_;
      Darabonba::Response response_= Darabonba::Core::doAction(request_, runtime_);
      if (true && true) {
        return nullptr;
      }
      else if (true || false) {
        return Darabonba_Source::RuntimeObject(new map<string, boost::any>(map<string, boost::any>()));
      }
      client->print(new ComplexRequest(request), new string("1"));
      client->printAsync(new ComplexRequest(request), new string("1"));
      hello(new ComplexRequest(request), new vector<string>(vector<string>({
        "1",
        "2"
      })));
      hello(new nullptr(nullptr), new nullptr(nullptr));
      Complex3(new nullptr(nullptr));
      return behavior.expected::fromMap(map<string, boost::any>());
    }
    catch (std::exception &e) {
      if (Darabonba::Core::isRetryable(&e)) {
        _lastException = e;
        continue;
      }
      BOOST_THROW_EXCEPTION(e);
    }
  }
  BOOST_THROW_EXCEPTION(Darabonba::UnretryableError(_lastRequest, _lastException));
}

map<string, boost::any> Darabonba_Complex::Client::Complex2(ComplexRequest *request, vector<string> *str, map<string, string> *val) {
  request->validate();
  Darabonba::Request request_ = Darabonba::Request();
  string name = "complex";
  Darabonba_Source::Config config = Darabonba_Source::Config(new map<string, boost::any>(map<string, boost::any>()));
  Darabonba_Import::Client client = Darabonba_Import::Client(new Darabonba_Source::Config(config));
  request_.protocol = "HTTP";
  request_.port = 80;
  request_.method = "GET";
  request_.pathname = "/";
  request_.query = Darabonba_Import::Client::query(new map<string, string>({
    {"date", "2019"},
    {"version", "2019-01-08"},
    {"protocol", request_.protocol}
  }));
  request_.body = Darabonba_Import::Client::body();
  Darabonba::Request _lastRequest = request_;
  Darabonba::Response response_= Darabonba::Core::doAction(request_);
}

ComplexRequest Darabonba_Complex::Client::Complex3(ComplexRequest *request) {
  request->validate();
  Darabonba::Request request_ = Darabonba::Request();
  string name = "complex";
  request_.protocol = TemplateString();
  request_.port = 80;
  request_.method = "GET";
  request_.pathname = "/";
  request_.query = Darabonba_Import::Client::query(new map<string, string>({
    {"date", "2019"}
  }));
  request_.body = Darabonba_Import::Client::body();
  request_.headers.insert(pair<string, string>("host", "hello"));
  Darabonba::Request _lastRequest = request_;
  Darabonba::Response response_= Darabonba::Core::doAction(request_);
  Darabonba::Response resp = Darabonba::Response response_;
  Darabonba_Source::Request req = Darabonba_Source::Request(new map<string, string>({
    {"accesskey", request->accessKey == nullptr ? NULL : *request->accessKey},
    {"region", resp.statusMessage}
  }));
  Client::array0(new ComplexRequest(request));
  req.accesskey = "accesskey";
  req.accesskey = *request->accessKey;
  Darabonba_Import::Client::parse(new class(ComplexRequest::class));
  Darabonba_Import::Client::array(new ComplexRequest(request), new string("1"));
  Darabonba_Import::Client::asyncFunc();
  return behavior.expected::fromMap(Darabonba::Converter::merge(map<string, string>(request_.query)));
}

vector<string> Darabonba_Complex::Client::hello(map<string, boost::any> *request, vector<string> *strs) {
  return Client::array1();
}

Darabonba_Source::Request Darabonba_Complex::Client::print(Darabonba::Request *reqeust,
                                                           vector<ComplexRequest> *reqs,
                                                           Darabonba::Response *response,
                                                           map<string, string> *val) {
  return behavior.expected::fromMap(map<string, boost::any>());
}

vector<boost::any> Darabonba_Complex::Client::array0(map<string, boost::any> *req) {
  return vector<boost::any>()
;
}

vector<string> Darabonba_Complex::Client::array1() {
  return vector<string>({
    "1"
  });
}

string Darabonba_Complex::Client::arrayAccess() {
  vector<string> configs = vector<string>({
    "a",
    "b",
    "c"
  });
  string config = configs[0];
  return config;
}

string Darabonba_Complex::Client::arrayAccess2() {
  map<string, vector<string>> data = {
    {"configs", vector<string>({
      "a",
      "b",
      "c"
    })}
  };
  string config = data["configs"][0];
  return config;
}

string Darabonba_Complex::Client::arrayAccess3(ComplexRequest *request) {
  string configVal = *request->configs.value[0];
  return configVal;
}

vector<string> Darabonba_Complex::Client::arrayAssign(string *config) {
  vector<string> configs = vector<string>({
    "a",
    "b",
    "c"
  });
  configs[3] = *config;
  return configs;
}

vector<string> Darabonba_Complex::Client::arrayAssign2(string *config) {
  map<string, vector<string>> data = {
    {"configs", vector<string>({
      "a",
      "b",
      "c"
    })}
  };
  data["configs"][3] = *config;
  return data["configs"];
}

void Darabonba_Complex::Client::arrayAssign3(ComplexRequest *request, string *config) {
  request->configs.value[0] = config;
}

string Darabonba_Complex::Client::mapAccess(ComplexRequest *request) {
  string configInfo = *request->configs.extra["name"];
  return configInfo;
}

string Darabonba_Complex::Client::mapAccess2(Darabonba_Source::Request *request) {
  string configInfo = *request->configs.extra["name"];
  return configInfo;
}

string Darabonba_Complex::Client::mapAccess3() {
  map<string, map<string, string>> data = {
    {"configs", map<string, string>({
      {"value", "string"}
    })}
  };
  return data["configs"]["value"];
}

void Darabonba_Complex::Client::mapAssign(ComplexRequest *request, string *name) {
  request->configs.extra.insert(pair<string, string>("name", name));
}

string Darabonba_Complex::Client::TemplateString() {
  return string("/" + *_protocol + "");
}

void Darabonba_Complex::Client::emptyModel() {
  ComplexRequest();
  ComplexRequestHeader();
}

void Darabonba_Complex::Client::tryCatch() {
  try {
    string str = TemplateString();
  }
  catch (std::exception &err) {
    Darabonba::Error error = err;
  }
  catch(std::exception &e) {
    string final = "ok";
  }
  try {
    string strNoFinal = TemplateString();
  }
  catch (std::exception &e) {
    Darabonba::Error errorNoFinal = e;
  }
  try {
    string strNoCatch = TemplateString();
  }
  catch(std::exception &e) {
    string finalNoCatch = "ok";
  }
}

