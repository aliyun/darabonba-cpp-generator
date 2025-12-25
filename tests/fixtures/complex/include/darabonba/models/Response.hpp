// This file is auto-generated, don't edit it. Thanks.
#ifndef DARABONBA_MODELS_RESPONSE_HPP_
#define DARABONBA_MODELS_RESPONSE_HPP_
#include <darabonba/Core.hpp>
#include <darabonba/models/ComplexRequestPart.hpp>
using namespace std;
using json = nlohmann::json;
namespace Darabonba
{
namespace Models
{
  class Response : public Darabonba::Model {
  public:
    friend void to_json(Darabonba::Json& j, const Response& obj) { 
      DARABONBA_PTR_TO_JSON(instance, instance_);
    };
    friend void from_json(const Darabonba::Json& j, Response& obj) { 
      DARABONBA_PTR_FROM_JSON(instance, instance_);
    };
    Response() = default ;
    Response(const Response &) = default ;
    Response(Response &&) = default ;
    Response(const Darabonba::Json & obj) { from_json(obj, *this); };
    virtual ~Response() = default ;
    Response& operator=(const Response &) = default ;
    Response& operator=(Response &&) = default ;
    virtual void validate() const override {
        DARABONBA_VALIDATE_REQUIRED(instance_);
    };
    virtual void fromMap(const Darabonba::Json &obj) override { from_json(obj, *this); validate(); };
    virtual Darabonba::Json toMap() const override { Darabonba::Json obj; to_json(obj, *this); return obj; };
    virtual bool empty() const override { return this->instance_ == nullptr; };
    // instance Field Functions 
    bool hasInstance() const { return this->instance_ != nullptr;};
    void deleteInstance() { this->instance_ = nullptr;};
    inline const ComplexRequestPart & getInstance() const { DARABONBA_PTR_GET_CONST(instance_, ComplexRequestPart) };
    inline ComplexRequestPart getInstance() { DARABONBA_PTR_GET(instance_, ComplexRequestPart) };
    inline Response& setInstance(const ComplexRequestPart & instance) { DARABONBA_PTR_SET_VALUE(instance_, instance) };
    inline Response& setInstance(ComplexRequestPart && instance) { DARABONBA_PTR_SET_RVALUE(instance_, instance) };


  protected:
    shared_ptr<ComplexRequestPart> instance_ {};
  };

  } // namespace Models
} // namespace Darabonba
#endif
