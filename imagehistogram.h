#ifndef qqq
#define qqq

#include <histogram_item.h>
#include <picturemode.h>
#include <QResizeEvent>


/*!
  \author Georgii Vasilev
  \class MyPlot
  \brief Widget for displaying histogram
  ///Widget for displaying histogram. Is a child of QwtPlot class
*/
class MyPlot : public QwtPlot{
public:
    PictureMode *picMode; /*!< picture mode pointer (mustn't be deleted)*/

    /*!
     \brief Basic constructor
    */
    MyPlot(const QwtText &t, PictureMode *pm, QWidget*p ) :QwtPlot(t,p){ picMode = pm;}

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

class Histogrammm : public QWidget
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
    void initPlot(PictureMode *pm);

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
    MyPlot *plot;
    /*!
     \brief calculating data for drawing
     \param im - image for draving histogram
    */
    void drawHistogram(QImage im);
    /*!
     \brief calculating data for drawing
     \param vec - 16bit data for drawing
    */
    void drawHistogram(std::vector<unsigned short> & vec);
    /*!
     \brief Constructor for IS_16BITGREY_MODE
     \param data - data for drawing histogram
     \param pm - seting picturemode pointer
     \param parent - parent widget pointer
    */
    Histogrammm(std::vector<unsigned short> &data, PictureMode *pm,QWidget *parent = 0);
    /*!
     \brief Constructor for not IS_16BITGREY_MODE
     \param img - current image
     \param pm - seting picturemode pointer
     \param parent - parent widget pointer
     \param type - NOT USED FOR CURRRENT VERSION (used drawHistogram(QImage im) "207 line")
    */
    Histogrammm(QImage,int type, PictureMode *pm, QWidget *parent = 0);
    /*!
     \brief basic constructor with null values initing
    */
    explicit Histogrammm(QWidget *parent = 0);
    /*!
     \brief Destructor
    */
    ~Histogrammm();
};

#endif // qqq
