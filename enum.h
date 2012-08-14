#ifndef ENUM_H
#define ENUM_H
/*!
  \file enum.h
  \author Georgii Vasilev
  \brief Defined names for some values
  ///Description of app MACROSes
*/
enum ImageTypes{ IS_16BITIMG_GREY=0     /*!< It is 16 bit greyscale  image*/,
                 IS_RGBIMG_GREY=1       /*!< It is RGB greyscale image*/,
                 IS_RGBIMG_COLOR=2      /*!< It is RGB color image*/,
                 IS_8BITIMG_GREY=3      /*!< It is 8 bit greyscale  image*/,
                 IS_8BITIMG_COLOR=4     /*!< It is 8 bit color image*/
               };
//enum StartParam {ReadFromFile = 2, LoadOneDevice = 4};
//enum StatusOfWork{DevNotSet = 1, Work = 0, Error = 2};
//enum Options{HELP = 'h', TANGO_HOST = 't', DEVICE = 'd', ATTRIBUTE = 'a', FILE_NAME = 'f', COMMAND = 'c', UNKNOWN_SYMBOL = '?'};

enum VideoSettingsWinValue{ BRIGHTNESS = 0 /*!< it is Brightness*/, CONTRAST = 1 /*!< it is Contrast*/, GAMMA = 2 /*!< it is Gamma*/,
                            ROTATION = 3 /*!< it is Rotation*/, SCALE = 4 /*!< it is Scale*/,
                            HOR_FLIP = 5 /*!< it is Horizontal Fliping (HorFlip)*/, VER_FLIP = 6 /*!< it is Vertical Fliping (VerFlip)*/,

                            BRIGHTNESS_CH_ON = 7 /*!< change Brightness on*/, CONTRAST_CH_ON = 8 /*!< change Brightness on*/,
                            GAMMA_CH_ON = 9 /*!< change Gamma on*/, ROTATION_CH_ON = 10 /*!< change Rotation on*/,
                            SCALE_CH_ON = 11 /*!< change Scale on*/, TANGO_COM = 12 /*!< It is Tango command*/,
                            IMAGE = 13 /*!< It is Image*/, IMAGE_16BIT_DATA = 14 /*!< It is 16 bit Image data*/,
                            CALC_STAT = 15 /*!< It is "have server calculate static"*/, STAT = 16 /*!< It is "have server static info"*/,
                            REALTIMETIMEOUT = 17 /*!< Realtime timeout data*/
                          };
enum TangoDataTypes{ IS_USHORT_DATA = 6 /*!< It is unsigned short data*/,
                     IS_UCHAR_DATA = 22 /*!< It is unsigned short data*/
                   };
enum BGCPL_WGT_MODE{ IS_16BITGREY_MODE = 0 /*!< It is 16 bit greyscale image*/,
                     IS_8BITGREY_MODE = 1 /*!< It is 8 bit greyscale image*/,
                     IS_COLOR_MODE = 2 /*!< It is color image*/
                   };
#endif // ENUM_H
