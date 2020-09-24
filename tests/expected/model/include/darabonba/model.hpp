// This file is auto-generated, don't edit it. Thanks.

#ifndef DARABONBA_MODEL_H_
#define DARABONBA_MODEL_H_

#include <boost/any.hpp>
#include <cpprest/streams.h>
#include <darabonba/core.hpp>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

namespace Darabonba_Model {
class M : public Darabonba::Model {
protected:
public:
  M() {_init();};
  explicit M(const std::map<string, boost::any> &config) : Darabonba::Model(config) {_init();};


  map<string, boost::any> toMap() {
    map<string, boost::any> res;
    return res;
  }


  ~M() {};
};
class MyModelSubmodel : public Darabonba::Model {
protected:
  void _init(){
  }
public:
  MyModelSubmodel() {_init();};
  explicit MyModelSubmodel(const std::map<string, boost::any> &config) : Darabonba::Model(config) {_init();};


  map<string, boost::any> toMap() {
    map<string, boost::any> res;
    if (nullptr != stringfield) {
      res["stringfield"] = boost::any(*stringfield);
    }
    return res;
  }

  string *stringfield{};

  ~MyModelSubmodel() {
    delete stringfield;
    stringfield = nullptr;
  };
};
class MyModelSubarraymodel : public Darabonba::Model {
protected:
public:
  MyModelSubarraymodel() {_init();};
  explicit MyModelSubarraymodel(const std::map<string, boost::any> &config) : Darabonba::Model(config) {_init();};


  map<string, boost::any> toMap() {
    map<string, boost::any> res;
    return res;
  }


  ~MyModelSubarraymodel() {};
};
class MyModel : public Darabonba::Model {
protected:
  void _init(){
    _name = map<string, string>({
      {"name" , "realName",
    });
  }
public:
  MyModel() {_init();};
  explicit MyModel(const std::map<string, boost::any> &config) : Darabonba::Model(config) {_init();};


  map<string, boost::any> toMap() {
    map<string, boost::any> res;
    if (nullptr != stringfield) {
      res["stringfield"] = boost::any(*stringfield);
    }
    if (nullptr != bytesfield) {
      res["bytesfield"] = boost::any(*bytesfield);
    }
    if (nullptr != stringarrayfield) {
      res["stringarrayfield"] = boost::any(*stringarrayfield);
    }
    if (nullptr != mapfield) {
      res["mapfield"] = boost::any(*mapfield);
    }
    if (nullptr != name) {
      res["realName"] = boost::any(*name);
    }
    if (nullptr != submodel) {
      res["submodel"] = nullptr != submodel ? boost::any(submodel->toMap()) : boost::any(map<string,boost::any>({}));
    }
    if (nullptr != subarraymodel) {
      res["subarraymodel"] = boost::any(vector<boost::any>({}));
      if(nullptr != subarraymodel){
vector<boost::any> vec_subarraymodel = boost::any_cast<vector<boost::any>>(res["subarraymodel"])
        for(auto item:*subarraymodel){
vec_subarraymodel.push_back(boost::any(item.toMap()));
        }
        res["subarraymodel"] = vec_subarraymodel;
      }
    }
    if (nullptr != subarray) {
      res["subarray"] = boost::any(vector<boost::any>({}));
      if(nullptr != subarray){
vector<boost::any> vec_subarray = boost::any_cast<vector<boost::any>>(res["subarray"])
        for(auto item:*subarray){
vec_subarray.push_back(boost::any(item.toMap()));
        }
        res["subarray"] = vec_subarray;
      }
    }
    if (nullptr != maparray) {
      res["maparray"] = boost::any(*maparray);
    }
    if (nullptr != object) {
      res["object"] = boost::any(*object);
    }
    if (nullptr != numberfield) {
      res["numberfield"] = boost::any(*numberfield);
    }
    if (nullptr != readable) {
      res["readable"] = boost::any(*readable);
    }
    if (nullptr != existModel) {
      res["existModel"] = nullptr != existModel ? boost::any(existModel->toMap()) : boost::any(map<string,boost::any>({}));
    }
    return res;
  }

  string *stringfield{};
  vector<uint8_t> *bytesfield{};
  vector<string> *stringarrayfield{};
  map<string, string> *mapfield{};
  string *name{};
  MyModelSubmodel *submodel{};
  vector<MyModelSubarraymodel> *subarraymodel{};
  vector<M> *subarray{};
  vector<map<string, boost::any>> *maparray{};
  map<string, boost::any> *object{};
  int *numberfield{};
  concurrency::streams::istream *readable{};
  M *existModel{};

  ~MyModel() {
    delete stringfield;
    stringfield = nullptr;
    delete bytesfield;
    bytesfield = nullptr;
    delete stringarrayfield;
    stringarrayfield = nullptr;
    delete mapfield;
    mapfield = nullptr;
    delete name;
    name = nullptr;
    delete submodel;
    submodel = nullptr;
    delete subarraymodel;
    subarraymodel = nullptr;
    delete subarray;
    subarray = nullptr;
    delete maparray;
    maparray = nullptr;
    delete object;
    object = nullptr;
    delete numberfield;
    numberfield = nullptr;
    delete readable;
    readable = nullptr;
    delete existModel;
    existModel = nullptr;
  };
};
class Client {
public:

  Client() {};
  ~Client() {};
};
} // namespace Darabonba_Model

#endif
