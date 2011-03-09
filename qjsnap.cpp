#include "qjsnap.h"

QJSnap::QJSnap(QWebPage *page , QWebView *widget) {
    mPage = page;
    mView = widget;
    mSawInitialLayout = false;
    mSawDocumentComplete = false;
}

void
QJSnap::InitialLayoutCompleted() {
  mSawInitialLayout = true;
  if (mSawInitialLayout && mSawDocumentComplete)
    TryDelayedRender();
}

void QJSnap::qrender(bool) {
    mSawDocumentComplete = true;
    if (mSawInitialLayout && mSawDocumentComplete)
      TryDelayedRender();
}

void
QJSnap::TryDelayedRender() {
    //qDebug() << 1;
    savesnap();
    //mPage->view()->showFullScreen();
    //QApplication::exit();
}

void QJSnap::savesnap() {

    QWebFrame *mainFrame = mPage->mainFrame();
    QPainter painter;
    //qDebug() << mainFrame->contentsSize();
    qDebug() << mainFrame->contentsSize().width();
    QSize qsize;
    qsize.setWidth( mainFrame->contentsSize().width() +100);
    qsize.setHeight(mainFrame->contentsSize().height() );
    mPage->setViewportSize( qsize);

    QImage image(mPage->viewportSize(), QImage::Format_ARGB32);
    qDebug() << image.width();
    painter.begin(&image);
    mainFrame->render(&painter);
    painter.end();

    //QString mOutput = "/home/thankwsx/QJSnap/newsqq.jpg";
    QString mOutput = "j:\\project\\QJSnap\\newsqq.jpg";
    qDebug() << image.save( mOutput );
    image.save( mOutput);

    QWebElement eleNode = mainFrame->findFirstElement("#auto_gen_1");

    qDebug() << eleNode.geometry();
    QImage qq_1(QSize(eleNode.geometry().width(),eleNode.geometry().height()),QImage::Format_ARGB32);
    painter.begin(&qq_1);
    eleNode.render(&painter);
    painter.end();
    //qq_1.save( QString("/home/thankwsx/QJSnap/News_Width1.jpg"));
    qq_1.save( QString("j:\\project\\QJSnap\\News_Width1.jpg"));
}
