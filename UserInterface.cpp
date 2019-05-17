#include "UserInterface.h"

using namespace std;

UserInterface* UserInterface::instance = NULL;
UserInterface* UserInterface::getInstance()
{
  if (instance == nullptr)
    instance = new UserInterface();
  return instance;
}

UserInterface::UserInterface() {
  utflix = new UTflix();
}

void UserInterface::signup(string email, string username, string password, int
  age, bool is_publisher)
{
  User user = utflix->signUp(email, username, password, age, is_publisher);
  cerr << "done!" << endl;
  cout <<
    user.first->getUsername()
    << "\n" <<
    user.first->getPassword()
    << endl;
}
