#ifndef __FRAGMENTS_HPP__
#define __FRAGMENTS_HPP__


#include <string>
#include <iostream>
#include "fragment.hpp"
#include "fragment_spec.hpp"


struct BFragSpec : public FragmentSpec {
  BFragSpec()
    : FragmentSpec("BFrag", {}) {}

  std::string whizz = "hi";
  float bang = 1.23;
};

struct DFragSpec : public FragmentSpec {
  DFragSpec()
    : FragmentSpec("DFrag", {}) {}

  std::string fruit = "apple";
  double weight = 5.987;
};

struct CFragSpec : public FragmentSpec {
  CFragSpec()
    : FragmentSpec("CFrag", {&dFragSpec}) {}

  DFragSpec dFragSpec;

  int baz = 5;
  float pop = 1.23;
};

struct AFragSpec : public FragmentSpec {
  AFragSpec()
    : FragmentSpec("AFrag", {&bFragSpec, &cFragSpec}) {}

  BFragSpec bFragSpec;
  CFragSpec cFragSpec;

  int foo = 5;
  float bar = 1.23;
};

struct AFragData : public FragmentData {
  int int1 = 12;
  float float1 = 12.34;
  int int2 = 123;
};

class AFrag : public Fragment {
  public:
    AFrag()
      : Fragment("AFrag", m_data) {}

    void foo() {
      std::cout << "AFrag::foo()\n";
    }

    virtual void rebuild(const FragmentSpec& spec_) override {
      Fragment::rebuild(spec_);

      AFragSpec spec = dynamic_cast<const AFragSpec&>(spec_);
      std::cout << "AFrag:rebuild()\n";
      std::cout << "int1=" << m_data.int1 << ", int2=" << m_data.int2 << ", float1=" << m_data.float1 << "\n";
    }

  private:
    AFragData m_data;
};

struct BFragData : public FragmentData {
  int int1 = 21;
  float float1 = 22.3;
  int int2 = 234;
};

class BFrag : public Fragment {
  public:
    BFrag(Fragment& parent, FragmentData& parentData)
      : Fragment("BFrag", parent, parentData, m_data) {}

    virtual void rebuild(const FragmentSpec& spec_) override {
      Fragment::rebuild(spec_);

      BFragSpec spec = dynamic_cast<const BFragSpec&>(spec_);
      std::cout << "BFrag:rebuild()\n";
      std::cout << "int1=" << m_data.int1 << ", int2=" << m_data.int2 << ", float1=" << m_data.float1 << "\n";

      AFragData& aFragData = parentData<AFragData>();
      std::cout << "AFragData: int1=" << aFragData.int1 << ", int2=" << aFragData.int2 << ", float1=" << aFragData.float1 << "\n";

      AFrag& aFrag = parent<AFrag>();
      aFrag.foo();
    }

  private:
    BFragData m_data;
};

struct CFragData : public FragmentData {
  int int1 = 34;
  float float1 = 34.56;
  int int2 = 321;
};

class CFrag : public Fragment {
  public:
    CFrag(Fragment& parent, FragmentData& parentData)
      : Fragment("CFrag", parent, parentData, m_data) {}

    void foo() {
      std::cout << "CFrag::foo()\n";
    }

    virtual void rebuild(const FragmentSpec& spec_) override {
      Fragment::rebuild(spec_);

      CFragSpec spec = dynamic_cast<const CFragSpec&>(spec_);
      std::cout << "CFrag:rebuild()\n";
      std::cout << "int1=" << m_data.int1 << ", int2=" << m_data.int2 << ", float1=" << m_data.float1 << "\n";

      AFragData& aFragData = parentData<AFragData>();
      std::cout << "AFragData: int1=" << aFragData.int1 << ", int2=" << aFragData.int2 << ", float1=" << aFragData.float1 << "\n";

      AFrag& aFrag = parent<AFrag>();
      aFrag.foo();
    }

  private:
    CFragData m_data;
};

struct DFragData : public FragmentData {
  int int1 = 45;
  float float1 = 45.67;
  int int2 = 432;
};

class DFrag : public Fragment {
  public:
    DFrag(Fragment& parent, FragmentData& parentData)
      : Fragment("DFrag", parent, parentData, m_data) {}

    virtual void rebuild(const FragmentSpec& spec_) override {
      Fragment::rebuild(spec_);

      DFragSpec spec = dynamic_cast<const DFragSpec&>(spec_);
      std::cout << "DFrag:rebuild()\n";
      std::cout << "int1=" << m_data.int1 << ", int2=" << m_data.int2 << ", float1=" << m_data.float1 << "\n";

      CFragData& cFragData = parentData<CFragData>();
      std::cout << "CFragData: int1=" << cFragData.int1 << ", int2=" << cFragData.int2 << ", float1=" << cFragData.float1 << "\n";

      CFrag& cFrag = parent<CFrag>();
      cFrag.foo();
    }

  private:
    DFragData m_data;
};


#endif
