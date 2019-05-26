#ifndef CLIENT_H_
#define CLIENT_H_

#include "Film.h"
#include <iostream>
#include <vector>
#include <string>
#include <utility>

class Film;
class Publisher;

class Client {
public:
  Client(int _user_id, std::string _username, std::string _password, std::string
    _email, int _age);

  virtual const std::string& getUsername() const;
  virtual const std::string& getPassword() const;
  virtual int getId() const;

  virtual void follow(Publisher* publisher);
  virtual void addCredit(double amount);
  virtual void buyFilm(Film* film);
  virtual void viewPurchasedFilms(std::string name, double price, int min_year,
    int max_year, std::string director) const;
  virtual void setNotification(std::string content, bool seen);
  virtual void printUnseenNotifications();
  virtual void printAllNotifications(int limit) const;
  virtual void showMoney() const;

  friend std::ostream& operator<<(std::ostream& out, const Client* user);

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
    int min_year, int max_year, std::string director) const;
  void pay(Film* film);

};

#endif
