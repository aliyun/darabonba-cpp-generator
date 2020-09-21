// This file is auto-generated, don't edit it. Thanks.

#include <darabonba/map.hpp>
#include <darabonba/import.hpp>
#include <darabonba/source.hpp>
#include <iostream>
#include <map>

using namespace std;

Darabonba_Map::Client::Client(Darabonba_Source::Config *config) : Darabonba_Import::Client(config) {
  _endpointRule = new string("central");
  _endpointMap = new map<string, string>({
    {"ap-northeast-1", "cusanalytic.aliyuncs.com"},
    {"ap-south-1", "cusanalytic.aliyuncs.com"}
  });
  _endpointMap["ap-northeast-1"];
  _endpointMap.insert(pair<string, string>("ap-northeast-1", ""));
  _endpointMap.insert(pair<string, string>("test", "test"));
};

