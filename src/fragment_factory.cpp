#include <cassert>
#include <iostream>
#include "fragment_factory.hpp"
#include "fragments.hpp"


using std::string;


//===========================================
// constructFragment
//===========================================
Fragment* constructFragment(const string& name, Fragment& parent, FragmentData& parentData) {
  std::cout << "constructFragment(), name=" << name << "\n";

  if (name == "BFrag") return new BFrag(parent, parentData);
  if (name == "CFrag") return new CFrag(parent, parentData);
  if (name == "DFrag") return new DFrag(parent, parentData);

  assert(false);
}

