// $Header$
#include "dom/DOM_Element.hpp"
#include "dom/DOMString.hpp"
#include "xml/Dom.h"
#include "xmlUtil/id/DictNode.h"
#include "xmlUtil/id/DictFieldMan.h"

namespace xmlUtil {
  DictNode::DictNode(DOM_Element elt, DictNode *parent,
                     DictFieldMan *fieldMan) : m_parent(parent) {
    // check it's a dictNode element
    if (!(elt.getTagName().equals("dictNode"))) {;} // big trouble
    
    // Field name stuff:
    std::string fName = 
      std::string(xml::Dom::transToChar(elt.getAttribute("fieldName")));
    
    m_field = fieldMan->find(fName);
    // Do something if it doesn't exist?? Shouldn't be terribly
    // necessary by ID/IDREF mechanism
    
    DOM_Element child = xml::Dom::getFirstChildElement(elt);
    if ((child.getTagName()).equals("pValues")) { // parent constraints
      DOM_Element gChild = xml::Dom::getFirstChildElement(child);
      m_parConstraints = new DictConstraints(gChild);
      
      // check for compatibility
      DictConstraints* fromParent = 0;
      if (parent->m_myConstraints) fromParent = (parent->m_myConstraints);
      else {
        fromParent = parent->m_field->getConstraints();
      }
      if (fromParent) {
        if (!fromParent->allowed(m_parConstraints)) {
          // make a fuss
        }
      }
      child = xml::Dom::getSiblingElement(child);
    }
    
    // Next up we might have our own constraint
    if (!(child.getTagName().equals("dictNode")) ) {
      m_myConstraints = new DictConstraints(child);
      
      // Check it's consistent with constraints on our own field,
      // if any
      if (!(m_field->getConstraints())->allowed(m_myConstraints)) {
        // make a fuss
      }
      child = xml::Dom::getSiblingElement(child);
    }
    
    // All that's left are child nodes, if any
    
    while (child != DOM_Element()) {
      DictNode *nextChild = new DictNode(child, this, fieldMan);
      
      m_children.push_back(nextChild);
      child = xml::Dom::getSiblingElement(child);
    }
    // Finally, how about checking for consistency among children?
    if (!consistent()) {
      // make a fuss
    }
  }
  
  // If 0 or 1 child, we're done.  Else all children must
  // have parent constraints, and they must define sets
  // such that for any pair, the sets are disjoint or
  // they are identical.  Now collect all nodes with identical
  // parent constraints and check their "personal" value constraints.
  // They must be disjoint.
  bool DictNode::consistent() {
    if (m_children.size() < 2) return true; // most common case
    
    // Either all children must have parent-value constraints or
    // none can.
    NodeIterator it = m_children.begin();
    bool childMode = ((*it)->m_parConstraints != 0);
    ++it;
    for (; it < m_children.end(); ++it) {
      if (((*it)->m_parConstraints != 0) != childMode) return false;
    }
    if (!childMode) { // no parent constraints
      return valuesDisjoint(m_children.begin(), m_children.end());
    }
    
    // Otherwise sort nodes by minValue of parent constraint
    POrder parOrder;
    sort(m_children.begin(), m_children.end(), parOrder);
    
    // Check that parent constraints are disjoint or identical
    for (it = m_children.begin(); (it + 1) != m_children.end(); ++it) {
      DictConstraints *par1 = (*it)->m_parConstraints;
      DictConstraints *par2 = (*(it + 1))->m_parConstraints;
      
      // if mins are equal, maxs must be also 
      if ((par1->getMin() == par2->getMin()) ) {
        if (par1->getMax() != par2->getMax())  return false;
      }  // else min of next must be > max of current
      else {
        if (par2->getMin() <= par1->getMax())  return false;
      }
    }
    
    // Finally need to check that child values are disjoint
    // within subcollection of nodes with same parent constraints
    it = m_children.begin();
    while (it  != m_children.end() ) {
      NodeIterator follow = it + 1;
      unsigned   ourMin = (*it)->m_parConstraints->getMin();
      
      while (follow != m_children.end()) {
        DictConstraints *par2 = (*follow)->m_parConstraints;
        
        if (par2->getMin() != ourMin) {
          --follow;
          break;
        }
        
      }
      // If we got here, it's time to check out a collection of children
      bool ok = valuesDisjoint(it, follow);
      if (!ok) return false;
      
      // Otherwise see if there is another bunch left
      it = ++follow;
    }
    return true;
  }

  
  bool DictNode::valuesDisjoint(NodeIterator start, NodeIterator last) {
    if (*start == *last) return true;
    
    NodeIterator pCurrentNode = start;
    std::set<unsigned> values;
    (*start)->insertValues(values);

    while (pCurrentNode != last) {

      ++pCurrentNode;
      
      // Make a new set containing values for current node
      std::set<unsigned> curValues;
      (*pCurrentNode)->insertValues(curValues);

      // See if it intersects accumulated values from previous nodes
      std::vector<unsigned> intersect;
      std::set_intersection(values.begin(), values.end(), curValues.begin(),
                            curValues.end(), intersect.begin());
      if (intersect.size() > 0) return false;
      
      // If not, continue to accumulate
      (*pCurrentNode)->insertValues(values);

    } 
    return true;
    
  }
  
  bool DictNode::allowed(const unsigned value) const {
    if (!m_myConstraints) return true;
    
    return m_myConstraints->allowed(value);
  }
  
  void DictNode::insertValues(std::set<unsigned>& aSet) {
    if (!m_myConstraints->m_valList) {
      for (unsigned i = m_myConstraints->m_minVal; 
           i <= m_myConstraints->m_maxVal;
           i++) {
        aSet.insert(i);
      }
    }
    else {
      DictValList *valList = m_myConstraints->m_valList;
      aSet.insert(valList->begin(), valList->end());
    }
    return;
  }
}                  // end namespace

