#ifndef TANGOVARIABLES_H
#define TANGOVARIABLES_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSettings>
#include <mylineedit.h>

/*!
  \file tangovariables.h
  \author Georgii Vasilev
  \class TangoVariables
  \brief Widget for setting/changing Tango attributes
  ///Setting/changing Tango attributes for reading serverside manipulation
*/
class TangoVariables : public QWidget
{
    Q_OBJECT
private:
    /*!
      \brief Read Last entered values
    */
    void readSettings();

    /*!
      \brief Save current entered values
    */
    void writeSettings();
public:
    QWidget *centralWidget; /*!< widget pointer for easy setting widgets*/
    QLabel *lbImg;          /*!< label*/
    QLabel *lbRot;          /*!< label*/
    QLabel *lbBr;           /*!< label*/
    QLabel *lbCon;          /*!< label*/
    QLabel *lbGam;          /*!< label*/
    QLabel *lbScl;          /*!< label*/
    QLabel *lbHorFl;        /*!< label*/
    QLabel *lbVerFl;        /*!< label*/
    QLabel *lbImgData;      /*!< label*/
    MyLineEdit *tlImg;      /*!< LineEdit for setting image tango variable*/
    MyLineEdit *tlRot;      /*!< LineEdit for setting rotation tango variable*/
    MyLineEdit *tlBr;       /*!< LineEdit for setting brightness tango variable*/
    MyLineEdit *tlCon;      /*!< LineEdit for setting contrast tango variable*/
    MyLineEdit *tlGam;      /*!< LineEdit for setting gamma tango variable*/
    MyLineEdit *tlScl;      /*!< LineEdit for setting scale tango variable*/
    MyLineEdit *tlHorFl;    /*!< LineEdit for setting horizontal flip tango variable*/
    MyLineEdit *tlVerFl;    /*!< LineEdit for setting vertical flip tango variable*/
    MyLineEdit *tlImgData;  /*!< LineEdit for setting 16 bit image data tango variable @SET VALUE EMPTY@*/
    QPushButton *btOk;      /*!< Button "Set value"*/
    QPushButton *btCancel;  /*!< Button "Cancel"*/

    /*!
      \brief Constructor
    */
    explicit TangoVariables(QWidget *parent = 0);

    /*!
      \brief Destructor
    */
    ~TangoVariables();
signals:
    void cancel();              /*!< on cancel*/
    void setVar(QStringList); /*!< setThis tango variable name*/
public slots:
    void onOk();            /*!< On Ok button click*/
    void onCancel();        /*!< On Cancel button click*/

};

#endif // TANGOVARIABLES_H
