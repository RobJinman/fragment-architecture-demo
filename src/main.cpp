#include <iostream>
#include "fragment_spec.hpp"
#include "fragments.hpp"


int main() {
  AFragSpec aFragSpec;
  aFragSpec.setEnabled(true);
  aFragSpec.foo = 1;
  aFragSpec.bar = 12.3;
  aFragSpec.bFragSpec.setEnabled(true);
  aFragSpec.bFragSpec.whizz = "Hello, World!";
  aFragSpec.bFragSpec.bang = 99.9;
  aFragSpec.cFragSpec.setEnabled(true);
  aFragSpec.cFragSpec.baz = 100;
  aFragSpec.cFragSpec.pop = 3.14;
  aFragSpec.cFragSpec.dFragSpec.setEnabled(true);
  aFragSpec.cFragSpec.dFragSpec.fruit = "banana";
  aFragSpec.cFragSpec.dFragSpec.weight = 672.9812;

  std::cout << aFragSpec.foo << "\n";
  std::cout << aFragSpec.bar << "\n";

  const BFragSpec& bFragSpec = dynamic_cast<const BFragSpec&>(aFragSpec.spec("BFrag"));
  std::cout << bFragSpec.whizz << "\n";
  std::cout << bFragSpec.bang << "\n";

  const CFragSpec& cFragSpec = dynamic_cast<const CFragSpec&>(aFragSpec.spec("CFrag"));
  std::cout << cFragSpec.baz << "\n";
  std::cout << cFragSpec.pop << "\n";

  const DFragSpec& dFragSpec = dynamic_cast<const DFragSpec&>(cFragSpec.spec("DFrag"));
  std::cout << dFragSpec.fruit << "\n";
  std::cout << dFragSpec.weight << "\n";

  AFrag aFrag;
  aFrag.rebuild(aFragSpec);

  return 0;
}
