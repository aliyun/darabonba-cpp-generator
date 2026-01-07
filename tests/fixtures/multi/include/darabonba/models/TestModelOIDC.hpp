// This file is auto-generated, don't edit it. Thanks.
#ifndef DARABONBA_MODELS_TESTMODELOIDC_HPP_
#define DARABONBA_MODELS_TESTMODELOIDC_HPP_
#include <darabonba/Core.hpp>
using namespace std;
using json = nlohmann::json;
namespace Darabonba
{
namespace Models
{
  class TestModelOIDC : public Darabonba::Model {
  public:
    friend void to_json(Darabonba::Json& j, const TestModelOIDC& obj) { 
      DARABONBA_PTR_TO_JSON(TEST, TEST_);
      DARABONBA_PTR_TO_JSON(OIDCName, OIDCName_);
    };
    friend void from_json(const Darabonba::Json& j, TestModelOIDC& obj) { 
      DARABONBA_PTR_FROM_JSON(TEST, TEST_);
      DARABONBA_PTR_FROM_JSON(OIDCName, OIDCName_);
    };
    TestModelOIDC() = default ;
    TestModelOIDC(const TestModelOIDC &) = default ;
    TestModelOIDC(TestModelOIDC &&) = default ;
    TestModelOIDC(const Darabonba::Json & obj) { from_json(obj, *this); };
    virtual ~TestModelOIDC() = default ;
    TestModelOIDC& operator=(const TestModelOIDC &) = default ;
    TestModelOIDC& operator=(TestModelOIDC &&) = default ;
    virtual void validate() const override {
        DARABONBA_VALIDATE_REQUIRED(TEST_);
        DARABONBA_VALIDATE_REQUIRED(OIDCName_);
    };
    virtual void fromMap(const Darabonba::Json &obj) override { from_json(obj, *this); validate(); };
    virtual Darabonba::Json toMap() const override { Darabonba::Json obj; to_json(obj, *this); return obj; };
    virtual bool empty() const override { return this->TEST_ == nullptr
        && this->OIDCName_ == nullptr; };
    // TEST Field Functions 
    bool hasTEST() const { return this->TEST_ != nullptr;};
    void deleteTEST() { this->TEST_ = nullptr;};
    inline string getTEST() const { DARABONBA_PTR_GET_DEFAULT(TEST_, "") };
    inline TestModelOIDC& setTEST(string TEST) { DARABONBA_PTR_SET_VALUE(TEST_, TEST) };


    // OIDCName Field Functions 
    bool hasOIDCName() const { return this->OIDCName_ != nullptr;};
    void deleteOIDCName() { this->OIDCName_ = nullptr;};
    inline string getOIDCName() const { DARABONBA_PTR_GET_DEFAULT(OIDCName_, "") };
    inline TestModelOIDC& setOIDCName(string OIDCName) { DARABONBA_PTR_SET_VALUE(OIDCName_, OIDCName) };


  protected:
    shared_ptr<string> TEST_ {};
    shared_ptr<string> OIDCName_ {};
  };

  } // namespace Models
} // namespace Darabonba
#endif
