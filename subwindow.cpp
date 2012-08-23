#include "subwindow.h"

SubWindow::SubWindow(QMdiSubWindow *parent) :
    QMdiSubWindow(parent)
{
    _setOffMarker = new QAction(tr("&Set off Marker"), this);
    _setOffMarker->setStatusTip(tr("&Set off Marker"));
    QObject::connect(_setOffMarker, SIGNAL(triggered()), this, SLOT(setOffMarker()));
    qDebug("in SubWindow Construcotr");
    scrollArea = NULL;//new QScrollArea(this);
    setAutoFillBackground(true);

 //   QObject::connect(this,SIGNAL(windowStateChanged(Qt::WindowStates,Qt::WindowStates )),
//                     this,SLOT(handleWindowStateChanged(Qt::WindowStates,Qt::WindowStates )));

}

SubWindow::~SubWindow(){
    qDebug("in SubWindow Destructor");
    delete wgt;
    delete lbRot;
    delete lbBr;
    delete lbCon;
    delete lbGam;
    delete lbScl;
    delete lbHorFl;
    delete lbVerFl;
    delete board;
    delete scrollArea;
}

void SubWindow::initLb(int x){
    lbRot = new QLabel(board);
    lbRot->setObjectName(QString::fromUtf8("lbRot"));
    lbRot->setGeometry(QRect(5+x, 3, 50, 27));

    lbBr = new QLabel(board);
    lbBr->setObjectName(QString::fromUtf8("lbBr"));
    lbBr->setGeometry(QRect(55+x, 3, 105, 27));

    lbCon = new QLabel(board);
    lbCon->setObjectName(QString::fromUtf8("lbCon"));
    lbCon->setGeometry(QRect(100+x, 3, 150, 27));

    lbGam = new QLabel(board);
    lbGam->setObjectName(QString::fromUtf8("lbGam"));
    lbGam->setGeometry(QRect(155+x, 3, 205, 27));

    lbScl = new QLabel(board);
    lbScl->setObjectName(QString::fromUtf8("lbScl"));
    lbScl->setGeometry(QRect(210+x, 3, 260, 27));

    lbHorFl = new QLabel(board);
    lbHorFl->setObjectName(QString::fromUtf8("lbHorFl"));
    lbHorFl->setGeometry(QRect(270+x, 3, 310, 27));

    lbVerFl = new QLabel(board);
    lbVerFl->setObjectName(QString::fromUtf8("lbVerFl"));
    lbVerFl->setGeometry(QRect(315+x, 3, 370, 27));

    lbBr->setWordWrap(true);
    lbRot->setWordWrap(true);
    lbCon->setWordWrap(true);
    lbGam->setWordWrap(true);
    lbScl->setWordWrap(true);
    lbHorFl->setWordWrap(true);
    lbVerFl->setWordWrap(true);

    lbBr->setText("Br:\n n/a");
    lbRot->setText("Rot:\n n/a");
    lbCon->setText("Con:\n n/a");
    lbGam->setText("Gam:\n n/a");
    lbScl->setText("Scl:\n n/a");
    lbHorFl->setText("H_Fl:\n n/a");
    lbVerFl->setText("V_Fl:\n n/a");
}

void SubWindow::setLbBr(QVariant val){
     lbBr->setText("Br:\n "+val.toString());
}
void SubWindow::setLbRot(QVariant val){
    lbRot->setText("Rot:\n "+val.toString());
}
void SubWindow::setLbCon(QVariant val){
    lbCon->setText("Con:\n "+val.toString());
}
void SubWindow::setLbGam(QVariant val){
    lbGam->setText("Gm:\n "+val.toString());
}
void SubWindow::setLbScl(QVariant val){
    bool isDouble = false;
    double valDouble = val.toDouble(&isDouble);
    if (isDouble){
        lbScl->setText("Scl:\n "+QString().number(valDouble,'g',4));
    }
    else
        lbScl->setText("Scl:\n "+val.toString());
}
void SubWindow::setLbHFlip(QVariant val){
    lbHorFl->setText("HFl:\n "+val.toString());
}
void SubWindow::setLbVFlip(QVariant val){
    lbVerFl->setText("VFl:\n "+val.toString());
}

void SubWindow::chImageMode(int mode){
   delete wgt->picMode;
    wgt->picMode = NULL;
    switch(mode){
    case IS_RGBIMG_COLOR:
        wgt->setRGBImgColorMode();
        break;
    case IS_16BITIMG_GREY:
        wgt->set16BitImgGreyMode();
        break;
    case IS_16BITIMG_RGB:
        wgt->set16BitImgRGBMode();
        break;
    case IS_RGBIMG_GREY:
        wgt->setRGBImgGreyMode();
        break;
    case IS_8BITIMG_GREY:
        wgt->set8BitImgGreyMode();
        break;
    case IS_8BITIMG_COLOR:
        wgt->set8BitImgColorMode();
        break;
    }
}

void SubWindow::send16BitDataSlot(){
    emit send16BitDataDirect(wgt->valUSh);
}

void SubWindow::calcFullPictureScale(int width, int height){
   wgt->calcFullPictureScale(width, height, _space);
}

void SubWindow::setActionMenu(QList<QAction *> acts){
    contextMenu.addActions(acts);
    contextMenu.addAction(_setOffMarker);
}

void SubWindow::ShowContextMenu(const QPoint& pos){
    QPoint globalPos = this->mapToGlobal(pos);
    contextMenu.popup(globalPos);
}

void SubWindow::setOffMarker(){
    wgt->isMarked = false;
}
