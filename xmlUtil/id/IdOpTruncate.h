// $Header: /nfs/slac/g/glast/ground/cvs/xmlUtil/xmlUtil/id/IdOpTruncate.h,v 1.2 2001/08/24 22:46:38 jrb Exp $

#ifndef XMLUTIL_IDOPTRUNCATE_H
#define XMLUTIL_IDOPTRUNCATE_H

#include <string>
#include "xmlUtil/id/IdOperation.h"


namespace xmlUtil {
  //! 
  class IdOpTruncate : public IdOperation {
  public:
    IdOpTruncate(DOM_Element trunc);
    ~IdOpTruncate() {}

    virtual NamedId * convert(const NamedId& inputId);
    virtual std::string myOp() const {return std::string("TRUNCATE");}
  private:
    std::string start;
    bool       beyond;
  };    
}
#endif
