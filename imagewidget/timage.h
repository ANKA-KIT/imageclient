#ifndef TIMAGE_H
#define TIMAGE_H

#include "eimagebase.h"
#include "TImageSnapshot"
#include "etangodevice.h"
#include <QCoreApplication>
#include <QTimer>

class ImageMarker;
class RoiAction;

/**
 * \brief a widget for displaying current image from TANGO
 *
 */
class TImage : public EImageBase, public TDevice
{
    Q_PROPERTY(int period READ period WRITE setPeriod)
    Q_PROPERTY(bool pause READ pause WRITE setPause)

    Q_OBJECT
private:
    bool roiAddedFromServer;
    /**
     * \brief Set pause on getting new image from TANGO
     *
     * @see setPause
     * @see pause
     **/
    bool _pause;
    bool _serverMode;

    QVector<double> initParametersVector();
    void writeMarkerColorToDevice(ImageMarker *m);
    void writeMarkerSizeToDevice(ImageMarker *m);
    void writeMarkerThicknessToDevice(ImageMarker *m);
    void writeMarkerRoiToDevice(Tango::DevULong x0, Tango::DevULong y0, Tango::DevULong width, Tango::DevULong height);
public:
    /**
     * \brief Allow preparing new coming data for displaying
     *
     **/
    bool canLoadnewPic;

    /**
     * \brief Time between preparing new data for displaying
     *
     **/
    QTime time;

    /**
     * \brief Time of preparing current data for displaying
     *
     **/
    QTime timeWorking;

    TImage(QWidget *parent, Qt::WFlags f=0);
    ~TImage();

    /** \brief Get pause value
    *
    * @see _pause
    * @see setPause
    **/
    bool pause() {return _pause;}

    /** \brief Make snapshot of whole image with markers
    *
    **/
    TImageSnapshot* makeSnpImage(QWidget *scr);

    /** \brief Make snapshot of visiable part image with markers
    *
    **/
    TImageSnapshot* makeSnpImageCat(QWidget *scr);

    /** \brief Make snapshot of ROI(region of interests) image with markers
    *
    **/
    TImageSnapshot* makeSnpImageCat(QRect rec, QWidget *scr);

    /** \brief Get whole image without any trnsformation
    *
    **/
    QImage makeSnpImage();

    bool serverMode(){return _serverMode;}

    QList<QRect> roiList;
    QList<ImageMarker*> serverMarkerList;
    int serverMarkerCount;
    QList<RoiAction*> roiActionList;
    QList<RoiAction*> serverRoiActionList;
    RoiAction* initRoi(QPoint,QPoint);
signals:
    /** \brief New picture is ready (without any transformation)
    *
    **/
    void newPicture(QVector <unsigned short>, int,int,int);
    void newPicture(QImage, int,int,int);
    void newPicture(QImage, TImage*);

    /** \brief Picture size
    *
    **/
    void newPictureDim(int, int);

    /** \brief Getting new picture is paused
    *
    *   @see setPause
    **/
    void isPaused();

    /** \brief Reqred time for displaying and getting new picture
    *
    **/
    void timeNewPic(int);
    void timePicDisplaying(int);
    void ROIlist(TImage*, QList<QRect>);
    void addRoi(RoiAction*);
public slots:
    void onRoiDelete(RoiAction *pointer);

    void setServerMode(bool );
    /** \brief change the period of the readings. This is a slot.
     *
     */
    void setPeriod(int p);

    /** \brief Set transformation and display image. This is a slot.
     *
     */
    void draw(QImage img);

    void drawInServerMode(QImage img);

    /** \brief Show property window. This is a slot.
     *
     */
    void showParams();

    /** \brief Set pause value
    *
    * @see _pause
    * @see pause
    **/
    void setPause(bool value);

    void writeProperty();
    void writeProperty(QVector<double>);
    void writeMarker(QPoint p, QRgb col);
    void writeROI(QPoint p1,QPoint p2);

    void delMarker(QPoint p, QRgb col);
    void delROI(QPoint p1,QPoint p2);
protected slots:
    /**
     * \brief Set signals for drawing histogram in property window on newPicture
     */
    void autoDrawingHistogram(bool val);

    void refresh(const TVariant &);
    void syncMarker(ImageMarker *m);
    void markerDeleted();
    void colorChanged(ImageMarker *m);
    void markerResized(ImageMarker *m);
};

#endif // TIMAGE_H
