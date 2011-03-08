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
    QLibrary qlib("/home/thankwsx/QJSnap/plugins/libgnashplugin.so");
    qlib.load();
    qDebug() << "qlib" << qlib.isLoaded();
    QLibrary qlib1("/home/thankwsx/QJSnap/plugins/libgnashamf-0.8.8.so");
    qlib1.load();
    qDebug() << "qlib1" << qlib1.isLoaded();
    QLibrary qlib2("/home/thankwsx/QJSnap/plugins/libgnashmedia-0.8.8.so");
    qlib2.load();
    qDebug() << "qlib2" << qlib2.isLoaded();
    QLibrary qlib4("/home/thankwsx/QJSnap/plugins/libgnashbase-0.8.8.so");
    qlib4.load();
    qDebug() << "qlib4" << qlib4.isLoaded();
    QLibrary qlib5("/home/thankwsx/QJSnap/plugins/libgnashnet-0.8.8.so");
    qlib5.load();
    qDebug() << "qlib5" <<  qlib5.isLoaded();
    QLibrary qlib6("/home/thankwsx/QJSnap/plugins/libgnashsound-0.8.8.so");
    qlib6.load();
    qDebug() << "qlib6" << qlib6.isLoaded();
    QLibrary qlib7("/home/thankwsx/QJSnap/plugins/libgnashcore-0.8.8.so");
    qlib7.load();
    qDebug() << "qlib7" << qlib7.isLoaded();
    QLibrary qlib3("/home/thankwsx/QJSnap/plugins/libgnashrender-0.8.8.so");
    qlib3.load();
    qDebug() << "qlib3" << qlib3.isLoaded();
    //libgnashamf-0.8.8.so   libgnashmedia-0.8.8.so  libgnashrender-0.8.8.so
    //libgnashbase-0.8.8.so  libgnashnet-0.8.8.so    libgnashsound-0.8.8.so
    //libgnashcore-0.8.8.so  libgnashplugin.so

            //->setFileName("/home/thankwsx/QJSnap/plugins/libgnashplugin.so");
    //  1 QWebView-> 1 QWebPage -> n QWebFrame
    //QWebView *view = new QWebView();
    //view->load(QUrl("http://websvn.com"));
    //view->show();
    //QNetworkRequest req;
    //req.setUrl( QUrl::fromEncoded("http://websvn.com") );
    QWebView widget;
    QWebPage page;
    //QNetworkAccessManager manager;
    //widget.show();
    //QUrl p = QUrl("http://web-proxy.oa.com:8080");
    //QNetworkProxy proxy = QNetworkProxy(QNetworkProxy::HttpProxy,p.host(), p.port(80), p.userName(), p.password());
    /*
    qDebug() << p.host();
    qDebug() << p.port();
    qDebug() << p.userName();
    qDebug() << p.password();
    manager.setProxy(proxy);
    */
    //page.setNetworkAccessManager(&manager);
    //widget.setPage( &page);
    //widget.load( QUrl("http://news.qq.com") );
    //widget.show();
    QJSnap w(&page , &widget);
    a.connect( &page,SIGNAL(loadFinished(bool)),&w ,SLOT( qrender(bool)) );
    a.connect( page.mainFrame(),   SIGNAL(initialLayoutCompleted()), &w,  SLOT(InitialLayoutCompleted()));
    //page->mainFrame()->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);
    //page->mainFrame()->setScrollBarPolicy(Qt::Vertical, Qt::ScrollBarAlwaysOff);
    //page.mainFrame()->load(req,QNetworkAccessManager::GetOperation);
    page.mainFrame()->load(QUrl("http://news.qq.com"));
    return a.exec();
}
