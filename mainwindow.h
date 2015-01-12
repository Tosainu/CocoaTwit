#include <QMainWindow>
#include <QtWidgets>
#include <memory>
#include "./lib/twitpp/oauth/account.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow();
  ~MainWindow();

private:
  void createActions();
  void createMenus();
  void createWidgets();

private slots:
  void showAuthDialog();
  void about();

  void authSuccess();
  void authFailure();

private:
  QMenu* accountMenu;
  QAction* addAccountAct;

  QMenu* helpMenu;
  QAction* aboutAct;

  std::shared_ptr<twitpp::oauth::account> account;
};
