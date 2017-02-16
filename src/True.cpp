//
// True.cpp for True in
// /home/marwane/Projets/Epitech/CPP/cpp_nanotekspice/src/
//
// Made by Marwane Khsime
// Login   <marwane.khsime@epitech.eu@epitech.eu>
//
// Started on  Wed Feb  1 10:36:45 2017 Marwane Khsime
// Last update Thu Feb  2 04:19:35 2017 Marwane
//

#include "True.hpp"

// TODO: Ajouter les exit (catch std::exception)
True::True(const std::string &name) : AComponent(name, "true") {

  this->_value = nts::Tristate::TRUE;
  this->pins[0] = NULL;
  this->links.first = 0;
  this->links.second = 0;
}

True::~True() {}

nts::Tristate True::Compute(size_t pin_num_this) {
  if (pin_num_this != 1) {
    throw Error("ERROR : [True COMPONENT | COMPUTING] : pin does not exist.\n");
  }
  return this->_value;
}

void True::Dump() const {
    std::cout << "[True COMPONENT] | Value : " << this->_value << std::endl;
}

void  True::SetTristate(size_t pin_num_this, nts::Tristate _value) {
  // Impossible to change the value of a True component
  (void)_value;
  (void)pin_num_this;
}

void True::SetLink(size_t pin_num_this, nts::IComponent &component,
                     size_t pin_num_target) {

  if (pin_num_this != 1) {
    throw Error("ERROR : [True COMPONENT | LINK] : pin does not exist.\n");
  }

  if (!this->pins[0]) {
    this->links.first = pin_num_this;
    this->links.second = pin_num_target;
    this->pins[0] = &component;
    try {
      this->pins[0]->SetLink(this->links.second, *this, this->links.first);
    } catch (const std::exception& err) {
      throw err;
    }
  }
}

int main() {
  return 0;
}