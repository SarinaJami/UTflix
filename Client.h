#ifndef CLIENT_H_
#define CLIENT_H_

#include "Film.h"
#include "Exception.h"
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <iterator>

class Film;
class Publisher;

class Client {
public:
  Client(int _user_id, std::string _username, std::string _password, std::string
    _email, int _age);

  virtual const std::string& getUsername() const;
  virtual const std::string& getPassword() const;
  virtual const std::vector<Film*>& getPurchasedFilms() const;

  virtual void follow(Publisher* publisher);
  virtual void addCredit(double amount);
  virtual void buyFilm(Film* film);
  virtual void viewPurchasedFilms(std::string name, double price, int min_year,
    int max_year, std::string director);
  virtual void addNotification(std::string notif, bool is_seen);
  virtual void viewUnseenNotifications() const;
  virtual void viewAllNotifications(int limit) const;

protected:
  int user_id;
  std::string username;
  std::string password;
  std::string email;
  int age;
  double money;
  std::vector<std::pair<std::string, bool>> notifications;
  std::vector<Film*> purchased_films;
  std::vector<Publisher*> followings;

  std::vector<Film*> filterFilms(std::string name, double price,
    int min_year, int max_year, std::string director);
  void printFilms(const std::vector<Film*>& films_list) const;
  bool isEnoughMoney(Film* film) const;

};

#endif