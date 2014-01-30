#include "syncdialog.h"
#include "ui_syncdialog.h"

SyncDialog::SyncDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SyncDialog)
{
    ui->setupUi(this);
}

SyncDialog::~SyncDialog()
{
    delete ui;
}
