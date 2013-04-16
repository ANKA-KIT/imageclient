#ifndef IMAGEHISTOGRAM_H
#define IMAGEHISTOGRAM_H

//My_Code
#include <QResizeEvent>
#include <qglobal.h>
#include <qcolor.h>
#include <qstring.h>
#include <qpainter.h>
#include <qwt_plot.h>
#include <qwt_interval_data.h>
#include <qwt_painter.h>
#include <qwt_scale_map.h>
#include "qwt_plot_item.h"

#include "imagepicturemode.h"
/*!
  \file histogram_item.h
  \author QWT-5.2.1_TUTORIAL
  \class HistogramItem
  \brief Initing Histogram widget
  ///Initing Histogram widget
*/

class QwtIntervalData;
class QString;

class HistogramItem: public QwtPlotItem
{
public:
    explicit HistogramItem(const QString &title = QString::null);
    explicit HistogramItem(const QwtText &title);
    virtual ~HistogramItem();

    void setData(const QwtIntervalData &data);
    const QwtIntervalData &data() const;

    void setColor(const QColor &);
    QColor color() const;

    virtual QwtDoubleRect boundingRect() const;

    virtual int rtti() const;

    virtual void draw(QPainter *, const QwtScaleMap &xMap,
        const QwtScaleMap &yMap, const QRect &) const;

    void setBaseline(double reference);
    double baseline() const;

    enum HistogramAttribute
    {
        Auto = 0,
        Xfy = 1
    };

    void setHistogramAttribute(HistogramAttribute, bool on = true);
    bool testHistogramAttribute(HistogramAttribute) const;

protected:
    virtual void drawBar(QPainter *,
        Qt::Orientation o, const QRect &) const;

private:
    void init();

    class PrivateData;
    PrivateData *d_data;
};




/*!
  \author Georgii Vasilev
  \class ImageHistogramPlot
  \brief Widget for displaying histogram
  ///Widget for displaying histogram. Is a child of QwtPlot class
*/
class ImageHistogramPlot : public QwtPlot{
public:
    //PictureMode *picMode; /*!< picture mode pointer (mustn't be deleted)*/
    int lBorder;
    int rBorder;
    int pictureMode;
    /*!
     \brief Basic constructor
    */
    ImageHistogramPlot(const QwtText &t,QWidget*p ) :QwtPlot(t,p){}
    ImageHistogramPlot(const QwtText &t, int picMode, int l, int r, QWidget*p ) :QwtPlot(t,p){
        pictureMode = picMode;
        lBorder = l;
        rBorder = r;
    }

    /*!
     \brief overloaded method used for drawing limit lines
     \param p - widget painter
    */
    void drawCanvas(QPainter *p);
    /*!
     \brief initing border lines
     \param p - widget painter
     \param maxHistVal - max X
    */
    void drawLimits(QPainter *p, int maxHistVal);
};


/*!
  \file imagehistogram.h
  \author Georgii Vasilev
  \class Histogrammm
  \brief Histogram widget
  ///Histogram widget which wll be displayed for user, based on QWT-5.2.1_tutorial
*/

class ImageHistogram : public QWidget
{
    Q_OBJECT

protected:
    /*!
     \brief initing with null values
    */
    void init();

    /*!
     \brief initing plot
     \param pm - seting picturemode pointer
    */
    void initPlot(int pm, int l, int r);

    HistogramItem *histogram;
    /*!
     \brief drawing gistogram
     \param val - data for drawing
     \param sizeArray - buffer size
    */
    void drawing(double *val, int sizeArray);
    /*!
     \brief calculating data for drawing 8bit image from image
     \param val - result array
     \param im - image for draving histogram
    */
    void SetVectorData_Grey(double val[], QImage &im);
    /*!
     \brief calculating data for drawing RGB image from image
     \param val - result array
     \param im - image for draving histogram
    */
    void SetVectorData_Color(double val[], QImage &im);
public:
    ImageHistogramPlot *plot;
    /*!
     \brief calculating data for drawing
     \param im - image for draving histogram
    */
    void drawHistogram(QImage im);
    /*!
     \brief calculating data for drawing
     \param vec - 16bit data for drawing
    */
    void drawHistogram(QVector<unsigned short> & vec);
    /*!
     \brief Constructor for IS_16BITGREY_MODE
     \param data - data for drawing histogram
     \param pm - seting picturemode pointer
     \param parent - parent widget pointer
    */
    ImageHistogram(QVector<unsigned short> &data, int pm, int l, int r,QWidget *parent = 0);
    /*!
     \brief Constructor for not IS_16BITGREY_MODE
     \param img - current image
     \param pm - seting picturemode pointer
     \param parent - parent widget pointer
     \param type - NOT USED FOR CURRRENT VERSION (used drawHistogram(QImage im) "207 line")
    */
    ImageHistogram(QImage, int pm, int l, int r, QWidget *parent = 0);
    /*!
     \brief basic constructor with null values initing
    */
    explicit ImageHistogram(QWidget *parent = 0);
    /*!
     \brief Destructor
    */
    ~ImageHistogram();
};


//My_Code_End
#endif // IMAGEHISTOGRAM_H
