#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QString>
#include "streaming_thread.h"

StreamingThread::StreamingThread(const std::shared_ptr<twitpp::oauth::account>& ap, QObject* parent) : QThread(parent), oauth(*ap) {}

StreamingThread::~StreamingThread() {}

void StreamingThread::run() {
  oauth.stream_get("https://userstream.twitter.com/1.1/user.json", [&](twitpp::net::response& response) {
    if (response.status_code != 200) {
      emit connectionError();
      return;
    }

    QJsonParseError status;
    auto json = QJsonDocument::fromJson(QByteArray(response.body.c_str()), &status).object().toVariantMap();

    if (status.error == QJsonParseError::NoError) {
      if      (!json["delete"].isNull())          { emit deleted(json);         }
      else if (!json["scrub_geo"].isNull())       { emit scrubGeo(json);        }
      else if (!json["limit"].isNull())           { emit limit(json);           }
      else if (!json["status_withheld"].isNull()) { emit statusWithheld(json);  }
      else if (!json["user_withheld"].isNull())   { emit userWithheld(json);    }
      else if (!json["disconnect"].isNull())      { emit disconnect(json);      }
      else if (!json["warning"].isNull())         { emit warning(json);         }
      else if (!json["for_user"].isNull())        { emit forUser(json);         }
      else if (!json["control"].isNull())         { emit control(json);         }
      else if (!json["friends"].isNull())         { emit friends(json);         }
      else if (!json["friends_str"].isNull())     { emit friends(json);         }
      else if (!json["direct_message"].isNull())  { emit directMessage(json);   }
      else if (!json["event"].isNull())           { emit event(json);
        auto userEvent = json["event"].toString();

        if      (userEvent == "block")                  { emit block(json);                 }
        else if (userEvent == "unblock")                { emit unblock(json);               }
        else if (userEvent == "favorite")               { emit favorite(json);              }
        else if (userEvent == "unfavorite")             { emit unfavorite(json);            }
        else if (userEvent == "follow")                 { emit follow(json);                }
        else if (userEvent == "unfollow")               { emit unfollow(json);              }
        else if (userEvent == "list_created")           { emit listCreated(json);           }
        else if (userEvent == "list_destroyed")         { emit listDestroyed(json);         }
        else if (userEvent == "list_updated")           { emit listUpdated(json);           }
        else if (userEvent == "list_member_added")      { emit listMemberAdded(json);       }
        else if (userEvent == "list_member_removed")    { emit listMemberRemoved(json);     }
        else if (userEvent == "list_user_subscribed")   { emit listUserSubscribed(json);    }
        else if (userEvent == "list_user_unsubscribed") { emit listUserUnsubscribed(json);  }
        else if (userEvent == "user_update")            { emit userUpdated(json);           }
      } else {
        emit tweet(json);
      }

      response.body.clear();
    }
  });
}
