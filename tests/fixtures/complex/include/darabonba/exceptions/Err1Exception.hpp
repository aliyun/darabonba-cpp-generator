// This file is auto-generated, don't edit it. Thanks.
#ifndef DARABONBA_EXCEPTIONS_ERR1EXCEPTION_HPP_
#define DARABONBA_EXCEPTIONS_ERR1EXCEPTION_HPP_
#include <darabonba/Core.hpp>
#include <darabonba/Exception.hpp>
#include <map>
using namespace std;
using json = nlohmann::json;
namespace Darabonba
{
namespace Exceptions
{
  class Err1Exception : public Darabonba::Exception {
  public:
    friend void from_json(const Darabonba::Json& j, Err1Exception& obj) { 
      DARABONBA_PTR_FROM_JSON(data, data_);
    };
    Err1Exception() ;
    Err1Exception(const Err1Exception &) = default ;
    Err1Exception(Err1Exception &&) = default ;
    Err1Exception(const Darabonba::Json & obj) : Darabonba::Exception(obj.value("msg", "").get<std::string>()) { from_json(obj, *this); };
    virtual ~Err1Exception() = default ;
    Err1Exception& operator=(const Err1Exception &) = default ;
    Err1Exception& operator=(Err1Exception &&) = default ;
    inline const map<string, string> & data() const { DARABONBA_PTR_GET_CONST(data_, map<string, string>) };
    inline map<string, string> data() { DARABONBA_PTR_GET(data_, map<string, string>) };
  protected:
    shared_ptr<map<string, string>> data_ {};
  };
  
  } // namespace Exceptions
} // namespace Darabonba
#endif
