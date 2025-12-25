// This file is auto-generated, don't edit it. Thanks.
#ifndef DARABONBA_EXCEPTIONS_MAINFILEEXCEPTION_HPP_
#define DARABONBA_EXCEPTIONS_MAINFILEEXCEPTION_HPP_
#include <darabonba/Core.hpp>
#include <darabonba/Exception.hpp>
#include <map>
#include <darabonba/models/Model.hpp>
#include <darabonba/models/MainFileModel.hpp>
using namespace std;
using json = nlohmann::json;
namespace Darabonba
{
namespace Test
{
namespace Exceptions
{
  class MainFileException : public Darabonba::Exception {
  public:
    friend void from_json(const Darabonba::Json& j, MainFileException& obj) { 
      DARABONBA_PTR_FROM_JSON(size, size_);
      DARABONBA_PTR_FROM_JSON(data, data_);
      DARABONBA_PTR_FROM_JSON(model, model_);
    };
    MainFileException() ;
    MainFileException(const MainFileException &) = default ;
    MainFileException(MainFileException &&) = default ;
    MainFileException(const Darabonba::Json & obj) : Darabonba::Exception(obj.value("msg", "").get<std::string>()) { from_json(obj, *this); };
    virtual ~MainFileException() = default ;
    MainFileException& operator=(const MainFileException &) = default ;
    MainFileException& operator=(MainFileException &&) = default ;
    inline int64_t size() const { DARABONBA_PTR_GET_DEFAULT(size_, 0) };
    inline const map<string, Darabonba::Test::Models::Model> & data() const { DARABONBA_PTR_GET_CONST(data_, map<string, Darabonba::Test::Models::Model>) };
    inline map<string, Darabonba::Test::Models::Model> data() { DARABONBA_PTR_GET(data_, map<string, Darabonba::Test::Models::Model>) };
    inline const Darabonba::Test::Models::MainFileModel & model() const { DARABONBA_PTR_GET_CONST(model_, Darabonba::Test::Models::MainFileModel) };
    inline Darabonba::Test::Models::MainFileModel model() { DARABONBA_PTR_GET(model_, Darabonba::Test::Models::MainFileModel) };
  protected:
    shared_ptr<int64_t> size_ {};
    shared_ptr<map<string, Darabonba::Test::Models::Model>> data_ {};
    shared_ptr<Darabonba::Test::Models::MainFileModel> model_ {};
  };
  
  } // namespace Exceptions
} // namespace Darabonba
} // namespace Test
#endif
