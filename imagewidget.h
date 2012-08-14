#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <tango.h>
#include <imgmanipulation.h>
#include <picturemode.h>
#include <QScrollArea>

#include <opencv/cv.h>
#include <opencv/highgui.h>

/*!
  \file imagewidget.h
  \author Georgii Vasilev
  \class ImageWidget
  \brief Widget for displaying device image
  ///Widget for background drawing device image
*/
class ImageWidget : public QWidget
{
    Q_OBJECT
private:
    /*!
        \brief recalculate image with limits
        \param valdata - picture data
        \param X - width of image
        \param Y - height of image
    */
    void recalcGreyImg(vector <unsigned char> &valData, int X, int Y);

    /*!
        \brief recalculate image with limits
    */
    void recalcGreyImg16Bit();

    /*!
        \brief set _OriginImg with new scale
    */
    void setOriginImg();
public:

    QImage *img;                /*!< image object which used for displaying*/
    QImage *_OriginImg;          /*!< copy of image for manipulation (NOT FOR 16bit gamma,brightness,contrast)*/
    QImage *_originSnap;        /*!< copy of image for manipulation (FOR 16bit gamma,brightness,contrast)*/
    int imgType;                /*!< duble information (picmode->_pictureMode)*/
    ImgManipulation* manip;     /*!< Manipulation stuff for image*/
    vector <unsigned short> valUSh;  /*!< Vector of 16bit image data from tangodevice*/
    //int curDataFormat;
    PictureMode *picMode;       /*!< Information about picture mode*/
    int ImgDimX;                /*!< Width image value, uses for calculating correct scale value in full picture mode*/
    int ImgDimY;                /*!< Height image value, uses for calculating correct scale value in full picture mode*/
    int _curMouseX;             /*!< Current X-mouse positsion in picture*/
    int _curMouseY;             /*!< Current Y-mouse positsion in picture*/
    int _clickedMouseX;         /*!< Last X-mouse clicked positsion in picture*/
    int _clickedMouseY;         /*!< Last Y-mouse clicked positsion in picture*/

    int originWidth;                /*!< Width of 16 bit image*/
    int originHeight;                /*!< Height of 16 bit image*/
    /*!
        \brief Constructor for realtime subwindow
    */
    explicit ImageWidget(QWidget *parent = 0);

    /*!
        \brief Keep Real picture size;
    */
    void setPicSize(int x, int y);

    /*!
        \brief Constructor for snapshot subwindow
        \param image - current realtime picture (for snapshot)
    */
    ImageWidget( QImage* image, QWidget *parent = 0);

    /*!
        \brief resize widget
        \param x - width
        \param y - height
    */
    void resizeWgt(int x, int y);

    /*!
        \brief set image as background image in widget
        \param img - image for displaying in wiget
    */
    void paintImg(QImage& img);

    /*!
        \brief set all changes (brightness, rotation, etc.) on image
    */
    void setClientValues();

    /*!
        \brief NOT USED!!
    */
    void makeSnpFromWgt();

    /*!
        \brief NOT USED!!
    */
    void makeSnpFromImg();

    /*!
        \brief Reaction on mouse press in widget
    */

    void mousePressEvent ( QMouseEvent * e);

    /*!
        \brief Reaction on mouse move in widget
    */
    void mouseMoveEvent ( QMouseEvent * e);

    /*!
        \brief Painting on widget
    */
    void paintEvent( QPaintEvent * e);

    /*!
        \brief Setting IS_8BITIMG_GREY mode for 8bit greyscale image
    */
    void set8BitImgGreyMode();

    /*!
        \brief Setting IS_16BITIMG_GREY mode for 16bit greyscale image
    */
    void set16BitImgGreyMode();

    /*!
        \brief Setting IS_RGBIMG_GREY mode for RGB image to set image greyscale
    */
    void setRGBImgGreyMode();

    /*!
        \brief Setting IS_RGBIMG_COLOR mode for RGB image
    */
    void setRGBImgColorMode();

    /*!
        \brief Setting IS_8BITIMG_COLOR mode for 8bit color image
    */
    void set8BitImgColorMode();

    /*!
        \brief Setting ImgDimX, ImgDimY
        \param x - ImgDimX
        \param y - ImgDimY
    */
    void setPicSetings(int x, int y);

    /*!
        \brief getting vector image from Image
        \param val - vector which will keep image
        \param w - image width
        \param h - image height
    */
    void getImageVector(vector<unsigned char>& val, int w, int h);

    /*!
        \brief Recalculate image values with new image levels (left-right border)
    */
    void calcGreyImg();

    /*!
        \brief set default values
    */
    void resetClientSideVal();

    /*!
        \brief Rescale snapshot image
        \param val - Scale value
    */
    void setScaleSnap(double val);

    /*!
        \brief Calculate new scale, depends from subwindow size (uses in full picture mode)
        \param width - image width
        \param height - image height
        \param space - some space to set image correct
    */
    void calcFullPictureScale(int width, int height, int space);

    /*!
        \brief Destructor
    */
    ~ImageWidget();

signals:
    void resizeImgWgt(int X, int Y);    /*!< subwindow should be resized with new image size(repaint) \param X - widget width \param Y - widget height */
    void repainting();                  /*!< need in repainting*/
   // void mkSnapshotRealtime(QImage*,ImgManipulation*);  /*!< make snapshot */
   // void mkSnapshotRealtime();
  //  void mkSnapshotRealtime(ImageWidget *);
    void mousePosition(int x, int y);    /*!< send mouse position \param x - X mouse position \param y - Y mouse position*/
    void mousePositionVal(int RGB, int val);    /*!< send image color value in mouse position \param RGB - RGB [0..255] value \param val - 16bib [0..65535] value*/
    void mousePositionVal(int RGB);             /*!< send image color value in mouse position \param RGB - RGB [0..255] value*/
    void mousePositionVal(int R, int G, int B); /*!< send image color value in mouse position \param R - red value (RGB) [0..255] value \param Green - green value (RGB) [0..255] value \param B - blue value (RGB) [0..255] value*/
    void sendScale(QVariant val);                   /*!< send current scale value \param val - scale value*/

public slots: 
    //void changeImg(int);

    /*!
        \brief Save snapshot
    */
    void saveImg();

    /*!
        \brief Print snapshot (NOT REALESED)
    */
    void printImg();

    /*!
        \brief Set all property on image
    */
    void setAllValues(int );

    /*!
        \brief Repaint image
    */
    void rescreen();

    /*!
        \brief Set imgType value
        \type - value
    */
    void setImgType(int type);
};

#endif // IMAGEWIDGET_H
