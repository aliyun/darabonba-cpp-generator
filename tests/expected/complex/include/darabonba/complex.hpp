// This file is auto-generated, don't edit it. Thanks.

#ifndef DARABONBA_COMPLEX_H_
#define DARABONBA_COMPLEX_H_

#include <boost/any.hpp>
#include <darabonba/core.hpp>
#include <darabonba/import.hpp>
#include <darabonba/source.hpp>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

namespace Darabonba_Complex {
class ComplexRequestHeader : public Darabonba::Model {
protected:
  void _init(){
    _name = map<string, string>({
      {"content" , "Content"},
    });
  }
public:
  ComplexRequestHeader() {_init();};
  explicit ComplexRequestHeader(const std::map<string, boost::any> &config) : Darabonba::Model(config) {_init();};


  map<string, boost::any> toMap() {
    map<string, boost::any> res;
    if (nullptr != content) {
      res["Content"] = boost::any(*content);
    }
    return res;
  }

  shared_ptr<string> content{};

  ~ComplexRequestHeader() {};
};
class ComplexRequestConfigs : public Darabonba::Model {
protected:
  void _init(){
  }
public:
  ComplexRequestConfigs() {_init();};
  explicit ComplexRequestConfigs(const std::map<string, boost::any> &config) : Darabonba::Model(config) {_init();};


  map<string, boost::any> toMap() {
    map<string, boost::any> res;
    if (nullptr != key) {
      res["key"] = boost::any(*key);
    }
    if (nullptr != value) {
      res["value"] = boost::any(*value);
    }
    if (nullptr != extra) {
      res["extra"] = boost::any(*extra);
    }
    return res;
  }

  shared_ptr<string> key{};
  shared_ptr<vector<string>> value{};
  shared_ptr<map<string, string>> extra{};

  ~ComplexRequestConfigs() {};
};
class ComplexRequestPart : public Darabonba::Model {
protected:
  void _init(){
    _name = map<string, string>({
      {"partNumber" , "PartNumber"},
    });
  }
public:
  ComplexRequestPart() {_init();};
  explicit ComplexRequestPart(const std::map<string, boost::any> &config) : Darabonba::Model(config) {_init();};


  map<string, boost::any> toMap() {
    map<string, boost::any> res;
    if (nullptr != partNumber) {
      res["PartNumber"] = boost::any(*partNumber);
    }
    return res;
  }

  shared_ptr<string> partNumber{};

  ~ComplexRequestPart() {};
};
class ComplexRequest : public Darabonba::Model {
protected:
  void _init(){
    _name = map<string, string>({
      {"body" , "Body"},
      {"strs" , "Strs"},
      {"header" , "header"},
      {"part" , "Part"},
    });
  }
public:
  ComplexRequest() {_init();};
  explicit ComplexRequest(const std::map<string, boost::any> &config) : Darabonba::Model(config) {_init();};


  map<string, boost::any> toMap() {
    map<string, boost::any> res;
    if (nullptr != accessKey) {
      res["accessKey"] = boost::any(*accessKey);
    }
    if (nullptr != body) {
      res["Body"] = boost::any(*body);
    }
    if (nullptr != strs) {
      res["Strs"] = boost::any(*strs);
    }
    if (nullptr != header) {
      res["header"] = nullptr != header ? boost::any(header->toMap()) : boost::any(map<string,boost::any>({}));
    }
    if (nullptr != Num) {
      res["Num"] = boost::any(*Num);
    }
    if (nullptr != configs) {
      res["configs"] = nullptr != configs ? boost::any(configs->toMap()) : boost::any(map<string,boost::any>({}));
    }
    if (nullptr != part) {
      res["Part"] = boost::any(vector<boost::any>({}));
      if(nullptr != part){
vector<boost::any> vec_part = boost::any_cast<vector<boost::any>>(res["Part"])
        for(auto item:*part){
vec_part.push_back(boost::any(item.toMap()));
        }
        res["Part"] = vec_part;
      }
    }
    return res;
  }

  shared_ptr<string> accessKey{};
  shared_ptr<istream> body{};
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
  explicit Client(shared_ptr<Darabonba_Source::Config> config): Darabonba_Import::Client(shared_ptr<Darabonba_Source::Config> config);
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
