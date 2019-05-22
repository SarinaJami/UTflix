#ifndef PUBLISHER_H_
#define PUBLISHER_H_

#include "Client.h"

class Publisher : public Client {
public:
  Publisher(int _user_id, std::string _username, std::string _password,
    std::string _email, int _age);
  void addFilm(Film* film);
  void addFollower(Client* user);
  void removeFilm(int film_id);
  bool ownsTheFilm(int film_id) const;
  void printFollowers() const;
  void addPayment(double _payment);
  void receivePayment();
  double getPayment() const;
  std::vector<Film*> getPublishedFilms();

private:
  std::vector<Film*> published_films;
  std::vector<Client*> followers;
  double payment;

};

#endif
