#ifndef UI_AUTH_H
#define UI_AUTH_H

#include <QDialog>
#include <QLineEdit>
#include <memory>
#include "./lib/twitpp/oauth/account.h"

class AuthDialog : public QDialog {
  Q_OBJECT

public:
  AuthDialog(const std::shared_ptr<twitpp::oauth::account> a, QWidget* parent = 0);

signals:
  void success();
  void failure();

private slots:
  void authorize();

private:
  QLineEdit* pin;

  std::shared_ptr<twitpp::oauth::account> account;
};

#endif
