// Remember adding -lvelocypack; linker library while compiling

#include "velocypack/vpack.h"
#include <iostream>

using namespace arangodb::velocypack;

int main () {
  // create an object with attributes "b", "a", "l" and "name"
  // note that the attribute names will be sorted in the target VPack object!
  Builder b;
  Builder b1;
  ValueType hey;
  // ValueType h = (ValueType)(int);

  b1(Value(ValueType::Object));
  b1.add("hey", Value(1.223));
  b1.close();

  // create an Object value...
  b(Value(ValueType::Object));
  b.add("foo", Value(42)); 
  b.add("bar", Value("some string value")); 
  b.add("qux", Value(true));
  b.add("fee", Value(13));
  b.close();

  Slice s(b.start());
  Slice s1(b1.start());
  ValueLength len;
  for (auto const& it : ObjectIterator(s)) {
    if( it.value.type() == ValueType::Int){
      Slice sl = it.value;
      std::cout << it.key.copyString() << ", value: " << std::to_string(sl.getInt()) << std::endl;
    }
  }
}
