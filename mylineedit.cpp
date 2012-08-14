#include "mylineedit.h"

MyLineEdit::MyLineEdit(QLineEdit *parent, bool itIsNumericLine): QLineEdit(parent){
    isNumericLine = itIsNumericLine;
}
MyLineEdit::~MyLineEdit(){}

void MyLineEdit::keyPressEvent ( QKeyEvent * event ){
    if (isNumericLine){
        if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter){
            int val;
            double valD;
            bool temp;
            valD = text().toDouble(&temp);
            if (temp){
                emit setValD(valD);
            }
            val = text().toInt(&temp);
            if (temp){
                emit setVal(val);
            }
        }
        else if ((event->key() >= '0' && event->key() <= '9') || event->key() == Qt::Key_Backspace || event->key() == '.' ||
                  event->key() == Qt::Key_Left || event->key() == Qt::Key_Right || event->key() == Qt::Key_Delete){
            QLineEdit::keyPressEvent(event);
        }
    }
    else{
        if (event->key() == Qt::Key_Return  || event->key() == Qt::Key_Enter){
            emit setVal(Qt::Key_Return);
        }
        else{
            QLineEdit::keyPressEvent(event);
        }
    }
}
