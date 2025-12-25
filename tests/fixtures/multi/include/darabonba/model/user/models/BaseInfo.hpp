// This file is auto-generated, don't edit it. Thanks.
#ifndef DARABONBA_MODEL_USER_MODELS_BASEINFO_HPP_
#define DARABONBA_MODEL_USER_MODELS_BASEINFO_HPP_
#include <darabonba/Core.hpp>
#include <darabonba/util.hpp>
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
  class BaseInfo : public DaraUtil::Models::RuntimeOptions {
  public:
    friend void to_json(Darabonba::Json& j, const BaseInfo& obj) { 
      DARABONBA_PTR_TO_JSON(maxAttemp, maxAttemp_);
    };
    friend void from_json(const Darabonba::Json& j, BaseInfo& obj) { 
      DARABONBA_PTR_FROM_JSON(maxAttemp, maxAttemp_);
    };
    BaseInfo() = default ;
    BaseInfo(const BaseInfo &) = default ;
    BaseInfo(BaseInfo &&) = default ;
    BaseInfo(const Darabonba::Json & obj) : DaraUtil::Models::RuntimeOptions(obj) { from_json(obj, *this); };
    virtual ~BaseInfo() = default ;
    BaseInfo& operator=(const BaseInfo &) = default ;
    BaseInfo& operator=(BaseInfo &&) = default ;
    virtual void validate() const override {
        DARABONBA_VALIDATE_REQUIRED(maxAttemp_);
    };
    virtual void fromMap(const Darabonba::Json &obj) override { from_json(obj, *this); validate(); };
    virtual Darabonba::Json toMap() const override { Darabonba::Json obj; to_json(obj, *this); return obj; };
    virtual bool empty() const override { return this->maxAttemp_ == nullptr; };
    // maxAttemp Field Functions 
    bool hasMaxAttemp() const { return this->maxAttemp_ != nullptr;};
    void deleteMaxAttemp() { this->maxAttemp_ = nullptr;};
    inline int64_t getMaxAttemp() const { DARABONBA_PTR_GET_DEFAULT(maxAttemp_, 0) };
    inline BaseInfo& setMaxAttemp(int64_t maxAttemp) { DARABONBA_PTR_SET_VALUE(maxAttemp_, maxAttemp) };


  protected:
    shared_ptr<int64_t> maxAttemp_ {};
  };

  } // namespace Models
} // namespace Darabonba
} // namespace Model
} // namespace User
#endif
