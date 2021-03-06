// $Header: /nfs/slac/g/glast/ground/cvs/xmlUtil/src/id/IdOpCompress.cxx,v 1.4 2004/11/10 18:58:58 jrb Exp $

#include "xmlUtil/id/IdOpCompress.h"
#include "xmlBase/Dom.h"

namespace xmlUtil {
  IdOpCompress::IdOpCompress(const XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* cmprss)
  {
    from = xmlBase::Dom::getAttribute(cmprss, "from");
    to = xmlBase::Dom::getAttribute(cmprss, "to");
  }

  NamedId *IdOpCompress::convert(const NamedId& inputId) {

    int fromIx = inputId.hasField(from);
    int toIx = inputId.hasField(to);

    // For now if input id doesn't have "from" and "to" fields
    // in the proper order, return null pointer.  Another
    // possible response in this case would be to return a copy
    // of the input id.

    if (toIx < fromIx) return 0;
    if (fromIx < 0) return 0;

    NamedId *newId = new NamedId(inputId, fromIx + 1);

    NamedId::Fields *newFields = newId->m_fields;
    NamedId::Fields *inFields = inputId.m_fields;

    for (unsigned int ix = toIx; ix < inFields->size(); ix++ ) {
      NamedId::IdField * aField = new NamedId::IdField( *((*inFields)[ix]) );
      newFields->push_back(aField);
    }
    return newId;
  }
}
