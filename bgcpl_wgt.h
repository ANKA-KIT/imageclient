#ifndef BGCPL_WGT_H
#define BGCPL_WGT_H
#include <propertymanipulation.h>

namespace br_gm_con_pixLevel{
/*!
    \file bgcpl_wgt.h
    \brief Brightness Gamma Contrast Pixel_Level - Widget
    /// Widget for comfortable manipulating Brightness, Gamma, Contrast. Also allow to manipulate pixel values of greyscale image
*/
class BGCPL_WGT : public QWidget{
    Q_OBJECT
private:
    /*!
     \brief Basic initing
    */
    void init();

    /*!
     \brief Set Left border value (used for greyscale image)
    */
    void setLeftVal(int val);

    /*!
     \brief Set Right border value (used for greyscale image)
    */
    void setRightVal(int val);
    /*!
     \brief initBrightness manipulator
    */
    void initBr();
    /*!
     \brief initContrast manipulator
    */
    void initCon();
    /*!
     \brief initGamma manipulator
    */
    void initGm(int);
    /*!
     \brief init left border manipulator
    */
    void initLBorder();
    /*!
     \brief init right border manipulator
    */
    void initRBorder();
    /*!
     \brief initColorMode
    */
    void initColorMode(int gm);

    /*!
     \brief init16BitGreyMode
    */
    void init16BitGreyMode();
    /*!
     \brief init8BitGreyMode
    */
    void init8BitGreyMode();
protected:
    QLabel *lbHisLB;            /*!< left border label*/
    QLabel *lbHisRB;            /*!< right border label*/
    QLabel *lbHisBr;            /*!< brightness label*/
    QLabel *lbHisCon;           /*!< contrast label*/
    QLabel *lbHisGm;            /*!< gamma label*/

    MyLineEdit *rightLine;      /*!< right border line edit*/
    MyLineEdit *leftLine;       /*!< left border line edit*/
    MyLineEdit *brLine;         /*!< brightness line edit*/
    MyLineEdit *conLine;        /*!< contrast line edit*/
    MyLineEdit *gmLine;         /*!< gamma line edit*/
    QSlider *leftBorder;        /*!< left border slider*/
    QSlider *rightBorder;       /*!< right border slider*/
    QSlider *brig;              /*!< brightness slider*/
    QSlider *contr;             /*!< contrast slider*/
    QSlider *gamma;             /*!< gamma slider*/

    int lastbr;                 /*!< brightness value*/
    int lastContr;              /*!< contrast value*/

    int maxContrast;            /*!< maximum contrast value*/
    int minContrast;            /*!< minimum contrast value*/
    int maxBrightness;          /*!< maximum brightness value*/
    int minBrightness;          /*!< minimum brightness value*/
    int stContr;                /*!< start contrast value*/
    int stBr;                   /*!< start brightness value*/
    int stLBorder;              /*!< start left border value*/
    int stRBorder;              /*!< start right border value*/
    bool isRGB;                 /*!< is it RGB image*/
    bool resetParam;            /*!< is should reset widget values*/
    /*!
     \brief Basic Constructor with NULL initing
     \param parent - parent Widget pointer
    */
    void switchMode(int mode, int gm);

public:
    /*!
     \brief Basic Constructor with NULL initing
     \param parent - parent Widget pointer
    */
    BGCPL_WGT(QWidget *parent=0);

    /*!
     \brief Constructor
     \param mode - BGCPL_WGT_MODE
     \param br - brightnes value
     \param con - contrast value
     \param parent - parent Widget pointer
     \param gm - gamma value
     \param lBr - left border value
     \param rBr - right border value
    */
    BGCPL_WGT(int mode,int br, int con, QWidget *parent=0, int gm=0, int lBr=0, int rBr=0 );

    /*!
     \brief Destructor
    */
    ~BGCPL_WGT();

signals:
    void setRBorder(unsigned short);        /*!< set right border limit of grescale image*/
    void setLBorder(unsigned short);        /*!< set left border limit of grescale image*/
    void setBr(QVariant);                   /*!< set brightness value*/
    void setCon(QVariant);                  /*!< set contrast value*/
    void setGm(QVariant);                   /*!< set Gamma value*/
public slots:
    /*!
     \brief set left border manipulator value (slot)
    */
    void setLeftBorder(int);
    /*!
     \brief set right border manipulator value (slot)
    */
    void setRightBorder(int);

    /*!
     \brief set brightness manipulator value (slot)
    */
    void setBrImg(int val);

    /*!
     \brief set contrast manipulator value (slot)
    */
    void setConImg(int val);

    /*!
     \brief set gamma manipulator value (slot)
    */
    void setGmImg(int val);

    /*!
     \brief get current brightnes value for correct setting (slot)
    */
    void receiveBr(QVariant val);

    /*!
     \brief get current contrast value for correct setting (slot)
    */
    void receiveCon(QVariant val);

    /*!
     \brief get current gamma value for correct setting (slot)
    */
    void receiveGm(QVariant val);
};
}
#endif // BGCPL_WGT_H
