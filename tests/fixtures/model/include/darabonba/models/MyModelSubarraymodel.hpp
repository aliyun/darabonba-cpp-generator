// This file is auto-generated, don't edit it. Thanks.
#ifndef DARABONBA_MODELS_MYMODELSUBARRAYMODEL_HPP_
#define DARABONBA_MODELS_MYMODELSUBARRAYMODEL_HPP_
#include <darabonba/Core.hpp>
using namespace std;
using json = nlohmann::json;
namespace Darabonba
{
namespace Test
{
namespace Models
{
  class MyModelSubarraymodel : public Darabonba::Model {
  public:
    friend void to_json(Darabonba::Json& j, const MyModelSubarraymodel& obj) { 
    };
    friend void from_json(const Darabonba::Json& j, MyModelSubarraymodel& obj) { 
    };
    MyModelSubarraymodel() = default ;
    MyModelSubarraymodel(const MyModelSubarraymodel &) = default ;
    MyModelSubarraymodel(MyModelSubarraymodel &&) = default ;
    MyModelSubarraymodel(const Darabonba::Json & obj) { from_json(obj, *this); };
    virtual ~MyModelSubarraymodel() = default ;
    MyModelSubarraymodel& operator=(const MyModelSubarraymodel &) = default ;
    MyModelSubarraymodel& operator=(MyModelSubarraymodel &&) = default ;
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
