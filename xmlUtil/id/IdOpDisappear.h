// $Header: /nfs/slac/g/glast/ground/cvs/xmlUtil/xmlUtil/id/IdOpDisappear.h,v 1.1 2001/08/09 22:28:56 jrb Exp $

#ifndef XMLUTIL_IDOPDISAPPEAR_H
#define XMLUTIL_IDOPDISAPPEAR_H

#include "xmlUtil/id/IdOperation.h"

namespace xmlUtil {
  //! Simplest possible operation, taking any id to null
  class IdOpDisappear : public IdOperation {
  public:
    IdOpDisappear(DOM_Element) {}
    ~IdOpDisappear() {}
    NamedId * convert(const NamedId& inputId) {return 0;}
  };
}    


#endif

