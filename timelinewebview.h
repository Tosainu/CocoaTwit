#ifndef TIMELINEWEBVIEW_H
#define TIMELINEWEBVIEW_H

#include <QtWebKitWidgets>
#include <QVariantMap>
#include "jsobj.h"

class TimelineWebView : public QWebView {
  Q_OBJECT

public:
  TimelineWebView(QWidget* parent = nullptr);
  ~TimelineWebView();

  void setJsObj(JsObj* jsobj);

public slots:
  void addItem(QVariantMap item);
};

#endif
