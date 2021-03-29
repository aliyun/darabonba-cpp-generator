// This file is auto-generated, don't edit it. Thanks.

#include <darabonba/number.hpp>
#include <iostream>
#include <vector>

using namespace std;

using namespace Darabonba_Number;

void Darabonba_Number::Client::main(shared_ptr<vector<string>> args) {
  shared_ptr<string> a = make_shared<string>("123");
  shared_ptr<int> b = make_shared<int>(std::stoi(*a));
  shared_ptr<double> c = make_shared<double>(std::stod(*a));
  shared_ptr<double> d = make_shared<double>(std::stod(*a));
  shared_ptr<long> e = make_shared<long>(std::itol(*b));
  shared_ptr<long> f = make_shared<long>(std::stol(*a));
  shared_ptr<long> g = make_shared<long>(*e + *f);
  g = make_shared<long>(*e - *f);
  g = make_shared<long>(*e * *f);
  shared_ptr<double> z = make_shared<double>(*e / *f);
  shared_ptr<bool> h = make_shared<bool>(*e > *f);
  h = make_shared<bool>(*e >= *f);
  h = make_shared<bool>(*e < *f);
  h = make_shared<bool>(*e <= *f);
}

