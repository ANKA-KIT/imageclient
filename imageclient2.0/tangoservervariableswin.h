#ifndef TANGOSERVERVARIABLESWIN_H
#define TANGOSERVERVARIABLESWIN_H

#include <QWidget>
#include <QSettings>
#include <QLabel>
#include <QFormLayout>
#include <imagemanipulator.h>
#include <etangodevice.h>

struct ServerVariables{
    QString image;
    QString hFlip;
    QString vFlip;
    QString rotate;
    QString scale;
    QString brightness;
    QString gamma;
    QString contrast;
    QString marker;
};

class TangoServerVariablesWin : public QWidget
{
    Q_OBJECT
private:
    /*!
      \brief Read Last entered values
    */
    void readSettings();
    QString _serverName;
    /*!
      \brief Save current entered values
    */
    void writeSettings();
public:
    QPushButton *btOk;      /*!< Button "Set value"*/
    QPushButton *btCancel;  /*!< Button "Cancel"*/

    PropertyLineEdit *tlProp;

    /*!
      \brief Constructor
    */
//    explicit TangoServerVariablesWin(ServerVariables*,QWidget *parent = 0);
    explicit TangoServerVariablesWin(QString);//(QWidget *parent = 0);

    /*!
      \brief Destructor
    */
    ~TangoServerVariablesWin(){}
signals:
    void cancel();              /*!< on cancel*/
//     void setVar(ServerVariables); /*!< setThis tango variable name*/
    void setVar(QString);
public slots:
    void onOk();            /*!< On Ok button click*/
    void onCancel();        /*!< On Cancel button click*/
};

#endif // TANGOSERVERVARIABLESWIN_H
