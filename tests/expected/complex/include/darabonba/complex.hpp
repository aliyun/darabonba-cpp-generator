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
    if (content) {
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
    if (partNumber) {
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
      int n1 = 0;
      ComplexRequestPart temp1;
      for(auto item1:*part){
        temp1[n1] = item1.second ? boost::any(item1.second->toMap()) : boost::any(map<string,boost::any>({}));
        n++;
      }
      res["Part"] = temp1;
    }
    return res;
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
