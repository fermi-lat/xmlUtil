// $Header: /nfs/slac/g/glast/ground/cvs/xmlUtil/xmlUtil/id/DictFieldMan.h,v 1.4 2001/06/12 19:57:06 jrb Exp $

#ifndef XMLUTIL_DICTFIELDMAN_H
#define XMLUTIL_DICTFIELDMAN_H

#include <string>
#ifdef __GNUG__
# if (__GNUC__ >= 3 )
#   include <ext/hash_map>
# else
#   include <hash_map>
# endif

#else
#include <map>
#endif

#include "xmlUtil/id/DictObject.h"

namespace xmlUtil {
  //! Keep track of the collection of fields which may be referenced
  //! in a particular IdDict
  class DictField;
  class DictVisitor;


#ifdef __GNUG__
  struct eqstr {
    bool operator()(const char* s1, const char* s2) const
    {
      return strcmp(s1, s2) == 0;
    }
  };
  typedef std::hash_map<const char *, DictField*, std::hash<const char *>, eqstr> 
  Registry;
#else
  struct ltstr {
    bool operator()(const char* s1, const char* s2) const
    {
      return strcmp(s1, s2) < 0;
    }
  };
  typedef std::map<const char *, DictField*, ltstr> Registry;
#endif

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
