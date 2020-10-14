// This file is auto-generated, don't edit it. Thanks.

#ifndef DARABONBA_MODEL_H_
#define DARABONBA_MODEL_H_

#include <boost/any.hpp>
#include <darabonba/core.hpp>
#include <darabonba/import.hpp>
#include <darabonba/source.hpp>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

namespace Darabonba_Model {
class MSubM : public Darabonba::Model {
protected:
public:
  MSubM() {_init();};
  explicit MSubM(const std::map<string, boost::any> &config) : Darabonba::Model(config) {_init();};


  map<string, boost::any> toMap() {
    map<string, boost::any> res;
    return res;
  }


  ~MSubM() {};
};
class M : public Darabonba::Model {
protected:
  void _init(){
  }
public:
  M() {_init();};
  explicit M(const std::map<string, boost::any> &config) : Darabonba::Model(config) {_init();};


  map<string, boost::any> toMap() {
    map<string, boost::any> res;
    if (subM) {
      res["subM"] = subM ? boost::any(subM->toMap()) : boost::any(map<string,boost::any>({}));
    }
    return res;
  }

  shared_ptr<MSubM> subM{};

  ~M() {};
};
class Class : public Darabonba::Model {
protected:
public:
  Class() {_init();};
  explicit Class(const std::map<string, boost::any> &config) : Darabonba::Model(config) {_init();};


  map<string, boost::any> toMap() {
    map<string, boost::any> res;
    return res;
  }


  ~Class() {};
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
    if (stringfield) {
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
    if (stringfield) {
      res["stringfield"] = boost::any(*stringfield);
    }
    if (bytesfield) {
      res["bytesfield"] = boost::any(*bytesfield);
    }
    if (stringarrayfield) {
      res["stringarrayfield"] = boost::any(*stringarrayfield);
    }
    if (mapfield) {
      res["mapfield"] = boost::any(*mapfield);
    }
    if (name) {
      res["realName"] = boost::any(*name);
    }
    if (submodel) {
      res["submodel"] = submodel ? boost::any(submodel->toMap()) : boost::any(map<string,boost::any>({}));
    }
    if (submodelMap) {
      MyModelSubmodel temp1;
      for(auto item1:*submodelMap){
        [item1.first] = item1.second ? boost::any(item1.second->toMap()) : boost::any(map<string,boost::any>({}));
      }
      res["submodelMap"] = temp1;
    }
    if (mapModel) {
      M temp1;
      for(auto item1:*mapModel){
        [item1.first] = item1.second ? boost::any(item1.second->toMap()) : boost::any(map<string,boost::any>({}));
      }
      res["mapModel"] = temp1;
    }
    if (subarraymodel) {
      int n1 = 0;
      MyModelSubarraymodel temp1;
      for(auto item1:*subarraymodel){
        temp1[n1] = item1.second ? boost::any(item1.second->toMap()) : boost::any(map<string,boost::any>({}));
        n++;
      }
      res["subarraymodel"] = temp1;
    }
    if (subarray) {
      int n1 = 0;
      M temp1;
      for(auto item1:*subarray){
        temp1[n1] = item1.second ? boost::any(item1.second->toMap()) : boost::any(map<string,boost::any>({}));
        n++;
      }
      res["subarray"] = temp1;
    }
    if (maparray) {
      res["maparray"] = boost::any(*maparray);
    }
    if (moduleModelMap) {
      Darabonba_Source::Request temp1;
      for(auto item1:*moduleModelMap){
        [item1.first] = item1.second ? boost::any(item1.second->toMap()) : boost::any(map<string,boost::any>({}));
      }
      res["moduleModelMap"] = temp1;
    }
    if (subModelMap) {
      MSubM temp1;
      for(auto item1:*subModelMap){
        [item1.first] = item1.second ? boost::any(item1.second->toMap()) : boost::any(map<string,boost::any>({}));
      }
      res["subModelMap"] = temp1;
    }
    if (modelMap) {
      M temp1;
      for(auto item1:*modelMap){
        [item1.first] = item1.second ? boost::any(item1.second->toMap()) : boost::any(map<string,boost::any>({}));
      }
      res["modelMap"] = temp1;
    }
    if (moduleMap) {
      res["moduleMap"] = boost::any(*moduleMap);
    }
    if (object) {
      res["object"] = boost::any(*object);
    }
    if (readable) {
      res["readable"] = boost::any(*readable);
    }
    if (writable) {
      res["writable"] = boost::any(*writable);
    }
    if (existModel) {
      res["existModel"] = existModel ? boost::any(existModel->toMap()) : boost::any(map<string,boost::any>({}));
    }
    if (request) {
      res["request"] = request ? boost::any(request->toMap()) : boost::any(map<string,boost::any>({}));
    }
    if (complexList) {
      res["complexList"] = boost::any(*complexList);
    }
    if (complexMap) {
      int n1 = 0;
      map<string, MyModelSubmodel> temp1;
      for(auto item1:*complexMap){
        MyModelSubmodel temp2;
        for(auto item2:item1.second){
          [item2.first] = item2.second ? boost::any(item2.second->toMap()) : boost::any(map<string,boost::any>({}));
        }
        temp1[n1] = temp2;
        n++;
      }
      res["complexMap"] = temp1;
    }
    if (numberfield) {
      res["numberfield"] = boost::any(*numberfield);
    }
    if (integerField) {
      res["integerField"] = boost::any(*integerField);
    }
    if (floatField) {
      res["floatField"] = boost::any(*floatField);
    }
    if (doubleField) {
      res["doubleField"] = boost::any(*doubleField);
    }
    if (longField) {
      res["longField"] = boost::any(*longField);
    }
    if (ulongField) {
      res["ulongField"] = boost::any(*ulongField);
    }
    if (int8Field) {
      res["int8Field"] = boost::any(*int8Field);
    }
    if (int16Field) {
      res["int16Field"] = boost::any(*int16Field);
    }
    if (int32Field) {
      res["int32Field"] = boost::any(*int32Field);
    }
    if (int64Field) {
      res["int64Field"] = boost::any(*int64Field);
    }
    if (uint8Field) {
      res["uint8Field"] = boost::any(*uint8Field);
    }
    if (uint16Field) {
      res["uint16Field"] = boost::any(*uint16Field);
    }
    if (uint32Field) {
      res["uint32Field"] = boost::any(*uint32Field);
    }
    if (uint64Field) {
      res["uint64Field"] = boost::any(*uint64Field);
    }
    return res;
  }

  shared_ptr<string> stringfield{};
  shared_ptr<vector<uint8_t>> bytesfield{};
  shared_ptr<vector<string>> stringarrayfield{};
  shared_ptr<map<string, string>> mapfield{};
  shared_ptr<string> name{};
  shared_ptr<MyModelSubmodel> submodel{};
  shared_ptr<map<string, MyModelSubmodel>> submodelMap{};
  shared_ptr<map<string, M>> mapModel{};
  shared_ptr<vector<MyModelSubarraymodel>> subarraymodel{};
  shared_ptr<vector<M>> subarray{};
  shared_ptr<vector<map<string, boost::any>>> maparray{};
  shared_ptr<map<string, Darabonba_Source::Request>> moduleModelMap{};
  shared_ptr<map<string, MSubM>> subModelMap{};
  shared_ptr<map<string, M>> modelMap{};
  shared_ptr<map<string, Darabonba_Import::Client>> moduleMap{};
  shared_ptr<map<string, boost::any>> object{};
  shared_ptr<Darabonba::Stream> readable{};
  shared_ptr<Darabonba::Stream> writable{};
  shared_ptr<M> existModel{};
  shared_ptr<Darabonba::Request> request{};
  shared_ptr<vector<vector<string>>> complexList{};
  shared_ptr<vector<map<string, MyModelSubmodel>>> complexMap{};
  shared_ptr<int> numberfield{};
  shared_ptr<int> integerField{};
  shared_ptr<float> floatField{};
  shared_ptr<float> doubleField{};
  shared_ptr<long> longField{};
  shared_ptr<long> ulongField{};
  shared_ptr<int> int8Field{};
  shared_ptr<int> int16Field{};
  shared_ptr<long> int32Field{};
  shared_ptr<long> int64Field{};
  shared_ptr<int> uint8Field{};
  shared_ptr<int> uint16Field{};
  shared_ptr<long> uint32Field{};
  shared_ptr<long> uint64Field{};

  ~MyModel() {};
};
class Client {
public:

  Client() {};
  ~Client() {};
};
} // namespace Darabonba_Model

#endif
