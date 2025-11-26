// This file is auto-generated, don't edit it. Thanks.
#ifndef DARABONBA_TEST_HPP_
#define DARABONBA_TEST_HPP_
#include <darabonba/Core.hpp>
#include <darabonba/testModel.hpp>
#include <darabonba/testException.hpp>
#include <darabonba/source.hpp>
#include <darabonba/test.hpp>
#include <map>
#include <darabonba/http/Request.hpp>
#include <darabonba/http/MCurlResponse.hpp>
using namespace std;
using json = nlohmann::json;
namespace Darabonba
{
  class Client : public TestSource::Source {
    public:

      Client(TestSource::Models::Config &sourceConfig);

      TestSource::Models::RuntimeObject Complex1(const Models::ComplexRequest &request, const shared_ptr<TestSource::Source> &sourceClient);

      Darabonba::Json Complex2(const Models::ComplexRequest &request, const vector<string> &str, const map<string, string> &val);

      json ComplexMap();

      Models::ComplexRequest Complex3(const Models::ComplexRequest &request, const string &name);

      void noReturn();
      vector<string> hello(const Darabonba::Json &request, const vector<string> &strs, const vector<vector<string>> &complexList);

      static TestSource::Models::Request print(const Darabonba::Http::Request &reqeust, const vector<Models::ComplexRequest> &reqs, const Darabonba::Http::MCurlResponse &response, const map<string, string> &val);

      static void intToInt32(const int32_t &a);

      static void assignWithArray();

      Darabonba::Json mapAcess();

      vector<string> exprFunc();

      static void printNull();

      static TestSource::Models::Request testTryWithComplexReturnType();

      static TestSource::Models::Request testTryWithComplexReturnTypeWithOutCat();

      static vector<Darabonba::Json> array0(const Darabonba::Json &req);

      static vector<string> array1();

      string templateString();

      void intOp(const int32_t &a);

      string throwsFunc();

      string throwsFunc1();

      void throwsFunc2();

      string throwsFunc3();

      int32_t getInt(const int32_t &num);

      string returnFunc();

      shared_ptr<TestSource::Source> returnFunc1(const TestSource::Models::Config &cfg);

      json returnFunc2();

      Models::ComplexRequest returnModel();

      void emptyFunc();

      Darabonba::Exception Error(const Darabonba::Exception &e);

      static string arrayAccess();

      static string arrayAccess2();

      static string arrayAccess3(const Models::ComplexRequest &request);

      static string arrayAccess4(const vector<TestSource::Models::Request> &requests);

      static vector<string> arrayAssign(const string &config);

      static vector<string> arrayAssign2(const string &config);

      static void arrayAssign3(const Models::ComplexRequest &request, const string &config);

      static string mapAccess(const Models::ComplexRequest &request);

      static string mapAccess2(const TestSource::Models::Request &request);

      static string mapAccess3();

      static string mapAccess4(const Models::ComplexRequest &request);

      static void mapAssign(const Models::ComplexRequest &request, const string &name);

      static string arrayimport2(const vector<TestSource::Models::Request> &request);

      static void defaultReturn();

      static void strFmt();

      void multiTryCatch(const int64_t &a);
    protected:
      string _protocol;

      string _pathname;

      vector<string> _Strs;

      vector<vector<string>> _compleList;

      map<string, string> _endpointMap;

      vector<TestSource::Models::Config> _configs;
  };
} // namespace Darabonba
#endif
