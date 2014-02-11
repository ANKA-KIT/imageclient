#include "imagehistogram.h"

void ImageHistogramPlot::drawLimits(QPainter *p, int maxHistVal){
    int l = lBorder;
    int r = rBorder;
    double w1 = this->width()-62;
    double coef = w1/maxHistVal;
    int lBord = l*coef;
    int rBord = r*coef;
    p->drawLine(4+lBord, 0, 4+lBord, 20000);
    p->drawLine(4+rBord, 0, 4+rBord, 20000);
}


void ImageHistogramPlot::drawCanvas(QPainter *p){
    QwtPlot::drawCanvas(p);
    p->setPen(QPen(Qt::red, 1));
    if(pictureMode == ImagePictureMode::IS_16BITGRAY){
        drawLimits(p, 70000);
    }
    else if (pictureMode == ImagePictureMode::IS_RGBGRAY ||
             pictureMode == ImagePictureMode::IS_8BIT){
        drawLimits(p, 300);
   }
}



class HistogramItem::PrivateData
{
public:
    int attributes;
    QwtIntervalData data;
    QColor color;
    double reference;
};

HistogramItem::HistogramItem(const QwtText &title):
    QwtPlotItem(title)
{
    init();
}

HistogramItem::HistogramItem(const QString &title):
    QwtPlotItem(QwtText(title))
{
    init();
}

HistogramItem::~HistogramItem()
{
    delete d_data;
}

void HistogramItem::init()
{
    d_data = new PrivateData();
    d_data->reference = 0.0;
    d_data->attributes = HistogramItem::Auto;

    setItemAttribute(QwtPlotItem::AutoScale, true);
    setItemAttribute(QwtPlotItem::Legend, true);

    setZ(20.0);
}

void HistogramItem::setBaseline(double reference)
{
    if ( d_data->reference != reference )
    {
        d_data->reference = reference;
        itemChanged();
    }
}

double HistogramItem::baseline() const
{
    return d_data->reference;
}

void HistogramItem::setData(const QwtIntervalData &data)
{
    d_data->data = data;
    itemChanged();
}

const QwtIntervalData &HistogramItem::data() const
{
    return d_data->data;
}

void HistogramItem::setColor(const QColor &color)
{
    if ( d_data->color != color )
    {
        d_data->color = color;
        itemChanged();
    }
}

QColor HistogramItem::color() const
{
    return d_data->color;
}

QwtDoubleRect HistogramItem::boundingRect() const
{
    QwtDoubleRect rect = d_data->data.boundingRect();
    if ( !rect.isValid() )
        return rect;

    if ( d_data->attributes & Xfy )
    {
        rect = QwtDoubleRect( rect.y(), rect.x(),
            rect.height(), rect.width() );

        if ( rect.left() > d_data->reference )
            rect.setLeft( d_data->reference );
        else if ( rect.right() < d_data->reference )
            rect.setRight( d_data->reference );
    }
    else
    {
        if ( rect.bottom() < d_data->reference )
            rect.setBottom( d_data->reference );
        else if ( rect.top() > d_data->reference )
            rect.setTop( d_data->reference );
    }

    return rect;
}


int HistogramItem::rtti() const
{
    return QwtPlotItem::Rtti_PlotHistogram;
}

void HistogramItem::setHistogramAttribute(HistogramAttribute attribute, bool on)
{
    if ( bool(d_data->attributes & attribute) == on )
        return;

    if ( on )
        d_data->attributes |= attribute;
    else
        d_data->attributes &= ~attribute;

    itemChanged();
}

bool HistogramItem::testHistogramAttribute(HistogramAttribute attribute) const
{
    return d_data->attributes & attribute;
}

void HistogramItem::draw(QPainter *painter, const QwtScaleMap &xMap,
    const QwtScaleMap &yMap, const QRect &) const
{
    const QwtIntervalData &iData = d_data->data;

    painter->setPen(QPen(d_data->color));

    const int x0 = xMap.transform(baseline());
    const int y0 = yMap.transform(baseline());

    for ( int i = 0; i < (int)iData.size(); i++ )
    {
        if ( d_data->attributes & HistogramItem::Xfy )
        {
            const int x2 = xMap.transform(iData.value(i));
            if ( x2 == x0 )
                continue;

            int y1 = yMap.transform( iData.interval(i).minValue());
            int y2 = yMap.transform( iData.interval(i).maxValue());
            if ( y1 > y2 )
                qSwap(y1, y2);

            if ( i < (int)iData.size() - 2 )
            {
                const int yy1 = yMap.transform(iData.interval(i+1).minValue());
                const int yy2 = yMap.transform(iData.interval(i+1).maxValue());

                if ( y2 == qwtMin(yy1, yy2) )
                {
                    const int xx2 = xMap.transform(
                        iData.interval(i+1).minValue());
                    if ( xx2 != x0 && ( (xx2 < x0 && x2 < x0) ||
                                          (xx2 > x0 && x2 > x0) ) )
                    {
                       // One pixel distance between neighboured bars
                       y2++;
                    }
                }
            }

            drawBar(painter, Qt::Horizontal,
                QRect(x0, y1, x2 - x0, y2 - y1));
        }
        else
        {
            const int y2 = yMap.transform(iData.value(i));
            if ( y2 == y0 )
                continue;

            int x1 = xMap.transform(iData.interval(i).minValue());
            int x2 = xMap.transform(iData.interval(i).maxValue());
            if ( x1 > x2 )
                qSwap(x1, x2);

            if ( i < (int)iData.size() - 2 )
            {
                const int xx1 = xMap.transform(iData.interval(i+1).minValue());
                const int xx2 = xMap.transform(iData.interval(i+1).maxValue());

                if ( x2 == qwtMin(xx1, xx2) )
                {
                    const int yy2 = yMap.transform(iData.value(i+1));
                    if ( yy2 != y0 && ( (yy2 < y0 && y2 < y0) ||
                                    (yy2 > y0 && y2 > y0) ) )
                    {
                        // One pixel distance between neighboured bars
                        x2--;
                    }
                }
            }
            drawBar(painter, Qt::Vertical,
                QRect(x1, y0, x2 - x1, y2 - y0) );
        }
    }
}

void HistogramItem::drawBar(QPainter *painter,
   Qt::Orientation, const QRect& rect) const
{
   painter->save();

   const QColor color(painter->pen().color());
#if QT_VERSION >= 0x040000
   const QRect r = rect.normalized();
#else
   const QRect r = rect.normalize();
#endif

   const int factor = 125;
   const QColor light(color.light(factor));
   const QColor dark(color.dark(factor));

   painter->setBrush(color);
   painter->setPen(Qt::NoPen);
   QwtPainter::drawRect(painter, r.x() + 1, r.y() + 1,
      r.width() - 2, r.height() - 2);
   painter->setBrush(Qt::NoBrush);

   painter->setPen(QPen(light, 2));
#if QT_VERSION >= 0x040000
   QwtPainter::drawLine(painter,
      r.left() + 1, r.top() + 2, r.right() + 1, r.top() + 2);
#else
   QwtPainter::drawLine(painter,
      r.left(), r.top() + 2, r.right() + 1, r.top() + 2);
#endif

   painter->setPen(QPen(dark, 2));
#if QT_VERSION >= 0x040000
   QwtPainter::drawLine(painter,
      r.left() + 1, r.bottom(), r.right() + 1, r.bottom());
#else
   QwtPainter::drawLine(painter,
      r.left(), r.bottom(), r.right() + 1, r.bottom());
#endif

   painter->setPen(QPen(light, 1));

#if QT_VERSION >= 0x040000
   QwtPainter::drawLine(painter,
      r.left(), r.top() + 1, r.left(), r.bottom());
   QwtPainter::drawLine(painter,
      r.left() + 1, r.top() + 2, r.left() + 1, r.bottom() - 1);
#else
   QwtPainter::drawLine(painter,
      r.left(), r.top() + 1, r.left(), r.bottom() + 1);
   QwtPainter::drawLine(painter,
      r.left() + 1, r.top() + 2, r.left() + 1, r.bottom());
#endif

   painter->setPen(QPen(dark, 1));

#if QT_VERSION >= 0x040000
   QwtPainter::drawLine(painter,
      r.right() + 1, r.top() + 1, r.right() + 1, r.bottom());
   QwtPainter::drawLine(painter,
      r.right(), r.top() + 2, r.right(), r.bottom() - 1);
#else
   QwtPainter::drawLine(painter,
      r.right() + 1, r.top() + 1, r.right() + 1, r.bottom() + 1);
   QwtPainter::drawLine(painter,
      r.right(), r.top() + 2, r.right(), r.bottom());
#endif

   painter->restore();
}







void ImageHistogram::init(){
    setVisible(false);
    resize(400,300);
    //move(0,120);

    //plot = NULL;
    histogram  = new HistogramItem();// NULL;
    histogram->setColor(Qt::darkCyan);
    plot = new ImageHistogramPlot(QwtText("Histogram"),this);
    plot->resize(400,300);
    plot->setAutoFillBackground(true);
}


ImageHistogram::ImageHistogram(QWidget *parent) : QWidget(parent){
    init();
}


ImageHistogram::ImageHistogram(QImage img, int pm, int l, int r, QWidget *parent) :
    QWidget(parent)
{
    init();
    initPlot(pm, l, r);
    drawHistogram(img);
}


ImageHistogram::ImageHistogram(QVector<unsigned short>&data, int pm, int l, int r, QWidget *parent) :
    QWidget(parent)
{
    init();
    initPlot(pm, l, r);
    drawHistogram(data);
}


ImageHistogram::~ImageHistogram(){
    delete histogram;
    delete plot;
}


void ImageHistogram::initPlot(int pm, int l, int r){
    histogram = new HistogramItem();
    histogram->setColor(Qt::darkCyan);
    plot = new ImageHistogramPlot(QwtText(" "),pm,l,r, this);
    plot->resize(400,300);
    plot->setAutoFillBackground(true);
}


void ImageHistogram::drawing(double val[], int sizeArray){
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

void ImageHistogram::drawHistogram(QVector<unsigned short> &vec){
    int sizeArray = 65536;
    double *val = new double [sizeArray];
    for (int i = 0; i < sizeArray; i++) {
        val[i]=0;
    }
    for (QVector<unsigned short>::iterator iter = vec.begin(); iter < vec.end(); iter++){
        val[*iter] += 1;
    }
    drawing(val, sizeArray);
}


void ImageHistogram::SetVectorData_Grey(double val[], QImage &im){
    for (int i = 0; i<im.height(); i++){
        unsigned char* line = im.scanLine(i);
        for( int x = 0;  x < im.width();  ++x ){
            val[line[x]] +=1;
        }
    }
}


void ImageHistogram::SetVectorData_Color(double val[], QImage &im){
    if( im.format() != QImage::Format_RGB32 )
        im = im.convertToFormat( QImage::Format_RGB32 );
    int i = 0;
    int sizeArray = 256;
    int *r = new int [sizeArray];
    int *g = new int [sizeArray];
    int *b = new int [sizeArray];
    for (i=0; i<sizeArray; i++){
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


void ImageHistogram::drawHistogram(QImage im){
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
