// This file is auto-generated, don't edit it. Thanks.
#ifndef DARABONBA_MODELS_TEST2_HPP_
#define DARABONBA_MODELS_TEST2_HPP_
#include <darabonba/Core.hpp>
using namespace std;
using json = nlohmann::json;
namespace Darabonba
{
namespace Models
{
  /**
    TestModel2
  */
  class Test2 : public Darabonba::Model {
  public:
    friend void to_json(Darabonba::Json& j, const Test2& obj) { 
      DARABONBA_PTR_TO_JSON(test, test_);
      DARABONBA_PTR_TO_JSON(test2, test2_);
    };
    friend void from_json(const Darabonba::Json& j, Test2& obj) { 
      DARABONBA_PTR_FROM_JSON(test, test_);
      DARABONBA_PTR_FROM_JSON(test2, test2_);
    };
    Test2() = default ;
    Test2(const Test2 &) = default ;
    Test2(Test2 &&) = default ;
    Test2(const Darabonba::Json & obj) { from_json(obj, *this); };
    virtual ~Test2() = default ;
    Test2& operator=(const Test2 &) = default ;
    Test2& operator=(Test2 &&) = default ;
    virtual void validate() const override {
        DARABONBA_VALIDATE_REQUIRED(test_);
        DARABONBA_VALIDATE_REQUIRED(test2_);
    };
    virtual void fromMap(const Darabonba::Json &obj) override { from_json(obj, *this); validate(); };
    virtual Darabonba::Json toMap() const override { Darabonba::Json obj; to_json(obj, *this); return obj; };
    virtual bool empty() const override { return this->test_ == nullptr
        && this->test2_ == nullptr; };
    // test Field Functions 
    bool hasTest() const { return this->test_ != nullptr;};
    void deleteTest() { this->test_ = nullptr;};
    inline string getTest() const { DARABONBA_PTR_GET_DEFAULT(test_, "") };
    inline Test2& setTest(string test) { DARABONBA_PTR_SET_VALUE(test_, test) };


    // test2 Field Functions 
    bool hasTest2() const { return this->test2_ != nullptr;};
    void deleteTest2() { this->test2_ = nullptr;};
    inline string getTest2() const { DARABONBA_PTR_GET_DEFAULT(test2_, "") };
    inline Test2& setTest2(string test2) { DARABONBA_PTR_SET_VALUE(test2_, test2) };


  protected:
    // model的test front comment
    // test desc
    shared_ptr<string> test_ {};
    // model的test front comment
    // test2 desc
    shared_ptr<string> test2_ {};
  };

  } // namespace Models
} // namespace Darabonba
#endif
