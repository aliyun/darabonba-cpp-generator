#include <darabonba/Core.hpp>
#include <darabonba/test.hpp>
#include <darabonba/source.hpp>
#include <darabonba/policy/Retry.hpp>
#include <darabonba/Runtime.hpp>
#include <darabonba/Exception.hpp>
#include <map>
#include <darabonba/Logger.hpp>
#include <darabonba/Stream.hpp>
#include <darabonba/http/MCurlResponse.hpp>
#include <darabonba/http/Request.hpp>
using namespace std;
using namespace Darabonba;
using namespace TestSource;
using json = nlohmann::json;
using namespace Darabonba::Models;
using namespace TestSource::Models;
using DaraLogger = Darabonba::Logger;
using namespace Darabonba::Exceptions;
using namespace TestSource::Exceptions;
namespace Darabonba
{

Darabonba::Client::Client(Config &sourceConfig): Source(sourceConfig){
  _configs.at(0) = sourceConfig;
  shared_ptr<Source> test = make_shared<Source>(sourceConfig);
  printData(sourceConfig.toMap(), "test");
}


RuntimeObject Client::Complex1(const ComplexRequest &request, const shared_ptr<Source> &sourceClient) {
  Darabonba::RuntimeOptions runtime_(json({
    {"timeouted", "retry"}
    }));

  shared_ptr<Darabonba::Http::Request> _lastRequest = nullptr;
  shared_ptr<Darabonba::Http::MCurlResponse> _lastResponse = nullptr;
  Darabonba::Exception _lastException;
  int _retriesAttempted = 0;
  Darabonba::Policy::RetryPolicyContext _context = json({
    {"retriesAttempted" , _retriesAttempted}
  });
  while (Darabonba::allowRetry(runtime_.retryOptions(), _context)) {
    if (_retriesAttempted > 0) {
      int _backoffTime = Darabonba::getBackoffTime(runtime_.retryOptions(), _context);
      if (_backoffTime > 0) {
        Darabonba::sleep(_backoffTime);
      }
    }
    _retriesAttempted++;
    try {
      Darabonba::Http::Request request_ = Darabonba::Http::Request();
      string name = "complex";
      shared_ptr<Darabonba::IStream> read = nullptr;
      Darabonba::Bytes byt = nullptr;
      map<string, RuntimeObject> moduleModelMapVal = {};
      map<string, shared_ptr<Source>> moduleMapVal = {};
      map<string, ComplexRequest> modelMapVal = {};
      map<string, ComplexRequestHeader> subModelMapVal = {};
      map<string, ComplexRequest> reqMap = nullptr;
      map<string, string> mapString = json({
        {"str" , request.accessKey()}
      }).get<map<string, string>>();
      int32_t inte = 1;
      int32_t a = 1;
      int32_t b = nullptr;
      b = a;
      int32_t c = a;
      Client::intToInt32(a);
      json mapVal = json({
        {"read" , read},
        {"test" , "{\"test\":\"ok\"}"},
        {"b" , request.b()},
        {"num" , request.num()},
        {"u16" , request.u16()},
        {"u32" , request.u32()},
        {"u64" , request.u64()},
        {"u16List" , request.uint16List()},
        {"u32List" , request.uint32List()},
        {"u64List" , request.uint64List()},
        {"i64List" , request.int64List()},
        {"i16List" , request.int16List()},
        {"i32List" , request.int32List()},
        {"intList" , request.intList()},
        {"stringList" , request.stringList()},
        {"i32" , request.i32()},
        {"booleantList" , request.booleantList()},
        {"floatList" , request.floatList()},
        {"float64List" , request.f64List()},
        {"f32" , request.f32()},
        {"f64" , request.f64()},
        {"i64" , request.i64()}
      });
      bool abool = true;
      ComplexRequest req = ComplexRequest(json({
        {"b" , false},
        {"num" , 10},
        {"i32" , a},
        {"intList" , vector<int32_t>()
          .push_back(10)
          .push_back(11)},
        {"int16List" , vector<int32_t>()
          .push_back(10)
          .push_back(11)},
        {"int32List" , vector<int32_t>()
          .push_back(10)
          .push_back(11)},
        {"int64List" , vector<int32_t>()
          .push_back(10)
          .push_back(11)},
        {"longList" , vector<int64_t>()
          .push_back(10L)
          .push_back(11L)},
        {"floatList" , vector<float>()
          .push_back(0.1f)
          .push_back(0.2f)},
        {"stringList" , vector<string>()
          .push_back("10")
          .push_back("11")},
        {"booleantList" , vector<bool>()
          .push_back(true)
          .push_back(false)}
      }));
      vector<int64_t> longList = vector<int64_t>()
        .push_back(432435L);
      vector<Darabonba::Json> anyList = vector<Darabonba::Json>()
        .push_back(432435L)
        .push_back("str")
        .push_back(true)
        .push_back(10)
        .push_back(0.1f);
      map<string, float> floatMap = json({
        {"key1" , 0.1f},
        {"key2" , 0.2f}
      }).get<map<string, float>>();
      map<string, double> doubleMap = json({
        {"key1" , 0.1},
        {"key2" , 0.2}
      }).get<map<string, double>>();
      map<string, int32_t> intMap = json({
        {"key1" , 1},
        {"key2" , 2}
      }).get<map<string, int32_t>>();
      map<string, int64_t> longMap = json({
        {"key1" , 1},
        {"key2" , 2}
      }).get<map<string, int64_t>>();
      map<string, int16> int16Map = json({
        {"key1" , 1},
        {"key2" , 2}
      }).get<map<string, int16>>();
      map<string, int32_t> int32Map = json({
        {"key1" , 1},
        {"key2" , 2}
      }).get<map<string, int32_t>>();
      map<string, int64_t> int64Map = json({
        {"key1" , 1},
        {"key2" , 2}
      }).get<map<string, int64_t>>();
      json anyMap = json({
        {"key1" , 0.1f},
        {"key2" , 1},
        {"key3" , "test"},
        {"key4" , true},
        {"key5" , vector<Darabonba::Json>()
          .push_back("test")
          .push_back(1)
          .push_back(true)
          .push_back(vector<string>()
            .push_back("test"))},
        {"key6" , vector<json>()
          .push_back(json({
            {"a" , "test"},
            {"b" , 1},
            {"c" , true},
            {"d" , vector<string>()
              .push_back("test")}
          }))}
      });
      for (Darabonba::Json itemTmp : anyList) {
        DaraLogger::info(DARA_STRING_TEMPLATE("" , itemTmp));
      }
      for (string item : vector<string>()
          .push_back("1")
          .push_back("2")) {
        map<string, string> anyMap = {};
        anyMap[item] = "test";
        break;
      }
      this->_Strs = request.strs();
      this->_protocol = "test";
      _endpointMap.at(_protocol);
      _endpointMap["test"] = "ok";
      request.setStrs(_Strs);
      request_.setProtocol(_protocol);
      request_.setPort(request.num());
      request_.setMethod("GET");
      request_.setPathname(DARA_STRING_TEMPLATE("/" , _pathname));
      request_.setQuery(json({
        {"date" , "2019"},
        {"name" , request_.method()}
      }).get<map<string, string>>());
      json tmp = Darabonba::Core::merge(request_.query(),
        request_.headers(),
        request_
      );
      _lastRequest = make_shared<Darabonba::Http::Request>(request_);
      auto futureResp_ = Darabonba::Core::doAction(request_, runtime_);
      shared_ptr<Darabonba::Http::MCurlResponse> response_ = futureResp_.get();
      _lastResponse  = response_;

      if (true && true) {
        return nullptr;
      } else if (Source::judgeStr("test") || false) {
        return RuntimeObject();
      }

      sourceClient->printData(request.toMap(), "1");
      hello(request.toMap(), vector<string>()
        .push_back("1")
        .push_back("2"), nullptr);
      hello(nullptr, nullptr, nullptr);
      return json({}).get<RuntimeObject>();
      Complex3(nullptr, "test");
      return nullptr;
    } catch (const Darabonba::Exception& ex) {
      _context = Darabonba::Policy::RetryPolicyContext(json({
        {"retriesAttempted" , _retriesAttempted},
        {"lastRequest" , _lastRequest},
        {"lastResponse" , _lastResponse},
        {"exception" , ex},
      }));
      continue;
    }
  }

  throw *_context.exception();
}

Darabonba::Json Client::Complex2(const ComplexRequest &request, const vector<string> &str, const map<string, string> &val) {
Darabonba::RuntimeOptions runtime_(json({}));

  Darabonba::Http::Request request_ = Darabonba::Http::Request();
  string name = "complex";
  Config config = Config();
  shared_ptr<Source> sourceClient = make_shared<Source>(config);
  vector<Config> configArray = vector<Config>()
    .push_back(config);
  sourceClient->printData(request.toMap(), "1");
  request_.setProtocol("HTTP");
  request_.setPort(80);
  request_.setMethod("GET");
  request_.setPathname("/");
  request_.setQuery(json({
    {"date" , "2019"},
    {"protocol" , request_.protocol()}
  }).get<map<string, string>>());
  auto futureResp_ = Darabonba::Core::doAction(request_, runtime_);
  shared_ptr<Darabonba::Http::MCurlResponse> response_ = futureResp_.get();
}

json Client::ComplexMap() {
  Darabonba::RuntimeOptions runtime_(json({
    }));

  shared_ptr<Darabonba::Http::Request> _lastRequest = nullptr;
  shared_ptr<Darabonba::Http::MCurlResponse> _lastResponse = nullptr;
  Darabonba::Exception _lastException;
  int _retriesAttempted = 0;
  Darabonba::Policy::RetryPolicyContext _context = json({
    {"retriesAttempted" , _retriesAttempted}
  });
  while (Darabonba::allowRetry(runtime_.retryOptions(), _context)) {
    if (_retriesAttempted > 0) {
      int _backoffTime = Darabonba::getBackoffTime(runtime_.retryOptions(), _context);
      if (_backoffTime > 0) {
        Darabonba::sleep(_backoffTime);
      }
    }
    _retriesAttempted++;
    try {
      Darabonba::Http::Request request_ = Darabonba::Http::Request();
      _lastRequest = make_shared<Darabonba::Http::Request>(request_);
      auto futureResp_ = Darabonba::Core::doAction(request_, runtime_);
      shared_ptr<Darabonba::Http::MCurlResponse> response_ = futureResp_.get();
      _lastResponse  = response_;
    } catch (const Darabonba::Exception& ex) {
      _context = Darabonba::Policy::RetryPolicyContext(json({
        {"retriesAttempted" , _retriesAttempted},
        {"lastRequest" , _lastRequest},
        {"lastResponse" , _lastResponse},
        {"exception" , ex},
      }));
      continue;
    }
  }

  throw *_context.exception();
}

ComplexRequest Client::Complex3(const ComplexRequest &request, const string &name) {
Darabonba::RuntimeOptions runtime_(json({}));

  Darabonba::Http::Request request_ = Darabonba::Http::Request();
  name = "complex";
  request_.setProtocol(templateString());
  request_.setPort(80);
  request_.setMethod("GET");
  request_.setPathname("/");
  request_.setBody(Darabonba::Stream::toReadable("body"));
  request_.setQuery(json({
    {"date" , "2019"}
  }).get<map<string, string>>());
  ComplexRequest tmp = nullptr;
  tmp = returnModel();
  name = _protocol;
  auto futureResp_ = Darabonba::Core::doAction(request_, runtime_);
  shared_ptr<Darabonba::Http::MCurlResponse> response_ = futureResp_.get();

  bool x = false;
  bool y = true;
  bool z = false;
  if (x && y || !z) {
    x = y;
  }

  Darabonba::Http::MCurlResponse resp = response_;
  Request req = Request(json({
    {"accesskey" , request.accessKey()},
    {"region" , resp.statusMessage()}
  }).get<map<string, string>>());
  Client::array0(request.toMap());
  req.setAccesskey("accesskey");
  req.setAccesskey(request.accessKey());
  Client::printNull();
  throwsFunc();
  response_->statusCode();
  Source::array(request.toMap(), "1");
  return json(Darabonba::Core::merge(request_.query()
  ).get<map<string, string>>()).get<ComplexRequest>();
}

void Client::noReturn() {
Darabonba::RuntimeOptions runtime_(json({}));

  Darabonba::Http::Request request_ = Darabonba::Http::Request();
  auto futureResp_ = Darabonba::Core::doAction(request_, runtime_);
  shared_ptr<Darabonba::Http::MCurlResponse> response_ = futureResp_.get();
}

vector<string> Client::hello(const Darabonba::Json &request, const vector<string> &strs, const vector<vector<string>> &complexList) {
  vector<vector<string>> a = nullptr;
  return Client::array1();
}

Request Client::print(const Darabonba::Http::Request &reqeust, const vector<ComplexRequest> &reqs, const Darabonba::Http::MCurlResponse &response, const map<string, string> &val) {}

void Client::intToInt32(const int32_t &a) {}

void Client::assignWithArray() {
  vector<string> list = nullptr;
  list = vector<string>()
    .push_back("test");
  string str = nullptr;
  str = throwsFunc();
}

Darabonba::Json Client::mapAcess() {
  json tmp = json({
    {"protocol" , _endpointMap.at(_protocol)}
  });
  return ;
}

vector<string> Client::exprFunc() {
  if (!true) {
  }

  int32_t num = 10;
  ComplexRequest req = ComplexRequest();
  json mapVal = json({
    {"num" , 10},
    {"client" , nullptr},
    {"strs" , Client::array1()},
    {"str" , DARA_STRING_TEMPLATE("string" , num)},
    {"str1" , DARA_STRING_TEMPLATE("string" , req.accessKey())}
  });
  return nullptr;
}

void Client::printNull() {
  try {
    string str = templateString();
  } catch (const Darabonba::Exception e) {
  } finally {
    string final = "ok";
  }  
}

Request Client::testTryWithComplexReturnType() {
  try {
    string str = templateString();
  } catch (const Darabonba::Exception e) {
  } finally {
    string final = "ok";
  }  
  return nullptr;
}

Request Client::testTryWithComplexReturnTypeWithOutCat() {
  try {
    string str = templateString();
  } catch (const Darabonba::Exception e) {
    string sim = "a";
  } finally {
    string final = "ok";
  }  
  return nullptr;
}

vector<Darabonba::Json> Client::array0(const Darabonba::Json &req) {
  return vector<Darabonba::Json>();
}

vector<string> Client::array1() {
  return vector<string>()
    .push_back("1");
}

string Client::templateString() {
  return DARA_STRING_TEMPLATE("/" , _protocol);
}

void Client::intOp(const int32_t &a) {
  int32_t b = a;
  map<string, int32_t> tmp = json({
    {"first" , a}
  }).get<map<string, int32_t>>();
  b++;
  ++b;
  b--;
  --b;
  tmp.at("a")++;
  ++tmp.at("a");
  tmp.at("a")--;
  --tmp.at("a");
}

string Client::throwsFunc() {
  return DARA_STRING_TEMPLATE("/" , _protocol);
}

string Client::throwsFunc1() {
  return "";
}

void Client::throwsFunc2() {
  throw   Darabonba::Exception(json({
    {"code" , ""}
  }));
}

string Client::throwsFunc3() {
  throw   Darabonba::Exception(json({
    {"code" , ""}
  }));
}

int32_t Client::getInt(const int32_t &num) {
  return num;
}

string Client::returnFunc() {
  int32_t index = 0;
  int32_t i = getInt(index);
  return nullptr;
}

shared_ptr<Source> Client::returnFunc1(const Config &cfg) {
  Config config = Config();
  return make_shared<Source>(config);
}

json Client::returnFunc2() {
  map<string, string> tmp = json({
    {"subMap" , "ok"}
  }).get<map<string, string>>();
  map<string, map<string, string>> mapVal = json({
    {"test" , tmp}
  }).get<map<string, map<string, string>>>();
  if (Source::judgeStr("test")) {
    return mapVal.at("test");
  } else {
    shared_ptr<Darabonba::IStream> body = nullptr;
    return Darabonba::Core::merge(json({
        {"body" , body}
      }),
      tmp
    );
  }

}

ComplexRequest Client::returnModel() {
  return ComplexRequest();
}

void Client::emptyFunc() {}

Darabonba::Exception Client::Error(const Darabonba::Exception &e) {
  Darabonba::Exception tmp23 = nullptr;
  class c = nullptr;
  return e;
}

string Client::arrayAccess() {
  vector<string> configs = vector<string>()
    .push_back("a")
    .push_back("b")
    .push_back("c");
  string config = configs.at(0);
  return config;
}

string Client::arrayAccess2() {
  map<string, vector<string>> data = json({
    {"configs" , vector<string>()
      .push_back("a")
      .push_back("b")
      .push_back("c")}
  }).get<map<string, vector<string>>>();
  string config = data.at("configs").at(0);
  return config;
}

string Client::arrayAccess3(const ComplexRequest &request) {
  Request req = Request();
  Client::arrayAccess4(vector<Request>()
    .push_back(req));
  string configVal = request.configs().value().at(0);
  return configVal;
}

string Client::arrayAccess4(const vector<Request> &requests) {
  return "";
}

vector<string> Client::arrayAssign(const string &config) {
  vector<string> configs = vector<string>()
    .push_back("a")
    .push_back("b")
    .push_back("c");
  configs.at(3) = config;
  return configs;
}

vector<string> Client::arrayAssign2(const string &config) {
  map<string, vector<string>> data = json({
    {"configs" , vector<string>()
      .push_back("a")
      .push_back("b")
      .push_back("c")}
  }).get<map<string, vector<string>>>();
  data.at("configs").at(3) = config;
  return data.at("configs");
}

void Client::arrayAssign3(const ComplexRequest &request, const string &config) {
  request.configs().value().at(0) = config;
}

string Client::mapAccess(const ComplexRequest &request) {
  string configInfo = request.configs().extra().at("name");
  return configInfo;
}

string Client::mapAccess2(const Request &request) {
  string configInfo = request.configs().extra().at("name");
  return configInfo;
}

string Client::mapAccess3() {
  map<string, map<string, string>> data = json({
    {"configs" , json({
      {"value" , "string"}
    }).get<map<string, string>>()}
  }).get<map<string, map<string, string>>>();
  return data.at("configs").at("value");
}

string Client::mapAccess4(const ComplexRequest &request) {
  string key = "name";
  Request model = request.modelMap().at(key);
  string configInfo = request.configs().extra().at(key);
  return configInfo;
}

void Client::mapAssign(const ComplexRequest &request, const string &name) {
  request.configs().extra()["name"] = name;
  string key = "name";
  name = key;
  request.configs().extra()[key] = name;
  name = request.configs().extra().at("name");
  request.map()[key] = name;
  request.numMap()[key] = 1;
}

string Client::arrayimport2(const vector<Request> &request) {
  return "";
}

void Client::defaultReturn() {
  if (true) {
  } else {
  }

}

void Client::strFmt() {
  string s = "strtest";
  string s1 = DARA_STRING_TEMPLATE(" % 1" , s);
  string s2 = DARA_STRING_TEMPLATE(" \"hello\" 'world' " , s);
  string s3 = DARA_STRING_TEMPLATE("hello world");
  string s4 = DARA_STRING_TEMPLATE("{
    \"json\": \"json val\",
    \"key\": \"value\"
  }");
  string s5 = DARA_STRING_TEMPLATE(" %s str:" , s);
  string s6 = DARA_STRING_TEMPLATE(" %%s str");
  string fs1 = DARA_STRING_TEMPLATE("{\"key\": \"" , s , "\"}");
  string fs2 = DARA_STRING_TEMPLATE("{{\"key\": \"" , s , "\"}}");
  string fs3 = DARA_STRING_TEMPLATE("" , " " , s);
}

void Client::multiTryCatch(const int64_t &a) {
  try {
    if (a > 0) {
      throw Err1Exception(json({
        {"name" , "str"},
        {"code" , "str"},
        {"data" , json({
          {"key1" , "str"}
        }).get<map<string, string>>()}
      }));
    } else if (a == 0) {
      throw Err2Exception(json({
        {"name" , "str"},
        {"code" , "str"},
        {"accessErrMessage" , "str2"}
      }).get<map<string, string>>());
    } else if (a == -10) {
      throw Err3Exception(json({
        {"name" , "str"},
        {"code" , "str"}
      }).get<map<string, string>>());
    } else {
      throw Exception(json({
        {"name" , "str"},
        {"code" , "str"}
      }).get<map<string, string>>());
    }

  } catch (const Err1Exception err) {
    DaraLogger::log(err.name());
  } catch (const Err2Exception err) {
    DaraLogger::log(err.name());
  } catch (const Err3Exception err) {
    DaraLogger::log(err.name());
  } catch (const Darabonba::Exception err) {
    DaraLogger::log(err.name());
  } finally {
    string final = "ok";
  }  
}
} // namespace Darabonba