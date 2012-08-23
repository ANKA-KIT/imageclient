#include "mythread.h"
#include <QtDebug>

MyThread::MyThread(QObject *parent) :  QThread(parent){}
void MyThread::run(){
    //qDebug() << "MyThread::run " << QThread::currentThread();
         exec();
}
void MyThread::doTheWork(){ /*qDebug() << "MyThread::doTheWork " << QThread::currentThread(); */emit paint();}

//void MyThread::mkSnap(){}//emit snap();}

MyThread::~MyThread(){qDebug("MyThread was deleted!");}
