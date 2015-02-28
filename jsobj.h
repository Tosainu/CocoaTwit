#ifndef JSOBJ_H
#define JSOBJ_H

#include <QtCore>
#include <QString>
#include <memory>
#include "./lib/twitpp/oauth/account.h"
#include "./lib/twitpp/oauth/oauth.h"

class JsObj : public QObject {
  Q_OBJECT

public:
  JsObj(const std::shared_ptr<twitpp::oauth::account> a, QObject *parent = nullptr);

public slots:
  void fav(QString id);
  void rt(QString id);

private:
  twitpp::oauth::client client;
};

#endif
