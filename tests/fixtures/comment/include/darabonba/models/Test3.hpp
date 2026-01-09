// This file is auto-generated, don't edit it. Thanks.
#ifndef DARABONBA_MODELS_TEST3_HPP_
#define DARABONBA_MODELS_TEST3_HPP_
#include <darabonba/Core.hpp>
using namespace std;
using json = nlohmann::json;
namespace Darabonba
{
namespace Models
{
  /**
    TestModel3
  */
  class Test3 : public Darabonba::Model {
  public:
    friend void to_json(Darabonba::Json& j, const Test3& obj) { 
    };
    friend void from_json(const Darabonba::Json& j, Test3& obj) { 
    };
    Test3() = default ;
    Test3(const Test3 &) = default ;
    Test3(Test3 &&) = default ;
    Test3(const Darabonba::Json & obj) { from_json(obj, *this); };
    virtual ~Test3() = default ;
    Test3& operator=(const Test3 &) = default ;
    Test3& operator=(Test3 &&) = default ;
    virtual void validate() const override {
    };
    virtual void fromMap(const Darabonba::Json &obj) override { from_json(obj, *this); validate(); };
    virtual Darabonba::Json toMap() const override { Darabonba::Json obj; to_json(obj, *this); return obj; };
    virtual bool empty() const override { return true; };
  };

  } // namespace Models
} // namespace Darabonba
#endif
