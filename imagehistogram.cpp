#include "imagehistogram.h"


void Histogrammm::init(){
    setVisible(false);
    resize(600,100);
    move(620,0);

    plot = NULL;
    histogram  = NULL;
}


Histogrammm::Histogrammm(QWidget *parent) : QWidget(parent){
    init();
}


Histogrammm::Histogrammm(QImage img,int type, PictureMode *pm, QWidget *parent) :
    QWidget(parent)
{
    init();
    initPlot(pm);
    drawHistogram(img);
}


Histogrammm::Histogrammm(std::vector<unsigned short>&data, PictureMode *pm, QWidget *parent) :
    QWidget(parent)
{
    init();
    initPlot(pm);
    drawHistogram(data);
}


Histogrammm::~Histogrammm(){
    delete histogram;
    delete plot;
}


void Histogrammm::initPlot(PictureMode *pm){
    histogram = new HistogramItem();
    histogram->setColor(Qt::darkCyan);
    plot = new MyPlot(QwtText("Histograma"),pm, this);
    plot->resize(350,100);
    plot->setAutoFillBackground(true);
}


void Histogrammm::drawing(double val[], int sizeArray){
    double pos = 0.0;
    const int numValues = sizeArray;
    QwtArray<QwtDoubleInterval> intervals(numValues);
    QwtArray<double> values(numValues);
    for ( int i = 0; i < (int)intervals.size(); i++ ){
        const int width = 1;
        const int value = (int)val[i];
        intervals[i] = QwtDoubleInterval(pos, pos + double(width));
        values[i] = value;
        pos += width;
    }

    histogram->setData(QwtIntervalData(intervals, values));
    histogram->attach(plot);
    setVisible(true);
    plot->replot();
    delete[] val;
}


void MyPlot::drawLimits(QPainter *p, int maxHistVal){
    int l = picMode->getLBorder();
    int r = picMode->getRBorder();
    double w1 = this->width()-62;
    double coef = w1/maxHistVal;
    int lBord = l*coef;
    int rBord = r*coef;
    p->drawLine(4+lBord, 0, 4+lBord, 20000);
    p->drawLine(4+rBord, 0, 4+rBord, 20000);
}

void MyPlot::drawCanvas(QPainter *p){
    QwtPlot::drawCanvas(p);
    p->setPen(QPen(Qt::red, 1));
    if(picMode->getPictureMode() == IS_16BITIMG_GREY){
        drawLimits(p, 70000);
    }
    else if (picMode->getPictureMode() == IS_RGBIMG_GREY ||
             picMode->getPictureMode() == IS_8BITIMG_GREY ||
             picMode->getPictureMode() == IS_8BITIMG_COLOR){
        drawLimits(p, 300);
   }
}


void Histogrammm::drawHistogram(std::vector<unsigned short> & vec){
    int sizeArray = 65536;
    double *val = new double [sizeArray];
    for (int i = 0; i < sizeArray; i++)
    {
        val[i]=0;
    }
    std::vector<unsigned short>::iterator iter;
    iter = vec.begin();
    for (iter; iter<vec.end(); iter++){
        val[*iter]+=1;
    }
    drawing(val, sizeArray);
}


void Histogrammm::SetVectorData_Grey(double val[], QImage &im){
    for (int i = 0; i<im.height(); i++){
        unsigned char* line = im.scanLine(i);
        for( int x = 0;  x < im.width();  ++x ){
            val[line[x]] +=1;
        }
    }
}


void Histogrammm::SetVectorData_Color(double val[], QImage &im){
    if( im.format() != QImage::Format_RGB32 )
        im = im.convertToFormat( QImage::Format_RGB32 );
    int i = 0;
    int sizeArray = 256;
    int *r = new int [sizeArray];
    int *g = new int [sizeArray];
    int *b = new int [sizeArray];
    for (i; i<sizeArray; i++){
        r[i]= g[i]= b[i]= 0;
    }

    for( int y = 0; y < im.height(); ++y ) {
        QRgb* line = reinterpret_cast< QRgb* >( im.scanLine( y ));
        for( int x = 0;  x < im.width();  ++x ){
            r[qRed(line[x])] += 1;
            g[qGreen(line[x])] += 1;
            b[qBlue(line[x])] += 1;
        }
    }
    for (i = 0; i<sizeArray; i++){
        val[i] = (r[i]+g[i]+b[i])/3.0;
    }
    delete[] r;
    delete[] g;
    delete[] b;
}


void Histogrammm::drawHistogram(QImage im){
        int sizeArray = 256;
        im.detach();
        double *val = new double [sizeArray];
        for (int i = 0; i < sizeArray; i++)
        {
            val[i]=0;
        }
        if (im.format() == QImage::Format_Indexed8){
            SetVectorData_Grey(val, im);
        }
        else{
            SetVectorData_Color(val, im);
        }
        drawing(val, sizeArray);
}
