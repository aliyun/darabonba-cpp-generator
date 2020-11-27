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
  explicit Client(const shared_ptr<vector<string>>& id, const shared_ptr<string>& str);
  static void Sample(shared_ptr<Darabonba_Source::Client> client);

  virtual ~Client() = default;
};
} // namespace Darabonba_Import

#endif
