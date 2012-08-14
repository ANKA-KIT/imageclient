#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H

#include <QLineEdit>
#include <QKeyEvent>

/*!
  \file mylineedit.h
  \author Georgii Vasilev
  \class MyLineEdit
  \brief Overloaded QLineEdit class
  ///Keeps extra signals and posibilities
*/
class MyLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    bool isNumericLine;         /*!< is it numeric line*/

    /*!
        \brief Constructor
        \param parent - parent widget
        \param itIsNumericLine - is it numeric line
    */
    MyLineEdit(QLineEdit *parent=0, bool itIsNumericLine=true);

    /*!
        \brief Destructor
    */
    ~MyLineEdit();
signals:
    void setVal(int);           /*!< set value*/
    void setValD(double);       /*!< set value double*/
public slots:
    /*!
        \brief on key press
        \param event - event pointer
    */
   void keyPressEvent ( QKeyEvent * event );
};

#endif // MYLINEEDIT_H
