// $Header: /nfs/slac/g/glast/ground/cvs/xmlUtil/src/id/Identifier.cxx,v 1.1 2002/01/03 21:09:12 jrb Exp $
#include "xmlUtil/id/Identifier.h"

#include <iterator>

namespace xmlUtil {

  // Nothing to do for now because, although we're formally a derived
  // class, haven't yet added anything to the base class implementation.
  Identifier::Identifier() {
    std::vector<unsigned int>();
  }
  Identifier::Identifier(unsigned n) :
    std::vector<unsigned int>(n) {
  }
  Identifier::Identifier(const Identifier& toCopy) :
    std::vector<unsigned int>(toCopy) {
  }
  void Identifier::append(const Identifier& toAppend) {
    std::copy(toAppend.begin(), toAppend.end(), std::back_inserter(*this));
  }
}
