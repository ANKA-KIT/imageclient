#ifndef STARTTANGOWIN_H
#define STARTTANGOWIN_H

#include <QWidget>
#include <QComboBox>
#include <etangodevice.h>
#include <imagemanipulator.h>
#include <QSettings>
#include <QFormLayout>

class StartTangoWindow : public QWidget, TDevice
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
    QWidget* centralWidget;        /*!< widget pointer for easy setting widgets*/
    QStringList lsDev;              /*!< list of devices*/
    QStringList lsAttr;             /*!< list of image attributes*/
    QStringList lsHost;             /*!< list of hosts*/
    QComboBox* cmbDevice;           /*!< device combobox*/
    QComboBox* cmbAttr;             /*!< image attribute combobox*/
    QComboBox* cmbHost;             /*!< host combobox*/
    PropertyLineEdit* tlAttr;            /*!< image attribute line edit*/
    PropertyLineEdit* tlDevice;           /*!< device line edit*/
    PropertyLineEdit* tlServer;          /*!< host line edit*/
    QLabel* lbServer;              /*!< host label*/
    QLabel* lbDevice;              /*!< device label*/
    QLabel* lbAttr;                /*!< image attribute label*/
    QLabel* status;                 /*!< display status label*/

    QPushButton* btCancel;         /*!< button "Cancel"*/
    QPushButton* btChangeDevice;   /*!< button "Set Device"*/

    /*!
      \brief Constructor
    */
    StartTangoWindow(QWidget* parent=0);
signals:
    void correctDev(QString, QString);      /*!< All was good, can create realtime subwindow*/
    void dev(QString, QString);
    void cancel();                        /*!< Close window*/
public slots:
    void onOk();        /*!< On ok button clicking*/
    void onCancel();    /*!< On cancel button clicking*/

    void testOnError(QString);  /*!< On some error in tango connection, inform about tango problems*/
    void testOnOk();            /*!< On correct tango connection*/
    void testOnOkImgVal();      /*!< On correct getting image data from tango server*/
    void refresh(const TVariant &newVal);
};

#endif // STARTTANGOWIN_H
