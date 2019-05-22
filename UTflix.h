#ifndef UTFLIX_H_
#define UTFLIX_H_

#include "Client.h"
#include "Publisher.h"
#include "Film.h"
#include <vector>
#include <string>

class Film;
class Client;

class UTflix {
public:
  UTflix();
  void signUp(std::string email, std::string username, std::string password,
    int age, bool is_publisher);
  void login(std::string username, std::string password);
  void publishFilm(std::string name, int year, double length, double price,
    std::string summary, std::string director);
  void editFilm(int film_id, std::string feature, std::string content);
  void deleteFilm(int film_id);
  void printFollowers() const;
  void printPublisherFilms(std::string name, double min_rate, int min_year,
    double price, int max_year, std::string director) const ;
  void replyComment(int film_id, int comment_id, std::string content);
  void deleteComment(int film_id, int comment_id);
  void followPublisher(int user_id);
  void addCredit(int amount);
  void printAllFilms(std::string name, double min_rate, int min_year, double price,
    int max_year, std::string director) const;
  void showFilmDetails(int film_id) const;
  void buyFilm(int film_id);
  void payPublisher();
  void rateFilm(int film_id, double score);
  void addComment(int film_id, std::string content);
  void printPurchasedFilms(std::string name, double price, int min_year, int max_year,
    std::string director) const;

private:
  std::vector<Client*> clients;
  std::vector<Publisher*> publishers;
  std::vector<Film*> films;
  int user_id_tracker;
  int film_id_tracker;
  Client* logged_client;
  Publisher* logged_publisher;
  double money;

  bool isUserLogged() const;
  bool isEmailValid(std::string email) const;
  bool isUser(std::string username, std::string password) const;
  bool isArchiveFilm(int film_id) const;
  std::vector<Film*> filterFilms(const std::vector<Film*>& _films, std::string
    name, double min_rate, int min_year, double price, int max_year, std::string
    director) const ;
  std::vector<Film*> filterFilmsOnName(const std::vector<Film*>& published_films,
    std::string name) const;
  std::vector<Film*> filterFilmsOnMinRate(const std::vector<Film*>& published_films,
    double min_rate) const;
  std::vector<Film*> filterFilmsOnMinYear(const std::vector<Film*>& published_films,
    int min_year) const;
  std::vector<Film*> filterFilmsOnPrice(const std::vector<Film*>& published_films,
    double price) const;
  std::vector<Film*> filterFilmsOnMaxYear(const std::vector<Film*>& published_films,
    int max_year) const;
  std::vector<Film*> filterFilmsOnDirector(const std::vector<Film*>& published_films,
    std::string director) const;
  int searchForPublisher(int user_id) const;
  void printFilms(const std::vector<Film*>& filtered_films) const;
  void printRecommendations() const;
  std::vector<Film*> sortTopfilms() const;
  void swap(Film*& a, Film*& b) const;
  void receiveMoney(int film_id);
  void calculatePublisherShare(int film_id);
  void updateMoney();

};

#endif
