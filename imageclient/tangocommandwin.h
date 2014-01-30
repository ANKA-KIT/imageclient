#ifndef TANGOCOMMANDWIN_H
#define TANGOCOMMANDWIN_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QFormLayout>
#include <imagemanipulator.h>
#include <etangodevice.h>

class TangoCommandWin : public QWidget
{
    Q_OBJECT
    QString _serverName;
public:
    explicit TangoCommandWin(QString ser);
    QPushButton *btOk;      /*!< Button "Set value"*/
    QPushButton *btCancel;  /*!< Button "Cancel"*/

    PropertyLineEdit *tlProp;


    void cancel();              /*!< on cancel*/
//     void setVar(ServerVariables); /*!< setThis tango variable name*/
    void setVar(QString);
public slots:
    void onOk();            /*!< On Ok button click*/
    void onCancel();        /*!< On Cancel button click*/
};

#endif // TANGOCOMMANDWIN_H
