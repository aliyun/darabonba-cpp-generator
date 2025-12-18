// This file is auto-generated, don't edit it. Thanks.
#ifndef DARABONBA_MODELS_TEST_HPP_
#define DARABONBA_MODELS_TEST_HPP_
#include <darabonba/Core.hpp>
using namespace std;
using json = nlohmann::json;
namespace Darabonba
{
namespace Models
{
  /**
    TestModel
  */
  class Test : public Darabonba::Model {
  public:
    friend void to_json(Darabonba::Json& j, const Test& obj) { 
      DARABONBA_PTR_TO_JSON(test, test_);
    };
    friend void from_json(const Darabonba::Json& j, Test& obj) { 
      DARABONBA_PTR_FROM_JSON(test, test_);
    };
    Test() = default ;
    Test(const Test &) = default ;
    Test(Test &&) = default ;
    Test(const Darabonba::Json & obj) { from_json(obj, *this); };
    virtual ~Test() = default ;
    Test& operator=(const Test &) = default ;
    Test& operator=(Test &&) = default ;
    virtual void validate() const override {
        DARABONBA_VALIDATE_REQUIRED(test_);
    };
    virtual void fromMap(const Darabonba::Json &obj) override { from_json(obj, *this); validate(); };
    virtual Darabonba::Json toMap() const override { Darabonba::Json obj; to_json(obj, *this); return obj; };
    virtual bool empty() const override { return this->test_ == nullptr; };
    // test Field Functions 
    bool hasTest() const { return this->test_ != nullptr;};
    void deleteTest() { this->test_ = nullptr;};
    inline string getTest() const { DARABONBA_PTR_GET_DEFAULT(test_, "") };
    inline Test& setTest(string test) { DARABONBA_PTR_SET_VALUE(test_, test) };


  protected:
    // Alichange app id 
    shared_ptr<string> test_ {};
  };

  } // namespace Models
} // namespace Darabonba
#endif
