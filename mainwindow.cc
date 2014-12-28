#include "mainwindow.h"

MainWindow::MainWindow() {
  createActions();
  createMenus();
}

MainWindow::~MainWindow() {}

void MainWindow::about() {
  QMessageBox::about(this, "About CocoaTwit",
      "<b>CocoaTwit</b> is a Simple and Cute Twitter Client.");
}

void MainWindow::createActions() {
  aboutAct = new QAction("&About", this);
  aboutAct->setStatusTip("Show the application's info");
  connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
}

void MainWindow::createMenus() {
  helpMenu = this->menuBar()->addMenu("&Help");
  helpMenu->addAction(aboutAct);
}
