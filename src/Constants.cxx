// $Header: /nfs/slac/g/glast/ground/cvs/xmlUtil/src/Constants.cxx,v 1.1.1.1 2001/03/30 00:03:31 jrb Exp $

#include <string>
#include "dom/DOMString.hpp"
#include "dom/DOM_Node.hpp"
#include "dom/DOM_NodeList.hpp"
#include "dom/DOM_TreeWalker.hpp"
#include "xmlUtil/Constants.h"
#include "xmlUtil/Arith.h"
#include "xml/Dom.h"


namespace {
  // Put a local utility in the unnamed namespace

/* For each <prim>
    if it's of type "length"
     if units are not "mm" then convert to "mm"

   For diagnostics, digits in return value are calculated as follows:
           1's place  -- was a <prim>
        1000 place  -- was a length
       10000 place  -- required conversion
      100000 place  -- unknown unit; couldn't convert
*/

  int normPrim(DOM_Element elt) {
    int ret = 0;
    if (!(elt.getNodeName()).equals(DOMString("prim"))) return ret;
    
    ret += 1;
    // Found a prim, but we don't have to convert since it's not a length
    if (!(elt.getAttribute(DOMString("uType"))).equals("length")) return ret;
    
    ret += 1000;
    DOMString uLength = DOMString("unitLength");
    
    DOMString units = elt.getAttribute(uLength);
    if (units.equals(DOMString("mm"))) return ret;
    
    double scale, value;
    DOMString valueString = DOMString("value");
    if (units.equals(DOMString("cm"))) {
      ret += 10000;
      scale = 10;
    }
    else if (units.equals(DOMString("m"))) {
      ret += 10000;
      scale = 1000;
    }
    else return (100000 + ret);          // should never happen
    
    value = atof(xml::Dom::transToChar(elt.getAttribute(valueString)));
    value *= scale;
    xml::Dom::addAttribute(elt, valueString, value);
    elt.setAttribute(uLength, DOMString("mm"));
    
    return ret;
  }
}

namespace xmlUtil {

  Constants::Constants(DOM_Document doc) : m_doc(doc) {
    DOM_NodeList list = m_doc.getElementsByTagName("constants");

    m_constants = (list.getLength() > 0) ? 
       static_cast<const DOM_Element &> (list.item(0)) : DOM_Element();
  }

  void Constants::normalizePrimary()
  {
    // find <primary>
    if (m_constants == DOM_Node()) return;

    DOM_NodeList primarys = m_constants.getElementsByTagName("primary");

    // must be precisely one <primary> element
    DOM_Node curNode = primarys.item(0);
    DOM_Element primary = static_cast<DOM_Element &>(curNode);
    if (primary.getAttribute("normalized").equals(DOMString("true"))) return;

    // Make a DOMTreeWalker which returns only elements
    unsigned long whatToShow = 1 << (DOM_Node::ELEMENT_NODE -1);
    
    DOM_TreeWalker walker = 
      m_doc.createTreeWalker(curNode, whatToShow, 0, 0);
    
    // Diagnostic -- number of <prim>s seen
    int count = 0;
    while (curNode != DOM_Node() ) {
      count += normPrim(static_cast<DOM_Element &> (curNode));
      curNode = walker.nextNode();
    }
    primary.setAttribute("normalized", "true");
    //    std::cout << "Results of normalizePrim: " << count << std::endl;
    //    return (count < 100000);
  }
 
  // Remove children of evaluated constants
  void Constants::pruneConstants(bool keepNotes) { 
    //  DOM_Element tmp;
    DOM_Element curConst;
    
    // For each derCategory, prune each const child
    DOM_NodeList cats = m_constants.getElementsByTagName("derCategory");
    int nCats = cats.getLength();
    int iCat;
    
    for (iCat = 0; iCat < nCats; iCat++) {
      DOM_Node catNode = cats.item(iCat);
      DOM_Element& curCat = static_cast<DOM_Element&> (catNode);
      curConst = xml::Dom::findFirstChildByName(curCat, "const" );
      
      while (curConst != DOM_Element()) {
        if (keepNotes) { // tread more carefully
          DOM_Element child = xml::Dom::getFirstChildElement(curConst);
          if (child != DOM_Element() ) {
            if ((child.getTagName()).equals(DOMString("notes"))) {
              child = xml::Dom::getSiblingElement(child);
              if (child != DOM_Element()) {
                xml::Dom::prune(child);
                (child.getParentNode()).removeChild(child);
              }
            }
            else {
              xml::Dom::prune(curConst);  // remove all its children
            }
          }
        }
        else {  // remove all its children
          xml::Dom::prune(curConst);  
        }
        curConst = xml::Dom::getSiblingElement(curConst);
      }
    }
  }

  /*! For each derCategory, evaluate each const child, writing
      value back to "value" attribute in the DOM */
  void Constants::evalConstants() {
  DOM_Element derived = 
    xml::Dom::findFirstChildByName(m_constants, "derived");  
  if ((derived.getAttribute("evaluated")).equals(DOMString("true"))) return;

  DOM_Element curConst;

  DOM_NodeList cats = m_doc.getElementsByTagName("derCategory");
  int nCats = cats.getLength();
  int iCat;
  
  for (iCat = 0; iCat < nCats; iCat++) {
    DOM_Node catNode = cats.item(iCat);
    DOM_Element& curCat = static_cast<DOM_Element&> (catNode); 
    curConst = xml::Dom::findFirstChildByName(curCat, "const" );

    while (curConst != DOM_Element()) {
      Arith curArith(curConst);
      double evalValue = curArith.evaluate();
      curArith.saveValue();
      
      curConst = xml::Dom::getSiblingElement(curConst);
    }
  }
  derived.setAttribute("evaluated", "true");
}


}

