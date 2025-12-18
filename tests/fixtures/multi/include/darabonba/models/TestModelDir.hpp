// This file is auto-generated, don't edit it. Thanks.
#ifndef DARABONBA_MODELS_TESTMODELDIR_HPP_
#define DARABONBA_MODELS_TESTMODELDIR_HPP_
#include <darabonba/Core.hpp>
#include <darabonba/model/User.hpp>
using namespace std;
using json = nlohmann::json;
namespace Darabonba
{
namespace Models
{
  class TestModelDIR : public Darabonba::Model {
  public:
    friend void to_json(Darabonba::Json& j, const TestModelDIR& obj) { 
      DARABONBA_PTR_TO_JSON(test, test_);
      DARABONBA_ANY_TO_JSON(a, a_);
    };
    friend void from_json(const Darabonba::Json& j, TestModelDIR& obj) { 
      DARABONBA_PTR_FROM_JSON(test, test_);
      DARABONBA_ANY_FROM_JSON(a, a_);
    };
    TestModelDIR() = default ;
    TestModelDIR(const TestModelDIR &) = default ;
    TestModelDIR(TestModelDIR &&) = default ;
    TestModelDIR(const Darabonba::Json & obj) { from_json(obj, *this); };
    virtual ~TestModelDIR() = default ;
    TestModelDIR& operator=(const TestModelDIR &) = default ;
    TestModelDIR& operator=(TestModelDIR &&) = default ;
    virtual void validate() const override {
        DARABONBA_VALIDATE_REQUIRED(test_);
        DARABONBA_VALIDATE_REQUIRED(a_);
    };
    virtual void fromMap(const Darabonba::Json &obj) override { from_json(obj, *this); validate(); };
    virtual Darabonba::Json toMap() const override { Darabonba::Json obj; to_json(obj, *this); return obj; };
    virtual bool empty() const override { return this->test_ == nullptr
        && this->a_ == nullptr; };
    // test Field Functions 
    bool hasTest() const { return this->test_ != nullptr;};
    void deleteTest() { this->test_ = nullptr;};
    inline string test() const { DARABONBA_PTR_GET_DEFAULT(test_, "") };
    inline TestModelDIR& setTest(string test) { DARABONBA_PTR_SET_VALUE(test_, test) };


    // a Field Functions 
    bool hasA() const { return this->a_ != nullptr;};
    void deleteA() { this->a_ = nullptr;};
    inline     const Darabonba::Json & a() const { DARABONBA_GET(a_) };
    Darabonba::Json & a() { DARABONBA_GET(a_) };
    inline TestModelDIR& setA(const Darabonba::Json & a) { DARABONBA_SET_VALUE(a_, a) };
    inline TestModelDIR& setA(Darabonba::Json && a) { DARABONBA_SET_RVALUE(a_, a) };


  protected:
    std::shared_ptr<string> test_ = nullptr;
    Darabonba::Json a_ = nullptr;
  };

  } // namespace Models
namespace Models
{
  class TestModelDir : public Darabonba::Model {
  public:
    friend void to_json(Darabonba::Json& j, const TestModelDir& obj) { 
      DARABONBA_PTR_TO_JSON(test, test_);
      DARABONBA_PTR_TO_JSON(m, m_);
    };
    friend void from_json(const Darabonba::Json& j, TestModelDir& obj) { 
      DARABONBA_PTR_FROM_JSON(test, test_);
      DARABONBA_PTR_FROM_JSON(m, m_);
    };
    TestModelDir() = default ;
    TestModelDir(const TestModelDir &) = default ;
    TestModelDir(TestModelDir &&) = default ;
    TestModelDir(const Darabonba::Json & obj) { from_json(obj, *this); };
    virtual ~TestModelDir() = default ;
    TestModelDir& operator=(const TestModelDir &) = default ;
    TestModelDir& operator=(TestModelDir &&) = default ;
    virtual void validate() const override {
        DARABONBA_VALIDATE_REQUIRED(test_);
        DARABONBA_VALIDATE_REQUIRED(m_);
    };
    virtual void fromMap(const Darabonba::Json &obj) override { from_json(obj, *this); validate(); };
    virtual Darabonba::Json toMap() const override { Darabonba::Json obj; to_json(obj, *this); return obj; };
    virtual bool empty() const override { return this->test_ == nullptr
        && this->m_ == nullptr; };
    // test Field Functions 
    bool hasTest() const { return this->test_ != nullptr;};
    void deleteTest() { this->test_ = nullptr;};
    inline int64_t test() const { DARABONBA_PTR_GET_DEFAULT(test_, 0) };
    inline TestModelDir& setTest(int64_t test) { DARABONBA_PTR_SET_VALUE(test_, test) };


    // m Field Functions 
    bool hasM() const { return this->m_ != nullptr;};
    void deleteM() { this->m_ = nullptr;};
    inline const Darabonba::Model::User::Models::Info & m() const { DARABONBA_PTR_GET_CONST(m_, Darabonba::Model::User::Models::Info) };
    inline Darabonba::Model::User::Models::Info m() { DARABONBA_PTR_GET(m_, Darabonba::Model::User::Models::Info) };
    inline TestModelDir& setM(const Darabonba::Model::User::Models::Info & m) { DARABONBA_PTR_SET_VALUE(m_, m) };
    inline TestModelDir& setM(Darabonba::Model::User::Models::Info && m) { DARABONBA_PTR_SET_RVALUE(m_, m) };


  protected:
    std::shared_ptr<int64_t> test_ = nullptr;
    std::shared_ptr<Darabonba::Model::User::Models::Info> m_ = nullptr;
  };

  } // namespace Models
} // namespace Darabonba
#endif
