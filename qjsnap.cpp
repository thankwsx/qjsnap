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
void QJSnap::realCapture() {
    savesnap();
}

void
QJSnap::TryDelayedRender() {
    //qDebug() << 1;
    QTimer *timer = new QTimer(this);
    QTimer::singleShot(200,this,SLOT(realCapture()));
    //savesnap();
    //mPage->view()->showFullScreen();
    //QApplication::exit();
}

void QJSnap::savesnap() {

    QWebFrame *mainFrame = mPage->mainFrame();
    QPainter painter;
    //qDebug() << mainFrame->contentsSize();
    //qDebug() << mainFrame->contentsSize().width();
    QSize qsize;
    qsize.setWidth( mainFrame->contentsSize().width() +100);
    qsize.setHeight(mainFrame->contentsSize().height() );
    mPage->setViewportSize( qsize);

    QImage image(mPage->viewportSize(), QImage::Format_ARGB32);
    //qDebug() << image.width();
    painter.begin(&image);
    mainFrame->render(&painter);
    painter.end();

    //QString mOutput = "/home/thankwsx/QJSnap/newsqq.jpg";
    QString mOutput = "j:\\project\\QJSnap\\newsqq.jpg";
    qDebug() << image.save( mOutput );
    image.save( mOutput);

    //QWebElement eleNode = mainFrame->findFirstElement("#auto_gen_1");
    QWebElementCollection elements = mainFrame->findAllElements(".bd a");
    int num = 0;
    foreach (QWebElement paraElement, elements) {
        QString href = paraElement.attribute( QString("href") , QString("nohref"));
        if( href.contains("loc=") && href.indexOf("News_F_Width2") < 0) {
            //if(num > 1) continue;
            num++;
            QString filename1 = href.mid( href.indexOf("loc=") + 4);
            //painter.restore();
            //painter.
            QImage qq_1;//(QSize(paraElement.geometry().width(),paraElement.geometry().height()),QImage::Format_ARGB32);
            qq_1 = image.copy( paraElement.geometry().left()-2 , paraElement.geometry().top()+1 , paraElement.geometry().width()+4 , paraElement.geometry().height());
            //painter.begin(&qq_1);
            //qDebug() << paraElement.geometry().left() << paraElement.geometry().top() << paraElement.geometry().width() << paraElement.geometry().height();
            //mainFrame->render(&painter,QRegion(0,8,200,200));
            //painter.end();
            qq_1.save( QString("j:\\project\\QJSnap\\snap\\").append(filename1).append(".jpg"));
        }
    }
    //qDebug() << eleNode.geometry();
    //QImage qq_1(QSize(eleNode.geometry().width(),eleNode.geometry().height()),QImage::Format_ARGB32);
    //painter.begin(&qq_1);
    //eleNode.render(&painter);
    //painter.end();
    //qq_1.save( QString("/home/thankwsx/QJSnap/News_Width1.jpg"));
    //qq_1.save( QString("j:\\project\\QJSnap\\News_Width1.jpg"));
}
