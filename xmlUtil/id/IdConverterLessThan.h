// $Header: /nfs/slac/g/glast/ground/cvs/xmlUtil/xmlUtil/id/IdConverterLessThan.h,v 1.3 2001/09/20 21:19:12 jrb Exp $

#ifndef XMLUTIL_IDCONVERTERLESSTHAN_H
#define XMLUTIL_IDCONVERTERLESSTHAN_H

#include <functional>
#include "xmlUtil/id/IdConverter.h"

#include "xmlUtil/id/IdConversion.h"

namespace xmlUtil {
  /*! This class describes a function object satisfying the
      definition of Strict Weak Ordering (like < except that
        a <= b and b <= a does not imply a == b)
      so that it may be used by the STL \b sort algorithm
  */
  class IdConverterLessThan : 
    public std::binary_function<IdConverter::ConversionIt, 
    IdConverter::ConversionIt, bool> 
  {
  public:
    //! One conversion is "less than" another iff it has a
    //! shorter path
    bool operator()(IdConversion* x, 
                    IdConversion* y) {
      return ((x->m_path)->size() < ((y->m_path)->size() ) );
    }
  };
}

#endif
