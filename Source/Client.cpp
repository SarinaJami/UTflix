#include "../Include/Client.h"
#include "../Include/Exception.h"
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
  int max_year, string director) const
{
  vector<Film*> filtered_films = filterFilms(name, price, min_year, max_year,
    director);

  cout << "#. Film Id | Film Name | Film Length | Film price | " <<
    "Rate | Production Year | Film Director" << endl;
  for (int i = 0;i < filtered_films.size(); ++i)
    filtered_films[i]->printPurchasedFilm(i + 1);

}

vector<Film*> Client::filterFilms(string name, double price, int min_year,
  int max_year, string director) const
{
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

ostream& operator<<(ostream& out, const Client* user)
{
  out << user->user_id << " | " <<
  user->username << " | " <<
  user->email;

  return out;
}

void Client::printUnseenNotifications()
{
  cout << "#. Notification Message" << endl;
  int count = 0;
  for (int i = notifications.size() - 1; i >= 0 ; --i)
  {
    if (notifications[i].second == false)
    {
      cout << ++count << ". " << notifications[i].first << endl;
      notifications[i].second = true;
    }
  }
}

void Client::printAllNotifications(int limit) const
{
  cout << "#. Notification Message" << endl;
  if (limit < notifications.size())
    limit = notifications.size() - limit;
  else
    limit = 0;

  int count = 0;
  for (int i = notifications.size() - 1; i >= limit ; --i)
    if (notifications[i].second == true)
      cout << ++count << ". " << notifications[i].first << endl;
}

void Client::setNotification(std::string content, bool seen)
{
  notifications.push_back(make_pair(content, seen));
}

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

void Client::showMoney() const
{
  cout << money << endl;
}
