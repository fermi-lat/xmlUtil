// $Header: /nfs/slac/g/glast/ground/cvs/xmlUtil/xmlUtil/id/IdOpDisappear.h,v 1.2 2001/08/24 22:46:38 jrb Exp $

#ifndef XMLUTIL_IDOPDISAPPEAR_H
#define XMLUTIL_IDOPDISAPPEAR_H

#include "xmlUtil/id/IdOperation.h"

namespace xmlUtil {
  //! Simplest possible operation, taking any id to one of zero length.
  //! Don't return 0 because that is used to indicate that conversion 
  //! isn't possible for some reason.  
  /* A better approach might be to throw an exception in the latter case 
     and let convert return 0 . */
  class IdOpDisappear : public IdOperation {
  public:
    IdOpDisappear(DOM_Element) {}
    ~IdOpDisappear() {}
    NamedId * convert(const NamedId& inputId) {return new NamedId();}
    virtual std::string myOp() const {return std::string("DISAPPEAR ");}
  };
}    


#endif

