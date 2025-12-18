// This file is auto-generated, don't edit it. Thanks.
#ifndef DARABONBA_MODELS_COMPLEXREQUEST_HPP_
#define DARABONBA_MODELS_COMPLEXREQUEST_HPP_
#include <darabonba/Core.hpp>
#include <vector>
#include <map>
#include <darabonba/http/Request.hpp>
#include <darabonba/http/MCurlResponse.hpp>
#include <darabonba/source.hpp>
using namespace std;
using json = nlohmann::json;
namespace Darabonba
{
namespace Models
{
  class ComplexRequest : public Darabonba::Model {
  public:
    friend void to_json(Darabonba::Json& j, const ComplexRequest& obj) { 
      DARABONBA_PTR_TO_JSON(accessKey, accessKey_);
      DARABONBA_TO_JSON(Body, body_);
      DARABONBA_PTR_TO_JSON(Strs, strs_);
      DARABONBA_PTR_TO_JSON(mapList, mapList_);
      DARABONBA_PTR_TO_JSON(header, header_);
      DARABONBA_PTR_TO_JSON(configs, configs_);
      DARABONBA_PTR_TO_JSON(num, num_);
      DARABONBA_PTR_TO_JSON(i64, i64_);
      DARABONBA_PTR_TO_JSON(f64, f64_);
      DARABONBA_PTR_TO_JSON(b, b_);
      DARABONBA_PTR_TO_JSON(f32, f32_);
      DARABONBA_PTR_TO_JSON(f64List, f64List_);
      DARABONBA_PTR_TO_JSON(floatList, floatList_);
      DARABONBA_PTR_TO_JSON(booleantList, booleantList_);
      DARABONBA_PTR_TO_JSON(i32, i32_);
      DARABONBA_PTR_TO_JSON(stringList, stringList_);
      DARABONBA_PTR_TO_JSON(intList, intList_);
      DARABONBA_PTR_TO_JSON(int32List, int32List_);
      DARABONBA_PTR_TO_JSON(int16List, int16List_);
      DARABONBA_PTR_TO_JSON(int64List, int64List_);
      DARABONBA_PTR_TO_JSON(longList, longList_);
      DARABONBA_PTR_TO_JSON(uint64List, uint64List_);
      DARABONBA_PTR_TO_JSON(uint32List, uint32List_);
      DARABONBA_PTR_TO_JSON(uint16List, uint16List_);
      DARABONBA_PTR_TO_JSON(u64, u64_);
      DARABONBA_PTR_TO_JSON(u32, u32_);
      DARABONBA_PTR_TO_JSON(u16, u16_);
      DARABONBA_PTR_TO_JSON(obj, obj_);
      DARABONBA_ANY_TO_JSON(any, any_);
      DARABONBA_PTR_TO_JSON(byt, byt_);
      DARABONBA_PTR_TO_JSON(req, req_);
      DARABONBA_PTR_TO_JSON(resp, resp_);
      DARABONBA_PTR_TO_JSON(map, map_);
      DARABONBA_PTR_TO_JSON(numMap, numMap_);
      DARABONBA_PTR_TO_JSON(modelMap, modelMap_);
      DARABONBA_PTR_TO_JSON(request, request_);
      DARABONBA_TO_JSON(client, client_);
      DARABONBA_PTR_TO_JSON(instance, instance_);
      DARABONBA_PTR_TO_JSON(from, from_);
      DARABONBA_PTR_TO_JSON(self, self_);
      DARABONBA_PTR_TO_JSON(print, print_);
      DARABONBA_PTR_TO_JSON(exec, exec_);
      DARABONBA_PTR_TO_JSON(srt, str_);
      DARABONBA_PTR_TO_JSON(Part, part_);
    };
    friend void from_json(const Darabonba::Json& j, ComplexRequest& obj) { 
      DARABONBA_PTR_FROM_JSON(accessKey, accessKey_);
      DARABONBA_FROM_JSON(Body, body_);
      DARABONBA_PTR_FROM_JSON(Strs, strs_);
      DARABONBA_PTR_FROM_JSON(mapList, mapList_);
      DARABONBA_PTR_FROM_JSON(header, header_);
      DARABONBA_PTR_FROM_JSON(configs, configs_);
      DARABONBA_PTR_FROM_JSON(num, num_);
      DARABONBA_PTR_FROM_JSON(i64, i64_);
      DARABONBA_PTR_FROM_JSON(f64, f64_);
      DARABONBA_PTR_FROM_JSON(b, b_);
      DARABONBA_PTR_FROM_JSON(f32, f32_);
      DARABONBA_PTR_FROM_JSON(f64List, f64List_);
      DARABONBA_PTR_FROM_JSON(floatList, floatList_);
      DARABONBA_PTR_FROM_JSON(booleantList, booleantList_);
      DARABONBA_PTR_FROM_JSON(i32, i32_);
      DARABONBA_PTR_FROM_JSON(stringList, stringList_);
      DARABONBA_PTR_FROM_JSON(intList, intList_);
      DARABONBA_PTR_FROM_JSON(int32List, int32List_);
      DARABONBA_PTR_FROM_JSON(int16List, int16List_);
      DARABONBA_PTR_FROM_JSON(int64List, int64List_);
      DARABONBA_PTR_FROM_JSON(longList, longList_);
      DARABONBA_PTR_FROM_JSON(uint64List, uint64List_);
      DARABONBA_PTR_FROM_JSON(uint32List, uint32List_);
      DARABONBA_PTR_FROM_JSON(uint16List, uint16List_);
      DARABONBA_PTR_FROM_JSON(u64, u64_);
      DARABONBA_PTR_FROM_JSON(u32, u32_);
      DARABONBA_PTR_FROM_JSON(u16, u16_);
      DARABONBA_PTR_FROM_JSON(obj, obj_);
      DARABONBA_ANY_FROM_JSON(any, any_);
      DARABONBA_PTR_FROM_JSON(byt, byt_);
      DARABONBA_PTR_FROM_JSON(req, req_);
      DARABONBA_PTR_FROM_JSON(resp, resp_);
      DARABONBA_PTR_FROM_JSON(map, map_);
      DARABONBA_PTR_FROM_JSON(numMap, numMap_);
      DARABONBA_PTR_FROM_JSON(modelMap, modelMap_);
      DARABONBA_PTR_FROM_JSON(request, request_);
      DARABONBA_FROM_JSON(client, client_);
      DARABONBA_PTR_FROM_JSON(instance, instance_);
      DARABONBA_PTR_FROM_JSON(from, from_);
      DARABONBA_PTR_FROM_JSON(self, self_);
      DARABONBA_PTR_FROM_JSON(print, print_);
      DARABONBA_PTR_FROM_JSON(exec, exec_);
      DARABONBA_PTR_FROM_JSON(srt, str_);
      DARABONBA_PTR_FROM_JSON(Part, part_);
    };
    ComplexRequest() = default ;
    ComplexRequest(const ComplexRequest &) = default ;
    ComplexRequest(ComplexRequest &&) = default ;
    ComplexRequest(const Darabonba::Json & obj) { from_json(obj, *this); };
    virtual ~ComplexRequest() = default ;
    ComplexRequest& operator=(const ComplexRequest &) = default ;
    ComplexRequest& operator=(ComplexRequest &&) = default ;
    virtual void validate() const override {
        DARABONBA_VALIDATE_REQUIRED(accessKey_);
        DARABONBA_VALIDATE_REQUIRED(body_);
        DARABONBA_VALIDATE_REQUIRED(strs_);
        DARABONBA_VALIDATE_REQUIRED(mapList_);
        DARABONBA_VALIDATE_REQUIRED(header_);
        DARABONBA_VALIDATE_REQUIRED(configs_);
        DARABONBA_VALIDATE_REQUIRED(num_);
        DARABONBA_VALIDATE_REQUIRED(i64_);
        DARABONBA_VALIDATE_REQUIRED(f64_);
        DARABONBA_VALIDATE_REQUIRED(b_);
        DARABONBA_VALIDATE_REQUIRED(f32_);
        DARABONBA_VALIDATE_REQUIRED(f64List_);
        DARABONBA_VALIDATE_REQUIRED(floatList_);
        DARABONBA_VALIDATE_REQUIRED(booleantList_);
        DARABONBA_VALIDATE_REQUIRED(i32_);
        DARABONBA_VALIDATE_REQUIRED(stringList_);
        DARABONBA_VALIDATE_REQUIRED(intList_);
        DARABONBA_VALIDATE_REQUIRED(int32List_);
        DARABONBA_VALIDATE_REQUIRED(int16List_);
        DARABONBA_VALIDATE_REQUIRED(int64List_);
        DARABONBA_VALIDATE_REQUIRED(longList_);
        DARABONBA_VALIDATE_REQUIRED(uint64List_);
        DARABONBA_VALIDATE_REQUIRED(uint32List_);
        DARABONBA_VALIDATE_REQUIRED(uint16List_);
        DARABONBA_VALIDATE_REQUIRED(u64_);
        DARABONBA_VALIDATE_REQUIRED(u32_);
        DARABONBA_VALIDATE_REQUIRED(u16_);
        DARABONBA_VALIDATE_REQUIRED(obj_);
        DARABONBA_VALIDATE_REQUIRED(any_);
        DARABONBA_VALIDATE_REQUIRED(byt_);
        DARABONBA_VALIDATE_REQUIRED(req_);
        DARABONBA_VALIDATE_REQUIRED(resp_);
        DARABONBA_VALIDATE_REQUIRED(map_);
        DARABONBA_VALIDATE_REQUIRED(numMap_);
        DARABONBA_VALIDATE_REQUIRED(modelMap_);
        DARABONBA_VALIDATE_REQUIRED(request_);
        DARABONBA_VALIDATE_REQUIRED(client_);
        DARABONBA_VALIDATE_REQUIRED(instance_);
        DARABONBA_VALIDATE_REQUIRED(from_);
        DARABONBA_VALIDATE_REQUIRED(self_);
        DARABONBA_VALIDATE_REQUIRED(print_);
        DARABONBA_VALIDATE_REQUIRED(exec_);
        DARABONBA_VALIDATE_REQUIRED(str_);
    };
    virtual void fromMap(const Darabonba::Json &obj) override { from_json(obj, *this); validate(); };
    virtual Darabonba::Json toMap() const override { Darabonba::Json obj; to_json(obj, *this); return obj; };
    class Part : public Darabonba::Model {
    public:
      friend void to_json(Darabonba::Json& j, const Part& obj) { 
        DARABONBA_PTR_TO_JSON(PartNumber, partNumber_);
      };
      friend void from_json(const Darabonba::Json& j, Part& obj) { 
        DARABONBA_PTR_FROM_JSON(PartNumber, partNumber_);
      };
      Part() = default ;
      Part(const Part &) = default ;
      Part(Part &&) = default ;
      Part(const Darabonba::Json & obj) { from_json(obj, *this); };
      virtual ~Part() = default ;
      Part& operator=(const Part &) = default ;
      Part& operator=(Part &&) = default ;
      virtual void validate() const override {
      };
      virtual void fromMap(const Darabonba::Json &obj) override { from_json(obj, *this); validate(); };
      virtual Darabonba::Json toMap() const override { Darabonba::Json obj; to_json(obj, *this); return obj; };
      virtual bool empty() const override { return this->partNumber_ == nullptr; };
      // partNumber Field Functions 
      bool hasPartNumber() const { return this->partNumber_ != nullptr;};
      void deletePartNumber() { this->partNumber_ = nullptr;};
      inline string partNumber() const { DARABONBA_PTR_GET_DEFAULT(partNumber_, "") };
      inline Part& setPartNumber(string partNumber) { DARABONBA_PTR_SET_VALUE(partNumber_, partNumber) };


    protected:
      // PartNumber
      std::shared_ptr<string> partNumber_ = nullptr;
    };

    class Configs : public Darabonba::Model {
    public:
      friend void to_json(Darabonba::Json& j, const Configs& obj) { 
        DARABONBA_PTR_TO_JSON(key, key_);
        DARABONBA_PTR_TO_JSON(value, value_);
        DARABONBA_PTR_TO_JSON(extra, extra_);
      };
      friend void from_json(const Darabonba::Json& j, Configs& obj) { 
        DARABONBA_PTR_FROM_JSON(key, key_);
        DARABONBA_PTR_FROM_JSON(value, value_);
        DARABONBA_PTR_FROM_JSON(extra, extra_);
      };
      Configs() = default ;
      Configs(const Configs &) = default ;
      Configs(Configs &&) = default ;
      Configs(const Darabonba::Json & obj) { from_json(obj, *this); };
      virtual ~Configs() = default ;
      Configs& operator=(const Configs &) = default ;
      Configs& operator=(Configs &&) = default ;
      virtual void validate() const override {
          DARABONBA_VALIDATE_REQUIRED(key_);
          DARABONBA_VALIDATE_REQUIRED(value_);
          DARABONBA_VALIDATE_REQUIRED(extra_);
      };
      virtual void fromMap(const Darabonba::Json &obj) override { from_json(obj, *this); validate(); };
      virtual Darabonba::Json toMap() const override { Darabonba::Json obj; to_json(obj, *this); return obj; };
      virtual bool empty() const override { return this->key_ == nullptr
        && this->value_ == nullptr && this->extra_ == nullptr; };
      // key Field Functions 
      bool hasKey() const { return this->key_ != nullptr;};
      void deleteKey() { this->key_ = nullptr;};
      inline string key() const { DARABONBA_PTR_GET_DEFAULT(key_, "") };
      inline Configs& setKey(string key) { DARABONBA_PTR_SET_VALUE(key_, key) };


      // value Field Functions 
      bool hasValue() const { return this->value_ != nullptr;};
      void deleteValue() { this->value_ = nullptr;};
      inline const vector<string> & value() const { DARABONBA_PTR_GET_CONST(value_, vector<string>) };
      inline vector<string> value() { DARABONBA_PTR_GET(value_, vector<string>) };
      inline Configs& setValue(const vector<string> & value) { DARABONBA_PTR_SET_VALUE(value_, value) };
      inline Configs& setValue(vector<string> && value) { DARABONBA_PTR_SET_RVALUE(value_, value) };


      // extra Field Functions 
      bool hasExtra() const { return this->extra_ != nullptr;};
      void deleteExtra() { this->extra_ = nullptr;};
      inline const map<string, string> & extra() const { DARABONBA_PTR_GET_CONST(extra_, map<string, string>) };
      inline map<string, string> extra() { DARABONBA_PTR_GET(extra_, map<string, string>) };
      inline Configs& setExtra(const map<string, string> & extra) { DARABONBA_PTR_SET_VALUE(extra_, extra) };
      inline Configs& setExtra(map<string, string> && extra) { DARABONBA_PTR_SET_RVALUE(extra_, extra) };


    protected:
      std::shared_ptr<string> key_ = nullptr;
      std::shared_ptr<vector<string>> value_ = nullptr;
      std::shared_ptr<map<string, string>> extra_ = nullptr;
    };

    class Header : public Darabonba::Model {
    public:
      friend void to_json(Darabonba::Json& j, const Header& obj) { 
        DARABONBA_PTR_TO_JSON(Content, content_);
      };
      friend void from_json(const Darabonba::Json& j, Header& obj) { 
        DARABONBA_PTR_FROM_JSON(Content, content_);
      };
      Header() = default ;
      Header(const Header &) = default ;
      Header(Header &&) = default ;
      Header(const Darabonba::Json & obj) { from_json(obj, *this); };
      virtual ~Header() = default ;
      Header& operator=(const Header &) = default ;
      Header& operator=(Header &&) = default ;
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
      inline Header& setContent(string content) { DARABONBA_PTR_SET_VALUE(content_, content) };


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

    virtual bool empty() const override { return this->accessKey_ == nullptr
        && this->body_ == nullptr && this->strs_ == nullptr && this->mapList_ == nullptr && this->header_ == nullptr && this->configs_ == nullptr
        && this->num_ == nullptr && this->i64_ == nullptr && this->f64_ == nullptr && this->b_ == nullptr && this->f32_ == nullptr
        && this->f64List_ == nullptr && this->floatList_ == nullptr && this->booleantList_ == nullptr && this->i32_ == nullptr && this->stringList_ == nullptr
        && this->intList_ == nullptr && this->int32List_ == nullptr && this->int16List_ == nullptr && this->int64List_ == nullptr && this->longList_ == nullptr
        && this->uint64List_ == nullptr && this->uint32List_ == nullptr && this->uint16List_ == nullptr && this->u64_ == nullptr && this->u32_ == nullptr
        && this->u16_ == nullptr && this->obj_ == nullptr && this->any_ == nullptr && this->byt_ == nullptr && this->req_ == nullptr
        && this->resp_ == nullptr && this->map_ == nullptr && this->numMap_ == nullptr && this->modelMap_ == nullptr && this->request_ == nullptr
        && this->client_ == nullptr && this->instance_ == nullptr && this->from_ == nullptr && this->self_ == nullptr && this->print_ == nullptr
        && this->exec_ == nullptr && this->str_ == nullptr && this->part_ == nullptr; };
    // accessKey Field Functions 
    bool hasAccessKey() const { return this->accessKey_ != nullptr;};
    void deleteAccessKey() { this->accessKey_ = nullptr;};
    inline string accessKey() const { DARABONBA_PTR_GET_DEFAULT(accessKey_, "") };
    inline ComplexRequest& setAccessKey(string accessKey) { DARABONBA_PTR_SET_VALUE(accessKey_, accessKey) };


    // body Field Functions 
    bool hasBody() const { return this->body_ != nullptr;};
    void deleteBody() { this->body_ = nullptr;};
    inline shared_ptr<Darabonba::IStream> body() const { DARABONBA_GET(body_) };
    inline ComplexRequest& setBody(shared_ptr<Darabonba::IStream> body) { DARABONBA_SET_VALUE(body_, body) };


    // strs Field Functions 
    bool hasStrs() const { return this->strs_ != nullptr;};
    void deleteStrs() { this->strs_ = nullptr;};
    inline const vector<string> & strs() const { DARABONBA_PTR_GET_CONST(strs_, vector<string>) };
    inline vector<string> strs() { DARABONBA_PTR_GET(strs_, vector<string>) };
    inline ComplexRequest& setStrs(const vector<string> & strs) { DARABONBA_PTR_SET_VALUE(strs_, strs) };
    inline ComplexRequest& setStrs(vector<string> && strs) { DARABONBA_PTR_SET_RVALUE(strs_, strs) };


    // mapList Field Functions 
    bool hasMapList() const { return this->mapList_ != nullptr;};
    void deleteMapList() { this->mapList_ = nullptr;};
    inline const vector<Darabonba::Json> & mapList() const { DARABONBA_PTR_GET_CONST(mapList_, vector<Darabonba::Json>) };
    inline vector<Darabonba::Json> mapList() { DARABONBA_PTR_GET(mapList_, vector<Darabonba::Json>) };
    inline ComplexRequest& setMapList(const vector<Darabonba::Json> & mapList) { DARABONBA_PTR_SET_VALUE(mapList_, mapList) };
    inline ComplexRequest& setMapList(vector<Darabonba::Json> && mapList) { DARABONBA_PTR_SET_RVALUE(mapList_, mapList) };


    // header Field Functions 
    bool hasHeader() const { return this->header_ != nullptr;};
    void deleteHeader() { this->header_ = nullptr;};
    inline const ComplexRequest::Header & header() const { DARABONBA_PTR_GET_CONST(header_, ComplexRequest::Header) };
    inline ComplexRequest::Header header() { DARABONBA_PTR_GET(header_, ComplexRequest::Header) };
    inline ComplexRequest& setHeader(const ComplexRequest::Header & header) { DARABONBA_PTR_SET_VALUE(header_, header) };
    inline ComplexRequest& setHeader(ComplexRequest::Header && header) { DARABONBA_PTR_SET_RVALUE(header_, header) };


    // configs Field Functions 
    bool hasConfigs() const { return this->configs_ != nullptr;};
    void deleteConfigs() { this->configs_ = nullptr;};
    inline const ComplexRequest::Configs & configs() const { DARABONBA_PTR_GET_CONST(configs_, ComplexRequest::Configs) };
    inline ComplexRequest::Configs configs() { DARABONBA_PTR_GET(configs_, ComplexRequest::Configs) };
    inline ComplexRequest& setConfigs(const ComplexRequest::Configs & configs) { DARABONBA_PTR_SET_VALUE(configs_, configs) };
    inline ComplexRequest& setConfigs(ComplexRequest::Configs && configs) { DARABONBA_PTR_SET_RVALUE(configs_, configs) };


    // num Field Functions 
    bool hasNum() const { return this->num_ != nullptr;};
    void deleteNum() { this->num_ = nullptr;};
    inline int64_t num() const { DARABONBA_PTR_GET_DEFAULT(num_, 0) };
    inline ComplexRequest& setNum(int64_t num) { DARABONBA_PTR_SET_VALUE(num_, num) };


    // i64 Field Functions 
    bool hasI64() const { return this->i64_ != nullptr;};
    void deleteI64() { this->i64_ = nullptr;};
    inline int64_t i64() const { DARABONBA_PTR_GET_DEFAULT(i64_, 0L) };
    inline ComplexRequest& setI64(int64_t i64) { DARABONBA_PTR_SET_VALUE(i64_, i64) };


    // f64 Field Functions 
    bool hasF64() const { return this->f64_ != nullptr;};
    void deleteF64() { this->f64_ = nullptr;};
    inline double f64() const { DARABONBA_PTR_GET_DEFAULT(f64_, 0.0) };
    inline ComplexRequest& setF64(double f64) { DARABONBA_PTR_SET_VALUE(f64_, f64) };


    // b Field Functions 
    bool hasB() const { return this->b_ != nullptr;};
    void deleteB() { this->b_ = nullptr;};
    inline bool b() const { DARABONBA_PTR_GET_DEFAULT(b_, false) };
    inline ComplexRequest& setB(bool b) { DARABONBA_PTR_SET_VALUE(b_, b) };


    // f32 Field Functions 
    bool hasF32() const { return this->f32_ != nullptr;};
    void deleteF32() { this->f32_ = nullptr;};
    inline float f32() const { DARABONBA_PTR_GET_DEFAULT(f32_, 0.0) };
    inline ComplexRequest& setF32(float f32) { DARABONBA_PTR_SET_VALUE(f32_, f32) };


    // f64List Field Functions 
    bool hasF64List() const { return this->f64List_ != nullptr;};
    void deleteF64List() { this->f64List_ = nullptr;};
    inline const vector<double> & f64List() const { DARABONBA_PTR_GET_CONST(f64List_, vector<double>) };
    inline vector<double> f64List() { DARABONBA_PTR_GET(f64List_, vector<double>) };
    inline ComplexRequest& setF64List(const vector<double> & f64List) { DARABONBA_PTR_SET_VALUE(f64List_, f64List) };
    inline ComplexRequest& setF64List(vector<double> && f64List) { DARABONBA_PTR_SET_RVALUE(f64List_, f64List) };


    // floatList Field Functions 
    bool hasFloatList() const { return this->floatList_ != nullptr;};
    void deleteFloatList() { this->floatList_ = nullptr;};
    inline const vector<float> & floatList() const { DARABONBA_PTR_GET_CONST(floatList_, vector<float>) };
    inline vector<float> floatList() { DARABONBA_PTR_GET(floatList_, vector<float>) };
    inline ComplexRequest& setFloatList(const vector<float> & floatList) { DARABONBA_PTR_SET_VALUE(floatList_, floatList) };
    inline ComplexRequest& setFloatList(vector<float> && floatList) { DARABONBA_PTR_SET_RVALUE(floatList_, floatList) };


    // booleantList Field Functions 
    bool hasBooleantList() const { return this->booleantList_ != nullptr;};
    void deleteBooleantList() { this->booleantList_ = nullptr;};
    inline const vector<bool> & booleantList() const { DARABONBA_PTR_GET_CONST(booleantList_, vector<bool>) };
    inline vector<bool> booleantList() { DARABONBA_PTR_GET(booleantList_, vector<bool>) };
    inline ComplexRequest& setBooleantList(const vector<bool> & booleantList) { DARABONBA_PTR_SET_VALUE(booleantList_, booleantList) };
    inline ComplexRequest& setBooleantList(vector<bool> && booleantList) { DARABONBA_PTR_SET_RVALUE(booleantList_, booleantList) };


    // i32 Field Functions 
    bool hasI32() const { return this->i32_ != nullptr;};
    void deleteI32() { this->i32_ = nullptr;};
    inline int32_t i32() const { DARABONBA_PTR_GET_DEFAULT(i32_, 0) };
    inline ComplexRequest& setI32(int32_t i32) { DARABONBA_PTR_SET_VALUE(i32_, i32) };


    // stringList Field Functions 
    bool hasStringList() const { return this->stringList_ != nullptr;};
    void deleteStringList() { this->stringList_ = nullptr;};
    inline const vector<string> & stringList() const { DARABONBA_PTR_GET_CONST(stringList_, vector<string>) };
    inline vector<string> stringList() { DARABONBA_PTR_GET(stringList_, vector<string>) };
    inline ComplexRequest& setStringList(const vector<string> & stringList) { DARABONBA_PTR_SET_VALUE(stringList_, stringList) };
    inline ComplexRequest& setStringList(vector<string> && stringList) { DARABONBA_PTR_SET_RVALUE(stringList_, stringList) };


    // intList Field Functions 
    bool hasIntList() const { return this->intList_ != nullptr;};
    void deleteIntList() { this->intList_ = nullptr;};
    inline const vector<int32_t> & intList() const { DARABONBA_PTR_GET_CONST(intList_, vector<int32_t>) };
    inline vector<int32_t> intList() { DARABONBA_PTR_GET(intList_, vector<int32_t>) };
    inline ComplexRequest& setIntList(const vector<int32_t> & intList) { DARABONBA_PTR_SET_VALUE(intList_, intList) };
    inline ComplexRequest& setIntList(vector<int32_t> && intList) { DARABONBA_PTR_SET_RVALUE(intList_, intList) };


    // int32List Field Functions 
    bool hasInt32List() const { return this->int32List_ != nullptr;};
    void deleteInt32List() { this->int32List_ = nullptr;};
    inline const vector<int32_t> & int32List() const { DARABONBA_PTR_GET_CONST(int32List_, vector<int32_t>) };
    inline vector<int32_t> int32List() { DARABONBA_PTR_GET(int32List_, vector<int32_t>) };
    inline ComplexRequest& setInt32List(const vector<int32_t> & int32List) { DARABONBA_PTR_SET_VALUE(int32List_, int32List) };
    inline ComplexRequest& setInt32List(vector<int32_t> && int32List) { DARABONBA_PTR_SET_RVALUE(int32List_, int32List) };


    // int16List Field Functions 
    bool hasInt16List() const { return this->int16List_ != nullptr;};
    void deleteInt16List() { this->int16List_ = nullptr;};
    inline const vector<int16> & int16List() const { DARABONBA_PTR_GET_CONST(int16List_, vector<int16>) };
    inline vector<int16> int16List() { DARABONBA_PTR_GET(int16List_, vector<int16>) };
    inline ComplexRequest& setInt16List(const vector<int16> & int16List) { DARABONBA_PTR_SET_VALUE(int16List_, int16List) };
    inline ComplexRequest& setInt16List(vector<int16> && int16List) { DARABONBA_PTR_SET_RVALUE(int16List_, int16List) };


    // int64List Field Functions 
    bool hasInt64List() const { return this->int64List_ != nullptr;};
    void deleteInt64List() { this->int64List_ = nullptr;};
    inline const vector<int64_t> & int64List() const { DARABONBA_PTR_GET_CONST(int64List_, vector<int64_t>) };
    inline vector<int64_t> int64List() { DARABONBA_PTR_GET(int64List_, vector<int64_t>) };
    inline ComplexRequest& setInt64List(const vector<int64_t> & int64List) { DARABONBA_PTR_SET_VALUE(int64List_, int64List) };
    inline ComplexRequest& setInt64List(vector<int64_t> && int64List) { DARABONBA_PTR_SET_RVALUE(int64List_, int64List) };


    // longList Field Functions 
    bool hasLongList() const { return this->longList_ != nullptr;};
    void deleteLongList() { this->longList_ = nullptr;};
    inline const vector<int64_t> & longList() const { DARABONBA_PTR_GET_CONST(longList_, vector<int64_t>) };
    inline vector<int64_t> longList() { DARABONBA_PTR_GET(longList_, vector<int64_t>) };
    inline ComplexRequest& setLongList(const vector<int64_t> & longList) { DARABONBA_PTR_SET_VALUE(longList_, longList) };
    inline ComplexRequest& setLongList(vector<int64_t> && longList) { DARABONBA_PTR_SET_RVALUE(longList_, longList) };


    // uint64List Field Functions 
    bool hasUint64List() const { return this->uint64List_ != nullptr;};
    void deleteUint64List() { this->uint64List_ = nullptr;};
    inline const vector<uint64_t> & uint64List() const { DARABONBA_PTR_GET_CONST(uint64List_, vector<uint64_t>) };
    inline vector<uint64_t> uint64List() { DARABONBA_PTR_GET(uint64List_, vector<uint64_t>) };
    inline ComplexRequest& setUint64List(const vector<uint64_t> & uint64List) { DARABONBA_PTR_SET_VALUE(uint64List_, uint64List) };
    inline ComplexRequest& setUint64List(vector<uint64_t> && uint64List) { DARABONBA_PTR_SET_RVALUE(uint64List_, uint64List) };


    // uint32List Field Functions 
    bool hasUint32List() const { return this->uint32List_ != nullptr;};
    void deleteUint32List() { this->uint32List_ = nullptr;};
    inline const vector<uint32_t> & uint32List() const { DARABONBA_PTR_GET_CONST(uint32List_, vector<uint32_t>) };
    inline vector<uint32_t> uint32List() { DARABONBA_PTR_GET(uint32List_, vector<uint32_t>) };
    inline ComplexRequest& setUint32List(const vector<uint32_t> & uint32List) { DARABONBA_PTR_SET_VALUE(uint32List_, uint32List) };
    inline ComplexRequest& setUint32List(vector<uint32_t> && uint32List) { DARABONBA_PTR_SET_RVALUE(uint32List_, uint32List) };


    // uint16List Field Functions 
    bool hasUint16List() const { return this->uint16List_ != nullptr;};
    void deleteUint16List() { this->uint16List_ = nullptr;};
    inline const vector<uint16_t> & uint16List() const { DARABONBA_PTR_GET_CONST(uint16List_, vector<uint16_t>) };
    inline vector<uint16_t> uint16List() { DARABONBA_PTR_GET(uint16List_, vector<uint16_t>) };
    inline ComplexRequest& setUint16List(const vector<uint16_t> & uint16List) { DARABONBA_PTR_SET_VALUE(uint16List_, uint16List) };
    inline ComplexRequest& setUint16List(vector<uint16_t> && uint16List) { DARABONBA_PTR_SET_RVALUE(uint16List_, uint16List) };


    // u64 Field Functions 
    bool hasU64() const { return this->u64_ != nullptr;};
    void deleteU64() { this->u64_ = nullptr;};
    inline uint64_t u64() const { DARABONBA_PTR_GET_DEFAULT(u64_, 0L) };
    inline ComplexRequest& setU64(uint64_t u64) { DARABONBA_PTR_SET_VALUE(u64_, u64) };


    // u32 Field Functions 
    bool hasU32() const { return this->u32_ != nullptr;};
    void deleteU32() { this->u32_ = nullptr;};
    inline uint32_t u32() const { DARABONBA_PTR_GET_DEFAULT(u32_, 0) };
    inline ComplexRequest& setU32(uint32_t u32) { DARABONBA_PTR_SET_VALUE(u32_, u32) };


    // u16 Field Functions 
    bool hasU16() const { return this->u16_ != nullptr;};
    void deleteU16() { this->u16_ = nullptr;};
    inline uint16_t u16() const { DARABONBA_PTR_GET_DEFAULT(u16_, 0) };
    inline ComplexRequest& setU16(uint16_t u16) { DARABONBA_PTR_SET_VALUE(u16_, u16) };


    // obj Field Functions 
    bool hasObj() const { return this->obj_ != nullptr;};
    void deleteObj() { this->obj_ = nullptr;};
    inline const Darabonba::Json & obj() const { DARABONBA_PTR_GET_CONST(obj_, Darabonba::Json) };
    inline Darabonba::Json obj() { DARABONBA_PTR_GET(obj_, Darabonba::Json) };
    inline ComplexRequest& setObj(const Darabonba::Json & obj) { DARABONBA_PTR_SET_VALUE(obj_, obj) };
    inline ComplexRequest& setObj(Darabonba::Json && obj) { DARABONBA_PTR_SET_RVALUE(obj_, obj) };


    // any Field Functions 
    bool hasAny() const { return this->any_ != nullptr;};
    void deleteAny() { this->any_ = nullptr;};
    inline     const Darabonba::Json & any() const { DARABONBA_GET(any_) };
    Darabonba::Json & any() { DARABONBA_GET(any_) };
    inline ComplexRequest& setAny(const Darabonba::Json & any) { DARABONBA_SET_VALUE(any_, any) };
    inline ComplexRequest& setAny(Darabonba::Json && any) { DARABONBA_SET_RVALUE(any_, any) };


    // byt Field Functions 
    bool hasByt() const { return this->byt_ != nullptr;};
    void deleteByt() { this->byt_ = nullptr;};
    inline Darabonba::Bytes byt() const { DARABONBA_GET(byt_) };
    inline ComplexRequest& setByt(Darabonba::Bytes byt) { DARABONBA_SET_VALUE(byt_, byt) };


    // req Field Functions 
    bool hasReq() const { return this->req_ != nullptr;};
    void deleteReq() { this->req_ = nullptr;};
    inline const Darabonba::Http::Request & req() const { DARABONBA_PTR_GET_CONST(req_, Darabonba::Http::Request) };
    inline Darabonba::Http::Request req() { DARABONBA_PTR_GET(req_, Darabonba::Http::Request) };
    inline ComplexRequest& setReq(const Darabonba::Http::Request & req) { DARABONBA_PTR_SET_VALUE(req_, req) };
    inline ComplexRequest& setReq(Darabonba::Http::Request && req) { DARABONBA_PTR_SET_RVALUE(req_, req) };


    // resp Field Functions 
    bool hasResp() const { return this->resp_ != nullptr;};
    void deleteResp() { this->resp_ = nullptr;};
    inline const Darabonba::Http::MCurlResponse & resp() const { DARABONBA_PTR_GET_CONST(resp_, Darabonba::Http::MCurlResponse) };
    inline Darabonba::Http::MCurlResponse resp() { DARABONBA_PTR_GET(resp_, Darabonba::Http::MCurlResponse) };
    inline ComplexRequest& setResp(const Darabonba::Http::MCurlResponse & resp) { DARABONBA_PTR_SET_VALUE(resp_, resp) };
    inline ComplexRequest& setResp(Darabonba::Http::MCurlResponse && resp) { DARABONBA_PTR_SET_RVALUE(resp_, resp) };


    // map Field Functions 
    bool hasMap() const { return this->map_ != nullptr;};
    void deleteMap() { this->map_ = nullptr;};
    inline const map<string, string> & _map() const { DARABONBA_PTR_GET_CONST(map_, map<string, string>) };
    inline map<string, string> _map() { DARABONBA_PTR_GET(map_, map<string, string>) };
    inline ComplexRequest& setMap(const map<string, string> & _map) { DARABONBA_PTR_SET_VALUE(map_, _map) };
    inline ComplexRequest& setMap(map<string, string> && _map) { DARABONBA_PTR_SET_RVALUE(map_, _map) };


    // numMap Field Functions 
    bool hasNumMap() const { return this->numMap_ != nullptr;};
    void deleteNumMap() { this->numMap_ = nullptr;};
    inline const map<string, int64_t> & numMap() const { DARABONBA_PTR_GET_CONST(numMap_, map<string, int64_t>) };
    inline map<string, int64_t> numMap() { DARABONBA_PTR_GET(numMap_, map<string, int64_t>) };
    inline ComplexRequest& setNumMap(const map<string, int64_t> & numMap) { DARABONBA_PTR_SET_VALUE(numMap_, numMap) };
    inline ComplexRequest& setNumMap(map<string, int64_t> && numMap) { DARABONBA_PTR_SET_RVALUE(numMap_, numMap) };


    // modelMap Field Functions 
    bool hasModelMap() const { return this->modelMap_ != nullptr;};
    void deleteModelMap() { this->modelMap_ = nullptr;};
    inline const map<string, TestSource::Models::Request> & modelMap() const { DARABONBA_PTR_GET_CONST(modelMap_, map<string, TestSource::Models::Request>) };
    inline map<string, TestSource::Models::Request> modelMap() { DARABONBA_PTR_GET(modelMap_, map<string, TestSource::Models::Request>) };
    inline ComplexRequest& setModelMap(const map<string, TestSource::Models::Request> & modelMap) { DARABONBA_PTR_SET_VALUE(modelMap_, modelMap) };
    inline ComplexRequest& setModelMap(map<string, TestSource::Models::Request> && modelMap) { DARABONBA_PTR_SET_RVALUE(modelMap_, modelMap) };


    // request Field Functions 
    bool hasRequest() const { return this->request_ != nullptr;};
    void deleteRequest() { this->request_ = nullptr;};
    inline const TestSource::Models::Request & request() const { DARABONBA_PTR_GET_CONST(request_, TestSource::Models::Request) };
    inline TestSource::Models::Request request() { DARABONBA_PTR_GET(request_, TestSource::Models::Request) };
    inline ComplexRequest& setRequest(const TestSource::Models::Request & request) { DARABONBA_PTR_SET_VALUE(request_, request) };
    inline ComplexRequest& setRequest(TestSource::Models::Request && request) { DARABONBA_PTR_SET_RVALUE(request_, request) };


    // client Field Functions 
    bool hasClient() const { return this->client_ != nullptr;};
    void deleteClient() { this->client_ = nullptr;};
    inline shared_ptr<TestSource::Source> client() const { DARABONBA_GET(client_) };
    inline ComplexRequest& setClient(shared_ptr<TestSource::Source> client) { DARABONBA_SET_RVALUE(client_, client) };


    // instance Field Functions 
    bool hasInstance() const { return this->instance_ != nullptr;};
    void deleteInstance() { this->instance_ = nullptr;};
    inline const TestSource::Models::RequestInstance & instance() const { DARABONBA_PTR_GET_CONST(instance_, TestSource::Models::RequestInstance) };
    inline TestSource::Models::RequestInstance instance() { DARABONBA_PTR_GET(instance_, TestSource::Models::RequestInstance) };
    inline ComplexRequest& setInstance(const TestSource::Models::RequestInstance & instance) { DARABONBA_PTR_SET_VALUE(instance_, instance) };
    inline ComplexRequest& setInstance(TestSource::Models::RequestInstance && instance) { DARABONBA_PTR_SET_RVALUE(instance_, instance) };


    // from Field Functions 
    bool hasFrom() const { return this->from_ != nullptr;};
    void deleteFrom() { this->from_ = nullptr;};
    inline string from() const { DARABONBA_PTR_GET_DEFAULT(from_, "") };
    inline ComplexRequest& setFrom(string from) { DARABONBA_PTR_SET_VALUE(from_, from) };


    // self Field Functions 
    bool hasSelf() const { return this->self_ != nullptr;};
    void deleteSelf() { this->self_ = nullptr;};
    inline string self() const { DARABONBA_PTR_GET_DEFAULT(self_, "") };
    inline ComplexRequest& setSelf(string self) { DARABONBA_PTR_SET_VALUE(self_, self) };


    // print Field Functions 
    bool hasPrint() const { return this->print_ != nullptr;};
    void deletePrint() { this->print_ = nullptr;};
    inline string print() const { DARABONBA_PTR_GET_DEFAULT(print_, "") };
    inline ComplexRequest& setPrint(string print) { DARABONBA_PTR_SET_VALUE(print_, print) };


    // exec Field Functions 
    bool hasExec() const { return this->exec_ != nullptr;};
    void deleteExec() { this->exec_ = nullptr;};
    inline string exec() const { DARABONBA_PTR_GET_DEFAULT(exec_, "") };
    inline ComplexRequest& setExec(string exec) { DARABONBA_PTR_SET_VALUE(exec_, exec) };


    // str Field Functions 
    bool hasStr() const { return this->str_ != nullptr;};
    void deleteStr() { this->str_ = nullptr;};
    inline string str() const { DARABONBA_PTR_GET_DEFAULT(str_, "") };
    inline ComplexRequest& setStr(string str) { DARABONBA_PTR_SET_VALUE(str_, str) };


    // part Field Functions 
    bool hasPart() const { return this->part_ != nullptr;};
    void deletePart() { this->part_ = nullptr;};
    inline const vector<ComplexRequest::Part> & part() const { DARABONBA_PTR_GET_CONST(part_, vector<ComplexRequest::Part>) };
    inline vector<ComplexRequest::Part> part() { DARABONBA_PTR_GET(part_, vector<ComplexRequest::Part>) };
    inline ComplexRequest& setPart(const vector<ComplexRequest::Part> & part) { DARABONBA_PTR_SET_VALUE(part_, part) };
    inline ComplexRequest& setPart(vector<ComplexRequest::Part> && part) { DARABONBA_PTR_SET_RVALUE(part_, part) };


  protected:
    std::shared_ptr<string> accessKey_ = nullptr;
    // Body
    shared_ptr<Darabonba::IStream> body_ = nullptr;
    // Strs
    std::shared_ptr<vector<string>> strs_ = nullptr;
    // mapList
    std::shared_ptr<vector<Darabonba::Json>> mapList_ = nullptr;
    // header
    std::shared_ptr<ComplexRequest::Header> header_ = nullptr;
    std::shared_ptr<ComplexRequest::Configs> configs_ = nullptr;
    std::shared_ptr<int64_t> num_ = nullptr;
    std::shared_ptr<int64_t> i64_ = nullptr;
    std::shared_ptr<double> f64_ = nullptr;
    std::shared_ptr<bool> b_ = nullptr;
    std::shared_ptr<float> f32_ = nullptr;
    std::shared_ptr<vector<double>> f64List_ = nullptr;
    std::shared_ptr<vector<float>> floatList_ = nullptr;
    std::shared_ptr<vector<bool>> booleantList_ = nullptr;
    std::shared_ptr<int32_t> i32_ = nullptr;
    std::shared_ptr<vector<string>> stringList_ = nullptr;
    std::shared_ptr<vector<int32_t>> intList_ = nullptr;
    std::shared_ptr<vector<int32_t>> int32List_ = nullptr;
    std::shared_ptr<vector<int16>> int16List_ = nullptr;
    std::shared_ptr<vector<int64_t>> int64List_ = nullptr;
    std::shared_ptr<vector<int64_t>> longList_ = nullptr;
    std::shared_ptr<vector<uint64_t>> uint64List_ = nullptr;
    std::shared_ptr<vector<uint32_t>> uint32List_ = nullptr;
    std::shared_ptr<vector<uint16_t>> uint16List_ = nullptr;
    std::shared_ptr<uint64_t> u64_ = nullptr;
    std::shared_ptr<uint32_t> u32_ = nullptr;
    std::shared_ptr<uint16_t> u16_ = nullptr;
    std::shared_ptr<Darabonba::Json> obj_ = nullptr;
    Darabonba::Json any_ = nullptr;
    Darabonba::Bytes byt_ = nullptr;
    std::shared_ptr<Darabonba::Http::Request> req_ = nullptr;
    std::shared_ptr<Darabonba::Http::MCurlResponse> resp_ = nullptr;
    std::shared_ptr<map<string, string>> map_ = nullptr;
    std::shared_ptr<map<string, int64_t>> numMap_ = nullptr;
    std::shared_ptr<map<string, TestSource::Models::Request>> modelMap_ = nullptr;
    std::shared_ptr<TestSource::Models::Request> request_ = nullptr;
    std::shared_ptr<TestSource::Source> client_ = nullptr;
    std::shared_ptr<TestSource::Models::RequestInstance> instance_ = nullptr;
    // test keywords
    std::shared_ptr<string> from_ = nullptr;
    // test keywords
    std::shared_ptr<string> self_ = nullptr;
    // test keywords
    std::shared_ptr<string> print_ = nullptr;
    // test keywords
    std::shared_ptr<string> exec_ = nullptr;
    // test keywords
    std::shared_ptr<string> str_ = nullptr;
    // Part
    std::shared_ptr<vector<ComplexRequest::Part>> part_ = nullptr;
  };

  } // namespace Models
} // namespace Darabonba
#endif
