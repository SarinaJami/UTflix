#include "UserInterface.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(int argc, const char* argv[])
{
  auto userInterface = UserInterface::getInstance();

  string email, username, password;
  int age;
  cin >> email >> username >> password >> age;

  userInterface->signup(email, username, password, age);

  return 0;
}
