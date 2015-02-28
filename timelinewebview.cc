#include <QDebug>
#include "timelinewebview.h"

static const QString timelineHtml(R"(
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8">
    <title>Timeline Test</title>
    <style>
/* http://meyerweb.com/eric/tools/css/reset/ 
v2.0 | 20110126
License: none (public domain)
 */
html,body,div,span,applet,object,iframe,h1,h2,h3,h4,h5,h6,p,blockquote,pre,a,abbr,acronym,address,big,cite,code,del,dfn,em,img,ins,kbd,q,s,samp,small,strike,strong,sub,sup,tt,var,b,u,i,center,dl,dt,dd,ol,ul,li,fieldset,form,label,legend,table,caption,tbody,tfoot,thead,tr,th,td,article,aside,canvas,details,embed,figure,figcaption,footer,header,hgroup,menu,nav,output,ruby,section,summary,time,mark,audio,video{margin:0;padding:0;border:0;font-size:100%;font:inherit;vertical-align:baseline;}article,aside,details,figcaption,figure,footer,header,hgroup,menu,nav,section{display:block;}body{line-height:1;}ol,ul{list-style:none;}blockquote,q{quotes:none;}blockquote:before,blockquote:after,q:before,q:after{content:'';content:none;}table{border-collapse:collapse;border-spacing:0;}body{-webkit-text-size-adjust:none}

html {
  background: #222426;
  color: #ddd;
  font: 16px/1.6 Roboto, 'Droid Sans', Meiryo, 'Hiragino Kaku Gothic ProN', sans-serif;
  overflow: hidden;
}
h1 {
  font-size: 140%;
  font-weight: bold;
  line-height: 45px;
}
small {
  color: #999;
  font-size: 90%;
  font-weight: 100;
}
.column {
  position: absolute;
  top: 0;
  bottom: 0;
  left: 0;
  right: 0;
  height: 100%;
  overflow: hidden;
}
.column-header {
  position: relative;
  background: #303236;
  border-bottom: 1px solid #3c3c3c;
  height: 45px;
  overflow-y: hidden;
  padding: 0 10px;
}
.timeline {
  position: absolute;
  top: 45px;
  bottom: 0;
  left: 0;
  right: 0;
  overflow-y: scroll;
}
.tweet {
  border-bottom: 1px solid #3c3c3c;
  padding: 10px;
  position: relative;
}
.tweet-content {
  padding-left: 58px;
}
.tweet-content:before, .tweet-content:after {
  content: ' ';
  display: block;
}
.tweet-header {
  display: block;
  font-weight: bold;
}
.avatar {
  float: left;
  margin-left: -58px;
  width: 48px;
  height: 48px;
}
.tweet-text {
  display: block;
  height: 100%;
  margin-top: 10px;
  width: 100%;
  word-break: break-word;
  word-wrap: break-word;
}
.action {
  margin-top: 10px;
  text-align: right;
}
.action > button {
  width: 36px;
}
    </style>
  </head>

  <body>
    <div class="column">
      <header class="column-header">
        <h1>Home</h1>
      </header>
      <div class="timeline">
      </div> <!-- timeline -->
    </div> <!-- column -->
  </body>
</html>
)");

TimelineWebView::TimelineWebView(QWidget* parent) : QWebView(parent) {
  this->setHtml(timelineHtml);
}

TimelineWebView::~TimelineWebView() {}

void TimelineWebView::setJsObj(JsObj* jsobj) {
  this->page()->mainFrame()->addToJavaScriptWindowObject("JsObj", jsobj);
}

void TimelineWebView::addItem(QVariantMap item) {
  auto id         = item["id_str"].toString();
  auto imageUrl   = item["user"].toMap()["profile_image_url_https"].toString();
  auto name       = item["user"].toMap()["name"].toString();
  auto screenName = item["user"].toMap()["screen_name"].toString();
  auto tweet      = item["text"].toString();

  auto timeline = this->page()->mainFrame()->findFirstElement("div.timeline");
  timeline.prependInside(R"(
    <div class="tweet">
      <div class="tweet-content">
        <header class="tweet-header">
          <img src=")" + imageUrl + R"(" alt="" class="avatar">
          <p>)" + name + " <small>@" + screenName + R"(</small></p>
        </header>
        <div class="tweet-text"><p>)" + tweet + R"(</p>
        </div>
      </div>
      <div class="action">
        <button onclick="JsObj.fav(')" + id + R"(');">Fav</button>
        <button onclick="JsObj.rt(')" + id + R"(');">RT</button>
      </div>
    </div>)");
}
