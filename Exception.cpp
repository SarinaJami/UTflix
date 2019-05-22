#include "Exception.h"

using namespace std;

const char* NotFound::what() const noexcept
{
  return "Not Found";
}

const char* BadRequest::what() const noexcept
{
  return "Bad Request";
}

const char* PermissionDenied::what() const noexcept
{
  return "Permission Denied";
}
