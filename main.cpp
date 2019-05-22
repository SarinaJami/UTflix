#include "UserInterface.h"
#include "UTflix.h"
#include <iostream>
#include <string>
#include <exception>

using namespace std;

int main(int argc, const char* argv[])
{
  auto* utflix = new UTflix;
  auto* userInterface = UserInterface::getInstance(utflix);

  string cmd;
  while(getline(cin, cmd))
  {
    if (!cmd.empty())
    {
      try {
        userInterface->processRequest(cmd);
      } catch (exception& ex) {
        cout << ex.what() << endl;
      }
    }
  }

  return 0;
}
