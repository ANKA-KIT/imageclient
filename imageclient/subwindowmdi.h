#ifndef SUBWINDOW_H
#define SUBWINDOW_H

#include <QObject>
#include <QMdiSubWindow>
#include <QMdiArea>
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>

#include <imagemanipulator.h>
#include <QFormLayout>

class SubWindow : public QMdiSubWindow
{
    Q_OBJECT
protected:
    void setLabelText(QLabel*, QString);
    QVBoxLayout *vbox;
    QWidget *centralWidget;
public:
    enum WINDOW_TYPE{REALTIME, SNAPSHOT};
    QLabel *lbTime;
    QLabel *lbRot;
    QLabel *lbBr;
    QLabel *lbCon;
    QLabel *lbGm;
    QLabel *lbScl;
    QLabel *lbVFl;
    QLabel *lbHFl;
    explicit  SubWindow(int,QMdiSubWindow *parent=0);
signals:
    void winChanged(SubWindow*);
public slots:
    void setTimeDisplay(int);
    void setRotateDisplay(double);
    void setGammaDisplay(int);
    void setBrightnessDisplay(int);
    void setContrastDisplay(int);
    void setHFlipDisplay(bool);
    void setVFlipDisplay(bool);
    void setScaleDisplay(double);

    void handleWindowStateChanged(Qt::WindowStates oldWSt, Qt::WindowStates newWSt);
};

class SetRoiWin: public QDialog{
    Q_OBJECT
public:
    PropertyLineEdit *p1X;
    PropertyLineEdit *p1Y;
    PropertyLineEdit *p2X;
    PropertyLineEdit *p2Y;
    QPushButton *btOk;
    QPushButton *btCancel;

    SetRoiWin(){
        p1X = new PropertyLineEdit((QLineEdit*)this);
        p1Y = new PropertyLineEdit((QLineEdit*)this);
        p2X = new PropertyLineEdit((QLineEdit*)this);
        p2Y = new PropertyLineEdit((QLineEdit*)this);
        resize(250,100);

        btCancel = new QPushButton("Cancel",this);
        btCancel->setStatusTip(tr("Cancel"));
        btCancel->setObjectName(QString::fromUtf8("btCancel"));
        btCancel->setGeometry(QRect(35, 220, 91, 20));
        btOk = new QPushButton("Set",this);
        btOk->setObjectName(QString::fromUtf8("btOk"));
        btOk->setStatusTip(tr("Set Point"));
        btOk->setGeometry(QRect(130, 220, 101, 20));


        QObject::connect(p1X, SIGNAL(setVal(int)), this, SLOT(onOk()));
        QObject::connect(p1Y, SIGNAL(setVal(int)), this, SLOT(onOk()));
        QObject::connect(p2X, SIGNAL(setVal(int)), this, SLOT(onOk()));
        QObject::connect(p2Y, SIGNAL(setVal(int)), this, SLOT(onOk()));

        QObject::connect(btOk, SIGNAL(clicked()),SLOT(onOk()));
        QObject::connect(btCancel, SIGNAL(clicked()), this, SLOT(onCancel()));


        QFormLayout *formLayout = new QFormLayout;
        QHBoxLayout *t = new QHBoxLayout;
        t->addWidget(p1X);
        t->addWidget(p1Y);
        QHBoxLayout *t2 = new QHBoxLayout;
        t2->addWidget(p2X);
        t2->addWidget(p2Y);
        formLayout->addRow(tr("Point Top Left"),t);
        formLayout->addRow(tr("Point Bottom Right"),t2);
        formLayout->addRow(btOk,btCancel);
        setLayout(formLayout);
    }
signals:
    void region(QPoint,QPoint);
public slots:
    void onOk(){
        if (p1X->text().toInt() < 0){p1X->setText("0");}
        if (p1Y->text().toInt() < 0){p1Y->setText("0");}
        if (p2X->text().toInt() <= 0){p2X->setText("9999");}
        if (p2Y->text().toInt() <= 0){p2Y->setText("9999");}
        emit region(QPoint(p1X->text().toInt(),p1Y->text().toInt()), QPoint(p2X->text().toInt(),p2Y->text().toInt()));
        deleteLater();
    }
    void onCancel(){
        deleteLater();
    }
};
#endif // SUBWINDOW_H
