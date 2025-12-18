// This file is auto-generated, don't edit it. Thanks.
#ifndef DARABONBA_MODELS_M_HPP_
#define DARABONBA_MODELS_M_HPP_
#include <darabonba/Core.hpp>
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
    class SubM : public Darabonba::Model {
    public:
      friend void to_json(Darabonba::Json& j, const SubM& obj) { 
      };
      friend void from_json(const Darabonba::Json& j, SubM& obj) { 
      };
      SubM() = default ;
      SubM(const SubM &) = default ;
      SubM(SubM &&) = default ;
      SubM(const Darabonba::Json & obj) { from_json(obj, *this); };
      virtual ~SubM() = default ;
      SubM& operator=(const SubM &) = default ;
      SubM& operator=(SubM &&) = default ;
      virtual void validate() const override {
      };
      virtual void fromMap(const Darabonba::Json &obj) override { from_json(obj, *this); validate(); };
      virtual Darabonba::Json toMap() const override { Darabonba::Json obj; to_json(obj, *this); return obj; };
      virtual bool empty() const override { return ; };
    };

    virtual bool empty() const override { return this->subM_ == nullptr; };
    // subM Field Functions 
    bool hasSubM() const { return this->subM_ != nullptr;};
    void deleteSubM() { this->subM_ = nullptr;};
    inline const M::SubM & getSubM() const { DARABONBA_PTR_GET_CONST(subM_, M::SubM) };
    inline M::SubM getSubM() { DARABONBA_PTR_GET(subM_, M::SubM) };
    inline M& setSubM(const M::SubM & subM) { DARABONBA_PTR_SET_VALUE(subM_, subM) };
    inline M& setSubM(M::SubM && subM) { DARABONBA_PTR_SET_RVALUE(subM_, subM) };


  protected:
    shared_ptr<M::SubM> subM_ {};
  };

  } // namespace Models
} // namespace Darabonba
} // namespace Test
#endif
