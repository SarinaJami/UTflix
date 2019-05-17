#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <iostream>
#include <exception>

class NotFound : public std::exception {
public:
  virtual const char* what() const noexcept;
};

class BadRequest : public std::exception {
public:
  virtual const char* what() const noexcept;
};

class PermissionDenied : public std::exception {
public:
  virtual const char* what() const noexcept;
};

#endif
