// $Header: /nfs/slac/g/glast/ground/cvs/xmlUtil/xmlUtil/id/DictVisitor.h,v 1.1 2001/06/12 18:34:01 jrb Exp $
#ifndef XMLUTIL_DICTVISITOR_H
#define XMLUTIL_DICTVISITOR_H

namespace xmlUtil {
  //! Pure virtual base class  for visitors to an id dictionary.
  class DictNode;
  class IdDict;
  class DictField;
  class DictFieldMan;

  class DictVisitor {
  public:
    virtual ~DictVisitor() {};
    virtual bool visitDict(IdDict *dict)=0;
    virtual bool visitNode(DictNode *node)=0;
    //    virtual bool visitField(DictField *field) {return false;}
    virtual bool visitField(DictField *field)=0;
    //    virtual bool visitFieldMan(DictFieldMan *fieldMan) {return false;}
    virtual bool visitFieldMan(DictFieldMan *fieldMan)=0;
  };
}
#endif
