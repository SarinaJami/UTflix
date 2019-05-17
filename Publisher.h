#ifndef PUBLISHER_H_
#define PUBLISHER_H_

#include "Client.h"
#include "Exception.h"

class Publisher : public Client {
public:
  Publisher(int _user_id, std::string _username, std::string _password,
    std::string _email, int _age);
private:
};

#endif
