#ifndef TANGOSETTINGSWIN_H
#define TANGOSETTINGSWIN_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QVariant>
#include <enum.h>
#include <mylineedit.h>

/*!
  \file tangosettingswin.h
  \author Georgii Vasilev
  \class TangoSettingsWin
  \brief Widget for setting device picture prorty
  ///Widget for setting device picture prorty
*/
class TangoSettingsWin : public QWidget
{
    Q_OBJECT
protected:
    bool _dif;           /*!< is it changing on some value*/
    QVariant _originVal; /*!< current device property value*/
public:
    QWidget *centralWidget; /*!< widget pointer for easy setting widgets*/
    QLabel * lb;            /*!< Property name label*/
    QLineEdit *tl;          /*!< LineEdit for setting property value*/
    QPushButton *btOk;      /*!< Button "Set value"*/
    QPushButton *btCancel;  /*!< Button "Cancel"*/

    /*!
        \brief void Constructor
    */
    explicit TangoSettingsWin(QWidget *parent = 0){}

    /*!
        \brief Constructor
        \param param - property num
        \param title - title of window
        \param prop - name of property
        \param curval - current property value
    */
    TangoSettingsWin(int param, QString title, QString prop, QVariant curVal);

    /*!
        \brief Constructor
        \param val - convert editine string to int and set value to this variable
        \return success
    */
    bool converToInt(int& val);

    /*!
        \brief Constructor
        \param val - convert editine string to double and set value to this variable
        \return success
    */
    bool converToDouble(double& val);

    /*!
        \brief Destructor
    */
    ~TangoSettingsWin();
signals:
    void settingChanged(QVariant setting);  /*!< OnSuccess every time*/
    void settingChangedI(int);              /*!< OnSuccess in int value property*/
    void settingChangedD(double);           /*!< OnSuccess in double value property*/
    void settingChangedS(QString);          /*!< OnSuccess in string value property*/
    void cancel();                          /*!< OnCancel*/
public slots:
    /*!
        \brief On OkButton clicking for sending tangoCommand
    */
    void onOk();

    /*!
        \brief On OkButton clicking for setting int value
    */
    void onOkInt();

    /*!
        \brief On OkButton clicking for setting double value
    */
    void onOkDouble();

    /*!
        \brief On OkButton clicking for setting bool value
    */
    void onOkBool();

    /*!
        \brief On CancelButton clicking
    */
    void onCancel();
};

/*!
  \file tangosettingswin.h
  \author Georgii Vasilev
  \class SetMarker
  \brief Widget for setting marker position
  ///Widget for setting marker position
*/
class SetMarker : public QWidget{
Q_OBJECT
public:
    QPushButton *btOk;  /*!< button ok  */
    QLabel *lbX;        /*!< Label  */
    MyLineEdit *tlX;    /*!< Line of text to set X marker position */
    MyLineEdit *tlY;    /*!< Line of text to set Y marker position */
    QLabel *lbY;        /*!< Label  */

    /*! \brief Constructor  */
    SetMarker();
    /*! \brief Destructor  */
    ~SetMarker();
signals:
    void setMarker(int x, int y); /*!< OnSuccess set marker \param x - X position \param y - Y position*/
public slots:
    /*! \brief On OkButton clicking  */
    void onOk();
};

#endif // TANGOSETTINGSWIN_H
