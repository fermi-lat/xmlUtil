// $Header: /nfs/slac/g/glast/ground/cvs/xmlUtil/xmlUtil/id/IdOpCompress.h,v 1.4 2004/01/21 06:49:31 jrb Exp $

#ifndef XMLUTIL_IDOPCOMPRESS_H
#define XMLUTIL_IDOPCOMPRESS_H

#include <string>
#include "xmlUtil/id/IdOperation.h"


namespace xmlUtil {
  //! Compresses out all fields between "from" and "to", leaving the
  //! "from" and "to" fields themselves alone.
  class IdOpCompress : public IdOperation {
  public:
    IdOpCompress(const XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* cmprss);
    ~IdOpCompress() {}

    virtual NamedId * convert(const NamedId& inputId);
    virtual std::string myOp() const {return std::string("COMPRESS");}
  private:
    std::string from;
    std::string to;
  };
}
#endif
