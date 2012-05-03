/*
    Author: Georgii Vasilev
    Project: Image client
    Aprel 2012
*/
#include "mainwindow.h"
#include "ui_mainwindow.h"

void CommandLine::initButtons(){
    btCancel = new QPushButton(centralWidget);
    btCancel->setObjectName(QString::fromUtf8("btCancel"));
    btCancel->setGeometry(QRect(100, 20, 91, 24));
    btSend = new QPushButton(centralWidget);
    btSend->setObjectName(QString::fromUtf8("btSend"));
    btSend->setGeometry(QRect(5, 20, 91, 24));
}

void CommandLine::initText(){
    btCancel->setText("Cancel");
    btSend->setText("Send");
    lbCommand->setText("Command:");
    tlCommand->setText("GeneratingRandomDataImage");
    fprintf(stderr, "in CommandLine constructor\n");
}
void CommandLine::initTextLine(){
    lbCommand = new QLabel(centralWidget);
    lbCommand->setObjectName(QString::fromUtf8("lbCommand"));
    lbCommand->setGeometry(QRect(5, 0, 71, 16));
    tlCommand = new QLineEdit(centralWidget);
    tlCommand->setObjectName(QString::fromUtf8("tlCommand"));
    tlCommand->setGeometry(QRect(90, 0, 180, 20));
}

//Constructor of CommandLine
CommandLine::CommandLine(MainWindow *main){
    CommandLine *MainWind = this;
    parent = main;
    centralWidget = new QWidget(MainWind);
    centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
    this->setFixedSize(300, 50);
    this->move(100,100);
    this->setWindowTitle("Send command");

    initButtons();
    initTextLine();
    initText();
}

void MainWindow::cancelCommandLine(){
    cmdTangoLine->close();
    delete cmdTangoLine;
    cmdTangoLine = NULL;
}

CommandLine::~CommandLine(){
    fprintf(stderr, "in CommandLine destructor\n");
    delete lbCommand;
    delete tlCommand;
    delete btSend;
    delete btCancel;

}

