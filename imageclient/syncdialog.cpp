#include "syncdialog.h"
#include "ui_syncdialog.h"

SyncDialog::SyncDialog(ImageTangoDevice* tangoDevice, QWidget *parent) :
    QDialog(parent),
    tangoDevice(tangoDevice),
    ui(new Ui::SyncDialog)
{
    ui->setupUi(this);

}

SyncDialog::~SyncDialog()
{
    delete ui;
}
