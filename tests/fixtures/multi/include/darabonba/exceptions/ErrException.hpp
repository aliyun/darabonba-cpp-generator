// This file is auto-generated, don't edit it. Thanks.
#ifndef DARABONBA_EXCEPTIONS_ERREXCEPTION_HPP_
#define DARABONBA_EXCEPTIONS_ERREXCEPTION_HPP_
#include <darabonba/Core.hpp>
#include <darabonba/Exception.hpp>
using namespace std;
using json = nlohmann::json;
namespace Darabonba
{
namespace Exceptions
{
  class ERRException : public Darabonba::Exception {
  public:
    friend void from_json(const Darabonba::Json& j, ERRException& obj) { 
      DARABONBA_PTR_FROM_JSON(test, test_);
    };
    ERRException() ;
    ERRException(const ERRException &) = default ;
    ERRException(ERRException &&) = default ;
    ERRException(const Darabonba::Json & obj) : Darabonba::Exception(obj.value("msg", "").get<std::string>()) { from_json(obj, *this); };
    virtual ~ERRException() = default ;
    ERRException& operator=(const ERRException &) = default ;
    ERRException& operator=(ERRException &&) = default ;
    inline int64_t test() const { DARABONBA_PTR_GET_DEFAULT(test_, 0) };
  protected:
    std::shared_ptr<int64_t> test_ = nullptr;
  };
  
  } // namespace Exceptions
namespace Exceptions
{
  class ErrException : public Darabonba::Exception {
  public:
    friend void from_json(const Darabonba::Json& j, ErrException& obj) { 
      DARABONBA_PTR_FROM_JSON(test, test_);
    };
    ErrException() ;
    ErrException(const ErrException &) = default ;
    ErrException(ErrException &&) = default ;
    ErrException(const Darabonba::Json & obj) : Darabonba::Exception(obj.value("msg", "").get<std::string>()) { from_json(obj, *this); };
    virtual ~ErrException() = default ;
    ErrException& operator=(const ErrException &) = default ;
    ErrException& operator=(ErrException &&) = default ;
    inline string test() const { DARABONBA_PTR_GET_DEFAULT(test_, "") };
  protected:
    std::shared_ptr<string> test_ = nullptr;
  };
  
  } // namespace Exceptions
} // namespace Darabonba
#endif
