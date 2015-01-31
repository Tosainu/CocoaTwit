#ifndef TIMELINEWEBVIEW_H
#define TIMELINEWEBVIEW_H

#include <QtWebKitWidgets>
#include <QVariantMap>

class TimelineWebView : public QWebView {
  Q_OBJECT

public:
  TimelineWebView(QWidget* parent = nullptr);
  ~TimelineWebView();

public slots:
  void addItem(QVariantMap item);
};

#endif
