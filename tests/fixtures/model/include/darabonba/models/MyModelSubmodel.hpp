// This file is auto-generated, don't edit it. Thanks.
#ifndef DARABONBA_MODELS_MYMODELSUBMODEL_HPP_
#define DARABONBA_MODELS_MYMODELSUBMODEL_HPP_
#include <darabonba/Core.hpp>
#include <darabonba/models/MyModelSubmodelModel.hpp>
using namespace std;
using json = nlohmann::json;
namespace Darabonba
{
namespace Test
{
namespace Models
{
  class MyModelSubmodel : public Darabonba::Model {
  public:
    friend void to_json(Darabonba::Json& j, const MyModelSubmodel& obj) { 
      DARABONBA_PTR_TO_JSON(stringfield, stringfield_);
      DARABONBA_PTR_TO_JSON(model, model_);
    };
    friend void from_json(const Darabonba::Json& j, MyModelSubmodel& obj) { 
      DARABONBA_PTR_FROM_JSON(stringfield, stringfield_);
      DARABONBA_PTR_FROM_JSON(model, model_);
    };
    MyModelSubmodel() = default ;
    MyModelSubmodel(const MyModelSubmodel &) = default ;
    MyModelSubmodel(MyModelSubmodel &&) = default ;
    MyModelSubmodel(const Darabonba::Json & obj) { from_json(obj, *this); };
    virtual ~MyModelSubmodel() = default ;
    MyModelSubmodel& operator=(const MyModelSubmodel &) = default ;
    MyModelSubmodel& operator=(MyModelSubmodel &&) = default ;
    virtual void validate() const override {
        DARABONBA_VALIDATE_REQUIRED(stringfield_);
        DARABONBA_VALIDATE_REQUIRED(model_);
    };
    virtual void fromMap(const Darabonba::Json &obj) override { from_json(obj, *this); validate(); };
    virtual Darabonba::Json toMap() const override { Darabonba::Json obj; to_json(obj, *this); return obj; };
    virtual bool empty() const override { return this->stringfield_ == nullptr
        && this->model_ == nullptr; };
    // stringfield Field Functions 
    bool hasStringfield() const { return this->stringfield_ != nullptr;};
    void deleteStringfield() { this->stringfield_ = nullptr;};
    inline string stringfield() const { DARABONBA_PTR_GET_DEFAULT(stringfield_, "") };
    inline MyModelSubmodel& setStringfield(string stringfield) { DARABONBA_PTR_SET_VALUE(stringfield_, stringfield) };


    // model Field Functions 
    bool hasModel() const { return this->model_ != nullptr;};
    void deleteModel() { this->model_ = nullptr;};
    inline const Models::MyModelSubmodelModel & model() const { DARABONBA_PTR_GET_CONST(model_, Models::MyModelSubmodelModel) };
    inline Models::MyModelSubmodelModel model() { DARABONBA_PTR_GET(model_, Models::MyModelSubmodelModel) };
    inline MyModelSubmodel& setModel(const Models::MyModelSubmodelModel & model) { DARABONBA_PTR_SET_VALUE(model_, model) };
    inline MyModelSubmodel& setModel(Models::MyModelSubmodelModel && model) { DARABONBA_PTR_SET_RVALUE(model_, model) };


  protected:
    std::shared_ptr<string> stringfield_ = nullptr;
    std::shared_ptr<Models::MyModelSubmodelModel> model_ = nullptr;
  };

  } // namespace Models
} // namespace Darabonba
} // namespace Test
#endif
