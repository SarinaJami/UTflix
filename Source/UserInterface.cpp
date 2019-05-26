#include "../Include/UserInterface.h"
#include "../Include/Exception.h"
#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>

using namespace std;

UserInterface* UserInterface::instance = NULL;
UserInterface* UserInterface::getInstance(UTflix* _utflix)
{
  if (instance == nullptr)
    instance = new UserInterface(_utflix);
  return instance;
}

UserInterface::UserInterface(UTflix* _utflix) : utflix(_utflix)
{
}

vector<string> UserInterface::parseInput(const string& cmd) const
{
  istringstream ss(cmd);
  string buf;
  vector<string> tokens;
  while (ss >> buf)
    tokens.push_back(buf);
  return tokens;
}

void UserInterface::signup(const vector<string>& request) const
{
  vector<string> signupInfo = getSignupInfo(request);

  bool is_publisher = false;
  if (signupInfo[4] == "true")
    is_publisher = true;

  utflix->signUp(signupInfo[0], signupInfo[1], signupInfo[2],
    stoi(signupInfo[3]), is_publisher);
}

void UserInterface::login(const vector<string>& request) const
{
  vector<string> loginInfo = getLoginInfo(request);
  utflix->login(loginInfo[0], loginInfo[1]);
}

void UserInterface::processRequest(const string& cmd) const
{
  vector<string> request = parseInput(cmd);
  auto request_type = request.begin();
  if (*request_type == "POST")
    processPost(request);
  else if (*request_type == "GET")
    processGet(request);
  else
    throw BadRequest();
}

void UserInterface::processPost(const vector<string>& request) const
{
  string instruction = (request.size() > 1) ? request[1] : "";
  string question_mark = (request.size() > 2) ? request[2] : "";
  if (instruction == "signup" && question_mark == "?")
  {
    signup(request);
    printSuccessMessage();
  }
  else if (instruction == "login" && question_mark == "?")
  {
    login(request);
    printSuccessMessage();
  }
  else if (instruction == "films" && question_mark == "?")
  {
    publishFilm(request);
    printSuccessMessage();
  }
  else if (instruction == "money")
  {
    if (question_mark.empty())
    {
      utflix->payPublisher();
      printSuccessMessage();
    }
    else if (question_mark == "?")
    {
      utflix->addCredit(stoi(findKeyWord(request, "amount")));
      printSuccessMessage();
    }
  }
  else if (instruction == "replies" && question_mark == "?")
  {
    reply(request);
    printSuccessMessage();
  }
  else if (instruction == "followers" && question_mark == "?")
  {
    utflix->followPublisher(stoi(findKeyWord(request, "user_id")));
    printSuccessMessage();
  }
  else if (instruction == "buy" && question_mark == "?")
  {
    utflix->buyFilm(stoi(findKeyWord(request, "film_id")));
    printSuccessMessage();
  }
  else if (instruction == "rate" && question_mark == "?")
  {
    utflix->rateFilm(stoi(findKeyWord(request, "film_id")),
      stod(findKeyWord(request, "score")));
    printSuccessMessage();
  }
  else if (instruction == "comments" && question_mark == "?")
  {
    utflix->addComment(stoi(findKeyWord(request, "film_id")),
      findKeyWord(request, "content"));
    printSuccessMessage();
  }
  else if (instruction == "put_films" && question_mark == "?")
  {
    editFilm(request);
    printSuccessMessage();
  }
  else if (instruction == "delete_films" && question_mark == "?")
  {
    deleteFilm(request);
    printSuccessMessage();
  }
  else if (instruction == "delete_comments" && question_mark == "?")
  {
    deleteComment(request);
    printSuccessMessage();
  }
  else
    throw NotFound();
}

void UserInterface::processGet(const vector<string>& request) const
{
  string instruction = (request.size() > 1) ? request[1] : "";
  string question_mark = (request.size() > 2) ? request[2] : "";

  if (instruction == "followers")
    utflix->printFollowers();
  else if (instruction == "published")
  {
    if (question_mark == "?" || question_mark.empty())
      showPublisherFilms(request);
  }
  else if (instruction == "films")
  {
    if (question_mark == "?" || question_mark.empty())
    {
      string film_id = findOptionalKeyWord(request, "film_id");
      if (film_id.empty())
        showAllFilms(request);
      else
        utflix->showFilmDetails(stoi(film_id));
    }
  }
  else if (instruction == "purchased")
    showPurchasedFilms(request);
  else if (instruction == "notifications")
  {
    if (question_mark.empty())
      utflix->printUnseenNotifications();
    else
      showAllNotifications(request);
  }
  else
    throw NotFound();
}

void UserInterface::showAllNotifications(const vector<string>& request) const
{
  if (find(request.begin(), request.end(), "read") == request.end() ||
    find(request.begin(), request.end(), "?") == request.end())
    return;
  int limit = stoi(findKeyWord(request, "limit"));
  utflix->printAllNotifications(limit);
}

void UserInterface::showPurchasedFilms(const vector<string>& request) const
{
  if (find(request.begin(), request.end(), "?") == request.end())
    return;

  vector<string> filmInfo = getPurchasedFilmsInfo(request);

  int min_year = -1;
  double price = -1;
  int max_year = -1;
  if (!filmInfo[1].empty())
    price = stod(filmInfo[1]);
  if (!filmInfo[2].empty())
    min_year = stoi(filmInfo[2]);
  if (!filmInfo[3].empty())
    min_year = stoi(filmInfo[3]);

  utflix->printPurchasedFilms(filmInfo[0], price, min_year, max_year, filmInfo[4]);
}

vector<string> UserInterface::getPurchasedFilmsInfo(const vector<string>& request) const
{
  vector<string> filmInfo;

  filmInfo.push_back(findOptionalKeyWord(request, "name"));
  filmInfo.push_back(findOptionalKeyWord(request, "price"));
  filmInfo.push_back(findOptionalKeyWord(request, "min_year"));
  filmInfo.push_back(findOptionalKeyWord(request, "max_year"));
  filmInfo.push_back(findOptionalKeyWord(request, "director"));

  return filmInfo;
}

void UserInterface::showAllFilms(const vector<string>& request) const
{
  double min_rate = -1;
  int min_year = -1;
  double price = -1;
  int max_year = -1;
  string name;
  string director;
  getFilmInfoForPrint(request, name, min_rate, min_year, price, max_year, director);
  utflix->printAllFilms(name, min_rate, min_year, price, max_year, director);
}

void UserInterface::reply(const vector<string>& request) const
{
  int film_id = stoi(findKeyWord(request, "film_id"));
  int comment_id = stoi(findKeyWord(request, "comment_id"));
  string content = findKeyWord(request, "content");
  utflix->replyComment(film_id, comment_id, content);
}

void UserInterface::deleteComment(const std::vector<std::string>& request) const
{
  int film_id = stoi(findKeyWord(request, "film_id"));
  int comment_id = stoi(findKeyWord(request, "comment_id"));
  utflix->deleteComment(film_id, comment_id);
}

void UserInterface::showPublisherFilms(const vector<string>& request) const
{
  double min_rate = -1;
  int min_year = -1;
  double price = -1;
  int max_year = -1;
  string name;
  string director;
  getFilmInfoForPrint(request, name, min_rate, min_year, price, max_year, director);
  utflix->printPublisherFilms(name, min_rate, min_year, price, max_year,
    director);
}

void UserInterface::convertFilmInfo(const vector<string>& filmInfo, double& min_rate, int&
  min_year, double& price, int& max_year) const
{
  if (!filmInfo[0].empty())
    min_rate = stod(filmInfo[0]);
  if (!filmInfo[1].empty())
    min_year = stoi(filmInfo[1]);
  if (!filmInfo[2].empty())
    price = stod(filmInfo[2]);
  if (!filmInfo[3].empty())
    max_year = stoi(filmInfo[3]);
}

void UserInterface::deleteFilm(const vector<string>& request) const
{
  int film_id = stoi(findKeyWord(request, "film_id"));
  utflix->deleteFilm(film_id);
}

void UserInterface::publishFilm(const vector<string>& request) const
{
  vector<string> filmInfo = getFilmInfoForPublish(request);
  utflix->publishFilm(filmInfo[0], stoi(filmInfo[1]), stod(filmInfo[2]),
  stod(filmInfo[3]), filmInfo[4], filmInfo[5]);
}

void UserInterface::getFilmInfoForPrint(const vector<string>& request, string&
  name, double& min_rate, int& min_year, double& price, int& max_year, string&
  director) const
{
  vector<string> filmInfo;

  name = findOptionalKeyWord(request, "name");
  director = findOptionalKeyWord(request, "director");
  filmInfo.push_back(findOptionalKeyWord(request, "min_rate"));
  filmInfo.push_back(findOptionalKeyWord(request, "min_year"));
  filmInfo.push_back(findOptionalKeyWord(request, "price"));
  filmInfo.push_back(findOptionalKeyWord(request, "max_year"));
  convertFilmInfo(filmInfo, min_rate, min_year, price, max_year);
}

vector<string> UserInterface::getFilmInfoForPublish(const vector<string>& request) const
{
  vector<string> filmInfo;
  filmInfo.push_back(findKeyWord(request, "name"));
  filmInfo.push_back(findKeyWord(request, "year"));
  filmInfo.push_back(findKeyWord(request, "length"));
  filmInfo.push_back(findKeyWord(request, "price"));
  filmInfo.push_back(findKeyWord(request, "summary"));
  filmInfo.push_back(findKeyWord(request, "director"));
  return filmInfo;
}

void UserInterface::editFilm(const vector<string>& request) const
{
  int film_id = stoi(findKeyWord(request, "film_id"));
  editFeature(film_id, "name", findOptionalKeyWord(request, "name"));
  editFeature(film_id, "year", findOptionalKeyWord(request, "year"));
  editFeature(film_id, "length", findOptionalKeyWord(request, "length"));
  editFeature(film_id, "summary", findOptionalKeyWord(request, "summary"));
  editFeature(film_id, "director", findOptionalKeyWord(request, "director"));
}

void UserInterface::editFeature(int film_id, string feature, string content) const
{
  if (!content.empty())
    utflix->editFilm(film_id, feature, content);
}

vector<string> UserInterface::getSignupInfo(const vector<string>& request) const
{
  vector<string> signupInfo;
  signupInfo.push_back(findKeyWord(request, "email"));
  signupInfo.push_back(findKeyWord(request, "username"));
  signupInfo.push_back(findKeyWord(request, "password"));
  signupInfo.push_back(findKeyWord(request, "age"));
  signupInfo.push_back(findOptionalKeyWord(request, "publisher"));
  if (signupInfo[4].empty())
    signupInfo[4] = "false";
  return signupInfo;
}

vector<string> UserInterface::getLoginInfo(const vector<string>& request) const
{
  vector<string> loginInfo;
  loginInfo.push_back(findKeyWord(request, "username"));
  loginInfo.push_back(findKeyWord(request, "password"));
  return loginInfo;
}

string UserInterface::findKeyWord(const vector<string>& request, string word) const
{
  auto it_to_word = find(request.begin(), request.end(), word);
  if (it_to_word == request.end())
    throw BadRequest();
  return *(++it_to_word);
}

string UserInterface::findOptionalKeyWord(const vector<string>& request, string
  word) const
{
  auto it_to_word = find(request.begin(), request.end(), word);
  if (it_to_word == request.end())
    return "";
  return (++it_to_word == request.end()) ? "" : *it_to_word;
}

void UserInterface::printSuccessMessage() const
{
  cout << "OK" << endl;
}
