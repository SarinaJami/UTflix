#include "Publisher.h"
#include "Exception.h"

using namespace std;

Publisher::Publisher(int _user_id, string _username, string _password, string
  _email, int _age) : Client(_user_id, _username, _password, _email, _age),
  payment(0)
{
}

void Publisher::addFilm(Film* film)
{
  published_films.push_back(film);
}

void Publisher::addFollower(Client* user)
{
  followers.push_back(user);
}

void Publisher::removeFilm(int film_id)
{
  published_films.erase(published_films.begin() + film_id - 1);
}

bool Publisher::ownsTheFilm(int film_id) const
{
  for (int i = 0; i < published_films.size(); ++i)
    if (published_films[i]->getId() == film_id)
      return true;
  return false;
}

void Publisher::printFollowers() const
{
  cout << "List of Followers" << endl;
  int count = 0;
  for (int i = 0; i < followers.size(); ++i)
    cout << ++count << ". " << followers[i] << endl;
}

void Publisher::addPayment(double _payment)
{
  payment += _payment;
}

void Publisher::receivePayment()
{
  money += payment;
  payment = 0;
}

double Publisher::getPayment() const
{
  return payment;
}

vector<Film*> Publisher::getPublishedFilms() const
{
  return published_films;
}

vector<Client*> Publisher::getFollowers() const
{
  return followers;
}
