// This file is auto-generated, don't edit it. Thanks.
#ifndef DARABONBA_MODELS_MYMODELMODEL_HPP_
#define DARABONBA_MODELS_MYMODELMODEL_HPP_
#include <darabonba/Core.hpp>
#include <darabonba/models/MyModelModelModel.hpp>
using namespace std;
using json = nlohmann::json;
namespace Darabonba
{
namespace Test
{
namespace Models
{
  class MyModelModel : public Darabonba::Model {
  public:
    friend void to_json(Darabonba::Json& j, const MyModelModel& obj) { 
      DARABONBA_PTR_TO_JSON(str, str_);
      DARABONBA_PTR_TO_JSON(model, model_);
    };
    friend void from_json(const Darabonba::Json& j, MyModelModel& obj) { 
      DARABONBA_PTR_FROM_JSON(str, str_);
      DARABONBA_PTR_FROM_JSON(model, model_);
    };
    MyModelModel() = default ;
    MyModelModel(const MyModelModel &) = default ;
    MyModelModel(MyModelModel &&) = default ;
    MyModelModel(const Darabonba::Json & obj) { from_json(obj, *this); };
    virtual ~MyModelModel() = default ;
    MyModelModel& operator=(const MyModelModel &) = default ;
    MyModelModel& operator=(MyModelModel &&) = default ;
    virtual void validate() const override {
        DARABONBA_VALIDATE_REQUIRED(str_);
        DARABONBA_VALIDATE_REQUIRED(model_);
    };
    virtual void fromMap(const Darabonba::Json &obj) override { from_json(obj, *this); validate(); };
    virtual Darabonba::Json toMap() const override { Darabonba::Json obj; to_json(obj, *this); return obj; };
    virtual bool empty() const override { return this->str_ == nullptr
        && this->model_ == nullptr; };
    // str Field Functions 
    bool hasStr() const { return this->str_ != nullptr;};
    void deleteStr() { this->str_ = nullptr;};
    inline string str() const { DARABONBA_PTR_GET_DEFAULT(str_, "") };
    inline MyModelModel& setStr(string str) { DARABONBA_PTR_SET_VALUE(str_, str) };


    // model Field Functions 
    bool hasModel() const { return this->model_ != nullptr;};
    void deleteModel() { this->model_ = nullptr;};
    inline const Models::MyModelModelModel & model() const { DARABONBA_PTR_GET_CONST(model_, Models::MyModelModelModel) };
    inline Models::MyModelModelModel model() { DARABONBA_PTR_GET(model_, Models::MyModelModelModel) };
    inline MyModelModel& setModel(const Models::MyModelModelModel & model) { DARABONBA_PTR_SET_VALUE(model_, model) };
    inline MyModelModel& setModel(Models::MyModelModelModel && model) { DARABONBA_PTR_SET_RVALUE(model_, model) };


  protected:
    std::shared_ptr<string> str_ = nullptr;
    std::shared_ptr<Models::MyModelModelModel> model_ = nullptr;
  };

  } // namespace Models
} // namespace Darabonba
} // namespace Test
#endif
