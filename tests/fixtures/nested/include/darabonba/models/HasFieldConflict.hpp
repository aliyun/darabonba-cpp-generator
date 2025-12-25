// This file is auto-generated, don't edit it. Thanks.
#ifndef DARABONBA_MODELS_HASFIELDCONFLICT_HPP_
#define DARABONBA_MODELS_HASFIELDCONFLICT_HPP_
#include <darabonba/Core.hpp>
using namespace std;
using json = nlohmann::json;
namespace Darabonba
{
namespace Nested
{
namespace Models
{
  class HasFieldConflict : public Darabonba::Model {
  public:
    friend void to_json(Darabonba::Json& j, const HasFieldConflict& obj) { 
      DARABONBA_PTR_TO_JSON(hasConfig, hasConfig_);
      DARABONBA_PTR_TO_JSON(config, config_);
    };
    friend void from_json(const Darabonba::Json& j, HasFieldConflict& obj) { 
      DARABONBA_PTR_FROM_JSON(hasConfig, hasConfig_);
      DARABONBA_PTR_FROM_JSON(config, config_);
    };
    HasFieldConflict() = default ;
    HasFieldConflict(const HasFieldConflict &) = default ;
    HasFieldConflict(HasFieldConflict &&) = default ;
    HasFieldConflict(const Darabonba::Json & obj) { from_json(obj, *this); };
    virtual ~HasFieldConflict() = default ;
    HasFieldConflict& operator=(const HasFieldConflict &) = default ;
    HasFieldConflict& operator=(HasFieldConflict &&) = default ;
    virtual void validate() const override {
    };
    virtual void fromMap(const Darabonba::Json &obj) override { from_json(obj, *this); validate(); };
    virtual Darabonba::Json toMap() const override { Darabonba::Json obj; to_json(obj, *this); return obj; };
    virtual bool empty() const override { return this->hasConfig_ == nullptr
        && this->config_ == nullptr; };
    // hasConfig Field Functions 
    bool hasHasConfig() const { return this->hasConfig_ != nullptr;};
    void deleteHasConfig() { this->hasConfig_ = nullptr;};
    inline int32_t getHasConfig() const { DARABONBA_PTR_GET_DEFAULT(hasConfig_, 0) };
    inline HasFieldConflict& setHasConfig(int32_t hasConfig) { DARABONBA_PTR_SET_VALUE(hasConfig_, hasConfig) };


    // config Field Functions 
    bool hasConfig() const { return this->config_ != nullptr;};
    void deleteConfig() { this->config_ = nullptr;};
    inline string getConfig() const { DARABONBA_PTR_GET_DEFAULT(config_, "") };
    inline HasFieldConflict& setConfig(string config) { DARABONBA_PTR_SET_VALUE(config_, config) };


  protected:
    // 测试has开头的字段
    shared_ptr<int32_t> hasConfig_ {};
    // 普通配置字段
    shared_ptr<string> config_ {};
  };

  } // namespace Models
} // namespace Darabonba
} // namespace Nested
#endif
