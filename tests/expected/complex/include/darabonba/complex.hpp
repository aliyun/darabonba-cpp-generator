// This file is auto-generated, don't edit it. Thanks.

#ifndef DARABONBA_COMPLEX_H_
#define DARABONBA_COMPLEX_H_

#include <boost/any.hpp>
#include <boost/throw_exception.hpp>
#include <darabonba/core.hpp>
#include <darabonba/import.hpp>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

namespace Darabonba_Complex {
class ComplexRequestHeader : public Darabonba::Model {
public:
  shared_ptr<string> content{};

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
    if (m.find("Content") != m.end() && !m["Content"].empty()) {
      content = make_shared<string>(boost::any_cast<string>(m["Content"]));
    }
  }


  virtual ~ComplexRequestHeader() = default;
};
class ComplexRequestConfigs : public Darabonba::Model {
public:
  shared_ptr<string> key{};
  shared_ptr<vector<string>> value{};
  shared_ptr<map<string, string>> extra{};

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
    if (m.find("key") != m.end() && !m["key"].empty()) {
      key = make_shared<string>(boost::any_cast<string>(m["key"]));
    }
    if (m.find("value") != m.end() && !m["value"].empty()) {
      vector<string> toVec1;
      if (typeid(vector<boost::any>) == m["value"].type()) {
        vector<boost::any> vec1 = boost::any_cast<vector<boost::any>>(m["value"]);
        for (auto item:vec1) {
           toVec1.push_back(boost::any_cast<string>(item));
        }
      }
      value = make_shared<vector<string>>(toVec1);
    }
    if (m.find("extra") != m.end() && !m["extra"].empty()) {
      map<string, string> map1 = boost::any_cast<map<string, string>>(m["extra"]);
      map<string, string> toMap1;
      for (auto item:map1) {
         toMap1[item.first] = item.second;
      }
      extra = make_shared<map<string, string>>(toMap1);
    }
  }


  virtual ~ComplexRequestConfigs() = default;
};
class ComplexRequestPart : public Darabonba::Model {
public:
  shared_ptr<string> partNumber{};

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
    if (m.find("PartNumber") != m.end() && !m["PartNumber"].empty()) {
      partNumber = make_shared<string>(boost::any_cast<string>(m["PartNumber"]));
    }
  }


  virtual ~ComplexRequestPart() = default;
};
class ComplexRequest : public Darabonba::Model {
public:
  shared_ptr<string> accessKey{};
  shared_ptr<Darabonba::Stream> body{};
  shared_ptr<vector<string>> strs{};
  shared_ptr<ComplexRequestHeader> header{};
  shared_ptr<int> Num{};
  shared_ptr<ComplexRequestConfigs> configs{};
  shared_ptr<vector<ComplexRequestPart>> part{};

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
    if (m.find("accessKey") != m.end() && !m["accessKey"].empty()) {
      accessKey = make_shared<string>(boost::any_cast<string>(m["accessKey"]));
    }
    if (m.find("Body") != m.end() && !m["Body"].empty()) {
      body = make_shared<Darabonba::Stream>(boost::any_cast<Darabonba::Stream>(m["Body"]));
    }
    if (m.find("Strs") != m.end() && !m["Strs"].empty()) {
      vector<string> toVec1;
      if (typeid(vector<boost::any>) == m["Strs"].type()) {
        vector<boost::any> vec1 = boost::any_cast<vector<boost::any>>(m["Strs"]);
        for (auto item:vec1) {
           toVec1.push_back(boost::any_cast<string>(item));
        }
      }
      strs = make_shared<vector<string>>(toVec1);
    }
    if (m.find("header") != m.end() && !m["header"].empty()) {
      if (typeid(map<string, boost::any>) == m["header"].type()) {
        ComplexRequestHeader model1;
        model1.fromMap(boost::any_cast<map<string, boost::any>>(m["header"]));
        header = make_shared<ComplexRequestHeader>(model1);
      }
    }
    if (m.find("Num") != m.end() && !m["Num"].empty()) {
      Num = make_shared<int>(boost::any_cast<int>(m["Num"]));
    }
    if (m.find("configs") != m.end() && !m["configs"].empty()) {
      if (typeid(map<string, boost::any>) == m["configs"].type()) {
        ComplexRequestConfigs model1;
        model1.fromMap(boost::any_cast<map<string, boost::any>>(m["configs"]));
        configs = make_shared<ComplexRequestConfigs>(model1);
      }
    }
    if (m.find("Part") != m.end() && !m["Part"].empty()) {
      if (typeid(vector<boost::any>) == m["Part"].type()) {
        vector<ComplexRequestPart> expect1;
        for(auto item1:boost::any_cast<vector<boost::any>>(m["Part"])){
          if (typeid(map<string, boost::any>) == item1.type()) {
            ComplexRequestPart model2;
            model2.fromMap(boost::any_cast<map<string, boost::any>>(item1));
            expect1.push_back(model2);
          }
        }
        part = make_shared<vector<ComplexRequestPart>>(expect1);
      }
    }
  }


  virtual ~ComplexRequest() = default;
};
class Client : Darabonba_Import::Client {
public:
  shared_ptr<vector<Darabonba_Import::Config>> _configs{};
  explicit Client(const shared_ptr<Darabonba_Import::Config>& config);
  Darabonba_Import::RuntimeObject complex1(shared_ptr<ComplexRequest> request, shared_ptr<Darabonba_Import::Client> client);
  map<string, boost::any> Complex2(shared_ptr<ComplexRequest> request, shared_ptr<vector<string>> str, shared_ptr<map<string, string>> val);
  ComplexRequest Complex3(shared_ptr<ComplexRequest> request);
  vector<string> hello(shared_ptr<map<string, boost::any>> request, shared_ptr<vector<string>> strs);
  static Darabonba_Import::Request print(shared_ptr<Darabonba::Request> reqeust,
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
  static string mapAccess2(shared_ptr<Darabonba_Import::Request> request);
  static string mapAccess3();
  static void mapAssign(shared_ptr<ComplexRequest> request, shared_ptr<string> name);
  string TemplateString();
  void emptyModel();
  void tryCatch();

  virtual ~Client() = default;
};
} // namespace Darabonba_Complex

#endif
