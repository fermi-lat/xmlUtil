// $Header: /nfs/slac/g/glast/ground/cvs/xmlUtil/xmlUtil/id/IdOpTruncate.h,v 1.4 2004/01/21 06:49:31 jrb Exp $

#ifndef XMLUTIL_IDOPTRUNCATE_H
#define XMLUTIL_IDOPTRUNCATE_H

#include <string>
#include "xmlUtil/id/IdOperation.h"


namespace xmlUtil {
  //! 
  class IdOpTruncate : public IdOperation {
  public:
    IdOpTruncate(const XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* trunc);
    ~IdOpTruncate() {}

    virtual NamedId * convert(const NamedId& inputId);
    virtual std::string myOp() const {return std::string("TRUNCATE");}
  private:
    std::string start;
    bool       beyond;
  };    
}
#endif
