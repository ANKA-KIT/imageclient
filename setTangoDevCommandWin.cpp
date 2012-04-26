#include "mainwindow.h"
#include "ui_mainwindow.h"


//Constructor of CommandLine
CommandLine::CommandLine(MainWindow *main){
    CommandLine *MainWind = this;
    parent = main;
    centralWidget = new QWidget(MainWind);
    centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
    this->setFixedSize(300, 50);
    this->move(100,100);
    this->setWindowTitle("Send command");

    btCancel = new QPushButton(centralWidget);
    btCancel->setObjectName(QString::fromUtf8("btCancel"));
    btCancel->setGeometry(QRect(100, 20, 91, 24));
    btSend = new QPushButton(centralWidget);
    btSend->setObjectName(QString::fromUtf8("btSend"));
    btSend->setGeometry(QRect(5, 20, 91, 24));
    lbCommand = new QLabel(centralWidget);
    lbCommand->setObjectName(QString::fromUtf8("lbCommand"));
    lbCommand->setGeometry(QRect(5, 0, 71, 16));
    tlCommand = new QLineEdit(centralWidget);
    tlCommand->setObjectName(QString::fromUtf8("tlCommand"));
    tlCommand->setGeometry(QRect(90, 0, 180, 20));

    btCancel->setText("Cancel");
    btSend->setText("Send");
    lbCommand->setText("Command:");
    tlCommand->setText("GeneratingRandomDataImage");
}

void CommandLine::cancel(){
    this->close();
    delete this;
}

CommandLine::~CommandLine(){
    fprintf(stderr, "in CommandLine destructor");
    delete lbCommand;
    delete tlCommand;
    delete btSend;
    delete btCancel;
}

