// This file is auto-generated, don't edit it. Thanks.
#ifndef DARABONBA_MODELS_COMPLEXREQUESTPART_HPP_
#define DARABONBA_MODELS_COMPLEXREQUESTPART_HPP_
#include <darabonba/Core.hpp>
using namespace std;
using json = nlohmann::json;
namespace Darabonba
{
namespace Models
{
  class ComplexRequestPart : public Darabonba::Model {
  public:
    friend void to_json(Darabonba::Json& j, const ComplexRequestPart& obj) { 
      DARABONBA_PTR_TO_JSON(PartNumber, partNumber_);
    };
    friend void from_json(const Darabonba::Json& j, ComplexRequestPart& obj) { 
      DARABONBA_PTR_FROM_JSON(PartNumber, partNumber_);
    };
    ComplexRequestPart() = default ;
    ComplexRequestPart(const ComplexRequestPart &) = default ;
    ComplexRequestPart(ComplexRequestPart &&) = default ;
    ComplexRequestPart(const Darabonba::Json & obj) { from_json(obj, *this); };
    virtual ~ComplexRequestPart() = default ;
    ComplexRequestPart& operator=(const ComplexRequestPart &) = default ;
    ComplexRequestPart& operator=(ComplexRequestPart &&) = default ;
    virtual void validate() const override {
    };
    virtual void fromMap(const Darabonba::Json &obj) override { from_json(obj, *this); validate(); };
    virtual Darabonba::Json toMap() const override { Darabonba::Json obj; to_json(obj, *this); return obj; };
    virtual bool empty() const override { return this->partNumber_ == nullptr; };
    // partNumber Field Functions 
    bool hasPartNumber() const { return this->partNumber_ != nullptr;};
    void deletePartNumber() { this->partNumber_ = nullptr;};
    inline string partNumber() const { DARABONBA_PTR_GET_DEFAULT(partNumber_, "") };
    inline ComplexRequestPart& setPartNumber(string partNumber) { DARABONBA_PTR_SET_VALUE(partNumber_, partNumber) };


  protected:
    // PartNumber
    std::shared_ptr<string> partNumber_ = nullptr;
  };

  } // namespace Models
} // namespace Darabonba
#endif
