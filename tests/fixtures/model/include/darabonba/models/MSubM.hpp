// This file is auto-generated, don't edit it. Thanks.
#ifndef DARABONBA_MODELS_MSUBM_HPP_
#define DARABONBA_MODELS_MSUBM_HPP_
#include <darabonba/Core.hpp>
using namespace std;
using json = nlohmann::json;
namespace Darabonba
{
namespace Test
{
namespace Models
{
  class MSubM : public Darabonba::Model {
  public:
    friend void to_json(Darabonba::Json& j, const MSubM& obj) { 
    };
    friend void from_json(const Darabonba::Json& j, MSubM& obj) { 
    };
    MSubM() = default ;
    MSubM(const MSubM &) = default ;
    MSubM(MSubM &&) = default ;
    MSubM(const Darabonba::Json & obj) { from_json(obj, *this); };
    virtual ~MSubM() = default ;
    MSubM& operator=(const MSubM &) = default ;
    MSubM& operator=(MSubM &&) = default ;
    virtual void validate() const override {
    };
    virtual void fromMap(const Darabonba::Json &obj) override { from_json(obj, *this); validate(); };
    virtual Darabonba::Json toMap() const override { Darabonba::Json obj; to_json(obj, *this); return obj; };
    virtual bool empty() const override { return ; };
  };

  } // namespace Models
} // namespace Darabonba
} // namespace Test
#endif
