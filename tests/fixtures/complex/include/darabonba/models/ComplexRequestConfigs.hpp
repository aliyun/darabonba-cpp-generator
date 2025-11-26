// This file is auto-generated, don't edit it. Thanks.
#ifndef DARABONBA_MODELS_COMPLEXREQUESTCONFIGS_HPP_
#define DARABONBA_MODELS_COMPLEXREQUESTCONFIGS_HPP_
#include <darabonba/Core.hpp>
#include <vector>
#include <map>
using namespace std;
using json = nlohmann::json;
namespace Darabonba
{
namespace Models
{
  class ComplexRequestConfigs : public Darabonba::Model {
  public:
    friend void to_json(Darabonba::Json& j, const ComplexRequestConfigs& obj) { 
      DARABONBA_PTR_TO_JSON(key, key_);
      DARABONBA_PTR_TO_JSON(value, value_);
      DARABONBA_PTR_TO_JSON(extra, extra_);
    };
    friend void from_json(const Darabonba::Json& j, ComplexRequestConfigs& obj) { 
      DARABONBA_PTR_FROM_JSON(key, key_);
      DARABONBA_PTR_FROM_JSON(value, value_);
      DARABONBA_PTR_FROM_JSON(extra, extra_);
    };
    ComplexRequestConfigs() = default ;
    ComplexRequestConfigs(const ComplexRequestConfigs &) = default ;
    ComplexRequestConfigs(ComplexRequestConfigs &&) = default ;
    ComplexRequestConfigs(const Darabonba::Json & obj) { from_json(obj, *this); };
    virtual ~ComplexRequestConfigs() = default ;
    ComplexRequestConfigs& operator=(const ComplexRequestConfigs &) = default ;
    ComplexRequestConfigs& operator=(ComplexRequestConfigs &&) = default ;
    virtual void validate() const override {
        DARABONBA_VALIDATE_REQUIRED(key_);
        DARABONBA_VALIDATE_REQUIRED(value_);
        DARABONBA_VALIDATE_REQUIRED(extra_);
    };
    virtual void fromMap(const Darabonba::Json &obj) override { from_json(obj, *this); validate(); };
    virtual Darabonba::Json toMap() const override { Darabonba::Json obj; to_json(obj, *this); return obj; };
    virtual bool empty() const override { return this->key_ == nullptr
        && this->value_ == nullptr && this->extra_ == nullptr; };
    // key Field Functions 
    bool hasKey() const { return this->key_ != nullptr;};
    void deleteKey() { this->key_ = nullptr;};
    inline string key() const { DARABONBA_PTR_GET_DEFAULT(key_, "") };
    inline ComplexRequestConfigs& setKey(string key) { DARABONBA_PTR_SET_VALUE(key_, key) };


    // value Field Functions 
    bool hasValue() const { return this->value_ != nullptr;};
    void deleteValue() { this->value_ = nullptr;};
    inline const vector<string> & value() const { DARABONBA_PTR_GET_CONST(value_, vector<string>) };
    inline vector<string> value() { DARABONBA_PTR_GET(value_, vector<string>) };
    inline ComplexRequestConfigs& setValue(const vector<string> & value) { DARABONBA_PTR_SET_VALUE(value_, value) };
    inline ComplexRequestConfigs& setValue(vector<string> && value) { DARABONBA_PTR_SET_RVALUE(value_, value) };


    // extra Field Functions 
    bool hasExtra() const { return this->extra_ != nullptr;};
    void deleteExtra() { this->extra_ = nullptr;};
    inline const map<string, string> & extra() const { DARABONBA_PTR_GET_CONST(extra_, map<string, string>) };
    inline map<string, string> extra() { DARABONBA_PTR_GET(extra_, map<string, string>) };
    inline ComplexRequestConfigs& setExtra(const map<string, string> & extra) { DARABONBA_PTR_SET_VALUE(extra_, extra) };
    inline ComplexRequestConfigs& setExtra(map<string, string> && extra) { DARABONBA_PTR_SET_RVALUE(extra_, extra) };


  protected:
    std::shared_ptr<string> key_ = nullptr;
    std::shared_ptr<vector<string>> value_ = nullptr;
    std::shared_ptr<map<string, string>> extra_ = nullptr;
  };

  } // namespace Models
} // namespace Darabonba
#endif
