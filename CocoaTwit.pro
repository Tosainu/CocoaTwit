QT += core gui webkitwidgets

TEMPLATE = app
TARGET = CocoaTwit
INCLUDEPATH += .

HEADERS += \
  mainwindow.h \
  auth_dialog.h \
  jsobj.h \
  streaming_thread.h \
  timelinewebview.h \
  tweet_dialog.h

SOURCES += \
  main.cc \
  mainwindow.cc \
  auth_dialog.cc \
  jsobj.cc \
  streaming_thread.cc \
  timelinewebview.cc \
  tweet_dialog.cc \
  lib/twitpp/net/async_client.cc \
  lib/twitpp/net/client.cc \
  lib/twitpp/oauth/account.cc \
  lib/twitpp/oauth/oauth.cc \
  lib/twitpp/util/util.cc

CONFIG += c++11
LIBS += -lboost_system -lboost_thread -lcrypto -lssl
