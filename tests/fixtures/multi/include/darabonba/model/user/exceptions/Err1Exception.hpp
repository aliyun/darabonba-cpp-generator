// This file is auto-generated, don't edit it. Thanks.
#ifndef DARABONBA_MODEL_USER_EXCEPTIONS_ERR1EXCEPTION_HPP_
#define DARABONBA_MODEL_USER_EXCEPTIONS_ERR1EXCEPTION_HPP_
#include <darabonba/Core.hpp>
using namespace std;
using json = nlohmann::json;
namespace Darabonba
{
namespace Model
{
namespace User
{
namespace Exceptions
{
  class Err1Exception : public Darabonba::Model::User::Models::BaseInfo {
  public:
    friend void from_json(const Darabonba::Json& j, Err1Exception& obj) { 
      DARABONBA_PTR_FROM_JSON(msg, msg_);
    };
    Err1Exception() ;
    Err1Exception(const Err1Exception &) = default ;
    Err1Exception(Err1Exception &&) = default ;
    Err1Exception(const Darabonba::Json & obj) : Darabonba::Model::User::Models::BaseInfo(obj) { from_json(obj, *this); };
    virtual ~Err1Exception() = default ;
    Err1Exception& operator=(const Err1Exception &) = default ;
    Err1Exception& operator=(Err1Exception &&) = default ;
    inline string msg() const { DARABONBA_PTR_GET_DEFAULT(msg_, "") };
  protected:
    std::shared_ptr<string> msg_ = nullptr;
  };
  
  } // namespace Exceptions
} // namespace Darabonba
} // namespace Model
} // namespace User
#endif
