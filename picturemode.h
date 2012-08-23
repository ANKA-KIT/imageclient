#ifndef PICTUREMODE_H
#define PICTUREMODE_H

#include <QImage>
#include <enum.h>
using namespace std;
/*!
  \file picturemode.h
  \author Georgii Vasilev
  \class PictureMode
  \brief Abstract class, uses for polymorphism
  ///abstract class, uses for polymorphism
*/
class PictureMode
{
protected:
    int _delim;                     /*!< Delimitr (for correct pixel value bytes for pixel)*/
    int _colorFormat;               /*!< QImage::Format value*/
    int _pictureMode;               /*!< index of current picture mode*/

    /*!
        \brief set image from unsigned char vector
        \param width - number of bytes for image width
        \param height - number of bytes for image height
        \param val - data vector
    */
    virtual QImage setImageVal(unsigned int width, unsigned int height, vector <unsigned char>& val);
public:
    int lastDelimetr; /*!< last Delim value, uses for correct displaying in RGBGREY mode */
    /*!
        \brief get picture mode value
        \return _pictureMode
    */
    int getPictureMode();

    /*!
        \brief get right border pixel level value
        \return default right border pixel level value
    */
    virtual int getRBorder(){return 0;}

    /*!
        \brief get left border pixel level value
        \return default left border pixel level value
    */
    virtual int getLBorder(){return 0;}

    /*!
        \brief set right border pixel level value (void method)
    */
    virtual void setRBorder(int){}

    /*! \brief set left border pixel level value (void method) */
    virtual void setLBorder(int){}

    /*!
        \brief set color format value
        \param val - value
    */
    void setColorFormat(int val);

    /*!
        \brief set delimitr value
        \param val - value
    */
    void setDelimitr(int val);

    /*!
        \brief get color format value
        \return _colorFormat
    */
    int getColorFormat();

    /*!
        \brief get Delimitr value
        \return _delim
    */
    int getDelimitr();

    /*!
        \brief Set colorFormat-delimtr
        \param format - color format value
    */
    void changeColorFormat(int format);

    /*!
        \brief Make image (virtual method)
        \param x - number of bytes for image width
        \param y - number of bytes for image height
        \param val - data vector
        \return image
    */
    virtual QImage setImage(int x, int y, vector <unsigned char>& val);

    /*! \brief convert 16 bit data to 8 bit for displaying (virtual void method) */
    virtual void Convert16BitData(vector <unsigned short>& val16, vector <unsigned char>& val8){}

    /*! \brief constructor */
    PictureMode();

    /*!
        \brief Make greyscale image (virtual void method)
        \return greyscale image
    */
    virtual QImage recalcGreyImg(int ,int, vector <unsigned char>& ){ return QImage();}

    /*! \brief recalculate image with new pixel levels (virtual void method)*/
    virtual void recalcColors(vector <unsigned char>& , vector <unsigned char>& ){}

    /*! \brief Destructor  */
    virtual ~PictureMode(){}
};

/*!
  \author Georgii Vasilev
  \class GreyImg
  \brief Parent class for greyscale modes
  ///abstract class, uses for polymorphism
*/
class GreyImg : public PictureMode{
protected:
    int _lBorder;                       /*!< left pixel level border*/
    int _rBorder;                       /*!< right pixel level border*/
    int _maxContrast;                   /*!< maximum contrast value for current picture mode*/
    vector <unsigned char> colorMap;    /*!< color map for correct displaying grayscale image*/
    bool _colorMapChanged;              /*!< is pixel level changed*/

    /*!
        \brief Recalculate color map
    */
    void recalcColorMap();

    /*!
        \brief Set image gray
        \param image - image which will be changed
    */
    void setGreyImg(QImage &image);

public:
    /*!
        \brief Constructor
    */
    GreyImg();

    /*!
        \brief recalculate image with new pixel levels
        \param valColor - input vector
        \param valGrey - vector, which will be set if pixel levels isn't default
    */
    void recalcColors(vector <unsigned char>& valColor, vector <unsigned char>& valGrey);

    /*!
        \brief get right border pixel level value
        \return _rBorder (right border pixel level value)
    */
    int getRBorder();

    /*!
        \brief get left border pixel level value
        \return _lBorder (left border pixel level value)
    */
    int getLBorder();

    /*!
        \brief set right border pixel level value
        \param val - value
    */
    void setRBorder(int val);

    /*!
        \brief set left border pixel level value
        \param val - value
    */
    void setLBorder(int val);

    /*!
        \brief Make greyscale image
        \param x - number of bytes for image width
        \param y - number of bytes for image height
        \param val - data vector
        \return greyscale image
    */
    QImage recalcGreyImg(int x, int y, vector <unsigned char>& val );
};

/*!
  \author Georgii Vasilev
  \class Is16BitGrey
  \brief 16 bit grayscale image mode
  ///Uses for correct displaying and 16 bit picture levels manipulation
*/
class Is16BitGrey : public GreyImg{
public:
    /*!
        \brief Constructor
    */
    Is16BitGrey();

    /*!
        \brief Make image (virtual method)
        \param x - number of bytes for image width
        \param y - number of bytes for image height
        \param val - data vector
        \return image
    */
    virtual QImage setImage(int x, int y, vector <unsigned char>& val);

    /*!
        \brief convert 16 bit data to 8 bit for displaying
        \param val16 - 16 bit data vector
        \param val8 - 8 bit data vector
    */
    void Convert16BitData(vector <unsigned short>& val16, vector <unsigned char>& val8);

    /*!
        \brief recalculate image with new pixel levels
        \param valColor - input vector
        \param valGrey - vector, which will be set if pixel levels isn't default
    */
    void recalcColors(vector <unsigned char>& valColor, vector <unsigned char>& valGrey);
};

/*!
  \author Georgii Vasilev
  \class Is8BitGrey
  \brief 8 bit grayscale image mode
  ///Uses for correct displaying and 8 bit grayscale picture levels manipulation
*/
class Is8BitGrey : public GreyImg{
public:
    /*!
        \brief Constructor
    */
    Is8BitGrey();

    /*!
        \brief Make image (virtual method)
        \param x - number of bytes for image width
        \param y - number of bytes for image height
        \param val - data vector
        \return image
    */
    virtual QImage setImage(int x, int y, vector <unsigned char>& val);

    /*!
        \brief recalculate image with new pixel levels
        \param valColor - input vector
        \param valGrey - vector, which will be set if pixel levels isn't default
    */
    void recalcColors(vector <unsigned char>& valColor, vector <unsigned char>& valGrey);
};

/*!
  \author Georgii Vasilev
  \class IsRGBGGrey
  \brief Converting RGB/RGBA image to grayscale image mode
  ///Converting RGB/RGBA image to 8 bit grayscale image. Uses for correct displaying and 8 bit grayscale picture levels manipulation
*/
class IsRGBGGrey : public GreyImg{
private:
    /*!
        \brief Convert RGB image to 8bit greyscale image
        \param iter - begin pointer of image vector
        \param iterEnd - end pointer of image vector
        \param x - number pixels for width
        \param y - number pixels for height
        \return output 8bit grayscale image
    */
    QImage compressImage(vector<unsigned char>::iterator iter, vector<unsigned char>::iterator iterEnd, int x, int y);

public:
    /*!
        \brief Constructor
    */
    IsRGBGGrey();

    /*!
        \brief Make image (virtual method)
        \param x - number of bytes for image width
        \param y - number of bytes for image height
        \param val - data vector
        \return image
    */
    virtual QImage setImage(int x, int y, vector <unsigned char>& val);

    /*!
        \brief recalculate image with new pixel levels
        \param valColor - input vector
        \param valGrey - vector, which will be set if pixel levels isn't default
    */
    void recalcColors(vector <unsigned char>& valColor, vector <unsigned char>& valGrey);

};

/*!
  \author Georgii Vasilev
  \class IsRGB
  \brief RGB/RGBA image mode
  ///Uses for correct displaying color image
*/
class IsRGB: public PictureMode{
public:
    /*!
        \brief Make image (virtual method)
        \param x - number of bytes for image width
        \param y - number of bytes for image height
        \param val - data vector
        \return image
    */
    virtual QImage setImage(int x, int y, vector <unsigned char>& val);

    /*!
        \brief Constructor
    */
    IsRGB();
};

/*!
  \author Georgii Vasilev
  \class Is8BitColor
  \brief  8 bit color image mode
  ///Uses for correct displaying 8 bit color image
*/
class Is8BitColor : public PictureMode{
public:
    /*!
        \brief Make image (virtual method)
        \param x - number of bytes for image width
        \param y - number of bytes for image height
        \param val - data vector
        \return image
    */
    virtual QImage setImage(int x, int y, vector <unsigned char>& val);

    /*!
        \brief Constructor
    */
    Is8BitColor();
};

/*!
  \author Georgii Vasilev
  \class Is16BitRGB
  \brief 16 bit RGB image mode
  ///Uses for correct displaying and 16 bit Color picture levels manipulation
*/
class Is16BitRGB : public GreyImg{
public:
    /*!
        \brief Constructor
    */
    Is16BitRGB();

    /*!
        \brief Make image (virtual method)
        \param x - number of bytes for image width
        \param y - number of bytes for image height
        \param val - data vector
        \return image
    */
    virtual QImage setImage(int x, int y, vector <unsigned char>& val);

    /*!
        \brief convert 16 bit data to 8 bit for displaying
        \param val16 - 16 bit data vector
        \param val8 - 8 bit data vector
    */
    void Convert16BitData(vector <unsigned short>& val16, vector <unsigned char>& val8);

    /*!
        \brief recalculate image with new pixel levels
        \param valColor - input vector
        \param valGrey - vector, which will be set if pixel levels isn't default
    */
    void recalcColors(vector <unsigned char>& valColor, vector <unsigned char>& valGrey);
};
#endif // PICTUREMODE_H
