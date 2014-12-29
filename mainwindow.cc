#include <QDebug>
#include <string>
#include "mainwindow.h"
#include "auth_dialog.h"

const std::string CK = "ywDt5KpeDYlO6vcYthEivwVWF";
const std::string CS = "Co2OmGUoTQlFCQ2H5iarWfSQz3BJ2lqr9uIuSvyaLCI8bzdfNN";

MainWindow::MainWindow() : account(std::make_shared<twitpp::oauth::account>(CK, CS)) {
  createActions();
  createMenus();
}

MainWindow::~MainWindow() {}

void MainWindow::about() {
  QMessageBox::about(this, "About CocoaTwit",
      "<b>CocoaTwit</b> is a Simple and Cute Twitter Client.");
}

void MainWindow::showAuthDialog() {
  AuthDialog* auth = new AuthDialog(account, this);
  auth->setModal(true);

  connect(auth, SIGNAL(success()), this, SLOT(authSuccess()));
  connect(auth, SIGNAL(failure()), this, SLOT(authFailure()));

  auth->exec();
}

void MainWindow::authSuccess() {
  qDebug() << "AccessToken:\t" << QString::fromStdString(account->oauth_token());
  qDebug() << "AccessSecret:\t" << QString::fromStdString(account->oauth_token_secret());
}

void MainWindow::authFailure() {
  qDebug() << "Failed to authenticate";
}

void MainWindow::createActions() {
  addAccountAct = new QAction("&Add Account", this);
  addAccountAct->setStatusTip("Add new Twitter Account");
  connect(addAccountAct, SIGNAL(triggered()), this, SLOT(showAuthDialog()));

  aboutAct = new QAction("&About", this);
  aboutAct->setStatusTip("Show the application's info");
  connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
}

void MainWindow::createMenus() {
  accountMenu = this->menuBar()->addMenu("&Account");
  accountMenu->addAction(addAccountAct);

  helpMenu = this->menuBar()->addMenu("&Help");
  helpMenu->addAction(aboutAct);
}
