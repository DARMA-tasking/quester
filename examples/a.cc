
#include <registry.h>
#include <cstdio>

struct A{};
struct B{};
struct C{};

struct Data {
  static Data construct() { return Data{}; }
};

struct MyTag{};

int main(int argc, char** argv) {
  using namespace registry;
  auto const ai = makeObjIdx<MyTag, Data, A>();
  auto const bi = makeObjIdx<MyTag, Data, B>();
  auto const ci = makeObjIdx<MyTag, Data, C>();

  printf("%zu %zu %zu\n", ai, bi, ci);

  return 0;
}
