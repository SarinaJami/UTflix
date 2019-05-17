#include "UTflix.h"

using namespace std;


UTflix::UTflix() : user_id_tracker(0)
{
}

User UTflix::signUp(string email, string username, string password, int age,
  bool is_publisher)
{
  if (isUser(username, password))
    throw BadRequest();
  if (isEmailValid(email))
  {
    ++user_id_tracker;
    User newUser;
    if (is_publisher)
    {
      Publisher* publisher = new Publisher(user_id_tracker, username, password,
        email, age);
      newUser = make_pair(publisher, true);
    }
    else
    {
      Client* client = new Client(user_id_tracker, username, password, email, age);
      newUser = make_pair(client, false);
    }
    users.push_back(newUser);
    return newUser;
  }
}

User UTflix::login(string username, string password)
{
  for (auto it_user = users.begin(); it_user != users.end(); ++it_user)
  {
    if ((*it_user).first->getUsername() == username &&
      (*it_user).first->getPassword() == password)
      return (*it_user);
  }
  throw BadRequest();
}
// similar to function above
bool UTflix::isUser(string username, string password)
{
  for (auto it_user = users.begin(); it_user != users.end(); ++it_user)
  {
    if ((*it_user).first->getUsername() == username &&
      (*it_user).first->getPassword() == password)
      return true;
  }
  return false;
}

bool UTflix::isEmailValid(string email)
{
  const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
  return regex_match(email, pattern);
}
