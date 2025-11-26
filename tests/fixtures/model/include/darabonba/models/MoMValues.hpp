// This file is auto-generated, don't edit it. Thanks.
#ifndef DARABONBA_MODELS_MOMVALUES_HPP_
#define DARABONBA_MODELS_MOMVALUES_HPP_
#include <darabonba/Core.hpp>
using namespace std;
using json = nlohmann::json;
namespace Darabonba
{
namespace Test
{
namespace Models
{
  class MoMValues : public Darabonba::Model {
  public:
    friend void to_json(Darabonba::Json& j, const MoMValues& obj) { 
      DARABONBA_PTR_TO_JSON(name, name_);
    };
    friend void from_json(const Darabonba::Json& j, MoMValues& obj) { 
      DARABONBA_PTR_FROM_JSON(name, name_);
    };
    MoMValues() = default ;
    MoMValues(const MoMValues &) = default ;
    MoMValues(MoMValues &&) = default ;
    MoMValues(const Darabonba::Json & obj) { from_json(obj, *this); };
    virtual ~MoMValues() = default ;
    MoMValues& operator=(const MoMValues &) = default ;
    MoMValues& operator=(MoMValues &&) = default ;
    virtual void validate() const override {
        DARABONBA_VALIDATE_REQUIRED(name_);
    };
    virtual void fromMap(const Darabonba::Json &obj) override { from_json(obj, *this); validate(); };
    virtual Darabonba::Json toMap() const override { Darabonba::Json obj; to_json(obj, *this); return obj; };
    virtual bool empty() const override { return this->name_ == nullptr; };
    // name Field Functions 
    bool hasName() const { return this->name_ != nullptr;};
    void deleteName() { this->name_ = nullptr;};
    inline string name() const { DARABONBA_PTR_GET_DEFAULT(name_, "") };
    inline MoMValues& setName(string name) { DARABONBA_PTR_SET_VALUE(name_, name) };


  protected:
    std::shared_ptr<string> name_ = nullptr;
  };

  } // namespace Models
} // namespace Darabonba
} // namespace Test
#endif
