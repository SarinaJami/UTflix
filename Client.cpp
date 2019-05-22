#include "Client.h"
#include "Exception.h"
#include <iterator>

using namespace std;

Client::Client(int _user_id, string _username, string _password, string _email,
  int _age) : user_id(_user_id), username(_username), password(_password),
  email(_email), age(_age), money(0)
{
}

void Client::follow(Publisher* publisher)
{
  followings.push_back(publisher);
}

void Client::addCredit(double amount)
{
  money += amount;
}

void Client::buyFilm(Film* film)
{
  pay(film);
  purchased_films.push_back(film);
}

void Client::pay(Film* film)
{
  if (money < film->getPrice())
    throw PermissionDenied();
  money -= film->getPrice();
}

void Client::viewPurchasedFilms(string name, double price, int min_year,
  int max_year, string director)
{
  vector<Film*> filtered_films = filterFilms(name, price, min_year, max_year,
    director);
  printFilms(filtered_films);

}

void Client::printFilms(const vector<Film*>& films_list) const
{
  // thinking of istringstream...
  int count = 0;
  for (int i = 0; i < films_list.size(); ++i)
  {
    cout << ++count << ". " <<
    films_list[i]->getId() << " | " <<
    films_list[i]->getName() << " | " <<
    films_list[i]->getLength() << " | " <<
    films_list[i]->getPrice() << " | " <<
    films_list[i]->getRate() << " | " <<
    films_list[i]->getYear() << " | " <<
    films_list[i]->getDirector() << " | " <<
    endl;
  }
}

vector<Film*> Client::filterFilms(string name, double price, int min_year,
  int max_year, string director)
{
  // thinking of a better way...
  vector<Film*> filtered_films;
  bool name_filtered = true;
  bool price_filtered = true;
  bool min_year_filtered = true;
  bool max_year_filtered = true;
  bool director_filtered = true;

  for (int i = 0; i < purchased_films.size(); ++i)
  {
    if (!name.empty())
      if (purchased_films[i]->getName() != name)
        name_filtered = false;
    if (price != -1)
      if (purchased_films[i]->getPrice() != price)
        price_filtered = false;
    if (min_year != -1)
      if (purchased_films[i]->getYear() < min_year)
        min_year_filtered = false;
    if (max_year != -1)
      if (purchased_films[i]->getYear() > max_year)
        max_year_filtered = false;
    if (!director.empty())
      if (purchased_films[i]->getDirector() != director)
        director_filtered = false;

    if (name_filtered && price_filtered && director_filtered &&
      min_year_filtered && max_year_filtered)
        filtered_films.push_back(purchased_films[i]);
  }
  return filtered_films;
}

void Client::addNotification(string notif, bool is_seen)
{
  notifications.push_back(make_pair(notif, is_seen));
}

void Client::viewUnseenNotifications() const
{
  int count = 0;
  // how to iterate?
  auto it_notif = notifications.end();
  while (it_notif >= notifications.begin())
  {
    if ((*it_notif).second == false)
      cout << ++count << ". " << (*it_notif).first << endl;
    --it_notif;
  }
}

void Client::viewAllNotifications(int limit) const
{
  int count = 0;
  // how to iterate?
  auto it_notif = notifications.end();
  while (it_notif >= (notifications.begin() + limit))
  {
    cout << ++count << ". " << (*it_notif).first << endl;
    --it_notif;
  }
}

ostream& operator<<(ostream& out, const Client* user)
{
  out << user->user_id << " | " <<
  user->username << " | " <<
  user->email;

  return out;
}

// bool operator==(const Client& user) const
// {
//   if (username == user.username && password == user.password)
//     return true;
//   return false;
// }

const string& Client::getUsername() const
{
  return username;
}

const string& Client::getPassword() const
{
  return password;
}

int Client::getId() const
{
  return user_id;
}

double Client::getMoney() const
{
  return money;
}

const vector<Film*>& Client::getPurchasedFilms() const
{
  return purchased_films;
}
