// This file is auto-generated, don't edit it. Thanks.
#ifndef DARABONBA_MODELS_PARENTMODEL_HPP_
#define DARABONBA_MODELS_PARENTMODEL_HPP_
#include <darabonba/Core.hpp>
using namespace std;
using json = nlohmann::json;
namespace Darabonba
{
namespace Nested
{
namespace Models
{
  class ParentModel : public Darabonba::Model {
  public:
    friend void to_json(Darabonba::Json& j, const ParentModel& obj) { 
      DARABONBA_PTR_TO_JSON(name, name_);
      DARABONBA_PTR_TO_JSON(parentModel, parentModel_);
    };
    friend void from_json(const Darabonba::Json& j, ParentModel& obj) { 
      DARABONBA_PTR_FROM_JSON(name, name_);
      DARABONBA_PTR_FROM_JSON(parentModel, parentModel_);
    };
    ParentModel() = default ;
    ParentModel(const ParentModel &) = default ;
    ParentModel(ParentModel &&) = default ;
    ParentModel(const Darabonba::Json & obj) { from_json(obj, *this); };
    virtual ~ParentModel() = default ;
    ParentModel& operator=(const ParentModel &) = default ;
    ParentModel& operator=(ParentModel &&) = default ;
    virtual void validate() const override {
    };
    virtual void fromMap(const Darabonba::Json &obj) override { from_json(obj, *this); validate(); };
    virtual Darabonba::Json toMap() const override { Darabonba::Json obj; to_json(obj, *this); return obj; };
    class ParentModelItem : public Darabonba::Model {
    public:
      friend void to_json(Darabonba::Json& j, const ParentModelItem& obj) { 
        DARABONBA_PTR_TO_JSON(id, id_);
        DARABONBA_PTR_TO_JSON(value, value_);
      };
      friend void from_json(const Darabonba::Json& j, ParentModelItem& obj) { 
        DARABONBA_PTR_FROM_JSON(id, id_);
        DARABONBA_PTR_FROM_JSON(value, value_);
      };
      ParentModelItem() = default ;
      ParentModelItem(const ParentModelItem &) = default ;
      ParentModelItem(ParentModelItem &&) = default ;
      ParentModelItem(const Darabonba::Json & obj) { from_json(obj, *this); };
      virtual ~ParentModelItem() = default ;
      ParentModelItem& operator=(const ParentModelItem &) = default ;
      ParentModelItem& operator=(ParentModelItem &&) = default ;
      virtual void validate() const override {
      };
      virtual void fromMap(const Darabonba::Json &obj) override { from_json(obj, *this); validate(); };
      virtual Darabonba::Json toMap() const override { Darabonba::Json obj; to_json(obj, *this); return obj; };
      virtual bool empty() const override { return this->id_ == nullptr
        && this->value_ == nullptr; };
      // id Field Functions 
      bool hasId() const { return this->id_ != nullptr;};
      void deleteId() { this->id_ = nullptr;};
      inline string id() const { DARABONBA_PTR_GET_DEFAULT(id_, "") };
      inline ParentModelItem& setId(string id) { DARABONBA_PTR_SET_VALUE(id_, id) };


      // value Field Functions 
      bool hasValue() const { return this->value_ != nullptr;};
      void deleteValue() { this->value_ = nullptr;};
      inline int32_t value() const { DARABONBA_PTR_GET_DEFAULT(value_, 0) };
      inline ParentModelItem& setValue(int32_t value) { DARABONBA_PTR_SET_VALUE(value_, value) };


    protected:
      std::shared_ptr<string> id_ = nullptr;
      std::shared_ptr<int32_t> value_ = nullptr;
    };

    virtual bool empty() const override { return this->name_ == nullptr
        && this->parentModel_ == nullptr; };
    // name Field Functions 
    bool hasName() const { return this->name_ != nullptr;};
    void deleteName() { this->name_ = nullptr;};
    inline string name() const { DARABONBA_PTR_GET_DEFAULT(name_, "") };
    inline ParentModel& setName(string name) { DARABONBA_PTR_SET_VALUE(name_, name) };


    // parentModel Field Functions 
    bool hasParentModel() const { return this->parentModel_ != nullptr;};
    void deleteParentModel() { this->parentModel_ = nullptr;};
    inline const ParentModel::ParentModelItem & parentModel() const { DARABONBA_PTR_GET_CONST(parentModel_, ParentModel::ParentModelItem) };
    inline ParentModel::ParentModelItem parentModel() { DARABONBA_PTR_GET(parentModel_, ParentModel::ParentModelItem) };
    inline ParentModel& setParentModel(const ParentModel::ParentModelItem & parentModel) { DARABONBA_PTR_SET_VALUE(parentModel_, parentModel) };
    inline ParentModel& setParentModel(ParentModel::ParentModelItem && parentModel) { DARABONBA_PTR_SET_RVALUE(parentModel_, parentModel) };


  protected:
    std::shared_ptr<string> name_ = nullptr;
    // 嵌套类名ParentModel与父类同名
    std::shared_ptr<ParentModel::ParentModelItem> parentModel_ = nullptr;
  };

  } // namespace Models
} // namespace Darabonba
} // namespace Nested
#endif
