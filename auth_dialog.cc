#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include "auth_dialog.h"

AuthDialog::AuthDialog(const std::shared_ptr<twitpp::oauth::account> a, QWidget* parent)
    : QDialog(parent), pin(new QLineEdit), account(a) {
  if (account->get_authorize_url()) {
    emit failure();
    this->close();
  }

  QString authorize_url = QString::fromStdString(account->authorize_url());

  auto button = new QPushButton("Auth");
  auto description = new QLabel("PIN:");
  auto info = new QLabel();
  info->setTextInteractionFlags(Qt::TextBrowserInteraction);
  info->setOpenExternalLinks(true);
  info->setText(
      "Open the following URL and Enter the PIN.<br>"
      "<a href=\"" +
      authorize_url + "\">" + authorize_url + "</a>");

  auto layout = new QGridLayout();
  layout->addWidget(info, 0, 0, 1, 0);
  layout->addWidget(description, 1, 0);
  layout->addWidget(pin, 1, 1);
  layout->addWidget(button, 1, 2);

  connect(button, SIGNAL(clicked()), this, SLOT(authorize()));

  this->setWindowTitle("Twitter Authorization");
  this->setLayout(layout);
}

AuthDialog::~AuthDialog() {}

void AuthDialog::authorize() {
  if (account->get_oauth_token(this->pin->text().toStdString())) {
    emit failure();
  } else {
    emit success();
  }

  this->close();
}
