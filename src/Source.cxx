// $Header: /nfs/slac/g/glast/ground/cvs/xmlUtil/src/Source.cxx,v 1.4 2003/03/15 01:06:37 jrb Exp $

#include "xmlUtil/Source.h"
#include <xercesc/dom/DOMString.hpp>
#include <xercesc/dom/DOM_Text.hpp>
#include "xml/Dom.h"


namespace { 
  // private utility to strip off $ 
  char * stripDollar(char* toStrip) {
    const char dollar = '$';
    
    char   nothing = 0;
    unsigned len = strlen(toStrip);
    
    if (dollar == toStrip[len - 1]) {
      len--;
      toStrip[len] = nothing;
    }
    if (dollar == toStrip[0]) {
      return (toStrip + 1);
    }
    return toStrip;
  }
}      // end of blank namespace

namespace xmlUtil {
  Source::Source(DOM_Document doc, const char * creator,
      const char* creatorCVSID) : m_doc(doc), m_creator(creator)  {
    
    char * tmp = new char[strlen(creatorCVSID) + 1];
    strcpy(tmp, creatorCVSID);
    m_myCVSID = std::string(stripDollar(tmp));
    delete [] tmp;
  }

  void Source::add(DOM_Element parentArg) {
    static char * unknownId = "unidentified input file";
    DOM_Element docElt = m_doc.getDocumentElement();
    DOM_Element parent = parentArg;
    if (parent == DOM_Element()) {
      parent = docElt;
    }

    DOM_Element source = m_doc.createElement("source");

    // Document element should have a CVSid attribute
    std::string idAtt = xml::Dom::getAttribute(docElt, "CVSid");

    char * strippedRaw;
    char * myRaw = 0;

    unsigned int len = idAtt.size();
    if (len > 0 ) {
      const char * raw = idAtt.c_str();
      myRaw = new char[len + 1];
      strcpy(myRaw, raw);
      strippedRaw = stripDollar(myRaw);
    }
    else strippedRaw = unknownId;

    xml::Dom::addAttribute(source, "inputId", std::string(strippedRaw));

    // Already have creator ID as std::string
    xml::Dom::addAttribute(source, "creatorId", m_myCVSID);
    
    std::string theText = 
      std::string("Do not edit! This file automatically created by ");
    theText.append(m_creator);
    DOM_Text    sourceText = m_doc.createTextNode(theText.c_str()); 


    source.appendChild(sourceText);

    if (myRaw) delete [] myRaw;
    // Finally need to insert this node as the first child of specified elt
    parent.insertBefore(source, parent.getFirstChild());
  }
}
