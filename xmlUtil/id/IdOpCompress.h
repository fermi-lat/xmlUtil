// $Header: /nfs/slac/g/glast/ground/cvs/xmlUtil/xmlUtil/id/IdOpCompress.h,v 1.2 2001/08/24 22:46:38 jrb Exp $

#ifndef XMLUTIL_IDOPCOMPRESS_H
#define XMLUTIL_IDOPCOMPRESS_H

#include <string>
#include "xmlUtil/id/IdOperation.h"


namespace xmlUtil {
  //! Compresses out all fields between "from" and "to", leaving the
  //! "from" and "to" fields themselves alone.
  class IdOpCompress : public IdOperation {
  public:
    IdOpCompress(DOM_Element cmprss);
    ~IdOpCompress() {}

    virtual NamedId * convert(const NamedId& inputId);
    virtual std::string myOp() const {return std::string("COMPRESS");}
  private:
    std::string from;
    std::string to;
  };
}
#endif
