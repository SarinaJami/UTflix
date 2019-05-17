#ifndef FILM_H_
#define FILM_H_

#include "Exception.h"
#include <iostream>
#include <vector>
#include <string>
#include <utility>

class Client;
class Publisher;

struct Comment {
  Comment(int _comment_id, Client* _user, std::string _content);
  int comment_id;
  std::string content;
  std::string reply;
  Client* user;
};

struct Rate {
  Rate(Client* _user, double _score);
  double score;
  Client* user;
};

class Film {
public:
  Film(int _id, std::string _name, int _year, double _length, double _price,
    std::string _summary, std::string _director, Publisher* _publisher);

  double getPrice();
  int getId();
  std::string getName();
  double getLength();
  double getRate();
  int getYear();
  std::string getDirector();

  void editName(std::string _name);
  void editYear(int _year);
  void editLength(double _length);
  void editSummary(std::string _summary);
  void editDirector(std::string _director);

  void addPurchaser(Client* purchaser);
  void addComment(const std::string& _content, Client* _user);
  void addReply(const std::string& _content, int _comment_id);
  void addRate(double _score, Client* purchaser);

  void printDetails() const;
  void printComments() const;

private:
  int film_id;
  std::string name;
  int year;
  double length;
  double price;
  std::string summary;
  std::string director;
  Publisher* publisher;
  std::vector<Client*> purchasers;
  std::vector<Comment> comments;
  std::vector<Rate> rates;
  double mean_rate;

  int searchForComment(int _comment_id);
  bool isPurchaser(Client* purchaser);
  void calculateMeanRate();

};

#endif
