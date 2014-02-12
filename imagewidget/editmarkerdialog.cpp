#include "editmarkerdialog.h"
#include "ui_editmarkerdialog.h"

EditMarkerDialog::EditMarkerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditMarkerDialog)
{
    ui->setupUi(this);
}

EditMarkerDialog::~EditMarkerDialog()
{
    delete ui;
}
