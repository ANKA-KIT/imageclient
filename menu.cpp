#include "mainwindow.h"
#include "ui_mainwindow.h"

//Creating Menu
void MainWindow::createMenu(){
    server = menuBar()->addMenu(QString("&Server"));
    server->addAction(addNewDevice);
    server->addAction(setDevice);
    server->addAction(pushCommand);
    server->addSeparator();
    server->addAction(exitAct);
    snapshot = menuBar()->addMenu(tr("&Snapshot"));
    snapshot->addAction(makeSnapshot);
    snapshot->addAction(saveSnapshot);

    snapshot->setEnabled(false);
    saveSnapshot->setEnabled(false);
    pushCommand->setEnabled(false);
}

//Init Actions
void MainWindow::createActions(){
    fprintf(stderr, "!!\n");
    makeSnapshot = new QAction(tr("&Make a snapshot"), this);
    makeSnapshot->setStatusTip(tr("Create a snapshot"));

    pushCommand = new QAction(tr("&Send a command"), this);
    pushCommand->setStatusTip(tr("Send a command"));
    connect(pushCommand, SIGNAL(triggered()), this, SLOT(setTangoCommand()));

    exitAct = new QAction(tr("&Exit"), this);
    exitAct->setStatusTip(tr("Finish working"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    addNewDevice = new QAction(tr("&Start new device"), this);
    addNewDevice->setStatusTip(tr("Start new device"));
    connect(addNewDevice, SIGNAL(triggered()), this, SLOT(setNewTangoDevice()));

    setDevice = new QAction(tr("&Set device"), this);
    setDevice->setStatusTip(tr("Set device"));
    connect(setDevice, SIGNAL(triggered()), this, SLOT(setTangoDevice()));

    saveSnapshot = new QAction(tr("&Save a snapshot"), this);
    saveSnapshot->setStatusTip(tr("Save a snapshot"));
    QObject::connect(saveSnapshot, SIGNAL(triggered()), this, SLOT(saveImg()));
}

