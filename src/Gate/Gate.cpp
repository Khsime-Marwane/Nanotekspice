#include "Gate.hpp"

Gate::Gate()
{
  this->tmpQ = nts::Tristate::UNDEFINED;
  this->tmpQ2 = nts::Tristate::UNDEFINED;

  // Create the map of functions. It's useful to call properly the associated function of the type
  // sent as parameter to the compute function.
  this->basiComputes["AND"] = std::bind(&Gate::computeAND, this, std::placeholders::_1, std::placeholders::_2);
  this->basiComputes["OR"] = std::bind(&Gate::computeOR, this, std::placeholders::_1, std::placeholders::_2);
  this->basiComputes["XOR"] = std::bind(&Gate::computeXOR, this, std::placeholders::_1, std::placeholders::_2);
  this->basiComputes["NAND"] = std::bind(&Gate::computeAND, this, std::placeholders::_1, std::placeholders::_2);
  this->basiComputes["NOR"] = std::bind(&Gate::computeOR, this, std::placeholders::_1, std::placeholders::_2);
  this->basiComputes["XNOR"] = std::bind(&Gate::computeXOR, this, std::placeholders::_1, std::placeholders::_2);
  this->basiComputes["LATCH"] = std::bind(&Gate::computeLATCH, this, std::placeholders::_1, std::placeholders::_2);

  this->AdvanceComputes["SUM"] = std::bind(&Gate::computeSUM, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
  this->AdvanceComputes["SUMC"] = std::bind(&Gate::computeSUMC, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
  this->AdvanceComputes["AND"] = std::bind(&Gate::computeAND2, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
  this->AdvanceComputes["NAND"] = std::bind(&Gate::computeAND2, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

}

/*
** The compute function takes as parameter the type of the door which we want to use,
** and the values of the inputs. In the case of the door NO, the second value is set
** to undefined because we don't use it. If among the values needed, one or more is
** UNDEFINED, or if the _type is unknown, it return UNDEFINED.
*/
nts::Tristate Gate::compute(std::string _type, nts::Tristate v1, nts::Tristate v2, nts::Tristate v3)
{
  this->_not = (_type == "NAND" || _type == "NOR" || _type == "XNOR") ? true : false;

  if (_type == "NOT" && v1 != nts::Tristate::UNDEFINED)
    return (computeNO(v1));
  if ((v1 == nts::Tristate::UNDEFINED) || (v2 == nts::Tristate::UNDEFINED))
    return (nts::Tristate::UNDEFINED);
  if (basiComputes.find(_type) != basiComputes.end() && (v1 != nts::Tristate::UNDEFINED && v2 != nts::Tristate::UNDEFINED && v3 == nts::Tristate::UNDEFINED))
    return (basiComputes.find(_type)->second(v1, v2));
  if (AdvanceComputes.find(_type) != AdvanceComputes.end() && (v1 != nts::Tristate::UNDEFINED && v2 != nts::Tristate::UNDEFINED && v3 != nts::Tristate::UNDEFINED))
    return (AdvanceComputes.find(_type)->second(v1, v2, v3));
  return (nts::Tristate::UNDEFINED);
}

/*
**   a | b | s
** +-----------
** | 0 | 0 | 0
** | 0 | 1 | 0
** | 1 | 0 | 0
** | 1 | 1 | 1
*/
nts::Tristate Gate::computeAND(nts::Tristate v1, nts::Tristate v2)
{
  if (_not)
    return ((nts::Tristate)(!(v1 && v2)));
  return ((nts::Tristate)(v1 && v2));
}

nts::Tristate Gate::computeAND2(nts::Tristate v1, nts::Tristate v2, nts::Tristate v3)
{
  if (_not)
    return ((nts::Tristate)(!(v1 && v2 && v3)));
  return ((nts::Tristate)(v1 && v2 && v3));
}

/*
**   a | b | s
** +-----------
** | 0 | 0 | 0
** | 0 | 1 | 1
** | 1 | 0 | 1
** | 1 | 1 | 1
*/
nts::Tristate Gate::computeOR(nts::Tristate v1, nts::Tristate v2)
{
  if (_not)
    return ((nts::Tristate)(!(v1 || v2)));
  return ((nts::Tristate)(v1 || v2));
}

/*
**   a | b | s
** +-----------
** | 0 | 0 | 0
** | 0 | 1 | 1
** | 1 | 0 | 1
** | 1 | 1 | 0
*/
nts::Tristate Gate::computeXOR(nts::Tristate v1, nts::Tristate v2)
{
  if (_not)
    return ((nts::Tristate)(!(v1 ^ v2)));
  return ((nts::Tristate)(v1 ^ v2));
}

/*
**   a | s
** +-----------
** | 0 | 1
** | 1 | 0
*/
nts::Tristate Gate::computeNO(nts::Tristate v)
{
  return ((nts::Tristate)(!v));
}

nts::Tristate Gate::computeLATCH(nts::Tristate v1, nts::Tristate v2)
{
  nts::Tristate inpS = computeAND(v1, v2);
  nts::Tristate inpR = computeAND(inpS, v2);

  if (inpS == nts::Tristate::FALSE && inpR == nts::Tristate::FALSE)
    {
      this->tmpQ = tmpQ;
      this->tmpQ2 = tmpQ;
    } else {
      this->tmpQ = inpS;
      this->tmpQ2 = inpR;
    }
  return (inpS);
}

nts::Tristate Gate::computeSUM(nts::Tristate v1, nts::Tristate v2, nts::Tristate cinp)
{
  return (computeXOR(computeXOR(v1, v2), cinp));
}

nts::Tristate Gate::computeSUMC(nts::Tristate v1, nts::Tristate v2, nts::Tristate cinp)
{
  return (computeOR(computeAND(computeXOR(v1, v2), cinp), computeAND(v1, v2)));
}

nts::Tristate Gate::getTmpQ()
{
  return (this->tmpQ);
}

nts::Tristate Gate::getTmpQ2()
{
  return (this->tmpQ2);
}