// $Header: /nfs/slac/g/glast/ground/cvs/xmlUtil/xmlUtil/id/IdConverter.h,v 1.3 2001/08/24 22:46:38 jrb Exp $

#ifndef XMLUTIL_IDCONVERTER_H
#define XMLUTIL_IDCONVERTER_H
#include "xmlUtil/id/NamedId.h"
#include "dom/DOM_Element.hpp"
#include <string>
#include <vector>

namespace xmlUtil {
  class IdDict;
  class IdConversion;
  class IdDictMan;

  class IdConverter {
  public:
    /*! Build IdConverter from its XML representation.
        Assume that the containing document has already been "normalized"
        in the sense that constants evaluation and substitution has
        been done.
    */
    IdConverter(DOM_Element elt);
    ~IdConverter();

    /*  Wait on implementing this one.
    // Return image of the input dictionary under the conversions
    // defined in the IdConverter object.
    //  \arg \b inDict: the input dictionary
        \arg \b status: report on success of conversion, validity of
             output dictionary (and hence of IdConverter object).
        Note the collection of conversions making up a converter must
        act on disjoint domains, which is identical to the restriction
        that no conversion have a path which is a subset of another
        converter's path.

    IdDict *convert(const IdDict const *inDict, unsigned *status) const;
    */

    //! Return the result of converting a single NamedId
    NamedId * convert(const NamedId *in) const;

    //! Return the result of converting a single Identifier.
    /*! Can only do this if there is an input IdDict so that
        the IdDict can be asked for the NamedId corresponding
        to the Identifier */
    Identifier *convert(const Identifier *inIdent) const;

    /*! Check that conversions comprising the converter have disjoint
        domains.  This is equivalent to checking that no conversion
        has a path which is an initial subsequence of the path for
        another conversion.  */
    bool isConsistent();

    // Better idea would be to make this a real class rather than
    // a typedef to hide implementation.
    // Might choose a different container for the conversions, for
    // example a tree, ordered by input path on which a conversion
    // operates
    typedef std::vector<IdConversion*>  Conversions; 
    typedef Conversions::iterator       ConversionIt;

  private:
    // Should inputDict be optional or required?
    std::string *inputDictName;
    IdDict *inputDict; /*< Input IdDict.   */

    // What about outputDict?
    std::string *outputDictName;
    IdDict *outputDict;

    // IdDictMan is a singleton
    static IdDictMan *dictMan;

    /*! It's convenient to have the conversions sorted by length of
      path when checking for consistency. */
    void sortConvs();


    Conversions convCol;  /*< collection of conversion operations making up the                          IdConverter */

    //! Define strict weak ordering so that we can sort (see IdConverter class)

    enum STATES {
      UNKNOWN = -1,
      NO = 0,
      YES = 1};

    STATES consistent; 
    STATES sorted;      // (sort into order of increasing path)

  };  // end class IdConverter

}  // end namespace
#endif
