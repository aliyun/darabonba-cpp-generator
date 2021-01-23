// This file is auto-generated, don't edit it. Thanks.

#include <iostream>
#include <vector>

using namespace std;

vector<string> arrayData() {
  shared_ptr<vector<string>> configs = make_shared<vector<string>>(vector<string>({
    "a",
    "b",
    "c"
  }));
  return *configs;
}

string arrayAccess() {
  shared_ptr<vector<string>> configs = make_shared<vector<string>>(arrayData());
  shared_ptr<string> config = make_shared<string>((*configs)[[object Object]]);
  return *config;
}

string hello() {
  return arrayAccess();
}

int main(int argc, char *args[]) {
  args++;
  hello();
}

