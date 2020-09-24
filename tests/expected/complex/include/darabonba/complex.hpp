// This file is auto-generated, don't edit it. Thanks.

#ifndef DARABONBA_COMPLEX_H_
#define DARABONBA_COMPLEX_H_

#include <boost/any.hpp>
#include <cpprest/streams.h>
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

  string *content{};

  ~ComplexRequestHeader() {
    delete content;
    content = nullptr;
  };
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

  string *key{};
  vector<string> *value{};
  map<string, string> *extra{};

  ~ComplexRequestConfigs() {
    delete key;
    key = nullptr;
    delete value;
    value = nullptr;
    delete extra;
    extra = nullptr;
  };
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

  string *partNumber{};

  ~ComplexRequestPart() {
    delete partNumber;
    partNumber = nullptr;
  };
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

  string *accessKey{};
  concurrency::streams::istream *body{};
  vector<string> *strs{};
  ComplexRequestHeader *header{};
  int *Num{};
  ComplexRequestConfigs *configs{};
  vector<ComplexRequestPart> *part{};

  ~ComplexRequest() {
    delete accessKey;
    accessKey = nullptr;
    delete body;
    body = nullptr;
    delete strs;
    strs = nullptr;
    delete header;
    header = nullptr;
    delete Num;
    Num = nullptr;
    delete configs;
    configs = nullptr;
    delete part;
    part = nullptr;
  };
};
class Client : Darabonba_Import::Client {
public:
  vector<Darabonba_Source::Config> *_configs{};
  explicit Client(Darabonba_Source::Config *config): Darabonba_Import::Client(Darabonba_Source::Config *config);
  Darabonba_Source::RuntimeObject complex1(ComplexRequest *request, Darabonba_Import::Client *client);
  map<string, boost::any> Complex2(ComplexRequest *request, vector<string> *str, map<string, string> *val);
  ComplexRequest Complex3(ComplexRequest *request);
  vector<string> hello(map<string, boost::any> *request, vector<string> *strs);
  static Darabonba_Source::Request print(Darabonba::Request *reqeust,
                                         vector<ComplexRequest> *reqs,
                                         Darabonba::Response *response,
                                         map<string, string> *val);
  static vector<boost::any> array0(map<string, boost::any> *req);
  static vector<string> array1();
  static string arrayAccess();
  static string arrayAccess2();
  static string arrayAccess3(ComplexRequest *request);
  static vector<string> arrayAssign(string *config);
  static vector<string> arrayAssign2(string *config);
  static void arrayAssign3(ComplexRequest *request, string *config);
  static string mapAccess(ComplexRequest *request);
  static string mapAccess2(Darabonba_Source::Request *request);
  static string mapAccess3();
  static void mapAssign(ComplexRequest *request, string *name);
  string TemplateString();
  void emptyModel();
  void tryCatch();

  ~Client() {
    delete _configs;
    _configs = nullptr;
  };
};
} // namespace Darabonba_Complex

#endif
