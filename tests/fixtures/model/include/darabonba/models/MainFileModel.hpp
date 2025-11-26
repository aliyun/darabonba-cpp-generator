// This file is auto-generated, don't edit it. Thanks.
#ifndef DARABONBA_MODELS_MAINFILEMODEL_HPP_
#define DARABONBA_MODELS_MAINFILEMODEL_HPP_
#include <darabonba/Core.hpp>
#include <darabonba/models/MainFileModelModel.hpp>
using namespace std;
using json = nlohmann::json;
namespace Darabonba
{
namespace Test
{
namespace Models
{
  class MainFileModel : public Darabonba::Model {
  public:
    friend void to_json(Darabonba::Json& j, const MainFileModel& obj) { 
      DARABONBA_PTR_TO_JSON(str, str_);
      DARABONBA_PTR_TO_JSON(model, model_);
    };
    friend void from_json(const Darabonba::Json& j, MainFileModel& obj) { 
      DARABONBA_PTR_FROM_JSON(str, str_);
      DARABONBA_PTR_FROM_JSON(model, model_);
    };
    MainFileModel() = default ;
    MainFileModel(const MainFileModel &) = default ;
    MainFileModel(MainFileModel &&) = default ;
    MainFileModel(const Darabonba::Json & obj) { from_json(obj, *this); };
    virtual ~MainFileModel() = default ;
    MainFileModel& operator=(const MainFileModel &) = default ;
    MainFileModel& operator=(MainFileModel &&) = default ;
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
    inline MainFileModel& setStr(string str) { DARABONBA_PTR_SET_VALUE(str_, str) };


    // model Field Functions 
    bool hasModel() const { return this->model_ != nullptr;};
    void deleteModel() { this->model_ = nullptr;};
    inline const Models::MainFileModelModel & model() const { DARABONBA_PTR_GET_CONST(model_, Models::MainFileModelModel) };
    inline Models::MainFileModelModel model() { DARABONBA_PTR_GET(model_, Models::MainFileModelModel) };
    inline MainFileModel& setModel(const Models::MainFileModelModel & model) { DARABONBA_PTR_SET_VALUE(model_, model) };
    inline MainFileModel& setModel(Models::MainFileModelModel && model) { DARABONBA_PTR_SET_RVALUE(model_, model) };


  protected:
    std::shared_ptr<string> str_ = nullptr;
    std::shared_ptr<Models::MainFileModelModel> model_ = nullptr;
  };

  } // namespace Models
} // namespace Darabonba
} // namespace Test
#endif
