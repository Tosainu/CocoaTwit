#ifndef TIMELINEWEBVIEW_H
#define TIMELINEWEBVIEW_H

#include <QtWebKitWidgets>

class TimelineWebView : public QWebView {
  Q_OBJECT

public:
  TimelineWebView(QWidget* parent = nullptr);
  ~TimelineWebView();
};

#endif
