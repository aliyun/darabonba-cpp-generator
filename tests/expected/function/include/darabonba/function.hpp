// This file is auto-generated, don't edit it. Thanks.

#ifndef DARABONBA_FUNCTION_H_
#define DARABONBA_FUNCTION_H_

#include <iostream>
#include <map>
#include <vector>

using namespace std;

namespace Darabonba_Function {
class Client {
public:
  static void hello();
  static map<string, string> helloMap();
  static vector<map<string, string>> helloArrayMap();
  static void helloParams(shared_ptr<string> a, shared_ptr<string> b);
  static void helloInterface();

  Client() {};
  virtual ~Client() = default;
};
} // namespace Darabonba_Function

#endif
