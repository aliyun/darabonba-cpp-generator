// This file is auto-generated, don't edit it. Thanks.
#ifndef DARABONBA_MODELS_MYMODEL_HPP_
#define DARABONBA_MODELS_MYMODEL_HPP_
#include <darabonba/Core.hpp>
#include <vector>
#include <map>
#include <darabonba/models/MyModelSubmodel.hpp>
#include <darabonba/models/M.hpp>
#include <darabonba/source.hpp>
#include <darabonba/models/MSubM.hpp>
#include <darabonba/http/Request.hpp>
using namespace std;
using json = nlohmann::json;
namespace Darabonba
{
namespace Test
{
namespace Models
{
  class MyModel : public Darabonba::Model {
  public:
    friend void to_json(Darabonba::Json& j, const MyModel& obj) { 
      DARABONBA_PTR_TO_JSON(model, model_);
      DARABONBA_PTR_TO_JSON(stringfield, stringfield_);
      DARABONBA_PTR_TO_JSON(bytesfield, bytesfield_);
      DARABONBA_PTR_TO_JSON(stringarrayfield, stringarrayfield_);
      DARABONBA_PTR_TO_JSON(mapfield, mapfield_);
      DARABONBA_PTR_TO_JSON(realName, name_);
      DARABONBA_PTR_TO_JSON(submodel, submodel_);
      DARABONBA_PTR_TO_JSON(submodelMap, submodelMap_);
      DARABONBA_PTR_TO_JSON(mapModel, mapModel_);
      DARABONBA_PTR_TO_JSON(subarraymodel, subarraymodel_);
      DARABONBA_PTR_TO_JSON(subarray, subarray_);
      DARABONBA_PTR_TO_JSON(ssubarray, ssubarray_);
      DARABONBA_PTR_TO_JSON(ssubmarray, ssubmarray_);
      DARABONBA_PTR_TO_JSON(sssubmarray, sssubmarray_);
      DARABONBA_PTR_TO_JSON(ssubmmarray, ssubmmarray_);
      DARABONBA_PTR_TO_JSON(sssubmmarray, sssubmmarray_);
      DARABONBA_PTR_TO_JSON(maparray, maparray_);
      DARABONBA_PTR_TO_JSON(mapsubmarray, mapsubmarray_);
      DARABONBA_PTR_TO_JSON(moduleModelMap, moduleModelMap_);
      DARABONBA_PTR_TO_JSON(arrModuleModelMap, arrModuleModelMap_);
      DARABONBA_PTR_TO_JSON(arrsModuleModelMap, arrsModuleModelMap_);
      DARABONBA_PTR_TO_JSON(subModelMap, subModelMap_);
      DARABONBA_PTR_TO_JSON(modelMap, modelMap_);
      DARABONBA_PTR_TO_JSON(moduleMap, moduleMap_);
      DARABONBA_PTR_TO_JSON(object, object_);
      DARABONBA_TO_JSON(readable, readable_);
      DARABONBA_TO_JSON(writable, writable_);
      DARABONBA_PTR_TO_JSON(existModel, existModel_);
      DARABONBA_PTR_TO_JSON(request, request_);
      DARABONBA_PTR_TO_JSON(complexList, complexList_);
      DARABONBA_PTR_TO_JSON(numberfield, numberfield_);
      DARABONBA_PTR_TO_JSON(integerField, integerField_);
      DARABONBA_PTR_TO_JSON(floatField, floatField_);
      DARABONBA_PTR_TO_JSON(doubleField, doubleField_);
      DARABONBA_PTR_TO_JSON(longField, longField_);
      DARABONBA_PTR_TO_JSON(ulongField, ulongField_);
      DARABONBA_PTR_TO_JSON(int8Field, int8Field_);
      DARABONBA_PTR_TO_JSON(int16Field, int16Field_);
      DARABONBA_PTR_TO_JSON(int32Field, int32Field_);
      DARABONBA_PTR_TO_JSON(int64Field, int64Field_);
      DARABONBA_PTR_TO_JSON(uint8Field, uint8Field_);
      DARABONBA_PTR_TO_JSON(uint16Field, uint16Field_);
      DARABONBA_PTR_TO_JSON(uint32Field, uint32Field_);
      DARABONBA_PTR_TO_JSON(uint64Field, uint64Field_);
      DARABONBA_PTR_TO_JSON(link, link_);
    };
    friend void from_json(const Darabonba::Json& j, MyModel& obj) { 
      DARABONBA_PTR_FROM_JSON(model, model_);
      DARABONBA_PTR_FROM_JSON(stringfield, stringfield_);
      DARABONBA_PTR_FROM_JSON(bytesfield, bytesfield_);
      DARABONBA_PTR_FROM_JSON(stringarrayfield, stringarrayfield_);
      DARABONBA_PTR_FROM_JSON(mapfield, mapfield_);
      DARABONBA_PTR_FROM_JSON(realName, name_);
      DARABONBA_PTR_FROM_JSON(submodel, submodel_);
      DARABONBA_PTR_FROM_JSON(submodelMap, submodelMap_);
      DARABONBA_PTR_FROM_JSON(mapModel, mapModel_);
      DARABONBA_PTR_FROM_JSON(subarraymodel, subarraymodel_);
      DARABONBA_PTR_FROM_JSON(subarray, subarray_);
      DARABONBA_PTR_FROM_JSON(ssubarray, ssubarray_);
      DARABONBA_PTR_FROM_JSON(ssubmarray, ssubmarray_);
      DARABONBA_PTR_FROM_JSON(sssubmarray, sssubmarray_);
      DARABONBA_PTR_FROM_JSON(ssubmmarray, ssubmmarray_);
      DARABONBA_PTR_FROM_JSON(sssubmmarray, sssubmmarray_);
      DARABONBA_PTR_FROM_JSON(maparray, maparray_);
      DARABONBA_PTR_FROM_JSON(mapsubmarray, mapsubmarray_);
      DARABONBA_PTR_FROM_JSON(moduleModelMap, moduleModelMap_);
      DARABONBA_PTR_FROM_JSON(arrModuleModelMap, arrModuleModelMap_);
      DARABONBA_PTR_FROM_JSON(arrsModuleModelMap, arrsModuleModelMap_);
      DARABONBA_PTR_FROM_JSON(subModelMap, subModelMap_);
      DARABONBA_PTR_FROM_JSON(modelMap, modelMap_);
      DARABONBA_PTR_FROM_JSON(moduleMap, moduleMap_);
      DARABONBA_PTR_FROM_JSON(object, object_);
      DARABONBA_FROM_JSON(readable, readable_);
      DARABONBA_FROM_JSON(writable, writable_);
      DARABONBA_PTR_FROM_JSON(existModel, existModel_);
      DARABONBA_PTR_FROM_JSON(request, request_);
      DARABONBA_PTR_FROM_JSON(complexList, complexList_);
      DARABONBA_PTR_FROM_JSON(numberfield, numberfield_);
      DARABONBA_PTR_FROM_JSON(integerField, integerField_);
      DARABONBA_PTR_FROM_JSON(floatField, floatField_);
      DARABONBA_PTR_FROM_JSON(doubleField, doubleField_);
      DARABONBA_PTR_FROM_JSON(longField, longField_);
      DARABONBA_PTR_FROM_JSON(ulongField, ulongField_);
      DARABONBA_PTR_FROM_JSON(int8Field, int8Field_);
      DARABONBA_PTR_FROM_JSON(int16Field, int16Field_);
      DARABONBA_PTR_FROM_JSON(int32Field, int32Field_);
      DARABONBA_PTR_FROM_JSON(int64Field, int64Field_);
      DARABONBA_PTR_FROM_JSON(uint8Field, uint8Field_);
      DARABONBA_PTR_FROM_JSON(uint16Field, uint16Field_);
      DARABONBA_PTR_FROM_JSON(uint32Field, uint32Field_);
      DARABONBA_PTR_FROM_JSON(uint64Field, uint64Field_);
      DARABONBA_PTR_FROM_JSON(link, link_);
    };
    MyModel() = default ;
    MyModel(const MyModel &) = default ;
    MyModel(MyModel &&) = default ;
    MyModel(const Darabonba::Json & obj) { from_json(obj, *this); };
    virtual ~MyModel() = default ;
    MyModel& operator=(const MyModel &) = default ;
    MyModel& operator=(MyModel &&) = default ;
    virtual void validate() const override {
        DARABONBA_VALIDATE_REQUIRED(model_);
        DARABONBA_VALIDATE_REQUIRED(stringfield_);
        DARABONBA_VALIDATE_REQUIRED(bytesfield_);
        DARABONBA_VALIDATE_REQUIRED(stringarrayfield_);
        DARABONBA_VALIDATE_REQUIRED(mapfield_);
        DARABONBA_VALIDATE_REQUIRED(name_);
        DARABONBA_VALIDATE_REQUIRED(submodel_);
        DARABONBA_VALIDATE_REQUIRED(submodelMap_);
        DARABONBA_VALIDATE_REQUIRED(mapModel_);
        DARABONBA_VALIDATE_REQUIRED(subarraymodel_);
        DARABONBA_VALIDATE_REQUIRED(subarray_);
        DARABONBA_VALIDATE_REQUIRED(ssubarray_);
        DARABONBA_VALIDATE_REQUIRED(ssubmarray_);
        DARABONBA_VALIDATE_REQUIRED(sssubmarray_);
        DARABONBA_VALIDATE_REQUIRED(ssubmmarray_);
        DARABONBA_VALIDATE_REQUIRED(sssubmmarray_);
        DARABONBA_VALIDATE_REQUIRED(maparray_);
        DARABONBA_VALIDATE_REQUIRED(mapsubmarray_);
        DARABONBA_VALIDATE_REQUIRED(moduleModelMap_);
        DARABONBA_VALIDATE_REQUIRED(arrModuleModelMap_);
        DARABONBA_VALIDATE_REQUIRED(arrsModuleModelMap_);
        DARABONBA_VALIDATE_REQUIRED(subModelMap_);
        DARABONBA_VALIDATE_REQUIRED(modelMap_);
        DARABONBA_VALIDATE_REQUIRED(moduleMap_);
        DARABONBA_VALIDATE_REQUIRED(object_);
        DARABONBA_VALIDATE_REQUIRED(readable_);
        DARABONBA_VALIDATE_REQUIRED(writable_);
        DARABONBA_VALIDATE_REQUIRED(existModel_);
        DARABONBA_VALIDATE_REQUIRED(request_);
        DARABONBA_VALIDATE_REQUIRED(complexList_);
        DARABONBA_VALIDATE_REQUIRED(numberfield_);
        DARABONBA_VALIDATE_REQUIRED(integerField_);
        DARABONBA_VALIDATE_REQUIRED(floatField_);
        DARABONBA_VALIDATE_REQUIRED(doubleField_);
        DARABONBA_VALIDATE_REQUIRED(longField_);
        DARABONBA_VALIDATE_REQUIRED(ulongField_);
        DARABONBA_VALIDATE_REQUIRED(int8Field_);
        DARABONBA_VALIDATE_REQUIRED(int16Field_);
        DARABONBA_VALIDATE_REQUIRED(int32Field_);
        DARABONBA_VALIDATE_REQUIRED(int64Field_);
        DARABONBA_VALIDATE_REQUIRED(uint8Field_);
        DARABONBA_VALIDATE_REQUIRED(uint16Field_);
        DARABONBA_VALIDATE_REQUIRED(uint32Field_);
        DARABONBA_VALIDATE_REQUIRED(uint64Field_);
    };
    virtual void fromMap(const Darabonba::Json &obj) override { from_json(obj, *this); validate(); };
    virtual Darabonba::Json toMap() const override { Darabonba::Json obj; to_json(obj, *this); return obj; };
    class Subarraymodel : public Darabonba::Model {
    public:
      friend void to_json(Darabonba::Json& j, const Subarraymodel& obj) { 
      };
      friend void from_json(const Darabonba::Json& j, Subarraymodel& obj) { 
      };
      Subarraymodel() = default ;
      Subarraymodel(const Subarraymodel &) = default ;
      Subarraymodel(Subarraymodel &&) = default ;
      Subarraymodel(const Darabonba::Json & obj) { from_json(obj, *this); };
      virtual ~Subarraymodel() = default ;
      Subarraymodel& operator=(const Subarraymodel &) = default ;
      Subarraymodel& operator=(Subarraymodel &&) = default ;
      virtual void validate() const override {
      };
      virtual void fromMap(const Darabonba::Json &obj) override { from_json(obj, *this); validate(); };
      virtual Darabonba::Json toMap() const override { Darabonba::Json obj; to_json(obj, *this); return obj; };
      virtual bool empty() const override { return ; };
    };

    class Submodel : public Darabonba::Model {
    public:
      friend void to_json(Darabonba::Json& j, const Submodel& obj) { 
        DARABONBA_PTR_TO_JSON(stringfield, stringfield_);
        DARABONBA_PTR_TO_JSON(model, model_);
      };
      friend void from_json(const Darabonba::Json& j, Submodel& obj) { 
        DARABONBA_PTR_FROM_JSON(stringfield, stringfield_);
        DARABONBA_PTR_FROM_JSON(model, model_);
      };
      Submodel() = default ;
      Submodel(const Submodel &) = default ;
      Submodel(Submodel &&) = default ;
      Submodel(const Darabonba::Json & obj) { from_json(obj, *this); };
      virtual ~Submodel() = default ;
      Submodel& operator=(const Submodel &) = default ;
      Submodel& operator=(Submodel &&) = default ;
      virtual void validate() const override {
          DARABONBA_VALIDATE_REQUIRED(stringfield_);
          DARABONBA_VALIDATE_REQUIRED(model_);
      };
      virtual void fromMap(const Darabonba::Json &obj) override { from_json(obj, *this); validate(); };
      virtual Darabonba::Json toMap() const override { Darabonba::Json obj; to_json(obj, *this); return obj; };
      class Model : public Darabonba::Model {
      public:
        friend void to_json(Darabonba::Json& j, const Model& obj) { 
          DARABONBA_PTR_TO_JSON(str, str_);
        };
        friend void from_json(const Darabonba::Json& j, Model& obj) { 
          DARABONBA_PTR_FROM_JSON(str, str_);
        };
        Model() = default ;
        Model(const Model &) = default ;
        Model(Model &&) = default ;
        Model(const Darabonba::Json & obj) { from_json(obj, *this); };
        virtual ~Model() = default ;
        Model& operator=(const Model &) = default ;
        Model& operator=(Model &&) = default ;
        virtual void validate() const override {
            DARABONBA_VALIDATE_REQUIRED(str_);
        };
        virtual void fromMap(const Darabonba::Json &obj) override { from_json(obj, *this); validate(); };
        virtual Darabonba::Json toMap() const override { Darabonba::Json obj; to_json(obj, *this); return obj; };
        virtual bool empty() const override { return this->str_ == nullptr; };
        // str Field Functions 
        bool hasStr() const { return this->str_ != nullptr;};
        void deleteStr() { this->str_ = nullptr;};
        inline string str() const { DARABONBA_PTR_GET_DEFAULT(str_, "") };
        inline Model& setStr(string str) { DARABONBA_PTR_SET_VALUE(str_, str) };


      protected:
        std::shared_ptr<string> str_ = nullptr;
      };

      virtual bool empty() const override { return this->stringfield_ == nullptr
        && this->model_ == nullptr; };
      // stringfield Field Functions 
      bool hasStringfield() const { return this->stringfield_ != nullptr;};
      void deleteStringfield() { this->stringfield_ = nullptr;};
      inline string stringfield() const { DARABONBA_PTR_GET_DEFAULT(stringfield_, "") };
      inline Submodel& setStringfield(string stringfield) { DARABONBA_PTR_SET_VALUE(stringfield_, stringfield) };


      // model Field Functions 
      bool hasModel() const { return this->model_ != nullptr;};
      void deleteModel() { this->model_ = nullptr;};
      inline const Submodel::Model & model() const { DARABONBA_PTR_GET_CONST(model_, Submodel::Model) };
      inline Submodel::Model model() { DARABONBA_PTR_GET(model_, Submodel::Model) };
      inline Submodel& setModel(const Submodel::Model & model) { DARABONBA_PTR_SET_VALUE(model_, model) };
      inline Submodel& setModel(Submodel::Model && model) { DARABONBA_PTR_SET_RVALUE(model_, model) };


    protected:
      std::shared_ptr<string> stringfield_ = nullptr;
      std::shared_ptr<Submodel::Model> model_ = nullptr;
    };

    class Model : public Darabonba::Model {
    public:
      friend void to_json(Darabonba::Json& j, const Model& obj) { 
        DARABONBA_PTR_TO_JSON(str, str_);
        DARABONBA_PTR_TO_JSON(model, model_);
      };
      friend void from_json(const Darabonba::Json& j, Model& obj) { 
        DARABONBA_PTR_FROM_JSON(str, str_);
        DARABONBA_PTR_FROM_JSON(model, model_);
      };
      Model() = default ;
      Model(const Model &) = default ;
      Model(Model &&) = default ;
      Model(const Darabonba::Json & obj) { from_json(obj, *this); };
      virtual ~Model() = default ;
      Model& operator=(const Model &) = default ;
      Model& operator=(Model &&) = default ;
      virtual void validate() const override {
          DARABONBA_VALIDATE_REQUIRED(str_);
          DARABONBA_VALIDATE_REQUIRED(model_);
      };
      virtual void fromMap(const Darabonba::Json &obj) override { from_json(obj, *this); validate(); };
      virtual Darabonba::Json toMap() const override { Darabonba::Json obj; to_json(obj, *this); return obj; };
      class ModelItem : public Darabonba::Model {
      public:
        friend void to_json(Darabonba::Json& j, const ModelItem& obj) { 
          DARABONBA_PTR_TO_JSON(str, str_);
        };
        friend void from_json(const Darabonba::Json& j, ModelItem& obj) { 
          DARABONBA_PTR_FROM_JSON(str, str_);
        };
        ModelItem() = default ;
        ModelItem(const ModelItem &) = default ;
        ModelItem(ModelItem &&) = default ;
        ModelItem(const Darabonba::Json & obj) { from_json(obj, *this); };
        virtual ~ModelItem() = default ;
        ModelItem& operator=(const ModelItem &) = default ;
        ModelItem& operator=(ModelItem &&) = default ;
        virtual void validate() const override {
            DARABONBA_VALIDATE_REQUIRED(str_);
        };
        virtual void fromMap(const Darabonba::Json &obj) override { from_json(obj, *this); validate(); };
        virtual Darabonba::Json toMap() const override { Darabonba::Json obj; to_json(obj, *this); return obj; };
        virtual bool empty() const override { return this->str_ == nullptr; };
        // str Field Functions 
        bool hasStr() const { return this->str_ != nullptr;};
        void deleteStr() { this->str_ = nullptr;};
        inline string str() const { DARABONBA_PTR_GET_DEFAULT(str_, "") };
        inline ModelItem& setStr(string str) { DARABONBA_PTR_SET_VALUE(str_, str) };


      protected:
        std::shared_ptr<string> str_ = nullptr;
      };

      virtual bool empty() const override { return this->str_ == nullptr
        && this->model_ == nullptr; };
      // str Field Functions 
      bool hasStr() const { return this->str_ != nullptr;};
      void deleteStr() { this->str_ = nullptr;};
      inline string str() const { DARABONBA_PTR_GET_DEFAULT(str_, "") };
      inline Model& setStr(string str) { DARABONBA_PTR_SET_VALUE(str_, str) };


      // model Field Functions 
      bool hasModel() const { return this->model_ != nullptr;};
      void deleteModel() { this->model_ = nullptr;};
      inline const Model::ModelItem & model() const { DARABONBA_PTR_GET_CONST(model_, Model::ModelItem) };
      inline Model::ModelItem model() { DARABONBA_PTR_GET(model_, Model::ModelItem) };
      inline Model& setModel(const Model::ModelItem & model) { DARABONBA_PTR_SET_VALUE(model_, model) };
      inline Model& setModel(Model::ModelItem && model) { DARABONBA_PTR_SET_RVALUE(model_, model) };


    protected:
      std::shared_ptr<string> str_ = nullptr;
      std::shared_ptr<Model::ModelItem> model_ = nullptr;
    };

    virtual bool empty() const override { return this->model_ == nullptr
        && this->stringfield_ == nullptr && this->bytesfield_ == nullptr && this->stringarrayfield_ == nullptr && this->mapfield_ == nullptr && this->name_ == nullptr
        && this->submodel_ == nullptr && this->submodelMap_ == nullptr && this->mapModel_ == nullptr && this->subarraymodel_ == nullptr && this->subarray_ == nullptr
        && this->ssubarray_ == nullptr && this->ssubmarray_ == nullptr && this->sssubmarray_ == nullptr && this->ssubmmarray_ == nullptr && this->sssubmmarray_ == nullptr
        && this->maparray_ == nullptr && this->mapsubmarray_ == nullptr && this->moduleModelMap_ == nullptr && this->arrModuleModelMap_ == nullptr && this->arrsModuleModelMap_ == nullptr
        && this->subModelMap_ == nullptr && this->modelMap_ == nullptr && this->moduleMap_ == nullptr && this->object_ == nullptr && this->readable_ == nullptr
        && this->writable_ == nullptr && this->existModel_ == nullptr && this->request_ == nullptr && this->complexList_ == nullptr && this->numberfield_ == nullptr
        && this->integerField_ == nullptr && this->floatField_ == nullptr && this->doubleField_ == nullptr && this->longField_ == nullptr && this->ulongField_ == nullptr
        && this->int8Field_ == nullptr && this->int16Field_ == nullptr && this->int32Field_ == nullptr && this->int64Field_ == nullptr && this->uint8Field_ == nullptr
        && this->uint16Field_ == nullptr && this->uint32Field_ == nullptr && this->uint64Field_ == nullptr && this->link_ == nullptr; };
    // model Field Functions 
    bool hasModel() const { return this->model_ != nullptr;};
    void deleteModel() { this->model_ = nullptr;};
    inline const MyModel::Model & model() const { DARABONBA_PTR_GET_CONST(model_, MyModel::Model) };
    inline MyModel::Model model() { DARABONBA_PTR_GET(model_, MyModel::Model) };
    inline MyModel& setModel(const MyModel::Model & model) { DARABONBA_PTR_SET_VALUE(model_, model) };
    inline MyModel& setModel(MyModel::Model && model) { DARABONBA_PTR_SET_RVALUE(model_, model) };


    // stringfield Field Functions 
    bool hasStringfield() const { return this->stringfield_ != nullptr;};
    void deleteStringfield() { this->stringfield_ = nullptr;};
    inline string stringfield() const { DARABONBA_PTR_GET_DEFAULT(stringfield_, "") };
    inline MyModel& setStringfield(string stringfield) { DARABONBA_PTR_SET_VALUE(stringfield_, stringfield) };


    // bytesfield Field Functions 
    bool hasBytesfield() const { return this->bytesfield_ != nullptr;};
    void deleteBytesfield() { this->bytesfield_ = nullptr;};
    inline Darabonba::Bytes bytesfield() const { DARABONBA_GET(bytesfield_) };
    inline MyModel& setBytesfield(Darabonba::Bytes bytesfield) { DARABONBA_SET_VALUE(bytesfield_, bytesfield) };


    // stringarrayfield Field Functions 
    bool hasStringarrayfield() const { return this->stringarrayfield_ != nullptr;};
    void deleteStringarrayfield() { this->stringarrayfield_ = nullptr;};
    inline const vector<string> & stringarrayfield() const { DARABONBA_PTR_GET_CONST(stringarrayfield_, vector<string>) };
    inline vector<string> stringarrayfield() { DARABONBA_PTR_GET(stringarrayfield_, vector<string>) };
    inline MyModel& setStringarrayfield(const vector<string> & stringarrayfield) { DARABONBA_PTR_SET_VALUE(stringarrayfield_, stringarrayfield) };
    inline MyModel& setStringarrayfield(vector<string> && stringarrayfield) { DARABONBA_PTR_SET_RVALUE(stringarrayfield_, stringarrayfield) };


    // mapfield Field Functions 
    bool hasMapfield() const { return this->mapfield_ != nullptr;};
    void deleteMapfield() { this->mapfield_ = nullptr;};
    inline const map<string, string> & mapfield() const { DARABONBA_PTR_GET_CONST(mapfield_, map<string, string>) };
    inline map<string, string> mapfield() { DARABONBA_PTR_GET(mapfield_, map<string, string>) };
    inline MyModel& setMapfield(const map<string, string> & mapfield) { DARABONBA_PTR_SET_VALUE(mapfield_, mapfield) };
    inline MyModel& setMapfield(map<string, string> && mapfield) { DARABONBA_PTR_SET_RVALUE(mapfield_, mapfield) };


    // name Field Functions 
    bool hasName() const { return this->name_ != nullptr;};
    void deleteName() { this->name_ = nullptr;};
    inline string name() const { DARABONBA_PTR_GET_DEFAULT(name_, "") };
    inline MyModel& setName(string name) { DARABONBA_PTR_SET_VALUE(name_, name) };


    // submodel Field Functions 
    bool hasSubmodel() const { return this->submodel_ != nullptr;};
    void deleteSubmodel() { this->submodel_ = nullptr;};
    inline const MyModel::Submodel & submodel() const { DARABONBA_PTR_GET_CONST(submodel_, MyModel::Submodel) };
    inline MyModel::Submodel submodel() { DARABONBA_PTR_GET(submodel_, MyModel::Submodel) };
    inline MyModel& setSubmodel(const MyModel::Submodel & submodel) { DARABONBA_PTR_SET_VALUE(submodel_, submodel) };
    inline MyModel& setSubmodel(MyModel::Submodel && submodel) { DARABONBA_PTR_SET_RVALUE(submodel_, submodel) };


    // submodelMap Field Functions 
    bool hasSubmodelMap() const { return this->submodelMap_ != nullptr;};
    void deleteSubmodelMap() { this->submodelMap_ = nullptr;};
    inline const map<string, MyModelSubmodel> & submodelMap() const { DARABONBA_PTR_GET_CONST(submodelMap_, map<string, MyModelSubmodel>) };
    inline map<string, MyModelSubmodel> submodelMap() { DARABONBA_PTR_GET(submodelMap_, map<string, MyModelSubmodel>) };
    inline MyModel& setSubmodelMap(const map<string, MyModelSubmodel> & submodelMap) { DARABONBA_PTR_SET_VALUE(submodelMap_, submodelMap) };
    inline MyModel& setSubmodelMap(map<string, MyModelSubmodel> && submodelMap) { DARABONBA_PTR_SET_RVALUE(submodelMap_, submodelMap) };


    // mapModel Field Functions 
    bool hasMapModel() const { return this->mapModel_ != nullptr;};
    void deleteMapModel() { this->mapModel_ = nullptr;};
    inline const map<string, M> & mapModel() const { DARABONBA_PTR_GET_CONST(mapModel_, map<string, M>) };
    inline map<string, M> mapModel() { DARABONBA_PTR_GET(mapModel_, map<string, M>) };
    inline MyModel& setMapModel(const map<string, M> & mapModel) { DARABONBA_PTR_SET_VALUE(mapModel_, mapModel) };
    inline MyModel& setMapModel(map<string, M> && mapModel) { DARABONBA_PTR_SET_RVALUE(mapModel_, mapModel) };


    // subarraymodel Field Functions 
    bool hasSubarraymodel() const { return this->subarraymodel_ != nullptr;};
    void deleteSubarraymodel() { this->subarraymodel_ = nullptr;};
    inline const vector<MyModel::Subarraymodel> & subarraymodel() const { DARABONBA_PTR_GET_CONST(subarraymodel_, vector<MyModel::Subarraymodel>) };
    inline vector<MyModel::Subarraymodel> subarraymodel() { DARABONBA_PTR_GET(subarraymodel_, vector<MyModel::Subarraymodel>) };
    inline MyModel& setSubarraymodel(const vector<MyModel::Subarraymodel> & subarraymodel) { DARABONBA_PTR_SET_VALUE(subarraymodel_, subarraymodel) };
    inline MyModel& setSubarraymodel(vector<MyModel::Subarraymodel> && subarraymodel) { DARABONBA_PTR_SET_RVALUE(subarraymodel_, subarraymodel) };


    // subarray Field Functions 
    bool hasSubarray() const { return this->subarray_ != nullptr;};
    void deleteSubarray() { this->subarray_ = nullptr;};
    inline const vector<M> & subarray() const { DARABONBA_PTR_GET_CONST(subarray_, vector<M>) };
    inline vector<M> subarray() { DARABONBA_PTR_GET(subarray_, vector<M>) };
    inline MyModel& setSubarray(const vector<M> & subarray) { DARABONBA_PTR_SET_VALUE(subarray_, subarray) };
    inline MyModel& setSubarray(vector<M> && subarray) { DARABONBA_PTR_SET_RVALUE(subarray_, subarray) };


    // ssubarray Field Functions 
    bool hasSsubarray() const { return this->ssubarray_ != nullptr;};
    void deleteSsubarray() { this->ssubarray_ = nullptr;};
    inline const vector<vector<M>> & ssubarray() const { DARABONBA_PTR_GET_CONST(ssubarray_, vector<vector<M>>) };
    inline vector<vector<M>> ssubarray() { DARABONBA_PTR_GET(ssubarray_, vector<vector<M>>) };
    inline MyModel& setSsubarray(const vector<vector<M>> & ssubarray) { DARABONBA_PTR_SET_VALUE(ssubarray_, ssubarray) };
    inline MyModel& setSsubarray(vector<vector<M>> && ssubarray) { DARABONBA_PTR_SET_RVALUE(ssubarray_, ssubarray) };


    // ssubmarray Field Functions 
    bool hasSsubmarray() const { return this->ssubmarray_ != nullptr;};
    void deleteSsubmarray() { this->ssubmarray_ = nullptr;};
    inline const vector<vector<shared_ptr<TestSource::Source>>> & ssubmarray() const { DARABONBA_PTR_GET_CONST(ssubmarray_, vector<vector<shared_ptr<TestSource::Source>>>) };
    inline vector<vector<shared_ptr<TestSource::Source>>> ssubmarray() { DARABONBA_PTR_GET(ssubmarray_, vector<vector<shared_ptr<TestSource::Source>>>) };
    inline MyModel& setSsubmarray(const vector<vector<shared_ptr<TestSource::Source>>> & ssubmarray) { DARABONBA_PTR_SET_VALUE(ssubmarray_, ssubmarray) };
    inline MyModel& setSsubmarray(vector<vector<shared_ptr<TestSource::Source>>> && ssubmarray) { DARABONBA_PTR_SET_RVALUE(ssubmarray_, ssubmarray) };


    // sssubmarray Field Functions 
    bool hasSssubmarray() const { return this->sssubmarray_ != nullptr;};
    void deleteSssubmarray() { this->sssubmarray_ = nullptr;};
    inline const vector<vector<shared_ptr<TestSource::Source>>> & sssubmarray() const { DARABONBA_PTR_GET_CONST(sssubmarray_, vector<vector<shared_ptr<TestSource::Source>>>) };
    inline vector<vector<shared_ptr<TestSource::Source>>> sssubmarray() { DARABONBA_PTR_GET(sssubmarray_, vector<vector<shared_ptr<TestSource::Source>>>) };
    inline MyModel& setSssubmarray(const vector<vector<shared_ptr<TestSource::Source>>> & sssubmarray) { DARABONBA_PTR_SET_VALUE(sssubmarray_, sssubmarray) };
    inline MyModel& setSssubmarray(vector<vector<shared_ptr<TestSource::Source>>> && sssubmarray) { DARABONBA_PTR_SET_RVALUE(sssubmarray_, sssubmarray) };


    // ssubmmarray Field Functions 
    bool hasSsubmmarray() const { return this->ssubmmarray_ != nullptr;};
    void deleteSsubmmarray() { this->ssubmmarray_ = nullptr;};
    inline const vector<vector<TestSource::Models::Request>> & ssubmmarray() const { DARABONBA_PTR_GET_CONST(ssubmmarray_, vector<vector<TestSource::Models::Request>>) };
    inline vector<vector<TestSource::Models::Request>> ssubmmarray() { DARABONBA_PTR_GET(ssubmmarray_, vector<vector<TestSource::Models::Request>>) };
    inline MyModel& setSsubmmarray(const vector<vector<TestSource::Models::Request>> & ssubmmarray) { DARABONBA_PTR_SET_VALUE(ssubmmarray_, ssubmmarray) };
    inline MyModel& setSsubmmarray(vector<vector<TestSource::Models::Request>> && ssubmmarray) { DARABONBA_PTR_SET_RVALUE(ssubmmarray_, ssubmmarray) };


    // sssubmmarray Field Functions 
    bool hasSssubmmarray() const { return this->sssubmmarray_ != nullptr;};
    void deleteSssubmmarray() { this->sssubmmarray_ = nullptr;};
    inline const vector<vector<vector<TestSource::Models::Request>>> & sssubmmarray() const { DARABONBA_PTR_GET_CONST(sssubmmarray_, vector<vector<vector<TestSource::Models::Request>>>) };
    inline vector<vector<vector<TestSource::Models::Request>>> sssubmmarray() { DARABONBA_PTR_GET(sssubmmarray_, vector<vector<vector<TestSource::Models::Request>>>) };
    inline MyModel& setSssubmmarray(const vector<vector<vector<TestSource::Models::Request>>> & sssubmmarray) { DARABONBA_PTR_SET_VALUE(sssubmmarray_, sssubmmarray) };
    inline MyModel& setSssubmmarray(vector<vector<vector<TestSource::Models::Request>>> && sssubmmarray) { DARABONBA_PTR_SET_RVALUE(sssubmmarray_, sssubmmarray) };


    // maparray Field Functions 
    bool hasMaparray() const { return this->maparray_ != nullptr;};
    void deleteMaparray() { this->maparray_ = nullptr;};
    inline const vector<Darabonba::Json> & maparray() const { DARABONBA_PTR_GET_CONST(maparray_, vector<Darabonba::Json>) };
    inline vector<Darabonba::Json> maparray() { DARABONBA_PTR_GET(maparray_, vector<Darabonba::Json>) };
    inline MyModel& setMaparray(const vector<Darabonba::Json> & maparray) { DARABONBA_PTR_SET_VALUE(maparray_, maparray) };
    inline MyModel& setMaparray(vector<Darabonba::Json> && maparray) { DARABONBA_PTR_SET_RVALUE(maparray_, maparray) };


    // mapsubmarray Field Functions 
    bool hasMapsubmarray() const { return this->mapsubmarray_ != nullptr;};
    void deleteMapsubmarray() { this->mapsubmarray_ = nullptr;};
    inline const vector<map<string, shared_ptr<TestSource::Source>>> & mapsubmarray() const { DARABONBA_PTR_GET_CONST(mapsubmarray_, vector<map<string, shared_ptr<TestSource::Source>>>) };
    inline vector<map<string, shared_ptr<TestSource::Source>>> mapsubmarray() { DARABONBA_PTR_GET(mapsubmarray_, vector<map<string, shared_ptr<TestSource::Source>>>) };
    inline MyModel& setMapsubmarray(const vector<map<string, shared_ptr<TestSource::Source>>> & mapsubmarray) { DARABONBA_PTR_SET_VALUE(mapsubmarray_, mapsubmarray) };
    inline MyModel& setMapsubmarray(vector<map<string, shared_ptr<TestSource::Source>>> && mapsubmarray) { DARABONBA_PTR_SET_RVALUE(mapsubmarray_, mapsubmarray) };


    // moduleModelMap Field Functions 
    bool hasModuleModelMap() const { return this->moduleModelMap_ != nullptr;};
    void deleteModuleModelMap() { this->moduleModelMap_ = nullptr;};
    inline const map<string, TestSource::Models::Request> & moduleModelMap() const { DARABONBA_PTR_GET_CONST(moduleModelMap_, map<string, TestSource::Models::Request>) };
    inline map<string, TestSource::Models::Request> moduleModelMap() { DARABONBA_PTR_GET(moduleModelMap_, map<string, TestSource::Models::Request>) };
    inline MyModel& setModuleModelMap(const map<string, TestSource::Models::Request> & moduleModelMap) { DARABONBA_PTR_SET_VALUE(moduleModelMap_, moduleModelMap) };
    inline MyModel& setModuleModelMap(map<string, TestSource::Models::Request> && moduleModelMap) { DARABONBA_PTR_SET_RVALUE(moduleModelMap_, moduleModelMap) };


    // arrModuleModelMap Field Functions 
    bool hasArrModuleModelMap() const { return this->arrModuleModelMap_ != nullptr;};
    void deleteArrModuleModelMap() { this->arrModuleModelMap_ = nullptr;};
    inline const vector<map<string, TestSource::Models::Request>> & arrModuleModelMap() const { DARABONBA_PTR_GET_CONST(arrModuleModelMap_, vector<map<string, TestSource::Models::Request>>) };
    inline vector<map<string, TestSource::Models::Request>> arrModuleModelMap() { DARABONBA_PTR_GET(arrModuleModelMap_, vector<map<string, TestSource::Models::Request>>) };
    inline MyModel& setArrModuleModelMap(const vector<map<string, TestSource::Models::Request>> & arrModuleModelMap) { DARABONBA_PTR_SET_VALUE(arrModuleModelMap_, arrModuleModelMap) };
    inline MyModel& setArrModuleModelMap(vector<map<string, TestSource::Models::Request>> && arrModuleModelMap) { DARABONBA_PTR_SET_RVALUE(arrModuleModelMap_, arrModuleModelMap) };


    // arrsModuleModelMap Field Functions 
    bool hasArrsModuleModelMap() const { return this->arrsModuleModelMap_ != nullptr;};
    void deleteArrsModuleModelMap() { this->arrsModuleModelMap_ = nullptr;};
    inline const vector<vector<map<string, TestSource::Models::Request>>> & arrsModuleModelMap() const { DARABONBA_PTR_GET_CONST(arrsModuleModelMap_, vector<vector<map<string, TestSource::Models::Request>>>) };
    inline vector<vector<map<string, TestSource::Models::Request>>> arrsModuleModelMap() { DARABONBA_PTR_GET(arrsModuleModelMap_, vector<vector<map<string, TestSource::Models::Request>>>) };
    inline MyModel& setArrsModuleModelMap(const vector<vector<map<string, TestSource::Models::Request>>> & arrsModuleModelMap) { DARABONBA_PTR_SET_VALUE(arrsModuleModelMap_, arrsModuleModelMap) };
    inline MyModel& setArrsModuleModelMap(vector<vector<map<string, TestSource::Models::Request>>> && arrsModuleModelMap) { DARABONBA_PTR_SET_RVALUE(arrsModuleModelMap_, arrsModuleModelMap) };


    // subModelMap Field Functions 
    bool hasSubModelMap() const { return this->subModelMap_ != nullptr;};
    void deleteSubModelMap() { this->subModelMap_ = nullptr;};
    inline const map<string, MSubM> & subModelMap() const { DARABONBA_PTR_GET_CONST(subModelMap_, map<string, MSubM>) };
    inline map<string, MSubM> subModelMap() { DARABONBA_PTR_GET(subModelMap_, map<string, MSubM>) };
    inline MyModel& setSubModelMap(const map<string, MSubM> & subModelMap) { DARABONBA_PTR_SET_VALUE(subModelMap_, subModelMap) };
    inline MyModel& setSubModelMap(map<string, MSubM> && subModelMap) { DARABONBA_PTR_SET_RVALUE(subModelMap_, subModelMap) };


    // modelMap Field Functions 
    bool hasModelMap() const { return this->modelMap_ != nullptr;};
    void deleteModelMap() { this->modelMap_ = nullptr;};
    inline const map<string, M> & modelMap() const { DARABONBA_PTR_GET_CONST(modelMap_, map<string, M>) };
    inline map<string, M> modelMap() { DARABONBA_PTR_GET(modelMap_, map<string, M>) };
    inline MyModel& setModelMap(const map<string, M> & modelMap) { DARABONBA_PTR_SET_VALUE(modelMap_, modelMap) };
    inline MyModel& setModelMap(map<string, M> && modelMap) { DARABONBA_PTR_SET_RVALUE(modelMap_, modelMap) };


    // moduleMap Field Functions 
    bool hasModuleMap() const { return this->moduleMap_ != nullptr;};
    void deleteModuleMap() { this->moduleMap_ = nullptr;};
    inline const map<string, shared_ptr<TestSource::Source>> & moduleMap() const { DARABONBA_PTR_GET_CONST(moduleMap_, map<string, shared_ptr<TestSource::Source>>) };
    inline map<string, shared_ptr<TestSource::Source>> moduleMap() { DARABONBA_PTR_GET(moduleMap_, map<string, shared_ptr<TestSource::Source>>) };
    inline MyModel& setModuleMap(const map<string, shared_ptr<TestSource::Source>> & moduleMap) { DARABONBA_PTR_SET_VALUE(moduleMap_, moduleMap) };
    inline MyModel& setModuleMap(map<string, shared_ptr<TestSource::Source>> && moduleMap) { DARABONBA_PTR_SET_RVALUE(moduleMap_, moduleMap) };


    // object Field Functions 
    bool hasObject() const { return this->object_ != nullptr;};
    void deleteObject() { this->object_ = nullptr;};
    inline const Darabonba::Json & object() const { DARABONBA_PTR_GET_CONST(object_, Darabonba::Json) };
    inline Darabonba::Json object() { DARABONBA_PTR_GET(object_, Darabonba::Json) };
    inline MyModel& setObject(const Darabonba::Json & object) { DARABONBA_PTR_SET_VALUE(object_, object) };
    inline MyModel& setObject(Darabonba::Json && object) { DARABONBA_PTR_SET_RVALUE(object_, object) };


    // readable Field Functions 
    bool hasReadable() const { return this->readable_ != nullptr;};
    void deleteReadable() { this->readable_ = nullptr;};
    inline shared_ptr<Darabonba::IStream> readable() const { DARABONBA_GET(readable_) };
    inline MyModel& setReadable(shared_ptr<Darabonba::IStream> readable) { DARABONBA_SET_VALUE(readable_, readable) };


    // writable Field Functions 
    bool hasWritable() const { return this->writable_ != nullptr;};
    void deleteWritable() { this->writable_ = nullptr;};
    inline shared_ptr<Darabonba::OStream> writable() const { DARABONBA_GET(writable_) };
    inline MyModel& setWritable(shared_ptr<Darabonba::OStream> writable) { DARABONBA_SET_VALUE(writable_, writable) };


    // existModel Field Functions 
    bool hasExistModel() const { return this->existModel_ != nullptr;};
    void deleteExistModel() { this->existModel_ = nullptr;};
    inline const M & existModel() const { DARABONBA_PTR_GET_CONST(existModel_, M) };
    inline M existModel() { DARABONBA_PTR_GET(existModel_, M) };
    inline MyModel& setExistModel(const M & existModel) { DARABONBA_PTR_SET_VALUE(existModel_, existModel) };
    inline MyModel& setExistModel(M && existModel) { DARABONBA_PTR_SET_RVALUE(existModel_, existModel) };


    // request Field Functions 
    bool hasRequest() const { return this->request_ != nullptr;};
    void deleteRequest() { this->request_ = nullptr;};
    inline const Darabonba::Http::Request & request() const { DARABONBA_PTR_GET_CONST(request_, Darabonba::Http::Request) };
    inline Darabonba::Http::Request request() { DARABONBA_PTR_GET(request_, Darabonba::Http::Request) };
    inline MyModel& setRequest(const Darabonba::Http::Request & request) { DARABONBA_PTR_SET_VALUE(request_, request) };
    inline MyModel& setRequest(Darabonba::Http::Request && request) { DARABONBA_PTR_SET_RVALUE(request_, request) };


    // complexList Field Functions 
    bool hasComplexList() const { return this->complexList_ != nullptr;};
    void deleteComplexList() { this->complexList_ = nullptr;};
    inline const vector<vector<string>> & complexList() const { DARABONBA_PTR_GET_CONST(complexList_, vector<vector<string>>) };
    inline vector<vector<string>> complexList() { DARABONBA_PTR_GET(complexList_, vector<vector<string>>) };
    inline MyModel& setComplexList(const vector<vector<string>> & complexList) { DARABONBA_PTR_SET_VALUE(complexList_, complexList) };
    inline MyModel& setComplexList(vector<vector<string>> && complexList) { DARABONBA_PTR_SET_RVALUE(complexList_, complexList) };


    // numberfield Field Functions 
    bool hasNumberfield() const { return this->numberfield_ != nullptr;};
    void deleteNumberfield() { this->numberfield_ = nullptr;};
    inline int64_t numberfield() const { DARABONBA_PTR_GET_DEFAULT(numberfield_, 0) };
    inline MyModel& setNumberfield(int64_t numberfield) { DARABONBA_PTR_SET_VALUE(numberfield_, numberfield) };


    // integerField Field Functions 
    bool hasIntegerField() const { return this->integerField_ != nullptr;};
    void deleteIntegerField() { this->integerField_ = nullptr;};
    inline int32_t integerField() const { DARABONBA_PTR_GET_DEFAULT(integerField_, 0) };
    inline MyModel& setIntegerField(int32_t integerField) { DARABONBA_PTR_SET_VALUE(integerField_, integerField) };


    // floatField Field Functions 
    bool hasFloatField() const { return this->floatField_ != nullptr;};
    void deleteFloatField() { this->floatField_ = nullptr;};
    inline float floatField() const { DARABONBA_PTR_GET_DEFAULT(floatField_, 0.0) };
    inline MyModel& setFloatField(float floatField) { DARABONBA_PTR_SET_VALUE(floatField_, floatField) };


    // doubleField Field Functions 
    bool hasDoubleField() const { return this->doubleField_ != nullptr;};
    void deleteDoubleField() { this->doubleField_ = nullptr;};
    inline double doubleField() const { DARABONBA_PTR_GET_DEFAULT(doubleField_, 0.0) };
    inline MyModel& setDoubleField(double doubleField) { DARABONBA_PTR_SET_VALUE(doubleField_, doubleField) };


    // longField Field Functions 
    bool hasLongField() const { return this->longField_ != nullptr;};
    void deleteLongField() { this->longField_ = nullptr;};
    inline int64_t longField() const { DARABONBA_PTR_GET_DEFAULT(longField_, 0L) };
    inline MyModel& setLongField(int64_t longField) { DARABONBA_PTR_SET_VALUE(longField_, longField) };


    // ulongField Field Functions 
    bool hasUlongField() const { return this->ulongField_ != nullptr;};
    void deleteUlongField() { this->ulongField_ = nullptr;};
    inline const ulong & ulongField() const { DARABONBA_PTR_GET_CONST(ulongField_, ulong) };
    inline ulong ulongField() { DARABONBA_PTR_GET(ulongField_, ulong) };
    inline MyModel& setUlongField(const ulong & ulongField) { DARABONBA_PTR_SET_VALUE(ulongField_, ulongField) };
    inline MyModel& setUlongField(ulong && ulongField) { DARABONBA_PTR_SET_RVALUE(ulongField_, ulongField) };


    // int8Field Field Functions 
    bool hasInt8Field() const { return this->int8Field_ != nullptr;};
    void deleteInt8Field() { this->int8Field_ = nullptr;};
    inline int8_t int8Field() const { DARABONBA_PTR_GET_DEFAULT(int8Field_, 0) };
    inline MyModel& setInt8Field(int8_t int8Field) { DARABONBA_PTR_SET_VALUE(int8Field_, int8Field) };


    // int16Field Field Functions 
    bool hasInt16Field() const { return this->int16Field_ != nullptr;};
    void deleteInt16Field() { this->int16Field_ = nullptr;};
    inline int16 int16Field() const { DARABONBA_PTR_GET_DEFAULT(int16Field_, 0) };
    inline MyModel& setInt16Field(int16 int16Field) { DARABONBA_PTR_SET_VALUE(int16Field_, int16Field) };


    // int32Field Field Functions 
    bool hasInt32Field() const { return this->int32Field_ != nullptr;};
    void deleteInt32Field() { this->int32Field_ = nullptr;};
    inline int32_t int32Field() const { DARABONBA_PTR_GET_DEFAULT(int32Field_, 0) };
    inline MyModel& setInt32Field(int32_t int32Field) { DARABONBA_PTR_SET_VALUE(int32Field_, int32Field) };


    // int64Field Field Functions 
    bool hasInt64Field() const { return this->int64Field_ != nullptr;};
    void deleteInt64Field() { this->int64Field_ = nullptr;};
    inline int64_t int64Field() const { DARABONBA_PTR_GET_DEFAULT(int64Field_, 0L) };
    inline MyModel& setInt64Field(int64_t int64Field) { DARABONBA_PTR_SET_VALUE(int64Field_, int64Field) };


    // uint8Field Field Functions 
    bool hasUint8Field() const { return this->uint8Field_ != nullptr;};
    void deleteUint8Field() { this->uint8Field_ = nullptr;};
    inline uint8 uint8Field() const { DARABONBA_PTR_GET_DEFAULT(uint8Field_, 0) };
    inline MyModel& setUint8Field(uint8 uint8Field) { DARABONBA_PTR_SET_VALUE(uint8Field_, uint8Field) };


    // uint16Field Field Functions 
    bool hasUint16Field() const { return this->uint16Field_ != nullptr;};
    void deleteUint16Field() { this->uint16Field_ = nullptr;};
    inline uint16_t uint16Field() const { DARABONBA_PTR_GET_DEFAULT(uint16Field_, 0) };
    inline MyModel& setUint16Field(uint16_t uint16Field) { DARABONBA_PTR_SET_VALUE(uint16Field_, uint16Field) };


    // uint32Field Field Functions 
    bool hasUint32Field() const { return this->uint32Field_ != nullptr;};
    void deleteUint32Field() { this->uint32Field_ = nullptr;};
    inline uint32_t uint32Field() const { DARABONBA_PTR_GET_DEFAULT(uint32Field_, 0) };
    inline MyModel& setUint32Field(uint32_t uint32Field) { DARABONBA_PTR_SET_VALUE(uint32Field_, uint32Field) };


    // uint64Field Field Functions 
    bool hasUint64Field() const { return this->uint64Field_ != nullptr;};
    void deleteUint64Field() { this->uint64Field_ = nullptr;};
    inline uint64_t uint64Field() const { DARABONBA_PTR_GET_DEFAULT(uint64Field_, 0L) };
    inline MyModel& setUint64Field(uint64_t uint64Field) { DARABONBA_PTR_SET_VALUE(uint64Field_, uint64Field) };


    // link Field Functions 
    bool hasLink() const { return this->link_ != nullptr;};
    void deleteLink() { this->link_ = nullptr;};
    inline string link() const { DARABONBA_PTR_GET_DEFAULT(link_, "") };
    inline MyModel& setLink(string link) { DARABONBA_PTR_SET_VALUE(link_, link) };


  protected:
    std::shared_ptr<MyModel::Model> model_ = nullptr;
    std::shared_ptr<string> stringfield_ = nullptr;
    Darabonba::Bytes bytesfield_ = nullptr;
    std::shared_ptr<vector<string>> stringarrayfield_ = nullptr;
    std::shared_ptr<map<string, string>> mapfield_ = nullptr;
    std::shared_ptr<string> name_ = nullptr;
    std::shared_ptr<MyModel::Submodel> submodel_ = nullptr;
    std::shared_ptr<map<string, MyModelSubmodel>> submodelMap_ = nullptr;
    std::shared_ptr<map<string, M>> mapModel_ = nullptr;
    std::shared_ptr<vector<MyModel::Subarraymodel>> subarraymodel_ = nullptr;
    std::shared_ptr<vector<M>> subarray_ = nullptr;
    std::shared_ptr<vector<vector<M>>> ssubarray_ = nullptr;
    std::shared_ptr<vector<vector<shared_ptr<TestSource::Source>>>> ssubmarray_ = nullptr;
    std::shared_ptr<vector<vector<shared_ptr<TestSource::Source>>>> sssubmarray_ = nullptr;
    std::shared_ptr<vector<vector<TestSource::Models::Request>>> ssubmmarray_ = nullptr;
    std::shared_ptr<vector<vector<vector<TestSource::Models::Request>>>> sssubmmarray_ = nullptr;
    std::shared_ptr<vector<Darabonba::Json>> maparray_ = nullptr;
    std::shared_ptr<vector<map<string, shared_ptr<TestSource::Source>>>> mapsubmarray_ = nullptr;
    std::shared_ptr<map<string, TestSource::Models::Request>> moduleModelMap_ = nullptr;
    std::shared_ptr<vector<map<string, TestSource::Models::Request>>> arrModuleModelMap_ = nullptr;
    std::shared_ptr<vector<vector<map<string, TestSource::Models::Request>>>> arrsModuleModelMap_ = nullptr;
    std::shared_ptr<map<string, MSubM>> subModelMap_ = nullptr;
    std::shared_ptr<map<string, M>> modelMap_ = nullptr;
    std::shared_ptr<map<string, shared_ptr<TestSource::Source>>> moduleMap_ = nullptr;
    std::shared_ptr<Darabonba::Json> object_ = nullptr;
    shared_ptr<Darabonba::IStream> readable_ = nullptr;
    shared_ptr<Darabonba::OStream> writable_ = nullptr;
    std::shared_ptr<M> existModel_ = nullptr;
    std::shared_ptr<Darabonba::Http::Request> request_ = nullptr;
    std::shared_ptr<vector<vector<string>>> complexList_ = nullptr;
    std::shared_ptr<int64_t> numberfield_ = nullptr;
    std::shared_ptr<int32_t> integerField_ = nullptr;
    std::shared_ptr<float> floatField_ = nullptr;
    std::shared_ptr<double> doubleField_ = nullptr;
    std::shared_ptr<int64_t> longField_ = nullptr;
    std::shared_ptr<ulong> ulongField_ = nullptr;
    std::shared_ptr<int8_t> int8Field_ = nullptr;
    std::shared_ptr<int16> int16Field_ = nullptr;
    std::shared_ptr<int32_t> int32Field_ = nullptr;
    std::shared_ptr<int64_t> int64Field_ = nullptr;
    std::shared_ptr<uint8> uint8Field_ = nullptr;
    std::shared_ptr<uint16_t> uint16Field_ = nullptr;
    std::shared_ptr<uint32_t> uint32Field_ = nullptr;
    std::shared_ptr<uint64_t> uint64Field_ = nullptr;
    std::shared_ptr<string> link_ = nullptr;
  };

  } // namespace Models
} // namespace Darabonba
} // namespace Test
#endif
