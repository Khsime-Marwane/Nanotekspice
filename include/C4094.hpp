//
// Author: Marwane Khsime 
// Date: 2017-02-04 19:55:57 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-02-04 19:55:57
//

#ifndef _C4094_HPP_
# define _C4094_HPP_

#include "AComponent.hpp"
namespace nts
{
  class   C4094 : public nts::AComponent {

   public:
// Constructor / Destructor
    C4094(const std::string &name);
    virtual ~C4094() { }

// Basics
    virtual nts::Tristate Compute(size_t pin_num_this = 1);
    virtual void computeGates();

   private:
// Pins Order
    std::map<size_t, size_t>  outputPins;
    bool            first;

    void            reset();
  };
}
#endif /* _C4094_HPP_ */