#include <QtGui/QApplication>
#include "widget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    QWidget *w1= new QWidget(&w);
    QWidget *w2= new QWidget(&w);
    QPalette p1;
    QPalette p2;
    p1.setColor(w1->backgroundRole(), Qt::red);
    p2.setColor(w2->backgroundRole(), Qt::blue);

    w1->setPalette(p1);
    w2->setPalette(p2);

    w1->resize(40,20);
    w2->resize(25,50);
    w1->move(10,10);
    w2->move(25,15);
    w1->setAutoFillBackground(true);
    w2->setAutoFillBackground(true);
    w.show();

    return a.exec();
}
