// This file is auto-generated, don't edit it. Thanks.

#ifndef DARABONBA_MODEL_H_
#define DARABONBA_MODEL_H_

#include <boost/any.hpp>
#include <boost/throw_exception.hpp>
#include <darabonba/core.hpp>
#include <darabonba/import.hpp>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

namespace Darabonba_Model {
class MSubM : public Darabonba::Model {
public:

  MSubM() {}

  explicit MSubM(const std::map<string, boost::any> &config) : Darabonba::Model(config) {
    fromMap(config);
  };

  void validate() override {}

  map<string, boost::any> toMap() override {
    map<string, boost::any> res;
    return res;
  }

  void fromMap(map<string, boost::any> m) override {
  }


  virtual ~MSubM() = default;
};
class M : public Darabonba::Model {
public:
  shared_ptr<MSubM> subM{};

  M() {}

  explicit M(const std::map<string, boost::any> &config) : Darabonba::Model(config) {
    fromMap(config);
  };

  void validate() override {
    if (!subM) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("subM is required.")));
    }
  }

  map<string, boost::any> toMap() override {
    map<string, boost::any> res;
    if (subM) {
      res["subM"] = subM ? boost::any(subM->toMap()) : boost::any(map<string,boost::any>({}));
    }
    return res;
  }

  void fromMap(map<string, boost::any> m) override {
    if (m.find("subM") != m.end() && !m["subM"].empty()) {
      if (typeid(map<string, boost::any>) == m["subM"].type()) {
        MSubM model1;
        model1.fromMap(boost::any_cast<map<string, boost::any>>(m["subM"]));
        subM = make_shared<MSubM>(model1);
      }
    }
  }


  virtual ~M() = default;
};
class Class : public Darabonba::Model {
public:

  Class() {}

  explicit Class(const std::map<string, boost::any> &config) : Darabonba::Model(config) {
    fromMap(config);
  };

  void validate() override {}

  map<string, boost::any> toMap() override {
    map<string, boost::any> res;
    return res;
  }

  void fromMap(map<string, boost::any> m) override {
  }


  virtual ~Class() = default;
};
class MyModelSubmodel : public Darabonba::Model {
public:
  shared_ptr<string> stringfield{};

  MyModelSubmodel() {}

  explicit MyModelSubmodel(const std::map<string, boost::any> &config) : Darabonba::Model(config) {
    fromMap(config);
  };

  void validate() override {
    if (!stringfield) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("stringfield is required.")));
    }
  }

  map<string, boost::any> toMap() override {
    map<string, boost::any> res;
    if (stringfield) {
      res["stringfield"] = boost::any(*stringfield);
    }
    return res;
  }

  void fromMap(map<string, boost::any> m) override {
    if (m.find("stringfield") != m.end() && !m["stringfield"].empty()) {
      stringfield = make_shared<string>(boost::any_cast<string>(m["stringfield"]));
    }
  }


  virtual ~MyModelSubmodel() = default;
};
class MyModelSubarraymodel : public Darabonba::Model {
public:

  MyModelSubarraymodel() {}

  explicit MyModelSubarraymodel(const std::map<string, boost::any> &config) : Darabonba::Model(config) {
    fromMap(config);
  };

  void validate() override {}

  map<string, boost::any> toMap() override {
    map<string, boost::any> res;
    return res;
  }

  void fromMap(map<string, boost::any> m) override {
  }


  virtual ~MyModelSubarraymodel() = default;
};
class MyModel : public Darabonba::Model {
public:
  // keyword property
  shared_ptr<string> delete_{};
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
  shared_ptr<map<string, Darabonba_Import::Request>> moduleModelMap{};
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
  shared_ptr<double> floatField{};
  shared_ptr<double> doubleField{};
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
  shared_ptr<long> numberPattern{};

  MyModel() {}

  explicit MyModel(const std::map<string, boost::any> &config) : Darabonba::Model(config) {
    fromMap(config);
  };

  void validate() override {
    if (!delete_) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("delete is required.")));
    }
    if (!stringfield) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("stringfield is required.")));
    }
    if (!bytesfield) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("bytesfield is required.")));
    }
    if (!stringarrayfield) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("stringarrayfield is required.")));
    }
    if (!mapfield) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("mapfield is required.")));
    }
    if (!name) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("name is required.")));
    }
    if (!submodel) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("submodel is required.")));
    }
    if (!submodelMap) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("submodelMap is required.")));
    }
    if (!mapModel) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("mapModel is required.")));
    }
    if (!subarraymodel) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("subarraymodel is required.")));
    }
    if (!subarray) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("subarray is required.")));
    }
    if (!maparray) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("maparray is required.")));
    }
    if (!moduleModelMap) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("moduleModelMap is required.")));
    }
    if (!subModelMap) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("subModelMap is required.")));
    }
    if (!modelMap) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("modelMap is required.")));
    }
    if (!moduleMap) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("moduleMap is required.")));
    }
    if (!object) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("object is required.")));
    }
    if (!readable) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("readable is required.")));
    }
    if (!writable) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("writable is required.")));
    }
    if (!existModel) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("existModel is required.")));
    }
    if (!request) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("request is required.")));
    }
    if (!complexList) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("complexList is required.")));
    }
    if (!complexMap) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("complexMap is required.")));
    }
    if (!numberfield) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("numberfield is required.")));
    }
    if (!integerField) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("integerField is required.")));
    }
    if (!floatField) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("floatField is required.")));
    }
    if (!doubleField) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("doubleField is required.")));
    }
    if (!longField) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("longField is required.")));
    }
    if (!ulongField) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("ulongField is required.")));
    }
    if (!int8Field) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("int8Field is required.")));
    }
    if (!int16Field) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("int16Field is required.")));
    }
    if (!int32Field) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("int32Field is required.")));
    }
    if (!int64Field) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("int64Field is required.")));
    }
    if (!uint8Field) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("uint8Field is required.")));
    }
    if (!uint16Field) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("uint16Field is required.")));
    }
    if (!uint32Field) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("uint32Field is required.")));
    }
    if (!uint64Field) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("uint64Field is required.")));
    }
    if (numberPattern && *numberPattern > 100) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("numberPattern is required.")));
    }
    if (numberPattern && *numberPattern < 0) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("numberPattern is required.")));
    }
  }

  map<string, boost::any> toMap() override {
    map<string, boost::any> res;
    if (delete_) {
      res["Delete"] = boost::any(*delete_);
    }
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
      map<string, boost::any> temp1;
      for(auto item1:*submodelMap){
        temp1[item1.first] = boost::any(item1.second.toMap());
      }
      res["submodelMap"] = boost::any(temp1);
    }
    if (mapModel) {
      map<string, boost::any> temp1;
      for(auto item1:*mapModel){
        temp1[item1.first] = boost::any(item1.second.toMap());
      }
      res["mapModel"] = boost::any(temp1);
    }
    if (subarraymodel) {
      vector<boost::any> temp1;
      for(auto item1:*subarraymodel){
        temp1.push_back(boost::any(item1.toMap()));
      }
      res["subarraymodel"] = boost::any(temp1);
    }
    if (subarray) {
      vector<boost::any> temp1;
      for(auto item1:*subarray){
        temp1.push_back(boost::any(item1.toMap()));
      }
      res["subarray"] = boost::any(temp1);
    }
    if (maparray) {
      res["maparray"] = boost::any(*maparray);
    }
    if (moduleModelMap) {
      map<string, boost::any> temp1;
      for(auto item1:*moduleModelMap){
        temp1[item1.first] = boost::any(item1.second.toMap());
      }
      res["moduleModelMap"] = boost::any(temp1);
    }
    if (subModelMap) {
      map<string, boost::any> temp1;
      for(auto item1:*subModelMap){
        temp1[item1.first] = boost::any(item1.second.toMap());
      }
      res["subModelMap"] = boost::any(temp1);
    }
    if (modelMap) {
      map<string, boost::any> temp1;
      for(auto item1:*modelMap){
        temp1[item1.first] = boost::any(item1.second.toMap());
      }
      res["modelMap"] = boost::any(temp1);
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
      vector<boost::any> temp1;
      for(auto item1:*complexMap){
        map<string, boost::any> temp2;
        for(auto item2:item1){
          temp2[item2.first] = boost::any(item2.second.toMap());
        }
        temp1 = boost::any(temp2);
      }
      res["complexMap"] = boost::any(temp1);
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
    if (numberPattern) {
      res["pattern"] = boost::any(*numberPattern);
    }
    return res;
  }

  void fromMap(map<string, boost::any> m) override {
    if (m.find("Delete") != m.end() && !m["Delete"].empty()) {
      delete_ = make_shared<string>(boost::any_cast<string>(m["Delete"]));
    }
    if (m.find("stringfield") != m.end() && !m["stringfield"].empty()) {
      stringfield = make_shared<string>(boost::any_cast<string>(m["stringfield"]));
    }
    if (m.find("bytesfield") != m.end() && !m["bytesfield"].empty()) {
      bytesfield = make_shared<vector<uint8_t>>(boost::any_cast<vector<uint8_t>>(m["bytesfield"]));
    }
    if (m.find("stringarrayfield") != m.end() && !m["stringarrayfield"].empty()) {
      vector<string> toVec1;
      if (typeid(vector<boost::any>) == m["stringarrayfield"].type()) {
        vector<boost::any> vec1 = boost::any_cast<vector<boost::any>>(m["stringarrayfield"]);
        for (auto item:vec1) {
           toVec1.push_back(boost::any_cast<string>(item));
        }
      }
      stringarrayfield = make_shared<vector<string>>(toVec1);
    }
    if (m.find("mapfield") != m.end() && !m["mapfield"].empty()) {
      map<string, string> map1 = boost::any_cast<map<string, string>>(m["mapfield"]);
      map<string, string> toMap1;
      for (auto item:map1) {
         toMap1[item.first] = item.second;
      }
      mapfield = make_shared<map<string, string>>(toMap1);
    }
    if (m.find("realName") != m.end() && !m["realName"].empty()) {
      name = make_shared<string>(boost::any_cast<string>(m["realName"]));
    }
    if (m.find("submodel") != m.end() && !m["submodel"].empty()) {
      if (typeid(map<string, boost::any>) == m["submodel"].type()) {
        MyModelSubmodel model1;
        model1.fromMap(boost::any_cast<map<string, boost::any>>(m["submodel"]));
        submodel = make_shared<MyModelSubmodel>(model1);
      }
    }
    if (m.find("submodelMap") != m.end() && !m["submodelMap"].empty()) {
      if (typeid(map<string, boost::any>) == m["submodelMap"].type()) {
        map<string, MyModelSubmodel> expect1;
        for(auto item1:boost::any_cast<map<string, boost::any>>(m["submodelMap"])){
          if (typeid(map<string, boost::any>) == item1.second.type()) {
            MyModelSubmodel model2;
            model2.fromMap(boost::any_cast<map<string, boost::any>>(item1.second));
            expect1[item1.first] = model2;
          }
        }
        submodelMap = make_shared<map<string, MyModelSubmodel>>(expect1);
      }
    }
    if (m.find("mapModel") != m.end() && !m["mapModel"].empty()) {
      if (typeid(map<string, boost::any>) == m["mapModel"].type()) {
        map<string, M> expect1;
        for(auto item1:boost::any_cast<map<string, boost::any>>(m["mapModel"])){
          if (typeid(map<string, boost::any>) == item1.second.type()) {
            M model2;
            model2.fromMap(boost::any_cast<map<string, boost::any>>(item1.second));
            expect1[item1.first] = model2;
          }
        }
        mapModel = make_shared<map<string, M>>(expect1);
      }
    }
    if (m.find("subarraymodel") != m.end() && !m["subarraymodel"].empty()) {
      if (typeid(vector<boost::any>) == m["subarraymodel"].type()) {
        vector<MyModelSubarraymodel> expect1;
        for(auto item1:boost::any_cast<vector<boost::any>>(m["subarraymodel"])){
          if (typeid(map<string, boost::any>) == item1.type()) {
            MyModelSubarraymodel model2;
            model2.fromMap(boost::any_cast<map<string, boost::any>>(item1));
            expect1.push_back(model2);
          }
        }
        subarraymodel = make_shared<vector<MyModelSubarraymodel>>(expect1);
      }
    }
    if (m.find("subarray") != m.end() && !m["subarray"].empty()) {
      if (typeid(vector<boost::any>) == m["subarray"].type()) {
        vector<M> expect1;
        for(auto item1:boost::any_cast<vector<boost::any>>(m["subarray"])){
          if (typeid(map<string, boost::any>) == item1.type()) {
            M model2;
            model2.fromMap(boost::any_cast<map<string, boost::any>>(item1));
            expect1.push_back(model2);
          }
        }
        subarray = make_shared<vector<M>>(expect1);
      }
    }
    if (m.find("maparray") != m.end() && !m["maparray"].empty()) {
      vector<map<string, boost::any>> toVec1;
      if (typeid(vector<boost::any>) == m["maparray"].type()) {
        vector<boost::any> vec1 = boost::any_cast<vector<boost::any>>(m["maparray"]);
        for (auto item:vec1) {
          map<string, boost::any> map2 = boost::any_cast<map<string, boost::any>>(item);
          map<string, boost::any> toMap2;
          for (auto item:map2) {
             toMap2[item.first] = item.second;
          }
           toVec1.push_back(toMap2);
        }
      }
      maparray = make_shared<vector<map<string, boost::any>>>(toVec1);
    }
    if (m.find("moduleModelMap") != m.end() && !m["moduleModelMap"].empty()) {
      if (typeid(map<string, boost::any>) == m["moduleModelMap"].type()) {
        map<string, Darabonba_Import::Request> expect1;
        for(auto item1:boost::any_cast<map<string, boost::any>>(m["moduleModelMap"])){
          if (typeid(map<string, boost::any>) == item1.second.type()) {
            Darabonba_Import::Request model2;
            model2.fromMap(boost::any_cast<map<string, boost::any>>(item1.second));
            expect1[item1.first] = model2;
          }
        }
        moduleModelMap = make_shared<map<string, Darabonba_Import::Request>>(expect1);
      }
    }
    if (m.find("subModelMap") != m.end() && !m["subModelMap"].empty()) {
      if (typeid(map<string, boost::any>) == m["subModelMap"].type()) {
        map<string, MSubM> expect1;
        for(auto item1:boost::any_cast<map<string, boost::any>>(m["subModelMap"])){
          if (typeid(map<string, boost::any>) == item1.second.type()) {
            MSubM model2;
            model2.fromMap(boost::any_cast<map<string, boost::any>>(item1.second));
            expect1[item1.first] = model2;
          }
        }
        subModelMap = make_shared<map<string, MSubM>>(expect1);
      }
    }
    if (m.find("modelMap") != m.end() && !m["modelMap"].empty()) {
      if (typeid(map<string, boost::any>) == m["modelMap"].type()) {
        map<string, M> expect1;
        for(auto item1:boost::any_cast<map<string, boost::any>>(m["modelMap"])){
          if (typeid(map<string, boost::any>) == item1.second.type()) {
            M model2;
            model2.fromMap(boost::any_cast<map<string, boost::any>>(item1.second));
            expect1[item1.first] = model2;
          }
        }
        modelMap = make_shared<map<string, M>>(expect1);
      }
    }
    if (m.find("moduleMap") != m.end() && !m["moduleMap"].empty()) {
      map<string, Darabonba_Import::Client> map1 = boost::any_cast<map<string, Darabonba_Import::Client>>(m["moduleMap"]);
      map<string, Darabonba_Import::Client> toMap1;
      for (auto item:map1) {
         toMap1[item.first] = Darabonba_Import::Client(item.second);
      }
      moduleMap = make_shared<map<string, Darabonba_Import::Client>>(toMap1);
    }
    if (m.find("object") != m.end() && !m["object"].empty()) {
      map<string, boost::any> map1 = boost::any_cast<map<string, boost::any>>(m["object"]);
      map<string, boost::any> toMap1;
      for (auto item:map1) {
         toMap1[item.first] = item.second;
      }
      object = make_shared<map<string, boost::any>>(toMap1);
    }
    if (m.find("readable") != m.end() && !m["readable"].empty()) {
      readable = make_shared<Darabonba::Stream>(boost::any_cast<Darabonba::Stream>(m["readable"]));
    }
    if (m.find("writable") != m.end() && !m["writable"].empty()) {
      writable = make_shared<Darabonba::Stream>(boost::any_cast<Darabonba::Stream>(m["writable"]));
    }
    if (m.find("existModel") != m.end() && !m["existModel"].empty()) {
      if (typeid(map<string, boost::any>) == m["existModel"].type()) {
        M model1;
        model1.fromMap(boost::any_cast<map<string, boost::any>>(m["existModel"]));
        existModel = make_shared<M>(model1);
      }
    }
    if (m.find("request") != m.end() && !m["request"].empty()) {
      if (typeid(map<string, boost::any>) == m["request"].type()) {
        Darabonba::Request model1;
        model1.fromMap(boost::any_cast<map<string, boost::any>>(m["request"]));
        request = make_shared<Darabonba::Request>(model1);
      }
    }
    if (m.find("complexList") != m.end() && !m["complexList"].empty()) {
      vector<vector<string>> toVec1;
      if (typeid(vector<boost::any>) == m["complexList"].type()) {
        vector<boost::any> vec1 = boost::any_cast<vector<boost::any>>(m["complexList"]);
        for (auto item:vec1) {
          vector<string> toVec2;
          if (typeid(vector<boost::any>) == item.type()) {
            vector<boost::any> vec2 = boost::any_cast<vector<boost::any>>(item);
            for (auto item:vec2) {
               toVec2.push_back(boost::any_cast<string>(item));
            }
          }
           toVec1 = toVec2;
        }
      }
      complexList = make_shared<vector<vector<string>>>(toVec1);
    }
    if (m.find("complexMap") != m.end() && !m["complexMap"].empty()) {
      if (typeid(vector<boost::any>) == m["complexMap"].type()) {
        vector<map<string, MyModelSubmodel>> expect1;
        for(auto item1:boost::any_cast<vector<boost::any>>(m["complexMap"])){
          if (typeid(map<string, boost::any>) == item1.type()) {
            map<string, MyModelSubmodel> expect2;
            for(auto item2:boost::any_cast<map<string, boost::any>>(item1)){
              if (typeid(map<string, boost::any>) == item2.second.type()) {
                MyModelSubmodel model3;
                model3.fromMap(boost::any_cast<map<string, boost::any>>(item2.second));
                expect2[item2.first] = model3;
              }
            }
            expect1.push_back(expect2);
          }
        }
        complexMap = make_shared<vector<map<string, MyModelSubmodel>>>(expect1);
      }
    }
    if (m.find("numberfield") != m.end() && !m["numberfield"].empty()) {
      numberfield = make_shared<int>(boost::any_cast<int>(m["numberfield"]));
    }
    if (m.find("integerField") != m.end() && !m["integerField"].empty()) {
      integerField = make_shared<int>(boost::any_cast<int>(m["integerField"]));
    }
    if (m.find("floatField") != m.end() && !m["floatField"].empty()) {
      floatField = make_shared<double>(boost::any_cast<double>(m["floatField"]));
    }
    if (m.find("doubleField") != m.end() && !m["doubleField"].empty()) {
      doubleField = make_shared<double>(boost::any_cast<double>(m["doubleField"]));
    }
    if (m.find("longField") != m.end() && !m["longField"].empty()) {
      longField = make_shared<long>(boost::any_cast<long>(m["longField"]));
    }
    if (m.find("ulongField") != m.end() && !m["ulongField"].empty()) {
      ulongField = make_shared<long>(boost::any_cast<long>(m["ulongField"]));
    }
    if (m.find("int8Field") != m.end() && !m["int8Field"].empty()) {
      int8Field = make_shared<int>(boost::any_cast<int>(m["int8Field"]));
    }
    if (m.find("int16Field") != m.end() && !m["int16Field"].empty()) {
      int16Field = make_shared<int>(boost::any_cast<int>(m["int16Field"]));
    }
    if (m.find("int32Field") != m.end() && !m["int32Field"].empty()) {
      int32Field = make_shared<long>(boost::any_cast<long>(m["int32Field"]));
    }
    if (m.find("int64Field") != m.end() && !m["int64Field"].empty()) {
      int64Field = make_shared<long>(boost::any_cast<long>(m["int64Field"]));
    }
    if (m.find("uint8Field") != m.end() && !m["uint8Field"].empty()) {
      uint8Field = make_shared<int>(boost::any_cast<int>(m["uint8Field"]));
    }
    if (m.find("uint16Field") != m.end() && !m["uint16Field"].empty()) {
      uint16Field = make_shared<int>(boost::any_cast<int>(m["uint16Field"]));
    }
    if (m.find("uint32Field") != m.end() && !m["uint32Field"].empty()) {
      uint32Field = make_shared<long>(boost::any_cast<long>(m["uint32Field"]));
    }
    if (m.find("uint64Field") != m.end() && !m["uint64Field"].empty()) {
      uint64Field = make_shared<long>(boost::any_cast<long>(m["uint64Field"]));
    }
    if (m.find("pattern") != m.end() && !m["pattern"].empty()) {
      numberPattern = make_shared<long>(boost::any_cast<long>(m["pattern"]));
    }
  }


  virtual ~MyModel() = default;
};
class UseBeforeDefineModel : public Darabonba::Model {
public:
  shared_ptr<MyModel> m{};

  UseBeforeDefineModel() {}

  explicit UseBeforeDefineModel(const std::map<string, boost::any> &config) : Darabonba::Model(config) {
    fromMap(config);
  };

  void validate() override {
    if (!m) {
      BOOST_THROW_EXCEPTION(boost::enable_error_info(std::runtime_error("m is required.")));
    }
  }

  map<string, boost::any> toMap() override {
    map<string, boost::any> res;
    if (m) {
      res["m"] = m ? boost::any(m->toMap()) : boost::any(map<string,boost::any>({}));
    }
    return res;
  }

  void fromMap(map<string, boost::any> m) override {
    if (m.find("m") != m.end() && !m["m"].empty()) {
      if (typeid(map<string, boost::any>) == m["m"].type()) {
        MyModel model1;
        model1.fromMap(boost::any_cast<map<string, boost::any>>(m["m"]));
        m = make_shared<MyModel>(model1);
      }
    }
  }


  virtual ~UseBeforeDefineModel() = default;
};
class Client {
public:

  Client() {};
  virtual ~Client() = default;
};
} // namespace Darabonba_Model

#endif
