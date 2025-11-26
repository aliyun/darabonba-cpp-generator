// This file is auto-generated, don't edit it. Thanks.
#ifndef DARABONBA_MODELS_MYMODELSUBMODELMODEL_HPP_
#define DARABONBA_MODELS_MYMODELSUBMODELMODEL_HPP_
#include <darabonba/Core.hpp>
using namespace std;
using json = nlohmann::json;
namespace Darabonba
{
namespace Test
{
namespace Models
{
  class MyModelSubmodelModel : public Darabonba::Model {
  public:
    friend void to_json(Darabonba::Json& j, const MyModelSubmodelModel& obj) { 
      DARABONBA_PTR_TO_JSON(str, str_);
    };
    friend void from_json(const Darabonba::Json& j, MyModelSubmodelModel& obj) { 
      DARABONBA_PTR_FROM_JSON(str, str_);
    };
    MyModelSubmodelModel() = default ;
    MyModelSubmodelModel(const MyModelSubmodelModel &) = default ;
    MyModelSubmodelModel(MyModelSubmodelModel &&) = default ;
    MyModelSubmodelModel(const Darabonba::Json & obj) { from_json(obj, *this); };
    virtual ~MyModelSubmodelModel() = default ;
    MyModelSubmodelModel& operator=(const MyModelSubmodelModel &) = default ;
    MyModelSubmodelModel& operator=(MyModelSubmodelModel &&) = default ;
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
    inline MyModelSubmodelModel& setStr(string str) { DARABONBA_PTR_SET_VALUE(str_, str) };


  protected:
    std::shared_ptr<string> str_ = nullptr;
  };

  } // namespace Models
} // namespace Darabonba
} // namespace Test
#endif
