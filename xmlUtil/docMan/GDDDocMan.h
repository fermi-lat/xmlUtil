// $Header: /nfs/slac/g/glast/ground/cvs/xmlUtil/xmlUtil/docMan/GDDDocMan.h,v 1.2 2001/11/09 21:05:58 jrb Exp $
#ifndef XMLUTIL_GDDDOCMAN_H
#define XMLUTIL_GDDDOCMAN_H

#include "xml/docMan/DocMan.h"
#include "xml/docMan/DocClient.h"
#include "xmlUtil/Substitute.h"

namespace xmlUtil {
  //! GDDDocMan knows about constants sections.  As part of construction
  //! it signs up an object it owns as a handler for <constants> so it 
  //! can do evaluation and substitution before any other clients see 
  //! the DOM
  class GDDDocMan : public xml::DocMan {
  public:
    static  GDDDocMan* getPointer();

    // Allow caller option of saving (or not) notes associated with constants 
    // docType should be gdd (should we even allow anything else?)
    virtual bool parse(const std::string& filename, 
                       bool saveNotes = true,
                       const std::string& docType=std::string("gdd"));

    virtual ~GDDDocMan() {delete m_constsClient;}

  protected:
    GDDDocMan::GDDDocMan();            // TO BE WRITTEN
    
    //! Nested class to do constansts handling; inherits from DocClient
    class ConstsClient : public xml::DocClient {
    public:
      virtual const std::string& getName() {
        return name;
      }
      ConstsClient(GDDDocMan *owner) : m_owner(owner), m_sub(0) {
        name=std::string("ConstsEvalSub");
        m_doc = 0;}
      virtual ~ConstsClient() {}

      void handleChild(DOM_Node elt);       /* TO BE WRITTEN */
      bool m_saveNotes;
    private:
      std::string name;
      GDDDocMan* m_owner;
      DOM_Document m_doc;
      Substitute* m_sub;
    };
    static GDDDocMan* m_me;
    ConstsClient* m_constsClient;
  };
}
#endif
