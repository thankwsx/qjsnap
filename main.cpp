//#include <QtGui/QApplication>
#include <QApplication>
#include <QtWebKit>
#include <QLibrary>
#include "qjsnap.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QJSnap w;
    //浏览器设置
    QWebSettings::globalSettings()->setAttribute(QWebSettings::PluginsEnabled,true);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::JavascriptEnabled,true);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::XSSAuditingEnabled,true);

    //  1 QWebView-> 1 QWebPage -> n QWebFrame
    //QNetworkRequest req;
    //req.setUrl( QUrl::fromEncoded("http://websvn.com") );
    QWebView widget;
    QWebPage page;
    // company proxy setting
    QNetworkAccessManager manager;
    QUrl p = QUrl("http://web-proxy.oa.com:8080");
    QNetworkProxy proxy = QNetworkProxy(QNetworkProxy::HttpProxy,p.host(), p.port(80), p.userName(), p.password());
    manager.setProxy(proxy);
    page.setNetworkAccessManager(&manager);
    QJSnap w(&page , &widget);
    a.connect( &page,SIGNAL(loadFinished(bool)),&w ,SLOT( qrender(bool)) );
    a.connect( page.mainFrame(),   SIGNAL(initialLayoutCompleted()), &w,  SLOT(InitialLayoutCompleted()));
    QUrl surl("http://news.qq.com/a/20110309/000616.htm");
    page.mainFrame()->load(surl);
    return a.exec();
}
