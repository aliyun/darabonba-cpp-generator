// This file is auto-generated, don't edit it. Thanks.
#ifndef DARABONBA_MODEL_USER_MODELS_INFO_HPP_
#define DARABONBA_MODEL_USER_MODELS_INFO_HPP_
#include <darabonba/Core.hpp>
using namespace std;
using json = nlohmann::json;
namespace Darabonba
{
namespace Model
{
namespace User
{
namespace Models
{
  class Info : public BaseInfo {
  public:
    friend void to_json(Darabonba::Json& j, const Info& obj) { 
      DARABONBA_PTR_TO_JSON(name, name_);
      DARABONBA_PTR_TO_JSON(age, age_);
    };
    friend void from_json(const Darabonba::Json& j, Info& obj) { 
      DARABONBA_PTR_FROM_JSON(name, name_);
      DARABONBA_PTR_FROM_JSON(age, age_);
    };
    Info() = default ;
    Info(const Info &) = default ;
    Info(Info &&) = default ;
    Info(const Darabonba::Json & obj) : BaseInfo(obj) { from_json(obj, *this); };
    virtual ~Info() = default ;
    Info& operator=(const Info &) = default ;
    Info& operator=(Info &&) = default ;
    virtual void validate() const override {
        DARABONBA_VALIDATE_REQUIRED(name_);
        DARABONBA_VALIDATE_REQUIRED(age_);
    };
    virtual void fromMap(const Darabonba::Json &obj) override { from_json(obj, *this); validate(); };
    virtual Darabonba::Json toMap() const override { Darabonba::Json obj; to_json(obj, *this); return obj; };
    virtual bool empty() const override { return this->name_ == nullptr
        && this->age_ == nullptr; };
    // name Field Functions 
    bool hasName() const { return this->name_ != nullptr;};
    void deleteName() { this->name_ = nullptr;};
    inline string getName() const { DARABONBA_PTR_GET_DEFAULT(name_, "") };
    inline Info& setName(string name) { DARABONBA_PTR_SET_VALUE(name_, name) };


    // age Field Functions 
    bool hasAge() const { return this->age_ != nullptr;};
    void deleteAge() { this->age_ = nullptr;};
    inline int32_t getAge() const { DARABONBA_PTR_GET_DEFAULT(age_, 0) };
    inline Info& setAge(int32_t age) { DARABONBA_PTR_SET_VALUE(age_, age) };


  protected:
    shared_ptr<string> name_ {};
    shared_ptr<int32_t> age_ {};
  };

  } // namespace Models
} // namespace Darabonba
} // namespace Model
} // namespace User
#endif
