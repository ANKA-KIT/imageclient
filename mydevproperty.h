#ifndef MyDevProperty_H
#define MyDevProperty_H

#include <QObject>
#include <QVariant>
#include <QString>

/*!
  \file mydevproperty.h
  \author Georgii Vasilev
  \class MyDevProperty
  \brief Answear for keeping picture properties
  ///Keeps Scale, Brightness, Gamma, Contrast, Rotation, Fliping values
*/
class MyDevProperty : public QObject
{
   Q_OBJECT
protected:
    QVariant _val;          /*!< value*/
    QString _propName;      /*!< name of property*/
    QString _attr;          /*!< attribute name of property*/
public:
    /*! \brief void constructor*/
    MyDevProperty(){}

    /*! \brief Destructor*/
    virtual ~MyDevProperty(){}

    /*! \brief Get property value*/
    virtual QVariant getValue();

    /*! \brief Get attribute property name*/
    virtual QString getAttrName();

    /*! \brief Get property name*/
    virtual QString getPropName();
signals:
    void setVal(QVariant);      /*!< send property value*/
    void repaint(int);          /*!< send a signal for repaint screen*/
public slots:
    /*! \brief set property value*/
    virtual void setValue(QVariant val);

    /*! \brief Set attribute property name*/
    void setAttrName(QString val);
};

/*!
  \file mydevproperty.h
  \author Georgii Vasilev
  \class Brightness
  \brief Answear for keeping Brightness property
  ///Keeps Brightness
*/
class Brightness : public MyDevProperty{
public:
    /*! \brief Constructor*/
    Brightness();
};

/*!
  \file mydevproperty.h
  \author Georgii Vasilev
  \class Gamma
  \brief Answear for keeping Gamma property
  ///Keeps Gamma
*/
class Gamma : public MyDevProperty{
public:
    /*! \brief Constructor*/
    Gamma();
};

/*!
  \file mydevproperty.h
  \author Georgii Vasilev
  \class Contrast
  \brief Answear for keeping Contrast property
  ///Keeps Contrast
*/
class Contrast : public MyDevProperty{
public:
    /*! \brief Constructor*/
    Contrast();
};

/*!
  \file mydevproperty.h
  \author Georgii Vasilev
  \class HorFlip
  \brief Answear for keeping Horizontal fliping (HorFlip) property
  ///Keeps keeping Horizontal fliping (HorFlip)
*/
class HorFlip : public MyDevProperty{
public:
    /*! \brief Constructor*/
    HorFlip();
};

/*!
  \file mydevproperty.h
  \author Georgii Vasilev
  \class VerFlip
  \brief Answear for keeping Vertical fliping (VerFlip) property
  ///Keeps keeping Vertical fliping (VerFlip)
*/
class VerFlip : public MyDevProperty{
public:
    /*! \brief Constructor*/
    VerFlip();
};

/*!
  \file mydevproperty.h
  \author Georgii Vasilev
  \class Rotation
  \brief Answear for keeping Rotation property
  ///Keeps Rotation
*/
class Rotation : public MyDevProperty{
public:
    /*!  \brief Constructor*/
    Rotation();
};

/*!
  \file mydevproperty.h
  \author Georgii Vasilev
  \class Scale
  \brief Answear for keeping Scale property
  ///Keeps Scale
*/
class Scale : public MyDevProperty{
    Q_OBJECT
public:
    /*! \brief Constructor*/
    Scale();
public slots:
    /*! \brief Set value (Scale) \param val - value*/
    void setValue(QVariant val);
};

#endif // MyDevProperty
