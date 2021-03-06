// $Header: /nfs/slac/g/glast/ground/cvs/GlastRelease-scons/xmlUtil/xmlUtil/id/DictFieldMan.h,v 1.7 2012/01/11 19:01:43 jrb Exp $

#ifndef XMLUTIL_DICTFIELDMAN_H
#define XMLUTIL_DICTFIELDMAN_H

#include <string>
#include <cstring>
// hash_map is causing more trouble than it's worth, so just use map
// everywhere
#include <map>
#include <cstring>

#include "xmlUtil/id/DictObject.h"

namespace xmlUtil {
  //! Keep track of the collection of fields which may be referenced
  //! in a particular IdDict
  class DictField;
  class DictVisitor;


  struct ltstr {
    bool operator()(const char* s1, const char* s2) const
    {
      return strcmp(s1, s2) < 0;
    }
  };
  typedef std::map<const char *, DictField*, ltstr> Registry;

  class DictFieldMan : public DictObject {
  public:

    DictFieldMan(int size = 0);
    ~DictFieldMan();


    bool accept(DictVisitor* vis);
    void signup(DictField *field);
    const DictField * const find(const std::string& name) const;

  private:
    // Mechanism for keeping track of the fields is a 
    // pair-associative container with key = name and 
    // value = pointer to the DictField object
    Registry *m_reg;

  };
}
#endif
