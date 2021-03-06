// $Header: /nfs/slac/g/glast/ground/cvs/xmlUtil/xmlUtil/Arith.h,v 1.9 2007/02/23 19:05:25 jrb Exp $
#ifndef XMLUTIL_ARITH_H 
#define XMLUTIL_ARITH_H

#include <string>
#include <xercesc/dom/DOMElement.hpp>
#include "xmlUtil/XmlUtilException.h"

namespace xmlUtil {
      
  using XERCES_CPP_NAMESPACE_QUALIFIER DOMElement;
  //! The Arith class handles the xml arithmetic elements, allowing
  //! derived constants to be computed and their values put into
  //! the DOM representation of the XML file.
  class Arith {
  public: 
    //! The different element types handled (evaluated) by this class

    Arith::Arith(DOMElement* elt = 0);
    //! Return a double, the result of performing all the operations
    //! indicated by the element and its children. 
    double evaluate();

    //! add "value" attribute into DOM. 
    /*! This is a no-op for all but const elements. */
    void   saveValue(); 

    //! Return scale factor due to units specification.  
    /*! For now only applies to lengths, which should be converted 
        to mm (always returns 1.0 for other kinds of constants)
    */
    static double getUnitsScale(const DOMElement* elt);
    ~Arith() {};

  private:
    enum  eTagType {
      ETAG_const = 0,
      ETAG_refer, 
      ETAG_add,
      ETAG_minus,
      ETAG_mul,
      ETAG_quo,
      ETAG_uminus,
      ETAG_max,
      ETAG_half,
      ETAG_sqrt,
      ETAG_sin,
      ETAG_cos,
      ETAG_tan,
      ETAG_asin,
      ETAG_acos,
      ETAG_atan,
      ETAG_n 
    } ;

    typedef std::string* ptrString;
    static ptrString *typeNames;
    static ptrString valString;   // pointer to std::string of  "value"
    static ptrString refToString; // ..and so forth
    static ptrString notesString;
    static ptrString lengthString;
    static ptrString cmString;
    static ptrString mString;


    double add();       /*< evaluate an \b add element */
    double minus();     /*< evaluate a \b minus element */
    double mul();       /*< evaluate a \b mul element */
    double quo();       /*< evalauate a \b quo element */
    double myMax();     /*< evaluate a \b max element */
    double sinElt();    /*< evaluate a \b sin element */
    double cosElt();    /*< evaluate a \b cos element */
    double tanElt();    /*< evaluate a \b tan element */
    double asinElt();    /*< evaluate an \b asin element */
    double acosElt();    /*< evaluate an \b acos element */
    double atanElt();    /*< evaluate an \b atan element */
    static void init();

    DOMElement*  m_elt; /*< element which may be evaluated */
    int     m_tag;      /*< element type (tagname) */
    double  m_number;   /*< value of element after evaluation */
    bool    m_evaluated;/*< flag to keep track of whether eval has been done*/

  };
  class BadTag : public XmlUtilException {
  public:
    BadTag(std::string reason = "") : XmlUtilException() {
      m_name = std::string("BadTag");
      makeMsg(reason);
    }
  };

}
#endif
