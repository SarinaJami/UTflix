#include "Film.h"
#include "Exception.h"
#include <utility>

using namespace std;

Film::Film(int _id, std::string _name, int _year, double _length, double _price,
  std::string _summary, std::string _director, Publisher* _publisher) : film_id(_id),
  name(_name), year(_year), length(_length), price(_price), summary(_summary),
  director(_director), publisher(_publisher), mean_rate(0), is_deleted(false),
  comment_id_tracker(0)
{
}

Film::Comment::Comment(int _comment_id, Client* _client_user, string _content) :
  comment_id(_comment_id), client_user(_client_user), content(_content)
{
}

Film::Rate::Rate(Client* _user, double _score) : score(_score), user(_user)
{
}

void Film::addPurchaser(Client* purchaser)
{
  purchasers.push_back(purchaser);

  // inform publisher
}

void Film::addComment(const string& _content, Client* purchaser)
{
  if (!isPurchaser(purchaser))
    throw PermissionDenied();

  Comment comment(++comment_id_tracker, purchaser, _content);
  comments.push_back(comment);

  // inform publisher
}

void Film::addReply(const std::string& _content, int _comment_id)
{
  comments[searchForComment(_comment_id)].reply.push_back(_content);
}

void Film::addRate(double _score, Client* purchaser)
{
  if (!isPurchaser(purchaser))
    throw PermissionDenied();

  bool rated_before = false;
  for (int i = 0; i < rates.size(); ++i)
  {
    if (rates[i].user == purchaser)
    {
      rates[i].score = _score;
      rated_before = true;
    }
  }
  if (!rated_before)
  {
    Rate rate(purchaser, _score);
    rates.push_back(rate);
  }

  calculateMeanRate();
}

void Film::deleteComment(int _comment_id)
{
  comments.erase(comments.begin() + searchForComment(_comment_id));
}

int Film::searchForComment(int id) const
{
  for (int i = 0; i < comments.size(); ++i)
    if (comments[i].comment_id == id)
      return i;

  throw NotFound();
}

void Film::calculateMeanRate()
{
  double rate_sum = 0.00;
  for (int i = 0; i < rates.size(); ++i)
    rate_sum += rates[i].score;
  mean_rate = rate_sum / rates.size();
}

bool Film::isPurchaser(Client* purchaser)
{
  for (int i = 0; i < purchasers.size(); ++i)
  {
    if (purchasers[i] == purchaser)
      return true;
  }
  return false;
}

ostream& operator<<(ostream& out, const Film* film)
{
  out << film->film_id << " | " <<
  film->name << " | " <<
  film->length << " | " <<
  film->price << " | " <<
  film->mean_rate << " | " <<
  film->year << " | " <<
  film->director;

  return out;
}

void Film::printDetails() const
{
  cout << "Details of Film " << name << "\n" <<
  "Id = " << film_id << "\n" <<
  "Director = " << director << "\n" <<
  "Length = " << length << "\n" <<
  "Year = " << year << "\n" <<
  "Summary = " << summary << "\n" <<
  "Rate = " << mean_rate << "\n" <<
  "Price = " << price << "\n\n" << endl;

  printComments();
}

void Film::printComments() const
{
  cout << "Comments" << endl;
  for (int i = 0; i < comments.size(); ++i)
  {
    int count = comments[i].reply.size();
    cout << comments[i].comment_id << ". " << comments[i].content << endl;
    for (int j = 0; j < comments[i].reply.size(); ++j)
    {
      cout << comments[i].comment_id << "." << j + 1 << ". " <<
      comments[i].reply[j] << endl;
    }
  }
  cout << "\n" << endl;
}

void Film::printAsRecommendation() const
{
  cout << film_id << " | " <<
  name << " | " <<
  length << " | " <<
  director;
}

void Film::remove()
{
  is_deleted = true;
}

void Film::editName(std::string _name)
{
  name = _name;
}

void Film::editYear(int _year)
{
  year = _year;
}

void Film::editLength(double _length)
{
  length = _length;
}

void Film::editSummary(std::string _summary)
{
  summary = _summary;
}

void Film::editDirector(std::string _director)
{
  director = _director;
}

double Film::getPrice()
{
  return price;
}

int Film::getId()
{
  return film_id;
}

string Film::getName()
{
  return name;
}

double Film::getLength()
{
  return length;
}

double Film::getRate()
{
  return mean_rate;
}

int Film::getYear()
{
  return year;
}

string Film::getDirector()
{
  return director;
}

bool Film::isRemoved()
{
  return is_deleted;
}

Publisher* Film::getPublisher()
{
  return publisher;
}

Client* Film::getCommenter(int _comment_id) const
{
  return comments[searchForComment(_comment_id)].client_user;
}
