// This file is auto-generated, don't edit it. Thanks.

#ifndef DARABONBA_IMPORT_H_
#define DARABONBA_IMPORT_H_

#include <darabonba/source.hpp>
#include <iostream>
#include <vector>

using namespace std;

namespace Darabonba_Import {
class Client {
public:
  shared_ptr<vector<string>> _id{};
  shared_ptr<string> _str{};
  explicit Client(shared_ptr<vector<string>> id, shared_ptr<string> str);
  static void Sample(shared_ptr<Darabonba_Source::Client> client);

  ~Client() {};
};
} // namespace Darabonba_Import

#endif
