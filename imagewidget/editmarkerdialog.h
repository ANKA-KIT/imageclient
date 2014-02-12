#ifndef EDITMARKERDIALOG_H
#define EDITMARKERDIALOG_H

#include <QDialog>

namespace Ui {
class EditMarkerDialog;
}

class EditMarkerDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit EditMarkerDialog(QWidget *parent = 0);
    ~EditMarkerDialog();
    
private:
    Ui::EditMarkerDialog *ui;
};

#endif // EDITMARKERDIALOG_H
