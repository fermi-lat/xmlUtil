// $Header: /nfs/slac/g/glast/ground/cvs/xmlUtil/src/eval.cxx,v 1.5 2003/03/15 01:06:37 jrb Exp $
/*! \file Standalone program to transform source xml file into a 
    preprocessed version suitable for most clients (documentation-type
    clients will probably stick with the original file). 
  
    In particular this program will
      - add a <source> element to the output, indicating how and
        from what the output was generated
      - convert any <prim> values not already expressed in standard
        units (mm) to the standard
      - substitute values for all references constants, evaluating
        such constants as needed
      - delete the <derived> element and all descendents from the
        output
 */

#include "xml/XmlParser.h"
#include "xml/Dom.h"
#include "xmlUtil/Arith.h"
#include "xmlUtil/Substitute.h"
#include "xmlUtil/Constants.h"
#include "xmlUtil/Source.h"
#include <xercesc/dom/DOM_Element.hpp>
#include <xercesc/dom/DOM_NodeList.hpp>
#include <xercesc/dom/DOM_DocumentType.hpp>

#include <string>
#include <iostream>
#include <fstream>

// openOut and outProlog can be found in src/local/outUtils.cxx
std::ostream *openOut(char * outfile);
void outProlog(const DOM_DocumentType& doctype, std::ostream& out);

const std::string myId("$Id: eval.cxx,v 1.5 2003/03/15 01:06:37 jrb Exp $");

/*!
    Main program for the eval application.
    \param arg1 is the input xml file
    \param arg2 is specification for the output file, or "-" to output
    to std::cout
*/
int main(int argc, char* argv[]) {
  std::ostream *out;
  if (argc < 3) {  // instructions
    std::cout << "Required first argument is xml file to be parsed" 
              << std::endl;
    std::cout << "Required second argument is output file (- for stdout)"
              << std::endl;
    exit(0);
  }

  xml::XmlParser* parser = new xml::XmlParser();
  DOM_Document doc = parser->parse(argv[1], "gdd");

  if (doc == 0) {
    std::cout << "Document failed to parse correctly" << std::endl;
    exit(0);
  }

  // Else successful.   Open output
  out = openOut(argv[2]);

  DOM_Element docElt = doc.getDocumentElement();
  DOM_DocumentType  doctype = doc.getDoctype(); //  check for gdd?? 

  // prim processing
  xmlUtil::Constants *constants = new xmlUtil::Constants(doc);
  constants->normalizePrimary();

  // No longer need the evaluate step since substitution will
  // evaluate any constant which has not yet been evaluated.

  // Search for all dimension and position references, substitute
  // value of referenced element.
  //  DOM_NodeList sections = docElt.getElementsByTagName(DOMString("section"));
  std::vector<DOM_Element> sections;
  xml::Dom::getChildrenByTagName(docElt, "section", sections);
  int nSec = sections.size();
  int iSec;

  xmlUtil::Substitute* sub = new xmlUtil::Substitute(doc);

  for (iSec = 0; iSec < nSec; iSec++) {
    int nSub;
    DOM_Element& secElt = sections[iSec];
    nSub = sub->execute(secElt);
    std::cout << "#elements substituted for in this section:  " << nSub
              << std::endl;
  }

  // In case there were no sections to substitute, do eval here
  constants->evalConstants();


  // Add a <source> child to the outer gdd element
  xmlUtil::Source *source = 
    new xmlUtil::Source(doc, "xmlUtil/v1/src/eval.exe", "$Id: eval.cxx,v 1.5 2003/03/15 01:06:37 jrb Exp $");
  source->add();
  
  // Output the xml declaration and all the text in the DOCTYPE (see DOMPrint)
  outProlog(doctype, *out);

  // Finally output the elements
  // May want option to exclude comments here
  xml::Dom::prettyPrintElement(docElt, *out, "");

  delete parser;
  return(0);
}







