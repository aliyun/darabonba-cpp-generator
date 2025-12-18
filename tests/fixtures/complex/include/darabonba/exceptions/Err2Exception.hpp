// This file is auto-generated, don't edit it. Thanks.
#ifndef DARABONBA_EXCEPTIONS_ERR2EXCEPTION_HPP_
#define DARABONBA_EXCEPTIONS_ERR2EXCEPTION_HPP_
#include <darabonba/Core.hpp>
#include <darabonba/Exception.hpp>
using namespace std;
using json = nlohmann::json;
namespace Darabonba
{
namespace Exceptions
{
  class Err2Exception : public Darabonba::Exception {
  public:
    friend void from_json(const Darabonba::Json& j, Err2Exception& obj) { 
      DARABONBA_PTR_FROM_JSON(accessErrMessage, accessErrMessage_);
    };
    Err2Exception() ;
    Err2Exception(const Err2Exception &) = default ;
    Err2Exception(Err2Exception &&) = default ;
    Err2Exception(const Darabonba::Json & obj) : Darabonba::Exception(obj.value("msg", "").get<std::string>()) { from_json(obj, *this); };
    virtual ~Err2Exception() = default ;
    Err2Exception& operator=(const Err2Exception &) = default ;
    Err2Exception& operator=(Err2Exception &&) = default ;
    inline string accessErrMessage() const { DARABONBA_PTR_GET_DEFAULT(accessErrMessage_, "") };
  protected:
    shared_ptr<string> accessErrMessage_ {};
  };
  
  } // namespace Exceptions
} // namespace Darabonba
#endif
