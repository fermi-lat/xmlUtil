// $Header: /nfs/slac/g/glast/ground/cvs/xmlUtil/src/id/DictFieldMan.cxx,v 1.6 2003/03/15 01:07:38 jrb Exp $

#include "xmlUtil/id/DictFieldMan.h"
#include "xmlUtil/id/DictField.h"
#include <utility> 
#include <algorithm>


namespace xmlUtil {
  typedef std::pair<const char *, DictField*> RegPair;

  typedef Registry::iterator RegIterator;

  DictFieldMan::DictFieldMan(int /* size */) {
    m_reg = new Registry();
  }

  DictFieldMan::~DictFieldMan() {
    // All other objects containing references to the fields 
    // (e.g., DictNodes) should have been deleted already.

    // Get rid of all fields...
    for (RegIterator it = m_reg->begin(); it != m_reg->end(); ++it) {
      delete it->second;
    }
    m_reg->clear();
    
      // then delete registry
    delete m_reg;
  }
  
  void DictFieldMan::signup(DictField *field)  {
    m_reg->insert(RegPair((field->getName()).c_str(), field));
  }

  const DictField* const DictFieldMan::find(const std::string& name) const {
    // find returns an iterator over the hash map, so a pointer
    // to a pair<std::string, DictField *>
    Registry::iterator  found;
    found = m_reg->find(name.c_str());
    if (found != m_reg->end() ) {
      return (*found).second;
    }
    else return 0;
      
      // *(reg->find(name));
  }

  bool DictFieldMan::accept(DictVisitor *vis) {
    // iterate through fields
    
    for (Registry::iterator it = m_reg->begin(); it != m_reg->end(); ++it) {
      bool ok = ( (it->second)->accept(vis) );
      if (!ok) return false;
    }
    return vis->visitFieldMan(this);

  }

}   // end namespace
