// This file is auto-generated, don't edit it. Thanks.
#ifndef DARABONBA_MODELS_M_HPP_
#define DARABONBA_MODELS_M_HPP_
#include <darabonba/Core.hpp>
#include <darabonba/models/MSubM.hpp>
using namespace std;
using json = nlohmann::json;
namespace Darabonba
{
namespace Test
{
namespace Models
{
  class M : public Darabonba::Model {
  public:
    friend void to_json(Darabonba::Json& j, const M& obj) { 
      DARABONBA_PTR_TO_JSON(subM, subM_);
    };
    friend void from_json(const Darabonba::Json& j, M& obj) { 
      DARABONBA_PTR_FROM_JSON(subM, subM_);
    };
    M() = default ;
    M(const M &) = default ;
    M(M &&) = default ;
    M(const Darabonba::Json & obj) { from_json(obj, *this); };
    virtual ~M() = default ;
    M& operator=(const M &) = default ;
    M& operator=(M &&) = default ;
    virtual void validate() const override {
        DARABONBA_VALIDATE_REQUIRED(subM_);
    };
    virtual void fromMap(const Darabonba::Json &obj) override { from_json(obj, *this); validate(); };
    virtual Darabonba::Json toMap() const override { Darabonba::Json obj; to_json(obj, *this); return obj; };
    virtual bool empty() const override { return this->subM_ == nullptr; };
    // subM Field Functions 
    bool hasSubM() const { return this->subM_ != nullptr;};
    void deleteSubM() { this->subM_ = nullptr;};
    inline const MSubM & subM() const { DARABONBA_PTR_GET_CONST(subM_, MSubM) };
    inline MSubM subM() { DARABONBA_PTR_GET(subM_, MSubM) };
    inline M& setSubM(const MSubM & subM) { DARABONBA_PTR_SET_VALUE(subM_, subM) };
    inline M& setSubM(MSubM && subM) { DARABONBA_PTR_SET_RVALUE(subM_, subM) };


  protected:
    std::shared_ptr<MSubM> subM_ = nullptr;
  };

  } // namespace Models
} // namespace Darabonba
} // namespace Test
#endif
