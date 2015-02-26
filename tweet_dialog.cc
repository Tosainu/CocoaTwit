#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include "tweet_dialog.h"

TweetDialog::TweetDialog(const std::shared_ptr<twitpp::oauth::account> a, QWidget* parent)
    : QDialog(parent), text(new QPlainTextEdit), client(*a) {
  auto button = new QPushButton("Tweet");

  auto layout = new QVBoxLayout();
  layout->addWidget(text);
  layout->addWidget(button);

  connect(button, SIGNAL(clicked()), this, SLOT(tweet()));

  this->setWindowTitle("Tweet");
  this->setLayout(layout);
}

TweetDialog::~TweetDialog() {}

void TweetDialog::tweet() {
  auto res = client.post("https://api.twitter.com/1.1/statuses/update.json", {
      {"status", text->toPlainText().toUtf8().constData()}
  });

  if (res.status_code != 200) {
    qWarning("Tweet failed!");
  }

  this->close();
}
