//
// Errors.hh for Errors in
// /home/marwane/Projets/Epitech/CPP/cpp_nanotekspice/Errors/
//
// Made by Marwane Khsime
// Login   <marwane.khsime@epitech.eu@epitech.eu>
//
// Started on  Tue Jan 31 20:33:33 2017 Marwane Khsime
// Last update Tue Jan 31 20:33:36 2017 Marwane Khsime
//

#ifndef _ERRORS_HPP_
#define _ERRORS_HPP_

#include <exception>
#include <fstream>
#include <iostream>
#include <string>
namespace nts
{
  class Error : public std::exception {
   public:
    /// Constructor
    Error(const std::string &_message) throw()
            : message(_message) {}
    /// Destructor
    virtual ~Error() throw() {}

   public:
    /// Get the description of the error
    const char *what() const throw() { return this->message.c_str(); }


   private:
    /// Description of the error
    std::string message;
  };

  class badExtensionFile : public Error
  {
   public:
    badExtensionFile(const std::string &_message) : Error(_message){}
    virtual ~badExtensionFile() throw(){}
  };

  class incorrectLine : public Error
  {
   public:
    incorrectLine(const std::string &_message) : Error(_message){}
    virtual ~incorrectLine() throw(){}
  };

  class missingSection : public Error
  {
   public:
    missingSection(const std::string &_message) : Error(_message){}
    virtual ~missingSection() throw(){}
  };

  class sameName : public Error
  {
   public:
    sameName(const std::string &_message) : Error(_message){}
    virtual ~sameName() throw(){}
  };

  class missingInput : public Error
  {
   public:
    missingInput(const std::string &_message) : Error(_message){}
    virtual ~missingInput() throw(){}
  };

  class unknownInput : public Error
  {
   public:
    unknownInput(const std::string &_message) : Error(_message){}
    virtual ~unknownInput() throw(){}
  };

  class incorrectValue : public Error
  {
   public:
    incorrectValue(const std::string &_message) : Error(_message){}
    virtual ~incorrectValue() throw(){}
  };

  class unknownLink : public Error
  {
   public:
    unknownLink(const std::string &_message) : Error(_message){}
    virtual ~unknownLink() throw(){}
  };
}
#endif /* end of include guard: _ERRORS_HPP_ */
