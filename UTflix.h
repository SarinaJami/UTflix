#ifndef UTFLIX_H_
#define UTFLIX_H_

#include "Client.h"
#include "Publisher.h"
#include "Film.h"
#include "Exception.h"
#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <utility>
#include <iterator>

class Film;
class Client;

typedef std::pair<Client*, bool> User;

class UTflix {
public:
  UTflix();
  User signUp(std::string email, std::string username, std::string password,
    int age, bool is_publisher = false);
  User login(std::string username, std::string password);

private:
  std::vector<Film*> films;
  std::vector<User> users;
  int user_id_tracker;

  bool isEmailValid(std::string email);
  bool isUser(std::string username, std::string password);

};

#endif
