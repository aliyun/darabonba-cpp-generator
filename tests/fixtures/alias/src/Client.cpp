#include <darabonba/Core.hpp>
#include <darabonba/test.hpp>
#include <darabonba/import.hpp>
#include <darabonba/srouce.hpp>
#include <darabonba/alias.hpp>
#include <darabonba/alias/source.hpp>
#include <darabonba/alias/symbol.hpp>
using namespace std;
using namespace Alias;
using json = nlohmann::json;
using ImportClient = Import::Client;
using SourceClient = Source::Client;
using namespace AliasSymbol::Models;
using AliasSymbolClient = AliasSymbol::Client;
using AliasSourceSourceClient = AliasSource::SourceClient;
namespace Darabonba
{

void Client::emptyModel() {
  ImportClient::test();
  SourceClient::test();
  AliasClient::test();
  AliasSourceSourceClient::test();
  AliasSymbolClient::test();
  TestModel model = TestModel();
}
} // namespace Darabonba