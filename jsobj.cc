#include "jsobj.h"

JsObj::JsObj(const std::shared_ptr<twitpp::oauth::account> a, QObject *parent)
    : QObject(parent), client(*a) {}

void JsObj::fav(QString id) {
  auto res = client.post("https://api.twitter.com/1.1/favorites/create.json", {{"id", id.toUtf8().constData()}});

  if (res.status_code != 200) {
    qWarning("Fav failed!");
    qWarning(res.body.c_str());
  }
}

void JsObj::rt(QString id) {
  auto res = client.post(QString("https://api.twitter.com/1.1/statuses/retweet/" + id + ".json").toUtf8().constData());

  if (res.status_code != 200) {
    qWarning("RT failed!");
    qWarning(res.body.c_str());
  }
}
