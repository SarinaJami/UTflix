#include "Exception.h"

using namespace std;

const char* NotFound::what() const noexcept
{
  cout << "Not Found" << endl;
}

const char* BadRequest::what() const noexcept
{
  cout << "Bad Request" << endl;
}

const char* PermissionDenied::what() const noexcept
{
  cout << "Permission Denied" << endl;
}
