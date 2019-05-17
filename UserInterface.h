#ifndef USER_INTERFACE_H_
#define USER_INTERFACE_H_

#include "UTflix.h"
#include <iostream>
#include <vector>
#include <string>

class UserInterface {
public:
  static UserInterface* getInstance();

  void signup(std::string email, std::string username, std::string password,
    int age, bool is_publisher = false);
private:
  UserInterface();
  static UserInterface* instance;

  UTflix* utflix;

};

#endif
