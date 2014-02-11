#include "roiclass.h"

#include "eimagescreen.h"
#include "imagemarker.h"

ROIClass::ROIClass(TImage* snp, QWidget*p, QRect rec) :QWidget(p)//: TImageSnapshot(snp->makeSnpImageCat(rec, p))
{
    ptr = snp;
    setWindowTitle(snp->_serverName + " " + QString().number(rec.x()) + "," + QString().number(rec.y())+
                                    + " " + QString().number(rec.x()+rec.width()) + "," + QString().number(rec.y()+rec.height()));
   sample = snp->makeSnpImageCat(rec, p);
  for(int i=0;i<sample->wgt->marker.size(); i++){
       sample->wgt->marker[i]->del();
   }
   sample->wgt->marker.clear();
   int iterX,iterY;
   for (int m=0; m<snp->wgt->marker.count(); m++){
        iterX=-1, iterY=-1;
        if(snp->wgt->marker.at(m)->_xOnPic >= rec.x() && snp->wgt->marker.at(m)->_xOnPic <= rec.x()+rec.width()){//-wgt->limX1
            iterX  = snp->wgt->marker.at(m)->_xOnPic;
        }
        if(snp->wgt->marker.at(m)->_yOnPic >= rec.y()){
            if(snp->wgt->marker.at(m)->_yOnPic <= rec.y()+rec.height())
                iterY  = snp->wgt->marker.at(m)->_yOnPic;
        }
        if (iterX == -1 || iterY==-1){}
        else{
        //*
            sample->wgt->initMarker(QPoint(iterX, iterY));
            sample->wgt->marker.last()->setMarkerColor(snp->wgt->marker.at(m)->_clr);
            sample->wgt->marker.last()->hLineLength = snp->wgt->marker.at(m)->hLineLength;
            sample->wgt->marker.last()->vLineLength = snp->wgt->marker.at(m)->vLineLength;
        //*/
        }
    }
    sample->wgt->recalcMarkerPos();
   sample->setGeometry(0,0,200,200);
   doubleMarker = false;
   connect(snp,SIGNAL(newPicture(QImage,int,int,int)),this,SLOT(onNewFrame(QImage)));
   offset = QPoint(rec.x(),rec.y());
   size = QPoint(rec.x()+rec.width(),rec.y()+rec.height());
   connect(snp,SIGNAL(newMarker(QPoint,QRgb)),this,SLOT(realtimeMarkerInited(QPoint,QRgb)));
   connect(sample->wgt,SIGNAL(newMarker(QPoint,QRgb)),this,SLOT(sendMarker(QPoint,QRgb)));
//   connect(this,SIGNAL(roiMarker(QPoint,QRgb)),snp,SLOT(setMarker(QPoint,QRgb)));

   connect(snp->wgt,SIGNAL(delMarker(QPoint,QRgb)),this,SLOT(realtimeMarkerDeleted(QPoint,QRgb)));
   connect(snp->wgt,SIGNAL(colorChMarker(QPoint,QRgb)),this,SLOT(realtimeMarkerColorChanged(QPoint,QRgb)));


   maxWidth = snp->wgt->picW;
   maxHeight = snp->wgt->picH;


}
void ROIClass::setRect(QPoint p1, QPoint p2){


    sample->dimX = (p2.x()-p1.x())*sample->picMode->getDelimitr();
    sample->dimY = (p2.y()-p1.y());

    sample->wgt->picW = (p2.x()-p1.x());
    sample->wgt->picH = (p2.y()-p1.y());

    offset = p1;
    size = p2;

    for(int i=0;i<sample->wgt->marker.size(); i++){
        ImageMarker *m = sample->wgt->marker[i];
        if ((p1.x() > m->_xOnPic) || (p1.y() > m->_yOnPic) || (p2.x() < m->_xOnPic) || (p2.y() < m->_yOnPic)){
            m->del();
        }
        else{
            m->_xOnPic = ptr->wgt->marker[i]->_xOnPic;
            m->_yOnPic = ptr->wgt->marker[i]->_yOnPic;
            m->_xOnPic -= p1.x();
            m->_yOnPic -= p1.y();
            m->menuAction()->setText("Marker["+QString().number(m->_xOnPic)+";"+QString().number(m->_yOnPic )+"]");
        }
    }
    sample->wgt->recalcMarkerPos();

}

void ROIClass::onNewFrame(QImage im){
    QPoint p1 = offset;
    QPoint p2 = size;
    QPoint temp = p1;

    if (p1.x() > p2.x()){
        p1.setX(p2.x());
        p2.setX(temp.x());
    }
    if (p1.y() > p2.y()){
        p1.setY(p2.y());
        p2.setY(temp.y());
    }
    if (sample->picMode->getPictureMode() != ptr->picMode->getPictureMode()){
        sample->chImageMode( ptr->picMode->getPictureMode());
    }
    sample->__serverMode = ptr->__serverMode;
    sample->setImage(im.copy(p1.x(),p1.y(),p2.x()-p1.x(),p2.y()-p1.y()));
   // sample->setImage(im.copy(p1.x(),p1.y(),p2.x()-p2.y(),p1.x()-p1.y()));
}

void ROIClass::realtimeMarkerInited(QPoint p, QRgb col){
    if (offset.x() < p.x() && offset.y() < p.y() && size.x() > p.x() && size.y() > p.y()){
        doubleMarker = true;
        sample->wgt->initMarker(QPoint(p.x()-offset.x(), p.y() - offset.y()));
        sample->wgt->marker.last()->setMarkerColor(col);
        sample->wgt->recalcMarkerPos();

    }
}

void ROIClass::sendMarker(QPoint p, QRgb col){
    if (!doubleMarker)
        emit roiMarker(QPoint(p.x()+offset.x(),p.y()+offset.y()),col);
    doubleMarker = false;
}

void ROIClass::realtimeMarkerDeleted(QPoint p, QRgb col){
    if (offset.x() < p.x() && offset.y() < p.y() && size.x() > p.x() && size.y() > p.y()){

        for(int i=0;i<sample->wgt->marker.size(); i++){
            ImageMarker *m = sample->wgt->marker[i];
            if ((m->_clr == col) && (m->_xOnPic = p.x()) && (m->_yOnPic == p.y())){
                //sample->wgt->marker[i]->deleteLater();
        sample->wgt->marker[i]->del();
            }
        }
    }
}

void ROIClass::realtimeMarkerColorChanged(QPoint p, QRgb col){
    if (offset.x() < p.x() && offset.y() < p.y() && size.x() > p.x() && size.y() > p.y()){

        for(int i=0;i<sample->wgt->marker.size(); i++){
            ImageMarker *m = sample->wgt->marker[i];
            if ((m->_xOnPic == p.x()-offset.x()) ){
                if (m->_yOnPic == p.y()-offset.y())
                    sample->wgt->marker[i]->setMarkerColor(col);
            }
        }
    }
}

