#ifndef STARTTANGOWIN_H
#define STARTTANGOWIN_H

#include <my_device.h>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QSettings>
#include <QComboBox>
#include <mylineedit.h>

class MainWindow;

/*!
  \file starttangowin.h
  \author Georgii Vasilev
  \class StartTangoWin
  \brief Widget for setting Tango device
  ///Checking device in database, check connecktion.
*/
class StartTangoWin : public QWidget
{
    Q_OBJECT
private:
    /*!
        \brief init buttons widgets
    */
    void initButtons();

    /*!
        \brief init static widgets text
    */
    void initText();

    /*!
        \brief init textline widgets
    */
    void initTextLine();

    /*!
        \brief init tango device class
    */
    void initTangoDev();

    /*!
        \brief entered values
    */
    void readSettings();

    /*!
        \brief write last entered values
    */
    void writeSettings();

    /*!
        \brief find str in the setting list
        \param cmb - list of settins parameter
        \param str - string value for searching index
        \return last entered index in the list
    */
    int findLastEnteredIndex(QStringList cmb, QString str);

    /*!
        \brief is str in the setting list
        \param listVal - list of settins parameter
        \param str - string value for searching in the list
        \return str in the list
    */
    bool curValIsSet(QStringList listVal, QString str);
public:
    QWidget * centralWidget;        /*!< widget pointer for easy setting widgets*/
    QStringList lsDev;              /*!< list of devices*/
    QStringList lsAttr;             /*!< list of image attributes*/
    QStringList lsHost;             /*!< list of hosts*/
    QComboBox *cmbDevice;           /*!< device combobox*/
    QComboBox *cmbAttr;             /*!< image attribute combobox*/
    QComboBox *cmbHost;             /*!< host combobox*/
    MyLineEdit * tlAttr;            /*!< image attribute line edit*/
    MyLineEdit *tlDevice;           /*!< device line edit*/
    MyLineEdit * tlServer;          /*!< host line edit*/
    QLabel * lbServer;              /*!< host label*/
    QLabel * lbDevice;              /*!< device label*/
    QLabel * lbAttr;                /*!< image attribute label*/

    my_Device *myDev;               /*!< tango device class object*/
    QLabel* status;                 /*!< display status label*/

    QPushButton * btCancel;         /*!< button "Cancel"*/
    QPushButton * btChangeDevice;   /*!< button "Set Device"*/

    /*!
      \brief Constructor
    */
    StartTangoWin(MainWindow* parent);

    /*!
      \brief Destructor
    */
    ~StartTangoWin();
signals:
    void correctDev(QString, QString);      /*!< All was good, can create realtime subwindow*/
    void cancel();                        /*!< Close window*/
public slots:
    void onOk();        /*!< On ok button clicking*/
    void onCancel();    /*!< On cancel button clicking*/

    void testOnError(QString);  /*!< On some error in tango connection, inform about tango problems*/
    void testOnOk();            /*!< On correct tango connection*/
    void testOnOkImgVal();      /*!< On correct getting image data from tango server*/
};

#endif // STARTTANGOWIN_H
