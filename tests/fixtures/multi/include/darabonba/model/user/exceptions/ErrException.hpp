// This file is auto-generated, don't edit it. Thanks.
#ifndef DARABONBA_MODEL_USER_EXCEPTIONS_ERREXCEPTION_HPP_
#define DARABONBA_MODEL_USER_EXCEPTIONS_ERREXCEPTION_HPP_
#include <darabonba/Core.hpp>
#include <darabonba/Exception.hpp>
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
  class ErrException : public Darabonba::Exception {
  public:
    friend void from_json(const Darabonba::Json& j, ErrException& obj) { 
      DARABONBA_PTR_FROM_JSON(msg, msg_);
    };
    ErrException() ;
    ErrException(const ErrException &) = default ;
    ErrException(ErrException &&) = default ;
    ErrException(const Darabonba::Json & obj) : Darabonba::Exception(obj.value("msg", "").get<std::string>()) { from_json(obj, *this); };
    virtual ~ErrException() = default ;
    ErrException& operator=(const ErrException &) = default ;
    ErrException& operator=(ErrException &&) = default ;
    inline string msg() const { DARABONBA_PTR_GET_DEFAULT(msg_, "") };
  protected:
    std::shared_ptr<string> msg_ = nullptr;
  };
  
  } // namespace Exceptions
} // namespace Darabonba
} // namespace Model
} // namespace User
#endif
