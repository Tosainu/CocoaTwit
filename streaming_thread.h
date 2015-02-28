#ifndef STREAMING_THREAD_H
#define STREAMING_THREAD_H

#include <QThread>
#include <QVariantMap>
#include <memory>
#include "lib/twitpp/oauth/account.h"
#include "lib/twitpp/oauth/oauth.h"

class StreamingThread : public QThread {
  Q_OBJECT

public:
  StreamingThread(const std::shared_ptr<twitpp::oauth::account>& ap, QObject* parent = 0);

protected:
  virtual void run();

signals:
  void connectionError();

  // public stream messages
  void deleted(QVariantMap);
  void scrubGeo(QVariantMap);
  void limit(QVariantMap);
  void statusWithheld(QVariantMap);
  void userWithheld(QVariantMap);
  void disconnect(QVariantMap);
  void warning(QVariantMap);

  // site stream messages
  void forUser(QVariantMap);
  void control(QVariantMap);

  // user stream messages
  void friends(QVariantMap);
  void directMessage(QVariantMap);
  void event(QVariantMap);
  void block(QVariantMap);
  void unblock(QVariantMap);
  void favorite(QVariantMap);
  void unfavorite(QVariantMap);
  void follow(QVariantMap);
  void unfollow(QVariantMap);
  void listCreated(QVariantMap);
  void listDestroyed(QVariantMap);
  void listUpdated(QVariantMap);
  void listMemberAdded(QVariantMap);
  void listMemberRemoved(QVariantMap);
  void listUserSubscribed(QVariantMap);
  void listUserUnsubscribed(QVariantMap);
  void userUpdated(QVariantMap);

  // tweet
  void tweet(QVariantMap);

private:
  twitpp::oauth::client oauth;
};

#endif
