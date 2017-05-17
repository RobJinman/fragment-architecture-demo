#ifndef __PROCALC_FRAGMENT_HPP__
#define __PROCALC_FRAGMENT_HPP__


#include <string>
#include <map>
#include <memory>


struct FragmentData {
  virtual ~FragmentData() = 0;
};


class FragmentSpec;
class Fragment;

typedef std::unique_ptr<Fragment> pFragment_t;

class Fragment {
  public:
    Fragment(const std::string& name, FragmentData& ownData);

    Fragment(const std::string& name, Fragment& parent,
      FragmentData& parentData, FragmentData& ownData);

    const std::string& name() const;
    virtual void rebuild(const FragmentSpec& spec);

    template<class T>
    T& parentData() {
      return dynamic_cast<T&>(*m_parentData);
    }

    template<class T>
    T& parent() {
      return dynamic_cast<T&>(*m_parent);
    }

    virtual ~Fragment() = 0;

  private:
    std::string m_name;
    Fragment* m_parent;
    FragmentData* m_parentData;
    FragmentData& m_ownData;

    std::map<std::string, pFragment_t> m_children;
};


#endif

