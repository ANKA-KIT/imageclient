#include "subwindowmdi.h"

SubWindow::SubWindow(int type, QMdiSubWindow *parent) : QMdiSubWindow(parent)
{
    setGeometry(0,0,210,200);
    centralWidget = new QWidget(this);
    setWidget(centralWidget);

    vbox = new QVBoxLayout(centralWidget);
    QHBoxLayout *hbox = new QHBoxLayout;//(centralWidget);
    hbox->setMargin(0);
    if (type == REALTIME){
        lbTime  =new QLabel("Time",this);
        lbTime->setWordWrap(true);
        hbox->addWidget(lbTime);
    }


    lbRot  =new QLabel("Rot",centralWidget);
    lbBr  =new QLabel("Br",centralWidget);
    lbCon  =new QLabel("Con",centralWidget);
    lbGm  =new QLabel("Gm",centralWidget);
    lbScl  =new QLabel("Scl",centralWidget);
    lbVFl  =new QLabel("VFl",centralWidget);
    lbHFl  =new QLabel("HFl",centralWidget);


    lbRot->setWordWrap(true);
    lbBr->setWordWrap(true);
    lbCon->setWordWrap(true);
    lbGm->setWordWrap(true);
    lbScl->setWordWrap(true);
    lbVFl->setWordWrap(true);
    lbHFl->setWordWrap(true);


    hbox->addWidget(lbScl);
    hbox->addWidget(lbGm);
    hbox->addWidget(lbCon);
    hbox->addWidget(lbBr);
    hbox->addWidget(lbRot);
    hbox->addWidget(lbHFl);
    hbox->addWidget(lbVFl);

    vbox->setMargin(0);
    vbox->addLayout(hbox);
    vbox->addStretch();
 //   centralWidget->setLayout(vbox);

    connect(this,SIGNAL(windowStateChanged(Qt::WindowStates,Qt::WindowStates )),
                     this,SLOT(handleWindowStateChanged(Qt::WindowStates,Qt::WindowStates )));
}

void SubWindow::setLabelText(QLabel* lb, QString text){
    lb->setText(text);
}

void SubWindow::setTimeDisplay(int val){
    setLabelText(lbTime, "Time\n" + QString().number(val));
}
void SubWindow::setRotateDisplay(double val){
    setLabelText(lbRot, "Rot\n" +QString().number(val));
}
void SubWindow::setGammaDisplay(int val){
    setLabelText(lbGm, "Gm\n" +QString().number(val));
}
void SubWindow::setBrightnessDisplay(int val){
    setLabelText(lbBr, "Br\n" +QString().number(val));
}
void SubWindow::setContrastDisplay(int val){
    setLabelText(lbCon, "Con\n" +QString().number(val));
}
void SubWindow::setHFlipDisplay(bool val){
    QString boolean = "F";
    if (val) boolean = "T";
    setLabelText(lbHFl, "HFl\n" +boolean);
}
void SubWindow::setVFlipDisplay(bool val){
    QString boolean = "F";
    if (val) boolean = "T";
    setLabelText(lbVFl, "VFl\n" +boolean);
}
void SubWindow::setScaleDisplay(double val){
    setLabelText(lbScl, "Scl\n" +QString().number(val));
}

void SubWindow::handleWindowStateChanged(Qt::WindowStates oldWSt, Qt::WindowStates newWSt){
    qDebug("WIN  %d OLD %d NEW %d\n", this, (int)oldWSt, (int)newWSt);
    if(newWSt == Qt::WindowActive && oldWSt == Qt::WindowNoState){
        qDebug("curRealtime handleWindowStateChanged");
        emit winChanged(this);
    }
    if(oldWSt == Qt::WindowActive &&  newWSt == Qt::WindowNoState){
        qDebug("curRealtime handleWindowStateChanged");
        emit winChanged(NULL);
    }
}
