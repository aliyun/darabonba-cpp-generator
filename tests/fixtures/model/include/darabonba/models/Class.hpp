// This file is auto-generated, don't edit it. Thanks.
#ifndef DARABONBA_MODELS_CLASS_HPP_
#define DARABONBA_MODELS_CLASS_HPP_
#include <darabonba/Core.hpp>
using namespace std;
using json = nlohmann::json;
namespace Darabonba
{
namespace Test
{
namespace Models
{
  class Class : public Darabonba::Model {
  public:
    friend void to_json(Darabonba::Json& j, const Class& obj) { 
    };
    friend void from_json(const Darabonba::Json& j, Class& obj) { 
    };
    Class() = default ;
    Class(const Class &) = default ;
    Class(Class &&) = default ;
    Class(const Darabonba::Json & obj) { from_json(obj, *this); };
    virtual ~Class() = default ;
    Class& operator=(const Class &) = default ;
    Class& operator=(Class &&) = default ;
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
