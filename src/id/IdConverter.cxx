// $Header: /nfs/slac/g/glast/ground/cvs/xmlUtil/src/id/IdConverter.cxx,v 1.10 2004/11/10 18:58:58 jrb Exp $

#include "xmlUtil/id/IdConversion.h"
#include "xmlUtil/id/IdConverter.h"
#include "xmlUtil/id/IdDictMan.h"
#include "xmlUtil/id/IdDict.h"
#include <xercesc/dom/DOMElement.hpp>
#include "xmlBase/Dom.h"
#include <algorithm>
#include "xmlUtil/id/IdConverterLessThan.h"

namespace xmlUtil {
XERCES_CPP_NAMESPACE_USE
  IdDictMan * IdConverter::dictMan = 0;

  IdConverter::IdConverter(DOMElement* elt) : m_consistent(UNKNOWN),
  m_sorted(NO) {
    if (!dictMan) dictMan = IdDictMan::getPointer();

    // An idConverter element may optionally have as first child
    // a constants element, but we're assuming that the XML document
    // has already had constants evaluation and substitution done
    // on it, if necessary.
    // Assume that any constant evaluations and substitutions have
    // already been dealt with 
    DOMElement* child = xmlBase::Dom::getFirstChildElement(elt);

    if ( xmlBase::Dom::getTagName(child) == std::string("constants") ) { // move on
      child = xmlBase::Dom::getSiblingElement(child);
    }
    while (xmlBase::Dom::getTagName(child) == std::string("idDict") )  {
      IdDict* dict = new IdDict(child);
      dictMan->registerDict(dict);
      child = xmlBase::Dom::getSiblingElement(child);
    }

    // Now that all id dictionaries we need should have been defined,
    // handle attributes
    std::string dictName = xmlBase::Dom::getAttribute(elt, "fromDict");
    if (dictName.size() > 0 ) {  // then it's not just an empty string
      inputDictName = new std::string(dictName);
      inputDict = dictMan->findDict(dictName);
    }
    dictName = xmlBase::Dom::getAttribute(elt, "toDict");
    if (dictName.size() > 0 ) {
      outputDictName = new std::string(dictName);
      outputDict = dictMan->findDict(dictName);
    }

    // All remaining elements should be idConv
    while (child != 0 ) {
      IdConversion *conv = new IdConversion(child);
      m_convCol.push_back(conv);
      child = xmlBase::Dom::getSiblingElement(child);
    }

    // check for consistency before unleashing this object
    isConsistent();
  }

  IdConverter::~IdConverter() {
    m_convCol.clear();
  }

  // Sort by path length
  void IdConverter::sortConvs() {
    if (m_sorted != YES) {
      ConversionIt start = m_convCol.begin(), last = m_convCol.end();
      IdConverterLessThan weakOrder;
      std::sort(start, last, weakOrder);  // sort them
      m_sorted = YES;
    }
  }

  bool IdConverter::isConsistent() {
    if (m_consistent == UNKNOWN) {
      sortConvs();
      // Check whether a path is a subsequence of some other path,
      // unfortunately an o(n**2) procedure
      unsigned int ix, jx;
      for (ix = 0; ix < (m_convCol.size() - 1); ix++ ) {
        for (jx = ix + 1; jx < (m_convCol.size()); jx++) {
          // Since conversions are ordered by size, only need
          // to check whether ix-th path is subpath of jx-th,
          // not the reverse
          if (m_convCol[ix]->subpathOf(*(m_convCol[jx]))) {
            m_consistent = NO;
            return false;
          }
        }
      }
      m_consistent = YES;
    }
    return m_consistent==YES;
  }

  NamedId *IdConverter::convert(const NamedId *in) const {
    unsigned int ix;

    if (m_consistent == NO) return 0;

    // Based on path, find appropriate conversion, if any
    for (ix = 0; ix < m_convCol.size(); ix++) {
      if ((m_convCol[ix])->inDomain(*in)) {  // convert
        return (m_convCol[ix]->convert(*in));
      }
    }
    //       else return copy of input  
    return new NamedId(*in);
  }


  Identifier *IdConverter::convert(const Identifier *inIdent) const {
    if (!inputDict) return 0;  // can't get names without dictionary

    if (m_consistent == NO) return 0;

    NamedId *inNamed = inputDict->getNamedId(*inIdent);
    if (inNamed == 0) return 0;

    NamedId *outNamed = convert(inNamed);
    
    Identifier *converted = outNamed->stripNames();
    delete inNamed;
    delete outNamed;
    return converted;
  }

  std::ostream& IdConverter::displayConversions(std::ostream& s) {
    Conversions::const_iterator it = m_convCol.begin();

    while (it != m_convCol.end() ) {
      s << (**it) << std::endl;
      ++it;
    }
    return s;
  }
}

