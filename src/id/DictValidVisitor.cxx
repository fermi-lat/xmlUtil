// $Header: /nfs/slac/g/glast/ground/cvs/xmlUtil/src/id/DictValidVisitor.cxx,v 1.1 2001/06/12 18:35:42 jrb Exp $

#include "xmlUtil/id/DictValidVisitor.h"
#include "xmlUtil/id/DictNode.h"

namespace xmlUtil {

  bool DictValidVisitor::visitDict() {
    if (!m_dict) {
      m_state = eInvalid;
      return false;
    }
    return visitDict(m_dict);
  }

  bool DictValidVisitor::visitDict(IdDict* dict) {
    m_dict = dict;

    m_state = eValid;  // so far

    return true;
  }

  bool DictValidVisitor::visitNode(DictNode* node) {
    if (m_state != eValid) {
      m_state = eInvalid;
      return false;
    }
    if ((node->consistentChildren()) &&
        (node->consistentParent())   &&
        (node->consistentValues())     ) return true;

    m_state = eInvalid;
    return false;
  }

}  // end namespace
