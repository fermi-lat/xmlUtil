// $Header: /nfs/slac/g/glast/ground/cvs/xmlUtil/xmlUtil/id/IdConversion.h,v 1.2 2001/08/09 22:28:56 jrb Exp $

#ifndef XMLUTIL_IDCONVERSION_H
#define XMLUTIL_IDCONVERSION_H

#include "dom/DOM_Element.hpp"
#include "xmlUtil/id/NamedId.h"

namespace xmlUtil {
  class IdOperation;

  //! An /b IdConversion object (corresponding to an idConv element
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
    IdConversion(const DOM_Element); 

    ~IdConversion();

    //! Check that start of inputId fieldnames match path
    bool inDomain(NamedId& inputId);

    //! Convert the identifier if in domain; else return null.
    NamedId * convert(NamedId& inputId);
    // {return new NamedId(*inputId);};

  private:

    // Returns true if inputId satisfies condition
    bool satisfies(NamedId& inputId);

    //! Doesn't check that input is in domain.  Typically invoked
    //! from \b convert.
    NamedId * internalConvert(NamedId& inputId);

    //! Form path component from corresponding piece of xml
    void makePath(const DOM_Element& pathElt);

    //! Determine operation type and instantiate object of
    //! appropriate operation class.
    void buildOp(const DOM_Element& optElt);
    
    //! For now only condition recognized is \b hasField, which
    //! can be represented by a string: the field name.
    typedef std::string  Condition;   // may want more complicated
    //definition for Condition later

    //! Defines domain of conversion
    NameSeq *path;

    //! Given an identifier in domain, convert if \b condition is satisfied
    Condition *condition;

    //! \b op knows how to do a conversion
    IdOperation *op;
  };  // end of class IdConversion
}   // end of namespace
#endif
