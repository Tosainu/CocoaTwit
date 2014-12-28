#include <QMainWindow>
#include <QtWidgets>

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow();
  ~MainWindow();

private slots:
  void about();

private:
  void createActions();
  void createMenus();

  QMenu* helpMenu;
  QAction* aboutAct;
};
