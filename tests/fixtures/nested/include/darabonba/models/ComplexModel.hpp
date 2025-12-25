// This file is auto-generated, don't edit it. Thanks.
#ifndef DARABONBA_MODELS_COMPLEXMODEL_HPP_
#define DARABONBA_MODELS_COMPLEXMODEL_HPP_
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
  class ComplexModel : public Darabonba::Model {
  public:
    friend void to_json(Darabonba::Json& j, const ComplexModel& obj) { 
      DARABONBA_PTR_TO_JSON(hasRecord, hasRecord_);
      DARABONBA_PTR_TO_JSON(record, record_);
    };
    friend void from_json(const Darabonba::Json& j, ComplexModel& obj) { 
      DARABONBA_PTR_FROM_JSON(hasRecord, hasRecord_);
      DARABONBA_PTR_FROM_JSON(record, record_);
    };
    ComplexModel() = default ;
    ComplexModel(const ComplexModel &) = default ;
    ComplexModel(ComplexModel &&) = default ;
    ComplexModel(const Darabonba::Json & obj) { from_json(obj, *this); };
    virtual ~ComplexModel() = default ;
    ComplexModel& operator=(const ComplexModel &) = default ;
    ComplexModel& operator=(ComplexModel &&) = default ;
    virtual void validate() const override {
    };
    virtual void fromMap(const Darabonba::Json &obj) override { from_json(obj, *this); validate(); };
    virtual Darabonba::Json toMap() const override { Darabonba::Json obj; to_json(obj, *this); return obj; };
    class Record : public Darabonba::Model {
    public:
      friend void to_json(Darabonba::Json& j, const Record& obj) { 
        DARABONBA_PTR_TO_JSON(id, id_);
        DARABONBA_PTR_TO_JSON(record, record_);
      };
      friend void from_json(const Darabonba::Json& j, Record& obj) { 
        DARABONBA_PTR_FROM_JSON(id, id_);
        DARABONBA_PTR_FROM_JSON(record, record_);
      };
      Record() = default ;
      Record(const Record &) = default ;
      Record(Record &&) = default ;
      Record(const Darabonba::Json & obj) { from_json(obj, *this); };
      virtual ~Record() = default ;
      Record& operator=(const Record &) = default ;
      Record& operator=(Record &&) = default ;
      virtual void validate() const override {
      };
      virtual void fromMap(const Darabonba::Json &obj) override { from_json(obj, *this); validate(); };
      virtual Darabonba::Json toMap() const override { Darabonba::Json obj; to_json(obj, *this); return obj; };
      class RecordItem : public Darabonba::Model {
      public:
        friend void to_json(Darabonba::Json& j, const RecordItem& obj) { 
          DARABONBA_PTR_TO_JSON(time, time_);
          DARABONBA_PTR_TO_JSON(data, data_);
        };
        friend void from_json(const Darabonba::Json& j, RecordItem& obj) { 
          DARABONBA_PTR_FROM_JSON(time, time_);
          DARABONBA_PTR_FROM_JSON(data, data_);
        };
        RecordItem() = default ;
        RecordItem(const RecordItem &) = default ;
        RecordItem(RecordItem &&) = default ;
        RecordItem(const Darabonba::Json & obj) { from_json(obj, *this); };
        virtual ~RecordItem() = default ;
        RecordItem& operator=(const RecordItem &) = default ;
        RecordItem& operator=(RecordItem &&) = default ;
        virtual void validate() const override {
        };
        virtual void fromMap(const Darabonba::Json &obj) override { from_json(obj, *this); validate(); };
        virtual Darabonba::Json toMap() const override { Darabonba::Json obj; to_json(obj, *this); return obj; };
        virtual bool empty() const override { return this->time_ == nullptr
        && this->data_ == nullptr; };
        // time Field Functions 
        bool hasTime() const { return this->time_ != nullptr;};
        void deleteTime() { this->time_ = nullptr;};
        inline string getTime() const { DARABONBA_PTR_GET_DEFAULT(time_, "") };
        inline RecordItem& setTime(string time) { DARABONBA_PTR_SET_VALUE(time_, time) };


        // data Field Functions 
        bool hasData() const { return this->data_ != nullptr;};
        void deleteData() { this->data_ = nullptr;};
        inline string getData() const { DARABONBA_PTR_GET_DEFAULT(data_, "") };
        inline RecordItem& setData(string data) { DARABONBA_PTR_SET_VALUE(data_, data) };


      protected:
        shared_ptr<string> time_ {};
        shared_ptr<string> data_ {};
      };

      virtual bool empty() const override { return this->id_ == nullptr
        && this->record_ == nullptr; };
      // id Field Functions 
      bool hasId() const { return this->id_ != nullptr;};
      void deleteId() { this->id_ = nullptr;};
      inline string getId() const { DARABONBA_PTR_GET_DEFAULT(id_, "") };
      inline Record& setId(string id) { DARABONBA_PTR_SET_VALUE(id_, id) };


      // record Field Functions 
      bool hasRecord() const { return this->record_ != nullptr;};
      void deleteRecord() { this->record_ = nullptr;};
      inline const vector<Record::RecordItem> & getRecord() const { DARABONBA_PTR_GET_CONST(record_, vector<Record::RecordItem>) };
      inline vector<Record::RecordItem> getRecord() { DARABONBA_PTR_GET(record_, vector<Record::RecordItem>) };
      inline Record& setRecord(const vector<Record::RecordItem> & record) { DARABONBA_PTR_SET_VALUE(record_, record) };
      inline Record& setRecord(vector<Record::RecordItem> && record) { DARABONBA_PTR_SET_RVALUE(record_, record) };


    protected:
      shared_ptr<string> id_ {};
      shared_ptr<vector<Record::RecordItem>> record_ {};
    };

    virtual bool empty() const override { return this->hasRecord_ == nullptr
        && this->record_ == nullptr; };
    // hasRecord Field Functions 
    bool hasHasRecord() const { return this->hasRecord_ != nullptr;};
    void deleteHasRecord() { this->hasRecord_ = nullptr;};
    inline bool getHasRecord() const { DARABONBA_PTR_GET_DEFAULT(hasRecord_, false) };
    inline ComplexModel& setHasRecord(bool hasRecord) { DARABONBA_PTR_SET_VALUE(hasRecord_, hasRecord) };


    // record Field Functions 
    bool hasRecord() const { return this->record_ != nullptr;};
    void deleteRecord() { this->record_ = nullptr;};
    inline const ComplexModel::Record & getRecord() const { DARABONBA_PTR_GET_CONST(record_, ComplexModel::Record) };
    inline ComplexModel::Record getRecord() { DARABONBA_PTR_GET(record_, ComplexModel::Record) };
    inline ComplexModel& setRecord(const ComplexModel::Record & record) { DARABONBA_PTR_SET_VALUE(record_, record) };
    inline ComplexModel& setRecord(ComplexModel::Record && record) { DARABONBA_PTR_SET_RVALUE(record_, record) };


  protected:
    shared_ptr<bool> hasRecord_ {};
    shared_ptr<ComplexModel::Record> record_ {};
  };

  } // namespace Models
} // namespace Darabonba
} // namespace Nested
#endif
