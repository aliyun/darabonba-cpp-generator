// This file is auto-generated, don't edit it. Thanks.

#include <darabonba/complex.hpp>
#include <boost/any.hpp>
#include <boost/throw_exception.hpp>
#include <darabonba/core.hpp>
#include <darabonba/import.hpp>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

using namespace Darabonba_Complex;

Darabonba_Complex::Client::Client(const shared_ptr<Darabonba_Import::Config>& config) : Darabonba_Import::Client(config) {
  (*_configs)[0] = *config;
};

Darabonba_Import::RuntimeObject Darabonba_Complex::Client::complex1(shared_ptr<ComplexRequest> request, shared_ptr<Darabonba_Import::Client> client) {
  request->validate();
  shared_ptr<map<string, boost::any>> runtime_ = make_shared<map<string, string>>(map<string, string>({
    {"timeouted", "retry"}
  })
);
  shared_ptr<Darabonba::Request> _lastRequest;
  shared_ptr<std::exception> _lastException;
  shared_ptr<int> _now = make_shared<int>(0);
  shared_ptr<int> _retryTimes = make_shared<int>(0);
  while (Darabonba::Core::allowRetry(make_shared<boost::any>((*runtime_)["retry"]), _retryTimes, _now)) {
    if (*_retryTimes > 0) {
      shared_ptr<int> _backoffTime = make_shared<int>(Darabonba::Core::getBackoffTime(make_shared<boost::any>((*runtime_)["backoff"]), _retryTimes));
      if (*_backoffTime > 0) {
        Darabonba::Core::sleep(_backoffTime);
      }
    }
    _retryTimes = make_shared<int>(*_retryTimes + 1);
    try {
      shared_ptr<Darabonba::Request> request_ = make_shared<Darabonba::Request>();
      shared_ptr<string> name = make_shared<string>("complex");
      shared_ptr<map<string, string>> mapVal = make_shared<map<string, string>>(map<string, string>({
        {"test", "ok"}
      })
);
      shared_ptr<string> version = make_shared<string>(string("/") + string("2019-01-08") + string(*_pathname));
      shared_ptr<string> mapAccess = make_shared<string>(_API[version]);
      request_->protocol = *_protocol;
      request_->port = 80;
      request_->method = "GET";
      request_->pathname = string("/") + string(*_pathname);
      request_->query = Darabonba_Import::Client::query(Darabonba::Converter::mapPointer(Darabonba::Converter::merge(map<string, boost::any>({
        {"date", boost::any(string("2019"))},
        {"access", !mapAccess ? boost::any() : boost::any(*mapAccess)},
        {"test", boost::any(string((*mapVal)["test"]))}
      }), !request->header ? map<string, boost::any>() : request->header.toMap())));
      request_->body = Darabonba::Converter::toStream(Darabonba_Import::Client::body());
      _lastRequest = request_;
      shared_ptr<Darabonba::Response> response_ = make_shared<Darabonba::Response>(Darabonba::Core::doAction(request_, runtime_));
      if (true && true) {
        return nullptr;
      }
      else if (true || false) {
        return Darabonba_Import::RuntimeObject();
      }
      client->print(make_shared<map<string, boost::any>>(request->toMap()), make_shared<string>("1"));
      client->printAsync(make_shared<map<string, boost::any>>(request->toMap()), make_shared<string>("1"));
      hello(make_shared<map<string, boost::any>>(request->toMap()), make_shared<vector<string>>(vector<string>({
        "1",
        "2"
      })));
      hello(nullptr, nullptr);
      Complex3(nullptr);
      return RuntimeObject(map<string, boost::any>());
    }
    catch (std::exception &e) {
      if (Darabonba::Core::isRetryable(e)) {
        _lastException = make_shared<std::exception>(e);
        continue;
      }
      BOOST_THROW_EXCEPTION(e);
    }
  }
  BOOST_THROW_EXCEPTION(Darabonba::UnretryableError(_lastRequest, _lastException));
}

map<string, boost::any> Darabonba_Complex::Client::Complex2(shared_ptr<ComplexRequest> request, shared_ptr<vector<string>> str, shared_ptr<map<string, string>> val) {
  request->validate();
  shared_ptr<Darabonba::Request> request_ = make_shared<Darabonba::Request>();
  shared_ptr<string> name = make_shared<string>("complex");
  shared_ptr<Darabonba_Import::Config> config = make_shared<Darabonba_Import::Config>();
  shared_ptr<Darabonba_Import::Client> client = make_shared<Darabonba_Import::Client>(config);
  request_->protocol = "HTTP";
  request_->port = 80;
  request_->method = "GET";
  request_->pathname = "/";
  request_->query = Darabonba_Import::Client::query(make_shared<map<string, string>>({
    {"date", "2019"},
    {"version", "2019-01-08"},
    {"protocol", request_->protocol}
  }));
  (*val)["test"];
  request_->body = Darabonba::Converter::toStream(Darabonba_Import::Client::body());
  shared_ptr<Darabonba::Request> _lastRequest = request_;
  shared_ptr<Darabonba::Response> response_ = make_shared<Darabonba::Response>(Darabonba::Core::doAction(request_));
}

ComplexRequest Darabonba_Complex::Client::Complex3(shared_ptr<ComplexRequest> request) {
  request->validate();
  shared_ptr<Darabonba::Request> request_ = make_shared<Darabonba::Request>();
  shared_ptr<string> name = make_shared<string>("complex");
  request_->protocol = TemplateString();
  request_->port = 80;
  request_->method = "GET";
  request_->pathname = "/";
  request_->query = Darabonba_Import::Client::query(make_shared<map<string, string>>({
    {"date", "2019"}
  }));
  request_->body = Darabonba::Converter::toStream(Darabonba_Import::Client::body());
  request_->headers.insert(pair<string, string>("host", "hello"));
  shared_ptr<Darabonba::Request> _lastRequest = request_;
  shared_ptr<Darabonba::Response> response_ = make_shared<Darabonba::Response>(Darabonba::Core::doAction(request_));
  shared_ptr<Darabonba::Response> resp = response_;
  shared_ptr<Darabonba_Import::Request> req = make_shared<Darabonba_Import::Request>(map<string, boost::any>({
    {"accesskey", !request->accessKey ? boost::any() : boost::any(*request->accessKey)},
    {"region", !resp->statusMessage ? boost::any() : boost::any(*resp->statusMessage)}
  }));
  Client::array0(make_shared<map<string, boost::any>>(request->toMap()));
  req->accesskey = make_shared<string>("accesskey");
  req->accesskey = request->accessKey;
  Darabonba_Import::Client::parse(nullptr);
  Darabonba_Import::Client::array(make_shared<map<string, boost::any>>(request->toMap()), make_shared<string>("1"));
  Darabonba_Import::Client::asyncFunc();
  return ComplexRequest(Darabonba::Converter::toGenericMap(Darabonba::Converter::merge(map<string, string>(), request_->query)));
}

vector<string> Darabonba_Complex::Client::hello(shared_ptr<map<string, boost::any>> request, shared_ptr<vector<string>> strs) {
  return Client::array1();
}

Darabonba_Import::Request Darabonba_Complex::Client::print(shared_ptr<Darabonba::Request> reqeust,
                                                           shared_ptr<vector<ComplexRequest>> reqs,
                                                           shared_ptr<Darabonba::Response> response,
                                                           shared_ptr<map<string, string>> val) {
  return Request(map<string, boost::any>());
}

vector<boost::any> Darabonba_Complex::Client::array0(shared_ptr<map<string, boost::any>> req) {
  return vector<boost::any>();
}

vector<string> Darabonba_Complex::Client::array1() {
  return vector<string>({
    "1"
  });
}

string Darabonba_Complex::Client::arrayAccess() {
  shared_ptr<vector<string>> configs = make_shared<vector<string>>(vector<string>({
    "a",
    "b",
    "c"
  }));
  shared_ptr<string> config = make_shared<string>((*configs)[0]);
  return *config;
}

string Darabonba_Complex::Client::arrayAccess2() {
  shared_ptr<map<string, vector<string>>> data = make_shared<map<string, vector<string>>>(map<string, vector<string>>({
    {"configs", vector<string>({
      "a",
      "b",
      "c"
    })}
  })
);
  shared_ptr<string> config = make_shared<string>((*data)["configs"][0]);
  return *config;
}

string Darabonba_Complex::Client::arrayAccess3(shared_ptr<ComplexRequest> request) {
  shared_ptr<string> configVal = make_shared<string>((*request->configs->value)[0]);
  return *configVal;
}

void Darabonba_Complex::Client::arrayAccess4(shared_ptr<ComplexRequest> request, shared_ptr<string> config, shared_ptr<int> index) {
  (*request->configs->value)[*index] = *config;
}

vector<string> Darabonba_Complex::Client::arrayAssign(shared_ptr<string> config) {
  shared_ptr<vector<string>> configs = make_shared<vector<string>>(vector<string>({
    "a",
    "b",
    "c"
  }));
  (*configs)[3] = *config;
  return *configs;
}

vector<string> Darabonba_Complex::Client::arrayAssign2(shared_ptr<string> config) {
  shared_ptr<map<string, vector<string>>> data = make_shared<map<string, vector<string>>>(map<string, vector<string>>({
    {"configs", vector<string>({
      "a",
      "b",
      "c"
    })}
  })
);
  (*data)["configs"][3] = *config;
  return (*data)["configs"];
}

void Darabonba_Complex::Client::arrayAssign3(shared_ptr<ComplexRequest> request, shared_ptr<string> config) {
  (*request->configs->value)[0] = *config;
}

string Darabonba_Complex::Client::mapAccess(shared_ptr<ComplexRequest> request) {
  shared_ptr<string> configInfo = make_shared<string>((*request->configs->extra)["name"]);
  return *configInfo;
}

string Darabonba_Complex::Client::mapAccess2(shared_ptr<Darabonba_Import::Request> request) {
  shared_ptr<string> configInfo = make_shared<string>((*request->configs->extra)["name"]);
  return *configInfo;
}

string Darabonba_Complex::Client::mapAccess3() {
  shared_ptr<map<string, map<string, string>>> data = make_shared<map<string, map<string, string>>>(map<string, map<string, string>>({
    {"configs", map<string, string>({
      {"value", "string"}
    })}
  })
);
  return (*data)["configs"]["value"];
}

void Darabonba_Complex::Client::mapAssign(shared_ptr<ComplexRequest> request, shared_ptr<string> name) {
  request->configs->extra->insert(pair<string, string>("name", *name));
}

string Darabonba_Complex::Client::TemplateString() {
  return string("/") + string(*_protocol);
}

void Darabonba_Complex::Client::emptyModel() {
  ComplexRequest();
  ComplexRequestHeader();
}

void Darabonba_Complex::Client::tryCatch() {
  try {
    shared_ptr<string> str = make_shared<string>(TemplateString());
  }
  catch (std::exception &err) {
    shared_ptr<Darabonba::Error> error = make_shared<Darabonba::Error>(err);
  }
  catch(std::exception &e) {
    shared_ptr<string> final = make_shared<string>("ok");
  }
  try {
    shared_ptr<string> strNoFinal = make_shared<string>(TemplateString());
  }
  catch (std::exception &e) {
    shared_ptr<Darabonba::Error> errorNoFinal = make_shared<Darabonba::Error>(e);
  }
  try {
    shared_ptr<string> strNoCatch = make_shared<string>(TemplateString());
  }
  catch(std::exception &e) {
    shared_ptr<string> finalNoCatch = make_shared<string>("ok");
  }
}

