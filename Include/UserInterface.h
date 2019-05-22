#ifndef USER_INTERFACE_H_
#define USER_INTERFACE_H_

#include "UTflix.h"
#include <vector>
#include <string>

class UTflix;

class UserInterface {
public:
  static UserInterface* getInstance(UTflix* _utflix);
  void processRequest(const std::string& cmd) const;

private:
  UserInterface(UTflix* _utflix);
  static UserInterface* instance;

  UTflix* utflix;

  std::vector<std::string> parseInput(const std::string& cmd) const;
  void signup(const std::vector<std::string>& request) const;
  void login(const std::vector<std::string>& request) const;
  void processPost(const std::vector<std::string>& request) const;
  void processPut(const std::vector<std::string>& request) const;
  void processGet(const std::vector<std::string>& request) const;
  void processDelete(const std::vector<std::string>& request) const;
  std::vector<std::string> getFilmInfoForPublish(const std::vector<std::string>&
    request) const;
  std::vector<std::string> getSignupInfo(const std::vector<std::string>& request) const;
  std::vector<std::string> getLoginInfo(const std::vector<std::string>& request) const;
  std::string findKeyWord(const std::vector<std::string>& request, std::string word) const;
  std::string findOptionalKeyWord(const std::vector<std::string>& request, std::
    string word) const;
  void publishFilm(const std::vector<std::string>& request) const;
  void editFilm(const std::vector<std::string>& request) const;
  void editFeature(int film_id, std::string feature, std::string content) const;
  void deleteFilm(const std::vector<std::string>& request) const;
  void showPublisherFilms(const std::vector<std::string>& request) const;
  std::vector<std::string> getFilmInfoForPrint(const std::vector<std::string>& request) const;
  void reply(const std::vector<std::string>& request) const;
  void deleteComment(const std::vector<std::string>& request) const;
  void showAllFilms(const std::vector<std::string>& request) const;
  void convertFilmInfo(const std::vector<std::string>& filmInfo, double& min_rate,
    int& min_year, double& price, int& max_year) const;
  void getFilmInfoForPrint(const std::vector<std::string>& request, std::string&
    name, double& min_rate, int& min_year, double& price, int& max_year, std::string&
    director) const;
  void showPurchasedFilms(const std::vector<std::string>& request) const;
  std::vector<std::string> getPurchasedFilmsInfo(const std::vector<std::string>& request) const;
  void showAllNotifications(const std::vector<std::string>& request) const;
  void printSuccessMessage() const;

};

#endif
