// $Header: /nfs/slac/g/glast/ground/cvs/xmlUtil/xmlUtil/id/IdConversion.h,v 1.10 2003/03/15 01:08:00 jrb Exp $

#ifndef XMLUTIL_IDCONVERSION_H
#define XMLUTIL_IDCONVERSION_H

#include <xercesc/dom/DOMElement.hpp>
#include "xmlUtil/id/NamedId.h"
#include <functional>
#include <iostream>

namespace xmlUtil {
  class IdOperation;
  class IdConversion;
  std::ostream& operator<<(std::ostream& s, const IdConversion& convers);

  //! An \b IdConversion object (corresponding to an idConv element
  //! as defined in gdd.dtd) "has" 
  //!    a path  (list of id field names)
  //!    a condition
  //!    an operation to be performed on identifiers starting with
  //!       the specified path and satisfying the condition
  //!       and producing a new NamedId.
  class IdConversion {
  public:
    //! Default constructor produces a conversion which acts on any NamedId 
    //! and does nothing to it; that is, returns a copy.
    IdConversion();


    //! The usual case:  build a conversion from its XML description
    IdConversion(const XERCES_CPP_NAMESPACE_QUALIFIER DOMElement*); 

    ~IdConversion();

    friend std::ostream& operator<<(std::ostream& s, 
                                    const IdConversion& convers);

    //! Check that start of inputId fieldnames match path
    bool inDomain(const NamedId& inputId);

    //! Convert the identifier if in domain; else return null.
    NamedId * convert(const NamedId& inputId);
    // {return new NamedId(*inputId);};


    //! Return true if our path is subpath of \a other
    bool subpathOf(const IdConversion& other) const;

    friend class IdConverterLessThan;
  private:

    // Returns true if inputId satisfies condition
    bool satisfies(const NamedId& inputId);

    //! Doesn't check that input is in domain.  Typically invoked
    //! from \b convert.
    NamedId * internalConvert(const NamedId& inputId);

    //! Form path component from corresponding piece of xml
    void makePath(const XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* pathElt);

    //! Determine operation type and instantiate object of
    //! appropriate operation class.
    void buildOp(const XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* optElt);
    
    //! For now only condition recognized is \b hasField, which
    //! can be represented by a string: the field name.
    typedef std::string  Condition;   // may want more complicated
    //definition for Condition later

    //! Defines domain of conversion
    NameSeq *m_path;

    //! Given an identifier in domain, convert if \b condition is satisfied
    Condition *m_condition;

    //! \b op knows how to do a conversion
    IdOperation *m_op;
  };  // end of class IdConversion
}   // end of namespace
#endif
