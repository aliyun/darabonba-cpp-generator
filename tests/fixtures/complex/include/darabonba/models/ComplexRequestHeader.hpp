// This file is auto-generated, don't edit it. Thanks.
#ifndef DARABONBA_MODELS_COMPLEXREQUESTHEADER_HPP_
#define DARABONBA_MODELS_COMPLEXREQUESTHEADER_HPP_
#include <darabonba/Core.hpp>
using namespace std;
using json = nlohmann::json;
namespace Darabonba
{
namespace Models
{
  class ComplexRequestHeader : public Darabonba::Model {
  public:
    friend void to_json(Darabonba::Json& j, const ComplexRequestHeader& obj) { 
      DARABONBA_PTR_TO_JSON(Content, content_);
    };
    friend void from_json(const Darabonba::Json& j, ComplexRequestHeader& obj) { 
      DARABONBA_PTR_FROM_JSON(Content, content_);
    };
    ComplexRequestHeader() = default ;
    ComplexRequestHeader(const ComplexRequestHeader &) = default ;
    ComplexRequestHeader(ComplexRequestHeader &&) = default ;
    ComplexRequestHeader(const Darabonba::Json & obj) { from_json(obj, *this); };
    virtual ~ComplexRequestHeader() = default ;
    ComplexRequestHeader& operator=(const ComplexRequestHeader &) = default ;
    ComplexRequestHeader& operator=(ComplexRequestHeader &&) = default ;
    virtual void validate() const override {
        DARABONBA_VALIDATE_REQUIRED(content_);
    };
    virtual void fromMap(const Darabonba::Json &obj) override { from_json(obj, *this); validate(); };
    virtual Darabonba::Json toMap() const override { Darabonba::Json obj; to_json(obj, *this); return obj; };
    virtual bool empty() const override { return this->content_ == nullptr; };
    // content Field Functions 
    bool hasContent() const { return this->content_ != nullptr;};
    void deleteContent() { this->content_ = nullptr;};
    inline string content() const { DARABONBA_PTR_GET_DEFAULT(content_, "") };
    inline ComplexRequestHeader& setContent(string content) { DARABONBA_PTR_SET_VALUE(content_, content) };


  protected:
    // The ID of the security group to which you want to assign the instance. Instances in the same security group can communicate with each other. The maximum number of instances that a security group can contain depends on the type of the security group. For more information, see the "Security group limits" section in [Limits](https://help.aliyun.com/document_detail/25412.html#SecurityGroupQuota).
    // 
    // >Notice:  The network type of the new instance must be the same as that of the security group specified by the `SecurityGroupId` parameter. For example, if the specified security group is of the VPC type, the new instance is also of the VPC type and you must specify `VSwitchId`.
    // 
    // If you do not use `LaunchTemplateId` or `LaunchTemplateName` to specify a launch template, you must specify SecurityGroupId. Take note of the following items:
    // 
    // *   You can set `SecurityGroupId` to specify a single security group or set `SecurityGroupIds.N` to specify one or more security groups. However, you cannot specify both `SecurityGroupId` and `SecurityGroupIds.N`.
    // *   If `NetworkInterface.N.InstanceType` is set to `Primary`, you cannot specify `SecurityGroupId` or `SecurityGroupIds.N` but can specify `NetworkInterface.N.SecurityGroupId` or `NetworkInterface.N.SecurityGroupIds.N`.
    std::shared_ptr<string> content_ = nullptr;
  };

  } // namespace Models
} // namespace Darabonba
#endif
