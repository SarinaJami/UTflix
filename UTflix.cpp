#include "UTflix.h"
#include "Exception.h"
#include <iostream>
#include <regex>
#include <iterator>
#include <iomanip>

using namespace std;

UTflix::UTflix() : user_id_tracker(0), film_id_tracker(0), money(0),
  logged_client(NULL), logged_publisher(NULL)
{
}

void UTflix::signUp(string email, string username, string password, int age,
  bool is_publisher)
{
  if (isUser(username, password))
    throw BadRequest();
  if (isEmailValid(email))
  {
    ++user_id_tracker;
    if (is_publisher)
    {
      Publisher* publisher = new Publisher(user_id_tracker, username, password,
        email, age);
      publishers.push_back(publisher);
      logged_publisher = publisher;
      logged_client = logged_publisher;
    }
    else
    {
      Client* client = new Client(user_id_tracker, username, password, email, age);
      clients.push_back(client);
      logged_client = client;
      logged_publisher = NULL;
    }
  }
}

void UTflix::login(string username, string password)
{
  for (int i = 0; i < publishers.size(); ++i)
  {
    if (publishers[i]->getUsername() == username && publishers[i]->getPassword() == password)
    {
      logged_publisher = publishers[i];
      logged_client = logged_publisher;
      return;
    }
  }
  for (int i = 0; i < clients.size(); ++i)
  {
    if (clients[i]->getUsername() == username && clients[i]->getPassword() == password)
    {
      logged_client = clients[i];
      logged_publisher = NULL;
      return;
    }
  }
  throw BadRequest();
}
// similar to function above
bool UTflix::isUser(string username, string password) const
{
  for (int i = 0; i < publishers.size(); ++i)
    if (publishers[i]->getUsername() == username && publishers[i]->getPassword() == password)
      return true;
  for (int i = 0; i < clients.size(); ++i)
    if (clients[i]->getUsername() == username && clients[i]->getPassword() == password)
      return true;
  return false;
}

bool UTflix::isEmailValid(string email) const
{
  const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
  return regex_match(email, pattern);
}

bool UTflix::isUserLogged() const
{
  if (logged_client == NULL && logged_publisher == NULL)
    return false;
  return true;
}

void UTflix::publishFilm(string name, int year, double length, double price, string
  summary, string director)
{
  if (!isUserLogged() || logged_publisher == NULL)
    throw PermissionDenied();

  Film* film = new Film(++film_id_tracker, name, year, length, price, summary,
    director, logged_publisher);
  logged_publisher->addFilm(film);
  films.push_back(film);
}

void UTflix::editFilm(int film_id, string feature, string content)
{
  if (!isUserLogged() || logged_publisher == NULL)
    throw PermissionDenied();
  if (!logged_publisher->ownsTheFilm(film_id))
    throw PermissionDenied();
  if (!isArchiveFilm(film_id))
    throw NotFound();

  if (feature == "name")
    films[film_id - 1]->editName(content);
  else if (feature == "year")
    films[film_id - 1]->editYear(stoi(content));
  else if (feature == "length")
    films[film_id - 1]->editLength(stod(content));
  else if (feature == "summary")
    films[film_id - 1]->editSummary(content);
  else if (feature == "director")
    films[film_id - 1]->editDirector(content);
  else
    throw BadRequest();
}

void UTflix::deleteFilm(int film_id)
{
  if (!isUserLogged() || logged_publisher == NULL)
    throw PermissionDenied();
  if (!logged_publisher->ownsTheFilm(film_id))
    throw PermissionDenied();
  if (!isArchiveFilm(film_id))
    throw NotFound();

  films[film_id - 1]->remove();
  logged_publisher->removeFilm(film_id);
}

bool UTflix::isArchiveFilm(int film_id) const
{
  if (film_id > films.size())
    return false;
  if (films[film_id - 1]->isRemoved())
    return false;
  return true;
}

void UTflix::printFollowers() const
{
  if (!isUserLogged() || logged_publisher == NULL)
    throw PermissionDenied();

  logged_publisher->printFollowers();
}

void UTflix::printPublisherFilms(string name, double min_rate, int min_year,
  double price, int max_year, string director) const
{
  if (!isUserLogged() || logged_publisher == NULL)
    throw PermissionDenied();

  vector<Film*> published_films = logged_publisher->getPublishedFilms();
  published_films = filterFilms(published_films, name, min_rate, min_year, price, max_year, director);

  printFilms(published_films);
}

void UTflix::printFilms(const vector<Film*>& filtered_films) const
{
  int count = 0;
  for (int i = 0; i < filtered_films.size(); ++i)
    cout << ++count << ". " << filtered_films[i] << endl;
}

vector<Film*> UTflix::filterFilms(const vector<Film*>& _films, string name, double
  min_rate, int min_year, double price, int max_year, string director) const
{
  vector<Film*> filtered_films = _films;

  if (!name.empty())
    filtered_films = filterFilmsOnName(_films, name);
  if (min_rate != -1)
    filtered_films = filterFilmsOnMinRate(_films, min_rate);
  if (min_year != -1)
    filtered_films = filterFilmsOnMinYear(_films, min_year);
  if (price != -1)
    filtered_films = filterFilmsOnPrice(_films, price);
  if (max_year != -1)
    filtered_films = filterFilmsOnMaxYear(_films, max_year);
  if (!director.empty())
    filtered_films = filterFilmsOnDirector(_films, director);

  return filtered_films;
}

vector<Film*> UTflix::filterFilmsOnName(const vector<Film*>& published_films,
  string name) const
{
  vector<Film*> filtered_films;
  for (int i = 0; i < published_films.size(); ++i)
    if (published_films[i]->getName() == name)
      filtered_films.push_back(published_films[i]);
  return filtered_films;
}

vector<Film*> UTflix::filterFilmsOnMinRate(const vector<Film*>& published_films,
  double min_rate) const
{
  vector<Film*> filtered_films;
  for (int i = 0; i < published_films.size(); ++i)
    if (published_films[i]->getRate() >= min_rate)
      filtered_films.push_back(published_films[i]);
  return filtered_films;
}

vector<Film*> UTflix::filterFilmsOnMinYear(const vector<Film*>& published_films,
  int min_year) const
{
  vector<Film*> filtered_films;
  for (int i = 0; i < published_films.size(); ++i)
    if (published_films[i]->getYear() >= min_year)
      filtered_films.push_back(published_films[i]);
  return filtered_films;
}

vector<Film*> UTflix::filterFilmsOnPrice(const vector<Film*>& published_films,
  double price) const
{
  vector<Film*> filtered_films;
  for (int i = 0; i < published_films.size(); ++i)
    if (published_films[i]->getPrice() == price)
      filtered_films.push_back(published_films[i]);
  return filtered_films;
}

vector<Film*> UTflix::filterFilmsOnMaxYear(const vector<Film*>& published_films,
  int max_year) const
{
  vector<Film*> filtered_films;
  for (int i = 0; i < published_films.size(); ++i)
    if (published_films[i]->getYear() <= max_year)
      filtered_films.push_back(published_films[i]);
  return filtered_films;
}

vector<Film*> UTflix::filterFilmsOnDirector(const vector<Film*>& published_films,
  string director) const
{
  vector<Film*> filtered_films;
  for (int i = 0; i < published_films.size(); ++i)
    if (published_films[i]->getDirector() == director)
      filtered_films.push_back(published_films[i]);
  return filtered_films;
}

void UTflix::replyComment(int film_id, int comment_id, string content)
{
  if (!isUserLogged() || logged_publisher == NULL)
    throw PermissionDenied();
  if (!logged_publisher->ownsTheFilm(film_id))
    throw PermissionDenied();
  if (!isArchiveFilm(film_id))
    throw NotFound();

  films[film_id - 1]->addReply(content, comment_id);
}

void UTflix::deleteComment(int film_id, int comment_id)
{
  if (!isUserLogged() || logged_publisher == NULL)
    throw PermissionDenied();
  if (!logged_publisher->ownsTheFilm(film_id))
    throw PermissionDenied();
  if (!isArchiveFilm(film_id))
    throw NotFound();

  films[film_id - 1]->deleteComment(comment_id);
}

int UTflix::searchForPublisher(int user_id) const
{
  for (int i = 0; i < publishers.size(); ++i)
    if (publishers[i]->getId() == user_id)
      return i;
  throw PermissionDenied();
}

void UTflix::followPublisher(int user_id)
{
  if (!isUserLogged())
    throw PermissionDenied();

  int index = searchForPublisher(user_id);
  logged_client->follow(publishers[index]);
  publishers[index]->addFollower(logged_client);
}

void UTflix::addCredit(int amount)
{
  if (!isUserLogged())
    throw PermissionDenied();

  logged_client->addCredit(amount);
}

void UTflix::printAllFilms(string name, double min_rate, int min_year, double price,
  int max_year, string director) const
{
  if (!isUserLogged())
    throw PermissionDenied();

  vector<Film*> filtered_films = filterFilms(films, name, min_rate, min_year,
    price, max_year, director);

  for (int i = 0; i < filtered_films.size(); ++i)
    if (filtered_films[i]->isRemoved())
      filtered_films.erase(filtered_films.begin() + i);

  printFilms(filtered_films);
}

void UTflix::showFilmDetails(int film_id) const
{
  if (!isUserLogged())
    throw PermissionDenied();
  if (!isArchiveFilm(film_id))
    throw NotFound();

  films[film_id - 1]->printDetails();
  printRecommendations(film_id);
}

void UTflix::sortTopFilms(vector<Film*>& sorted_films) const
{
  for (int i = 0; i < sorted_films.size(); ++i)
  {
    for (int j = 0; j < sorted_films.size(); ++j)
    {
      if (sorted_films[i]->getRate() >= sorted_films[j]->getRate())
        swap(sorted_films[i], sorted_films[j]);
    }
  }
}

void UTflix::swap(Film*& a, Film*& b) const
{
  Film* temp = a;
  a = b;
  b = temp;
}

vector<Film*> UTflix::omitWatchedFilms(int film_id) const
{
  vector<Film*> new_films;
  for (int i = 0; i < films.size(); ++i)
  {
    if (films[i]->isPurchaser(logged_client) || films[i]->isRemoved())
      break;
    if (i != film_id - 1)
      new_films.push_back(films[i]);
  }
  return new_films;
}

void UTflix::printRecommendations(int film_id) const
{
  cout << "Recommendation Film" << endl;

  vector<Film*> top_films = omitWatchedFilms(film_id);
  sortTopFilms(top_films);

  int count = 0;
  while (count < top_films.size() && count < 4)
  {
    cout << ++count << ". ";
    top_films[count - 1]->printAsRecommendation();
    cout << endl;
  }
}

void UTflix::buyFilm(int film_id)
{
  if (!isUserLogged())
    throw PermissionDenied();
  if (!isArchiveFilm(film_id))
    throw NotFound();

  logged_client->buyFilm(films[film_id - 1]);
  films[film_id - 1]->addPurchaser(logged_client);
  receiveMoney(film_id);
  calculatePublisherShare(film_id);
}

void UTflix::receiveMoney(int film_id)
{
  money += films[film_id - 1]->getPrice();
}

void UTflix::calculatePublisherShare(int film_id)
{
  double rate = films[film_id - 1]->getRate();
  double payment;
  double factor = 0.9;

  if (rate < 5)
    factor = 0.8;
  else if (rate >= 8)
    factor = 0.95;

  payment = factor * films[film_id - 1]->getPrice();
  films[film_id - 1]->getPublisher()->addPayment(payment);
}

void UTflix::payPublisher()
{
  if (!isUserLogged() || logged_publisher == NULL)
    throw PermissionDenied();

  updateMoney();
  logged_publisher->receivePayment();
}

void UTflix::updateMoney()
{
  money -= logged_publisher->getPayment();
}

void UTflix::rateFilm(int film_id, double score)
{
  if (!isUserLogged())
    throw PermissionDenied();
  if (!isArchiveFilm(film_id))
    throw NotFound();

  films[film_id - 1]->addRate(score, logged_client);
  // send notifications to publisher
}

void UTflix::addComment(int film_id, string content)
{
  if (!isUserLogged())
    throw PermissionDenied();
  if (!isArchiveFilm(film_id))
    throw NotFound();

  films[film_id - 1]->addComment(content, logged_client);
}

void UTflix::printPurchasedFilms(string name, double price, int min_year, int
  max_year, string director) const
{
  if (!isUserLogged())
    throw PermissionDenied();

  logged_client->viewPurchasedFilms(name, price, min_year, max_year, director);
}
