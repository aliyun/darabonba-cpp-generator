// This file is auto-generated, don't edit it. Thanks.

#ifndef DARABONBA_COMPLEX_H_
#define DARABONBA_COMPLEX_H_

#include <boost/any.hpp>
#include <boost/throw_exception.hpp>
#include <darabonba/core.hpp>
#include <darabonba/import.hpp>
#include <darabonba/source.hpp>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

namespace Darabonba_Complex {
class ComplexRequestHeader : public Darabonba::Model {
public:
  ComplexRequestHeader() {}
  explicit ComplexRequestHeader(const std::map<string, boost::any> &config) : Darabonba::Model(config) {
    fromMap(config);
  };

  void validate() override {
    if (!content) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("content is required.")));
    }
  }
  map<string, boost::any> toMap() override {
    map<string, boost::any> res;
    if (content) {
      res["Content"] = boost::any(*content);
    }
    return res;
  }

  void fromMap(map<string, boost::any> m) override {
    if (m.find("Content") != m.end()) {
      content = make_shared<string>(boost::any_cast<string>(m["Content"]));
    }
  }

  shared_ptr<string> content{};

  ~ComplexRequestHeader() {};
};
class ComplexRequestConfigs : public Darabonba::Model {
public:
  ComplexRequestConfigs() {}
  explicit ComplexRequestConfigs(const std::map<string, boost::any> &config) : Darabonba::Model(config) {
    fromMap(config);
  };

  void validate() override {
    if (!key) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("key is required.")));
    }
    if (!value) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("value is required.")));
    }
    if (!extra) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("extra is required.")));
    }
  }
  map<string, boost::any> toMap() override {
    map<string, boost::any> res;
    if (key) {
      res["key"] = boost::any(*key);
    }
    if (value) {
      res["value"] = boost::any(*value);
    }
    if (extra) {
      res["extra"] = boost::any(*extra);
    }
    return res;
  }

  void fromMap(map<string, boost::any> m) override {
    if (m.find("key") != m.end()) {
      key = make_shared<string>(boost::any_cast<string>(m["key"]));
    }
    if (m.find("value") != m.end()) {
      value = make_shared<vector<string>>(boost::any_cast<vector<string>>(m["value"]));
    }
    if (m.find("extra") != m.end()) {
      extra = make_shared<map<string, string>>(boost::any_cast<map<string, string>>(m["extra"]));
    }
  }

  shared_ptr<string> key{};
  shared_ptr<vector<string>> value{};
  shared_ptr<map<string, string>> extra{};

  ~ComplexRequestConfigs() {};
};
class ComplexRequestPart : public Darabonba::Model {
public:
  ComplexRequestPart() {}
  explicit ComplexRequestPart(const std::map<string, boost::any> &config) : Darabonba::Model(config) {
    fromMap(config);
  };

  void validate() override {}
  map<string, boost::any> toMap() override {
    map<string, boost::any> res;
    if (partNumber) {
      res["PartNumber"] = boost::any(*partNumber);
    }
    return res;
  }

  void fromMap(map<string, boost::any> m) override {
    if (m.find("PartNumber") != m.end()) {
      partNumber = make_shared<string>(boost::any_cast<string>(m["PartNumber"]));
    }
  }

  shared_ptr<string> partNumber{};

  ~ComplexRequestPart() {};
};
class ComplexRequest : public Darabonba::Model {
public:
  ComplexRequest() {}
  explicit ComplexRequest(const std::map<string, boost::any> &config) : Darabonba::Model(config) {
    fromMap(config);
  };

  void validate() override {
    if (!accessKey) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("accessKey is required.")));
    }
    if (!body) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("body is required.")));
    }
    if (!strs) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("strs is required.")));
    }
    if (!header) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("header is required.")));
    }
    if (!Num) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("Num is required.")));
    }
    if (!configs) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("configs is required.")));
    }
  }
  map<string, boost::any> toMap() override {
    map<string, boost::any> res;
    if (accessKey) {
      res["accessKey"] = boost::any(*accessKey);
    }
    if (body) {
      res["Body"] = boost::any(*body);
    }
    if (strs) {
      res["Strs"] = boost::any(*strs);
    }
    if (header) {
      res["header"] = header ? boost::any(header->toMap()) : boost::any(map<string,boost::any>({}));
    }
    if (Num) {
      res["Num"] = boost::any(*Num);
    }
    if (configs) {
      res["configs"] = configs ? boost::any(configs->toMap()) : boost::any(map<string,boost::any>({}));
    }
    if (part) {
      vector<boost::any> temp1;
      for(auto item1:*part){
        temp1.push_back(boost::any(item1.toMap()));
      }
      res["Part"] = boost::any(temp1);
    }
    return res;
  }

  void fromMap(map<string, boost::any> m) override {
    if (m.find("accessKey") != m.end()) {
      accessKey = make_shared<string>(boost::any_cast<string>(m["accessKey"]));
    }
    if (m.find("Body") != m.end()) {
      body = make_shared<shared_ptr<Darabonba::Stream>>(boost::any_cast<shared_ptr<Darabonba::Stream>>(m["Body"]));
    }
    if (m.find("Strs") != m.end()) {
      strs = make_shared<vector<string>>(boost::any_cast<vector<string>>(m["Strs"]));
    }
    if (m.find("header") != m.end()) {
      ComplexRequestHeader complexRequestHeader;
      complexRequestHeader.fromMap(boost::any_cast<map<string, boost::any>>(m["header"]));
      header = make_shared<ComplexRequestHeader>(complexRequestHeader);
    }
    if (m.find("Num") != m.end()) {
      Num = make_shared<int>(boost::any_cast<int>(m["Num"]));
    }
    if (m.find("configs") != m.end()) {
      ComplexRequestConfigs complexRequestConfigs;
      complexRequestConfigs.fromMap(boost::any_cast<map<string, boost::any>>(m["configs"]));
      configs = make_shared<ComplexRequestConfigs>(complexRequestConfigs);
    }
    if (m.find("Part") != m.end()) {
      vector<ComplexRequestPart> expect1;
      for(auto item1:boost::any_cast<vector<boost::any>>(m["Part"])){
        ComplexRequestPart complexRequestPart;
        complexRequestPart.fromMap(boost::any_cast<map<string, boost::any>>(item1));
        expect1.push_back(complexRequestPart);
      }
      part = make_shared<vector<ComplexRequestPart>>(expect1);
    }
  }

  shared_ptr<string> accessKey{};
  shared_ptr<Darabonba::Stream> body{};
  shared_ptr<vector<string>> strs{};
  shared_ptr<ComplexRequestHeader> header{};
  shared_ptr<int> Num{};
  shared_ptr<ComplexRequestConfigs> configs{};
  shared_ptr<vector<ComplexRequestPart>> part{};

  ~ComplexRequest() {};
};
class Client : Darabonba_Import::Client {
public:
  shared_ptr<vector<Darabonba_Source::Config>> _configs{};
  explicit Client(const shared_ptr<Darabonba_Source::Config>& config);
  Darabonba_Source::RuntimeObject complex1(shared_ptr<ComplexRequest> request, shared_ptr<Darabonba_Import::Client> client);
  map<string, boost::any> Complex2(shared_ptr<ComplexRequest> request, shared_ptr<vector<string>> str, shared_ptr<map<string, string>> val);
  ComplexRequest Complex3(shared_ptr<ComplexRequest> request);
  vector<string> hello(shared_ptr<map<string, boost::any>> request, shared_ptr<vector<string>> strs);
  static Darabonba_Source::Request print(shared_ptr<Darabonba::Request> reqeust,
                                         shared_ptr<vector<ComplexRequest>> reqs,
                                         shared_ptr<Darabonba::Response> response,
                                         shared_ptr<map<string, string>> val);
  static vector<boost::any> array0(shared_ptr<map<string, boost::any>> req);
  static vector<string> array1();
  static string arrayAccess();
  static string arrayAccess2();
  static string arrayAccess3(shared_ptr<ComplexRequest> request);
  static void arrayAccess4(shared_ptr<ComplexRequest> request, shared_ptr<string> config, shared_ptr<int> index);
  static vector<string> arrayAssign(shared_ptr<string> config);
  static vector<string> arrayAssign2(shared_ptr<string> config);
  static void arrayAssign3(shared_ptr<ComplexRequest> request, shared_ptr<string> config);
  static string mapAccess(shared_ptr<ComplexRequest> request);
  static string mapAccess2(shared_ptr<Darabonba_Source::Request> request);
  static string mapAccess3();
  static void mapAssign(shared_ptr<ComplexRequest> request, shared_ptr<string> name);
  string TemplateString();
  void emptyModel();
  void tryCatch();

  ~Client() {};
};
} // namespace Darabonba_Complex

#endif
