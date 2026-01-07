#include <darabonba/Core.hpp>
#include <darabonba/test.hpp>
#include <darabonba/encode/Encoder.hpp>
#include <darabonba/Bytes.hpp>
#include <darabonba/Date.hpp>
#include <darabonba/File.hpp>
#include <darabonba/http/Form.hpp>
#include <darabonba/Logger.hpp>
#include <map>
#include <darabonba/Number.hpp>
#include <cmath>
#include <darabonba/Stream.hpp>
#include <darabonba/http/URL.hpp>
#include <darabonba/XML.hpp>
#include <darabonba/Convert.hpp>
using namespace std;
using json = nlohmann::json;
using DaraLogger = Darabonba::Logger;
namespace Darabonba
{

void Client::arrayTest(const vector<string> &args) {
  if ((args.size() > 0) && Darabonba::Array::contains(args, "cn-hanghzou")) {
    int32_t index = Darabonba::Array::index(args, "cn-hanghzou");
    string regionId = args[index];
    string all = Darabonba::Array::join(args, ",");
    string first = args->shift();
    string last = args->pop();
    int32_t length1 = args->unshift(first);
    int32_t length2 = args->push(last);
    int32_t length3 = length1 + length2;
    string longStr = "long" + first + last;
    string fullStr = Darabonba::Array::join(args, ",");
    vector<string> newArr = vector<string>()
      .push_back("test");
    vector<string> cArr = newArr->concat(args);
    vector<string> acsArr = Darabonba::Array::acsSort(newArr);
    vector<string> descArr = Darabonba::Array::descSort(newArr);
    vector<string> llArr = acsArr->concat(descArr);
    llArr.insert(llArr.begin() + 10, "test");
    llArr.erase(std::remove(llArr.begin(), llArr.end(), "test"), llArr.end());
  }

}

void Client::bytesTest(const vector<string> &args) {
  string fullStr = Darabonba::Array::join(args, ",");
  Darabonba::Bytes data = Darabonba::BytesUtil::toBytes(fullStr);
  string newFullStr = Darabonba::Encode::Encoder::toString(data);
  if (fullStr != newFullStr) {
    return ;
  }

  string hexStr = Darabonba::Encode::Encoder::hexEncode(data);
  string base64Str = Darabonba::Encode::Encoder::base64EncodeToString(data);
  int32_t length = data.size();
  string obj = Darabonba::Encode::Encoder::toString(data);
  Darabonba::Bytes data2 = Darabonba::BytesUtil::from(fullStr, "base64");
}

void Client::dateTest(const vector<string> &args) {
  shared_ptr<Darabonba::Date> date = make_shared<Darabonba::Date>("2023-09-12 17:47:31.916000 +0800 UTC");
  string dateStr = date->format("YYYY-MM-DD HH:mm:ss");
  int32_t timestamp = date->unix();
  shared_ptr<Darabonba::Date> yesterday = date->sub("day", 1);
  int32_t oneDay = date->diff("day", yesterday);
  shared_ptr<Darabonba::Date> tomorrow = date->add("day", 1);
  int32_t twoDay = tomorrow->diff("day", date) + oneDay;
  int32_t hour = date->hour();
  int32_t minute = date->minute();
  int32_t second = date->second();
  int32_t dayOfMonth = date->dayOfMonth();
  int32_t dayOfWeek = date->dayOfWeek();
  int32_t weekOfYear = date->weekOfYear();
  int32_t month = date->month();
  int32_t year = date->year();
  shared_ptr<Darabonba::Date> utcDate = date->UTC();
}

void Client::envTest(const vector<string> &args) {
  string es = std::getenv("TEST");
  void ma = Darabonba::Env::setEnv("TEST", es + "test");
}

void Client::fileTest(const vector<string> &args) {
  if (Darabonba::File::exists("/tmp/test")) {
    shared_ptr<Darabonba::File> file = make_shared<Darabonba::File>("/tmp/test");
    string path = file->path();
    int32_t length = file->length() + 10;
    shared_ptr<Darabonba::Date> createTime = file->createTime();
    shared_ptr<Darabonba::Date> modifyTime = file->modifyTime();
    int32_t timeLong = modifyTime->diff("minute", createTime);
    Darabonba::Bytes data = file->read(300);
    file->write(Darabonba::BytesUtil::from("test", "utf8"));
    shared_ptr<Darabonba::IStream> rs = Darabonba::File::createReadStream("/tmp/test");
    shared_ptr<Darabonba::OStream> ws = Darabonba::File::createWriteStream("/tmp/test");
  }

}

void Client::formTest(const vector<string> &args) {
  json m = json({
    {"key1" , "test1"},
    {"key2" , "test2"},
    {"key3" , 3},
    {"key4" , json({
      {"key5" , 123},
      {"key6" , "321"}
    })}
  });
  string form = Darabonba::Http::Form::toFormString(m);
  form = form + "&key7=23233&key8=" + Darabonba::Http::Form::getBoundary();
  shared_ptr<Darabonba::IStream> r = Darabonba::Http::Form::toFileForm(m, Darabonba::Http::Form::getBoundary());
}

void Client::jsonTest(const vector<string> &args) {
  json m = json({
    {"key1" , "test1"},
    {"key2" , "test2"},
    {"key3" , 3},
    {"key4" , json({
      {"key5" , 123},
      {"key6" , "321"}
    })}
  });
  string ms = m.dump();
  Darabonba::Json ma = json::parse(ms);
  string arrStr = "[1,2,3,4]";
  Darabonba::Json arr = json::parse(arrStr);
}

void Client::logerTest(const vector<string> &args) {
  DaraLogger::log("test");
  DaraLogger::info("test");
  DaraLogger::warning("test");
  DaraLogger::debug("test");
  DaraLogger::error("test");
}

void Client::mapTestCase(const vector<string> &args) {
  map<string, string> mapTest = json({
    {"key1" , "value1"},
    {"key2" , "value2"},
    {"key3" , "value3"}
  }).get<map<string, string>>();
  int32_t length = mapTest.size();
  int32_t num = length + 3;
  vector<string> keys = Darabonba::Map::keySet(mapTest);
  string allKey = "";
  for (string key : keys) {
    allKey = allKey + key;
  }
  vector<pair<string,string>> entries = Darabonba::Map::entries(mapTest);
  string newKey = "";
  string newValue = "";
  for (pair<string,string> e : entries) {
    newKey = newKey + e.first;
    newValue = newValue + e.second;
  }
  string json = Darabonba::JSON::stringify(mapTest);
  map<string, string> mapTest2 = json({
    {"key1" , "value4"},
    {"key4" , "value5"}
  }).get<map<string, string>>();
  json mapTest3 = Darabonba::CORE::merge(mapTest , mapTest2);
  if (mapTest3.at("key1") == "value4") {
    return ;
  }

}

void Client::numberTest(const vector<string> &args) {
  float num = 3.2f;
  int32_t inum = Darabonba::Number::parseInt(num);
  int64_t lnum = Darabonba::Number::parseLong(num);
  float fnum = Darabonba::Number::parseFloat(num);
  double dnum = Darabonba::Number::parseDouble(num);
  inum = Darabonba::Number::parseInt(inum);
  lnum = Darabonba::Number::parseLong(inum);
  fnum = Darabonba::Number::parseFloat(inum);
  dnum = Darabonba::Number::parseDouble(inum);
  inum = Darabonba::Number::parseInt(lnum);
  lnum = Darabonba::Number::parseLong(lnum);
  fnum = Darabonba::Number::parseFloat(lnum);
  dnum = Darabonba::Number::parseDouble(lnum);
  inum = Darabonba::Number::parseInt(fnum);
  lnum = Darabonba::Number::parseLong(fnum);
  fnum = Darabonba::Number::parseFloat(fnum);
  dnum = Darabonba::Number::parseDouble(fnum);
  inum = Darabonba::Number::parseInt(dnum);
  lnum = Darabonba::Number::parseLong(dnum);
  fnum = Darabonba::Number::parseFloat(dnum);
  dnum = Darabonba::Number::parseDouble(dnum);
  lnum = Darabonba::Number::itol(inum);
  inum = Darabonba::Number::ltoi(lnum);
  double randomNum = Darabonba::Number::random();
  inum = std::floor(inum);
  inum = std::round(inum);
}

void Client::streamTest(const vector<string> &args) {
  if (Darabonba::File::exists("/tmp/test")) {
    shared_ptr<Darabonba::IStream> rs = Darabonba::File::createReadStream("/tmp/test");
    shared_ptr<Darabonba::OStream> ws = Darabonba::File::createWriteStream("/tmp/test");
    Darabonba::Bytes data = rs->read(30);
    ws->write(data);
    rs->pipe(ws);
    data = Darabonba::Stream::readAsBytes(rs);
    Darabonba::Json obj = Darabonba::Stream::readAsJSON(rs);
    string jsonStr = Darabonba::Stream::readAsString(rs);
  }

}

void Client::stringTest(const vector<string> &args) {
  string fullStr = Darabonba::Array::join(args, ",");
  args = Darabonba::String::split(fullStr, ",");
  if ((fullStr.size() > 0) && Darabonba::String::contains(fullStr, "hangzhou")) {
    string newStr1 = Darabonba::String::replace(fullStr, "/hangzhou/g", "beijing");
  }

  if (Darabonba::String::hasPrefix(fullStr, "cn")) {
    string newStr2 = Darabonba::String::replace(fullStr, "/cn/gi", "zh");
  }

  if (Darabonba::String::hasPrefix(fullStr, "beijing")) {
    string newStr3 = Darabonba::String::replace(fullStr, "/beijing/", "chengdu");
  }

  int32_t start = Darabonba::String::index(fullStr, "beijing");
  int32_t end = start + 7;
  string region = Darabonba::String::subString(fullStr, start);
  string lowerRegion = Darabonba::String::toLower(region);
  string upperRegion = Darabonba::String::toUpper(region);
  if (region == "beijing") {
    region = region + " ";
    region = Darabonba::String::trim(region);
  }

  Darabonba::Bytes tb = Darabonba::BytesUtil::toBytes(fullStr);
  string em = "xxx";
  if (em.empty()) {
    return ;
  }

  string num = "32.0a";
  int32_t inum = std::stoi(num) + 3;
  int64_t lnum = std::stol(num);
  float fnum = std::stof(num) + 1f;
  double dnum = std::stod(num) + 1;
}

void Client::urlTest(const vector<string> &args) {
  shared_ptr<Darabonba::Http::URL> url = make_shared<Darabonba::Http::URL>(args.at(0));
  string path = url->path();
  string pathname = url->pathname();
  string protocol = url->protocol();
  string hostname = url->hostname();
  string port = url->port();
  string host = url->host();
  string hash = url->hash();
  string search = url->search();
  string href = url->href();
  string auth = url->auth();
  shared_ptr<Darabonba::Http::URL> url2 = Darabonba::Http::URL::parse(args.at(1));
  path = url2->path();
  string newUrl = Darabonba::Http::URL::urlEncode(args.at(2));
  string newSearch = Darabonba::Encode::Encoder::percentEncode(search);
  string newPath = Darabonba::Http::URL::pathEncode(pathname);
  string all = "test" + path + protocol + hostname + hash + search + href + auth + newUrl + newSearch + newPath;
}

void Client::xmlTest(const vector<string> &args) {
  json m = json({
    {"key1" , "test1"},
    {"key2" , "test2"},
    {"key3" , 3},
    {"key4" , json({
      {"key5" , 123},
      {"key6" , "321"}
    })}
  });
  string xml = Darabonba::XML::toXML(m);
  xml = xml + "<key7>132</key7>";
  json respMap = Darabonba::XML::parseXml(xml, nullptr);
}

Darabonba::Json Client::returnAny() {}

void Client::main(const vector<string> &args) {
  Client::arrayTest(args);
  Client::bytesTest(args);
  Client::dateTest(args);
  Client::envTest(args);
  Client::fileTest(args);
  Client::formTest(args);
  Client::logerTest(args);
  Client::mapTestCase(args);
  Client::numberTest(args);
  Client::streamTest(args);
  Client::stringTest(args);
  Client::urlTest(args);
  Client::xmlTest(args);
  int32_t a = Darabonba::Convert::integerVal(args.at(0)) + 10;
  string b = Darabonba::Convert::stringVal(a) + args.at(1) + Darabonba::Convert::stringVal(Client::returnAny());
  int64_t c = Darabonba::Convert::int64Val(b) + Darabonba::Convert::int64Val(a) + Darabonba::Convert::int64Val(Client::returnAny());
  int8_t d = Darabonba::Convert::int8Val(b) + Darabonba::Convert::int8Val(a) + Darabonba::Convert::int8Val(Client::returnAny());
  int16 e = Darabonba::Convert::int16Val(b) + Darabonba::Convert::int16Val(a) + Darabonba::Convert::int16Val(Client::returnAny());
  int32_t f = Darabonba::Convert::int32Val(b) + Darabonba::Convert::int32Val(a) + Darabonba::Convert::int32Val(Client::returnAny());
  int64_t g = Darabonba::Convert::int64Val(b) + Darabonba::Convert::int64Val(a) + Darabonba::Convert::int64Val(Client::returnAny());
  int64_t h = Darabonba::Convert::longVal(b) + Darabonba::Convert::longVal(a) + Darabonba::Convert::longVal(Client::returnAny());
  ulong i = Darabonba::Convert::ulongVal(b) + Darabonba::Convert::ulongVal(a) + Darabonba::Convert::ulongVal(Client::returnAny());
  uint8 j = Darabonba::Convert::uint8Val(b) + Darabonba::Convert::uint8Val(a) + Darabonba::Convert::uint8Val(Client::returnAny());
  uint16_t k = Darabonba::Convert::uint16Val(b) + Darabonba::Convert::uint16Val(a) + Darabonba::Convert::uint16Val(Client::returnAny());
  uint32_t l = Darabonba::Convert::uint32Val(b) + Darabonba::Convert::uint32Val(a) + Darabonba::Convert::uint32Val(Client::returnAny());
  uint64_t m = Darabonba::Convert::uint64Val(b) + Darabonba::Convert::uint64Val(a) + Darabonba::Convert::uint64Val(Client::returnAny());
  float n = Darabonba::Convert::floatVal(b) + Darabonba::Convert::floatVal(a) + Darabonba::Convert::floatVal(Client::returnAny());
  double o = Darabonba::Convert::doubleVal(b) + Darabonba::Convert::doubleVal(a) + Darabonba::Convert::doubleVal(Client::returnAny());
  if (Darabonba::Convert::boolVal(args.at(2))) {
    Darabonba::Bytes data = Darabonba::BytesUtil::toBytes(Client::returnAny());
    int32_t length = data.size();
    Darabonba::Json test = json(data);
    map<string, string> maps = json({
      {"key" , "value"}
    }).get<map<string, string>>();
    json obj = json(maps);
    shared_ptr<Darabonba::OStream> ws = Darabonba::Stream::toWritable(obj);
    shared_ptr<Darabonba::IStream> rs = Darabonba::Stream::toReadable(maps);
    data = rs->read(30);
    if (!Darabonba::isNull(data)) {
      ws->write(data);
    }

  }

  Darabonba::sleep(a);
  string defaultVal = Darabonba::Convert::stringVal(Darabonba::defaultVal(args.at(0), args.at(1)));
  if (defaultVal == b) {
    return ;
  }

}
} // namespace Darabonba