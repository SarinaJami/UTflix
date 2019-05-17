#include "Film.h"

using namespace std;

Film::Film(int _id, std::string _name, int _year, double _length, double _price,
  std::string _summary, std::string _director, Publisher* _publisher) : film_id(_id),
  name(_name), year(_year), length(_length), price(_price), summary(_summary),
  director(_director), publisher(_publisher), mean_rate(0)
{
}

Comment::Comment(int _comment_id, Client* _user, string _content) :
  comment_id(++_comment_id), user(_user), content(_content)
{
}

Rate::Rate(Client* _user, double _score) : score(_score), user(_user)
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

  Comment comment(comments.size(), purchaser, _content);
  comments.push_back(comment);

  // inform publisher
}

void Film::addReply(const string& _content, int _comment_id)
{
  int index = searchForComment(_comment_id);
  comments[index].reply = _content;

  // inform purchaser
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

void Film::calculateMeanRate()
{
  double rate_sum = 0.00;
  for (int i = 0; i < rates.size(); ++i)
    rate_sum += rates[i].score;
  mean_rate = rate_sum / rates.size();
}

int Film::searchForComment(int _comment_id)
{
  for (int i = 0; i < comments.size(); ++i)
  {
    if (comments[i].comment_id == _comment_id)
      return i;
  }
  throw PermissionDenied();
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
}

void Film::printComments() const
{
  cout << "Comments" << endl;
  for (int i = 0; i < comments.size(); ++i)
  {
    cout << comments[i].comment_id << ". " << comments[i].content << "\n" <<
    comments[i].comment_id << ".1. " << comments[i].reply << endl;
  }
  cout << "\n" << endl;
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