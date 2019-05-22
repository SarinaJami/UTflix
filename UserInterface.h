#ifndef USER_INTERFACE_H_
#define USER_INTERFACE_H_

#include "UTflix.h"
#include <vector>
#include <string>

class UTflix;

class UserInterface {
public:
  static UserInterface* getInstance(UTflix* _utflix);
  void processRequest(const std::string& cmd);

private:
  UserInterface(UTflix* _utflix);
  static UserInterface* instance;

  UTflix* utflix;

  std::vector<std::string> parseInput(const std::string& cmd);
  void signup(const std::vector<std::string>& request);
  void login(const std::vector<std::string>& request);
  void processPost(const std::vector<std::string>& request);
  void processPut(const std::vector<std::string>& request);
  void processGet(const std::vector<std::string>& request);
  void processDelete(const std::vector<std::string>& request);
  std::vector<std::string> getFilmInfoForPublish(const std::vector<std::string>&
    request);
  std::vector<std::string> getSignupInfo(const std::vector<std::string>& request);
  std::vector<std::string> getLoginInfo(const std::vector<std::string>& request);
  std::string findKeyWord(const std::vector<std::string>& request, std::string word);
  std::string findOptionalKeyWord(const std::vector<std::string>& request, std::
    string word);
  void publishFilm(const std::vector<std::string>& request);
  void editFilm(const std::vector<std::string>& request);
  void editFeature(int film_id, std::string feature, std::string content);
  void deleteFilm(const std::vector<std::string>& request);
  void showPublisherFilms(const std::vector<std::string>& request);
  std::vector<std::string> getFilmInfoForPrint(const std::vector<std::string>& request);
  void reply(const std::vector<std::string>& request);
  void deleteComment(const std::vector<std::string>& request);
  void showAllFilms(const std::vector<std::string>& request);
  void convertFilmInfo(const std::vector<std::string>& filmInfo, double& min_rate,
    int& min_year, double& price, int& max_year);
  void getFilmInfoForPrint(const std::vector<std::string>& request, std::string&
    name, double& min_rate, int& min_year, double& price, int& max_year, std::string&
    director);
  void showPurchasedFilms(const std::vector<std::string>& request);
  std::vector<std::string> getPurchasedFilmsInfo(const std::vector<std::string>& request);
  void showAllNotifications(const std::vector<std::string>& request);
  void printSuccessMessage();

};

#endif
