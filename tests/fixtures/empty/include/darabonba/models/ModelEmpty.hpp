// This file is auto-generated, don't edit it. Thanks.
#ifndef DARABONBA_MODELS_MODELEMPTY_HPP_
#define DARABONBA_MODELS_MODELEMPTY_HPP_
#include <darabonba/Core.hpp>
using namespace std;
using json = nlohmann::json;
namespace Darabonba
{
namespace Test
{
namespace Models
{
  class ModelEmpty : public Darabonba::Model {
  public:
    friend void to_json(Darabonba::Json& j, const ModelEmpty& obj) { 
      DARABONBA_PTR_TO_JSON(name, name_);
      DARABONBA_PTR_TO_JSON(str, str_);
      DARABONBA_PTR_TO_JSON(num, num_);
      DARABONBA_PTR_TO_JSON(bool, bool_);
    };
    friend void from_json(const Darabonba::Json& j, ModelEmpty& obj) { 
      DARABONBA_PTR_FROM_JSON(name, name_);
      DARABONBA_PTR_FROM_JSON(str, str_);
      DARABONBA_PTR_FROM_JSON(num, num_);
      DARABONBA_PTR_FROM_JSON(bool, bool_);
    };
    ModelEmpty() = default ;
    ModelEmpty(const ModelEmpty &) = default ;
    ModelEmpty(ModelEmpty &&) = default ;
    ModelEmpty(const Darabonba::Json & obj) { from_json(obj, *this); };
    virtual ~ModelEmpty() = default ;
    ModelEmpty& operator=(const ModelEmpty &) = default ;
    ModelEmpty& operator=(ModelEmpty &&) = default ;
    virtual void validate() const override {
        DARABONBA_VALIDATE_REQUIRED(name_);
        DARABONBA_VALIDATE_REQUIRED(str_);
        DARABONBA_VALIDATE_REQUIRED(num_);
        DARABONBA_VALIDATE_REQUIRED(bool_);
    };
    virtual void fromMap(const Darabonba::Json &obj) override { from_json(obj, *this); validate(); };
    virtual Darabonba::Json toMap() const override { Darabonba::Json obj; to_json(obj, *this); return obj; };
    virtual bool empty() const override { return this->name_ == nullptr
        && this->str_ == nullptr && this->num_ == nullptr && this->bool_ == nullptr; };
    // name Field Functions 
    bool hasName() const { return this->name_ != nullptr;};
    void deleteName() { this->name_ = nullptr;};
    inline string getName() const { DARABONBA_PTR_GET_DEFAULT(name_, "") };
    inline ModelEmpty& setName(string name) { DARABONBA_PTR_SET_VALUE(name_, name) };


    // str Field Functions 
    bool hasStr() const { return this->str_ != nullptr;};
    void deleteStr() { this->str_ = nullptr;};
    inline string getStr() const { DARABONBA_PTR_GET_DEFAULT(str_, "") };
    inline ModelEmpty& setStr(string str) { DARABONBA_PTR_SET_VALUE(str_, str) };


    // num Field Functions 
    bool hasNum() const { return this->num_ != nullptr;};
    void deleteNum() { this->num_ = nullptr;};
    inline int64_t getNum() const { DARABONBA_PTR_GET_DEFAULT(num_, 0) };
    inline ModelEmpty& setNum(int64_t num) { DARABONBA_PTR_SET_VALUE(num_, num) };


    // bool Field Functions 
    bool hasBool() const { return this->bool_ != nullptr;};
    void deleteBool() { this->bool_ = nullptr;};
    inline bool getBool() const { DARABONBA_PTR_GET_DEFAULT(bool_, false) };
    inline ModelEmpty& setBool(bool _bool) { DARABONBA_PTR_SET_VALUE(bool_, _bool) };


  protected:
    shared_ptr<string> name_ {};
    shared_ptr<string> str_ {};
    shared_ptr<int64_t> num_ {};
    shared_ptr<bool> bool_ {};
  };

  } // namespace Models
} // namespace Darabonba
} // namespace Test
#endif
