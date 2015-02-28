#ifndef UI_TWEET_H
#define UI_TWEET_H

#include <QDialog>
#include <QPlainTextEdit>
#include <memory>
#include "./lib/twitpp/oauth/account.h"
#include "./lib/twitpp/oauth/oauth.h"

class TweetDialog : public QDialog {
  Q_OBJECT

public:
  TweetDialog(const std::shared_ptr<twitpp::oauth::account> a, QWidget* parent = 0);

private slots:
  void tweet();

private:
  QPlainTextEdit* text;

  twitpp::oauth::client client;
};

#endif
