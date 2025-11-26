// This file is auto-generated, don't edit it. Thanks.
#ifndef DARABONBA_MODEL_USER_EXCEPTIONS_ERR2EXCEPTION_HPP_
#define DARABONBA_MODEL_USER_EXCEPTIONS_ERR2EXCEPTION_HPP_
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
  class Err2Exception : public ErrException {
  public:
    friend void from_json(const Darabonba::Json& j, Err2Exception& obj) { 
      DARABONBA_PTR_FROM_JSON(msg2, msg2_);
    };
    Err2Exception() ;
    Err2Exception(const Err2Exception &) = default ;
    Err2Exception(Err2Exception &&) = default ;
    Err2Exception(const Darabonba::Json & obj) : ErrException(obj) { from_json(obj, *this); };
    virtual ~Err2Exception() = default ;
    Err2Exception& operator=(const Err2Exception &) = default ;
    Err2Exception& operator=(Err2Exception &&) = default ;
    inline string msg2() const { DARABONBA_PTR_GET_DEFAULT(msg2_, "") };
  protected:
    std::shared_ptr<string> msg2_ = nullptr;
  };
  
  } // namespace Exceptions
} // namespace Darabonba
} // namespace Model
} // namespace User
#endif
