// This file is auto-generated, don't edit it. Thanks.
#ifndef DARABONBA_API_MODELS_TESTMODELDIR2_HPP_
#define DARABONBA_API_MODELS_TESTMODELDIR2_HPP_
#include <darabonba/Core.hpp>
using namespace std;
using json = nlohmann::json;
namespace Darabonba
{
namespace Api
{
namespace Models
{
  class TestModelDir2 : public Darabonba::Model {
  public:
    friend void to_json(Darabonba::Json& j, const TestModelDir2& obj) { 
      DARABONBA_PTR_TO_JSON(test, test_);
    };
    friend void from_json(const Darabonba::Json& j, TestModelDir2& obj) { 
      DARABONBA_PTR_FROM_JSON(test, test_);
    };
    TestModelDir2() = default ;
    TestModelDir2(const TestModelDir2 &) = default ;
    TestModelDir2(TestModelDir2 &&) = default ;
    TestModelDir2(const Darabonba::Json & obj) { from_json(obj, *this); };
    virtual ~TestModelDir2() = default ;
    TestModelDir2& operator=(const TestModelDir2 &) = default ;
    TestModelDir2& operator=(TestModelDir2 &&) = default ;
    virtual void validate() const override {
        DARABONBA_VALIDATE_REQUIRED(test_);
    };
    virtual void fromMap(const Darabonba::Json &obj) override { from_json(obj, *this); validate(); };
    virtual Darabonba::Json toMap() const override { Darabonba::Json obj; to_json(obj, *this); return obj; };
    virtual bool empty() const override { return this->test_ == nullptr; };
    // test Field Functions 
    bool hasTest() const { return this->test_ != nullptr;};
    void deleteTest() { this->test_ = nullptr;};
    inline int64_t test() const { DARABONBA_PTR_GET_DEFAULT(test_, 0) };
    inline TestModelDir2& setTest(int64_t test) { DARABONBA_PTR_SET_VALUE(test_, test) };


  protected:
    std::shared_ptr<int64_t> test_ = nullptr;
  };

  } // namespace Models
} // namespace Darabonba
} // namespace Api
#endif
