//
// Author: Marwane Khsime 
// Date: 2017-02-04 19:55:57 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-02-04 19:55:57
//

#ifndef _C4514_HPP_
# define _C4514_HPP_

#include "AComponent.hpp"
#include "Gate.hpp"

class   C4514 : public AComponent {

 public:
// Constructor / Destructor
  C4514(const std::string &name);
  virtual ~C4514() { }

// Basics
  virtual nts::Tristate Compute(size_t pin_num_this = 1);
  virtual void  computeGates();
  virtual void SetLink(size_t pin_num_this, nts::IComponent &component,
                       size_t pin_num_target);
  virtual void Dump() const;

 private:

// Gates
  Gate  gate;
  std::map<size_t, std::pair<size_t, size_t> > gateLinks;

// Pin's Links
  std::map<size_t, std::pair<size_t, size_t> > links;

// Check if the index of the pin exist. return true if it's valid.
  bool            pinIndexIsValid(size_t pin_num_this);
  // Check if the component type match with the type expected by the pin.
  bool            doesComponentTypeMatch(AComponent &component, size_t first, size_t second);
// Check, when we are linking in the same component, if we are linking an
// Output to an Input.
  bool            doesPinsTypesMatch(size_t pin_num_this, size_t pin_num_target);

  void            initValuesOutputs();

  std::map<std::string, nts::Tristate> middleInputs;
  std::map<std::string, std::vector<int> > valOutputs;

};

#endif /* _C4514_HPP_ */