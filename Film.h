#ifndef FILM_H_
#define FILM_H_

#include <iostream>
#include <vector>
#include <string>

class Client;
class Publisher;

class Film {
public:
  Film(int _id, std::string _name, int _year, double _length, double _price,
    std::string _summary, std::string _director, Publisher* _publisher);

  struct Comment {
    Comment(int _comment_id, Client* _client_user, std::string _content);
    int comment_id;
    std::string content;
    std::string reply;
    Client* client_user;
  };

  struct Rate {
    Rate(Client* _use, double _score);
    double score;
    Client* user;
  };

  double getPrice();
  int getId();
  std::string getName();
  double getLength();
  double getRate();
  int getYear();
  std::string getDirector();
  bool isRemoved();
  Publisher* getPublisher();
  // inline Publisher* getPublisher();

  void editName(std::string _name);
  void editYear(int _year);
  void editLength(double _length);
  void editSummary(std::string _summary);
  void editDirector(std::string _director);

  void addPurchaser(Client* purchaser);
  void addComment(const std::string& _content, Client* _user);
  void addReply(const std::string& _content, int _comment_id);
  void addRate(double _score, Client* purchaser);
  void deleteComment(int _comment_id);

  friend std::ostream& operator<<(std::ostream& out, const Film* film);
  void printDetails() const;
  void printAsRecommendation() const;

  void remove();

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
  bool is_deleted;
  int comment_id_tracker;

  int searchForComment(int id) const;
  bool isPurchaser(Client* purchaser);
  void calculateMeanRate();
  void printComments() const;

};

// #include "Film-inl.h"

#endif
