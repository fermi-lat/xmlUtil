
// $Header: /nfs/slac/g/glast/ground/cvs/xmlUtil/xmlUtil/docMan/GDDDocMan.h,v 1.3 2004/01/09 00:56:42 jrb Exp $
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
    const std::string& getCVSid() const;
    const std::string& getDTDversion() const;

    virtual ~GDDDocMan() {delete m_constsClient;}

  protected:
    GDDDocMan::GDDDocMan();            // TO BE WRITTEN
    
    //! Nested class to do constansts handling; inherits from DocClient
    class ConstsClient : public xml::DocClient {
    public:
      virtual const std::string& getName() {
        return name;
      }
      ConstsClient(GDDDocMan *owner) : m_owner(owner), m_sub(0),
                                       CVSid(std::string("")),
                                       DTDversion(std::string(""))
      {
        name=std::string("ConstsEvalSub");
        m_doc = 0;
      }

      virtual ~ConstsClient() {}

      void handleChild(DOM_Node elt); 
      bool m_saveNotes;
      const std::string& getCVSid() const {return CVSid;}
      const std::string& getDTDversion() const {return DTDversion;}
    private:
      std::string name;
      GDDDocMan* m_owner;
      DOM_Document m_doc;
      Substitute* m_sub;
      std::string CVSid;
      std::string DTDversion;
    };
    static GDDDocMan* m_me;
    ConstsClient* m_constsClient;
  };
}
#endif
