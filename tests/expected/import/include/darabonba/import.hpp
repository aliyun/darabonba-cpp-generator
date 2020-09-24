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
  vector<string> *_id{};
  string *_str{};
  explicit Client(vector<string> *id, string *str);
  static void Sample(Darabonba_Source::Client *client);

  ~Client() {
    delete _id;
    _id = nullptr;
    delete _str;
    _str = nullptr;
  };
};
} // namespace Darabonba_Import

#endif
