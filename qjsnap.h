#ifndef QJSNAP_H
#define QJSNAP_H

#include <QWidget>
#include <QtWebKit/QtWebKit>

class QJSnap;

class QJSnap : public QObject {
  Q_OBJECT

public:
    QJSnap(QWebPage *page , QWebView *widget);

private slots:
    void qrender(bool ok);  //page loadFinished 事件触发
    void InitialLayoutCompleted();  //page initialLayoutCompleted
private:
    void TryDelayedRender();
    void savesnap();    //保存截图
    bool mSawInitialLayout; //标志位
    bool mSawDocumentComplete;  //标志位
protected:
    QWebPage *mPage;
    QWebView *mView;
};

#endif // QJSNAP_H
