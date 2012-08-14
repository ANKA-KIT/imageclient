#ifndef PROPERTYMANIPULATION_H
#define PROPERTYMANIPULATION_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QSlider>
#include <mylineedit.h>
#include <enum.h>

/*!
  \file propertymanipulation.h
  \author Georgii Vasilev
  \class Int_WGT
  \brief Base class for manipulation int value property
  ///Base class for manipulation int value property
*/
class Int_WGT : public QWidget{
    Q_OBJECT
protected:
    QLabel *lb;                 /*!< label (name of manipulator)*/
    MyLineEdit *line;           /*!< line edit (set value) manipulator*/
    QSlider *slider;            /*!< slider (set value) manipulator*/
public:
    /*! \brief void constructor*/
    Int_WGT(QWidget *parent=0){}

    /*! \brief  constructor \param curVal - current manipulator value*/
    Int_WGT(int curVal,QWidget *parent=0);

    /*! \brief Destructor*/
    ~Int_WGT();
signals:
    void sendVal(QVariant val);     /*!< Send value*/
public slots:
    /*! \brief  on set Value \param val - value*/
    void setVal(int val);
    /*! \brief  on set Value somewhere (throw another manipulator) \param val - value*/
    void receiveVal(QVariant val);
};
/*
class Con_WGT : public Int_WGT{
    Q_OBJECT
public:
    Con_WGT(int curVal,QWidget *parent=0);
public slots:
    void setVal(int val);
};

class Gm_WGT : public Int_WGT{
    Q_OBJECT
public:
    Gm_WGT(int curVal,QWidget *parent=0);
public slots:
    void setVal(int val);
};

class Br_WGT : public Int_WGT{
    Q_OBJECT
public:
    Br_WGT(int curVal,QWidget *parent=0);
public slots:
    void setVal(int val);
};

class LBorder_WGT : public Int_WGT{
    Q_OBJECT
public:
    LBorder_WGT(int curVal,QWidget *parent=0);
public slots:
    void setVal(int val);
};

class RBorder_WGT : public Int_WGT{
    Q_OBJECT
public:
    RBorder_WGT(int curVal,QWidget *parent=0);
public slots:
    void setVal(int val);
};
*/

/*!
  \author Georgii Vasilev
  \class Double_WGT
  \brief Base class for manipulation double value property
  *Base class for manipulation double value property
*/
class Double_WGT : public QWidget{
    Q_OBJECT
protected:
    QLabel *lb;                 /*!< label (name of manipulator)*/
    MyLineEdit *line;           /*!< line edit (set value) manipulator*/
    QSlider *slider;            /*!< slider (set value) manipulator*/
public:
    /*! \brief void constructor*/
    Double_WGT(QWidget *parent=0){}

    /*! \brief  constructor \param curVal - current manipulator value*/
    Double_WGT(double curVal,QWidget *parent=0);

    /*! \brief Destructor*/
    ~Double_WGT();
signals:
    void sendVal(QVariant val);     /*!< Send value*/
public slots:
    /*! \brief  on set Value slider \param val - value*/
    void setVal(int val);

    /*! \brief  on set-send Value \param valD - value*/
    void setValD(double val);

    /*! \brief  on set Value somewhere (throw another manipulator) \param val - value*/
    void receiveVal(QVariant val);
};

/*!
  \author Georgii Vasilev
  \class Scl_WGT
  \brief class for scale manipulation
  *scale manipulator
*/
class Scl_WGT : public Double_WGT{
    Q_OBJECT
public:
    /*! \brief void constructor*/
    Scl_WGT(QWidget *parent=0){}

    /*! \brief  constructor \param curVal - current manipulator value*/
    Scl_WGT(double curVal,QWidget *parent=0);
public slots:
    /*! \brief  on set Value slider \param val - value*/
    void setVal(int val);
};

/*!
  \author Georgii Vasilev
  \class Rot_WGT
  \brief class for rotation manipulation
  *rotation manipulator
*/
class Rot_WGT : public Double_WGT{
    Q_OBJECT
public:
    /*! \brief  constructor \param curVal - current manipulator value*/
    Rot_WGT(double curVal,QWidget *parent=0);
};

/*!
  \author Georgii Vasilev
  \class Binar_WGT
  \brief class for boolean value manipulation
  *boolean value manipulator
*/
class Binar_WGT : public QWidget{
    Q_OBJECT
private:
    QLabel *lb;         /*!< label (name of manipulator)*/
    QLabel *value;      /*!< label (value of manipulator)*/
    QSlider *slider;    /*!< slider (set value) manipulator*/
public:
    /*! \brief  constructor \param curVal - current manipulator value \brief str - name of manipulator*/
    Binar_WGT(QString curVal, QString str="",QWidget *parent=0);

    /*! \brief Destructor*/
    ~Binar_WGT();
signals:
    void sendVal(QVariant);     /*!< Send value*/
public slots:
     /*! \brief  on set Value slider \param val - value*/
    void setVal(int val);
};


#endif // PROPERTYMANIPULATION_H
