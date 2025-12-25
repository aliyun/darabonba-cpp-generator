// This file is auto-generated, don't edit it. Thanks.
#ifndef DARABONBA_MODELS_OUTERMODEL_HPP_
#define DARABONBA_MODELS_OUTERMODEL_HPP_
#include <darabonba/Core.hpp>
#include <vector>
using namespace std;
using json = nlohmann::json;
namespace Darabonba
{
namespace Nested
{
namespace Models
{
  class OuterModel : public Darabonba::Model {
  public:
    friend void to_json(Darabonba::Json& j, const OuterModel& obj) { 
      DARABONBA_PTR_TO_JSON(data, data_);
    };
    friend void from_json(const Darabonba::Json& j, OuterModel& obj) { 
      DARABONBA_PTR_FROM_JSON(data, data_);
    };
    OuterModel() = default ;
    OuterModel(const OuterModel &) = default ;
    OuterModel(OuterModel &&) = default ;
    OuterModel(const Darabonba::Json & obj) { from_json(obj, *this); };
    virtual ~OuterModel() = default ;
    OuterModel& operator=(const OuterModel &) = default ;
    OuterModel& operator=(OuterModel &&) = default ;
    virtual void validate() const override {
    };
    virtual void fromMap(const Darabonba::Json &obj) override { from_json(obj, *this); validate(); };
    virtual Darabonba::Json toMap() const override { Darabonba::Json obj; to_json(obj, *this); return obj; };
    class Data : public Darabonba::Model {
    public:
      friend void to_json(Darabonba::Json& j, const Data& obj) { 
        DARABONBA_PTR_TO_JSON(items, items_);
      };
      friend void from_json(const Darabonba::Json& j, Data& obj) { 
        DARABONBA_PTR_FROM_JSON(items, items_);
      };
      Data() = default ;
      Data(const Data &) = default ;
      Data(Data &&) = default ;
      Data(const Darabonba::Json & obj) { from_json(obj, *this); };
      virtual ~Data() = default ;
      Data& operator=(const Data &) = default ;
      Data& operator=(Data &&) = default ;
      virtual void validate() const override {
      };
      virtual void fromMap(const Darabonba::Json &obj) override { from_json(obj, *this); validate(); };
      virtual Darabonba::Json toMap() const override { Darabonba::Json obj; to_json(obj, *this); return obj; };
      class Items : public Darabonba::Model {
      public:
        friend void to_json(Darabonba::Json& j, const Items& obj) { 
          DARABONBA_PTR_TO_JSON(name, name_);
          DARABONBA_PTR_TO_JSON(value, value_);
        };
        friend void from_json(const Darabonba::Json& j, Items& obj) { 
          DARABONBA_PTR_FROM_JSON(name, name_);
          DARABONBA_PTR_FROM_JSON(value, value_);
        };
        Items() = default ;
        Items(const Items &) = default ;
        Items(Items &&) = default ;
        Items(const Darabonba::Json & obj) { from_json(obj, *this); };
        virtual ~Items() = default ;
        Items& operator=(const Items &) = default ;
        Items& operator=(Items &&) = default ;
        virtual void validate() const override {
        };
        virtual void fromMap(const Darabonba::Json &obj) override { from_json(obj, *this); validate(); };
        virtual Darabonba::Json toMap() const override { Darabonba::Json obj; to_json(obj, *this); return obj; };
        virtual bool empty() const override { return this->name_ == nullptr
        && this->value_ == nullptr; };
        // name Field Functions 
        bool hasName() const { return this->name_ != nullptr;};
        void deleteName() { this->name_ = nullptr;};
        inline string name() const { DARABONBA_PTR_GET_DEFAULT(name_, "") };
        inline Items& setName(string name) { DARABONBA_PTR_SET_VALUE(name_, name) };


        // value Field Functions 
        bool hasValue() const { return this->value_ != nullptr;};
        void deleteValue() { this->value_ = nullptr;};
        inline int32_t value() const { DARABONBA_PTR_GET_DEFAULT(value_, 0) };
        inline Items& setValue(int32_t value) { DARABONBA_PTR_SET_VALUE(value_, value) };


      protected:
        std::shared_ptr<string> name_ = nullptr;
        std::shared_ptr<int32_t> value_ = nullptr;
      };

      virtual bool empty() const override { return this->items_ == nullptr; };
      // items Field Functions 
      bool hasItems() const { return this->items_ != nullptr;};
      void deleteItems() { this->items_ = nullptr;};
      inline const vector<Data::Items> & items() const { DARABONBA_PTR_GET_CONST(items_, vector<Data::Items>) };
      inline vector<Data::Items> items() { DARABONBA_PTR_GET(items_, vector<Data::Items>) };
      inline Data& setItems(const vector<Data::Items> & items) { DARABONBA_PTR_SET_VALUE(items_, items) };
      inline Data& setItems(vector<Data::Items> && items) { DARABONBA_PTR_SET_RVALUE(items_, items) };


    protected:
      std::shared_ptr<vector<Data::Items>> items_ = nullptr;
    };

    virtual bool empty() const override { return this->data_ == nullptr; };
    // data Field Functions 
    bool hasData() const { return this->data_ != nullptr;};
    void deleteData() { this->data_ = nullptr;};
    inline const OuterModel::Data & data() const { DARABONBA_PTR_GET_CONST(data_, OuterModel::Data) };
    inline OuterModel::Data data() { DARABONBA_PTR_GET(data_, OuterModel::Data) };
    inline OuterModel& setData(const OuterModel::Data & data) { DARABONBA_PTR_SET_VALUE(data_, data) };
    inline OuterModel& setData(OuterModel::Data && data) { DARABONBA_PTR_SET_RVALUE(data_, data) };


  protected:
    std::shared_ptr<OuterModel::Data> data_ = nullptr;
  };

  } // namespace Models
} // namespace Darabonba
} // namespace Nested
#endif
