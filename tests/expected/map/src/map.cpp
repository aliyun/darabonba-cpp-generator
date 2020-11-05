// This file is auto-generated, don't edit it. Thanks.

#include <darabonba/map.hpp>
#include <darabonba/import.hpp>
#include <darabonba/source.hpp>
#include <iostream>
#include <map>

using namespace std;

using namespace Darabonba_Map;

Darabonba_Map::Client::Client(const shared_ptr<Darabonba_Source::Config>& config) : Darabonba_Import::Client(config) {
  _endpointRule = make_shared<string>("central");
  _endpointMap = make_shared<map<string, string>>(map<string, string>({
    {"ap-northeast-1", "cusanalytic.aliyuncs.com"},
    {"ap-south-1", "cusanalytic.aliyuncs.com"}
  })
);
  _endpointMap["ap-northeast-1"];
  _endpointMap.insert(pair<string, string>("ap-northeast-1", ""));
  _endpointMap.insert(pair<string, string>("test", "test"));
};

