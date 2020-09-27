// This file is auto-generated, don't edit it. Thanks.

#ifndef DARABONBA_MODEL_H_
#define DARABONBA_MODEL_H_

#include <boost/any.hpp>
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

  shared_ptr<string> stringfield{};

  ~MyModelSubmodel() {};
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
      {"name" , "realName"},
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

  shared_ptr<string> stringfield{};
  shared_ptr<vector<uint8_t>> bytesfield{};
  shared_ptr<vector<string>> stringarrayfield{};
  shared_ptr<map<string, string>> mapfield{};
  shared_ptr<string> name{};
  shared_ptr<MyModelSubmodel> submodel{};
  shared_ptr<vector<MyModelSubarraymodel>> subarraymodel{};
  shared_ptr<vector<M>> subarray{};
  shared_ptr<vector<map<string, boost::any>>> maparray{};
  shared_ptr<map<string, boost::any>> object{};
  shared_ptr<int> numberfield{};
  shared_ptr<istream> readable{};
  shared_ptr<M> existModel{};

  ~MyModel() {};
};
class Client {
public:

  Client() {};
  ~Client() {};
};
} // namespace Darabonba_Model

#endif
