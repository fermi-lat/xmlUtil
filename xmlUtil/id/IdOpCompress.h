// $Header: /nfs/slac/g/glast/ground/cvs/xmlUtil/xmlUtil/id/IdOpCompress.h,v 1.3 2001/09/25 21:43:06 jrb Exp $

#ifndef XMLUTIL_IDOPCOMPRESS_H
#define XMLUTIL_IDOPCOMPRESS_H

#include <string>
#include "xmlUtil/id/IdOperation.h"


namespace xmlUtil {
  //! Compresses out all fields between "from" and "to", leaving the
  //! "from" and "to" fields themselves alone.
  class IdOpCompress : public IdOperation {
  public:
    IdOpCompress(DomElement cmprss);
    ~IdOpCompress() {}

    virtual NamedId * convert(const NamedId& inputId);
    virtual std::string myOp() const {return std::string("COMPRESS");}
  private:
    std::string from;
    std::string to;
  };
}
#endif
