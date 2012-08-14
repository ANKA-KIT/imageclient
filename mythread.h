#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
/*!
  \file mythread.h
  \author Georgii Vasilev
  \class MyThread
  \brief
  ///Need to think about this class. should be deleted and changed by QTimer (f.e.)
*/
class MyThread : public QThread
{
    Q_OBJECT
public:
    /*! void constructor*/
    explicit MyThread(QObject *parent = 0);

    /*! execute process*/
    void run();

    /*! destructor*/
    ~MyThread();

signals:
    void paint();       /*!< send ping*/
   // void ping();
public slots:
    /*! send ping*/
    void doTheWork();
    //void mkSnap();
};



#endif // MYTHREAD_H
