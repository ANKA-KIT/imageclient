#include "syncdialog.h"
#include "ui_syncdialog.h"

#include "etangodevice.h"

SyncDialog::SyncDialog(ImageTangoDevice* tangoDevice, QWidget *parent) :
    QDialog(parent),
    tangoDevice(tangoDevice),
    ui(new Ui::SyncDialog)
{
    ui->setupUi(this);
    QString thickness("CrosshairThickness");
    qDebug("in StartTangoWin constructor");

    ui->tangoCrosshairThicknessEdit->setText(QString(tangoDevice->readULongAttr(thickness)));
}

SyncDialog::~SyncDialog()
{
    delete ui;
}

void SyncDialog::showEvent(QShowEvent* event)
{
    qDebug("Showing sync dialog");
    refreshCrosshairValues();
}

void SyncDialog::refreshCrosshair()
{
    refreshCrosshairValues();
}

void SyncDialog::refreshCrosshairValues()
{
    if (!tangoDevice->checkAttr(tangoDevice->getServerName(), "CrosshairEnabled")) {
        qDebug("No crosshair functionality on device. No values will be read!");
        return;
    }
    ui->tangoCrosshairEnabledcheckBox->setChecked(tangoDevice->readBoolAttr(QString::fromAscii("CrosshairEnabled")));
    vector<uint> crosshairPosition = tangoDevice->readULongSpectrumAttr(QString::fromAscii("CrosshairPosition"));
    QString position = "[";
    for (vector<uint>::iterator it = crosshairPosition.begin(); it != crosshairPosition.end(); ++it) {
        position += QString::number(*it);
        position += ",";
    }
    position.replace(position.length() - 1, 1, QChar(']'));
    ui->tangoCrosshairPositionEdit->setText(position);
    ui->tangoCrosshairThicknessEdit->setText(QString::number(tangoDevice->readULongAttr(QString::fromAscii("CrosshairThickness"))));
    vector<uchar> crosshairColor = tangoDevice->readUCharSpectrumAttr(QString::fromAscii("CrosshairColor"));
    QString color = "[";
    for (vector<uchar>::iterator it = crosshairColor.begin(); it != crosshairColor.end(); ++it) {
        color += QString::number(*it);
        color += ",";
    }
    color.replace(color.length() - 1, 1, QChar(']'));
    ui->tangoCrosshairColorEdit->setText(color);
    ui->tangoRoiXEdit->setText(QString::number(tangoDevice->readULongAttr(QString::fromAscii("roi-x0"))));
    ui->tangoRoiYEdit->setText(QString::number(tangoDevice->readULongAttr(QString::fromAscii("roi-y0"))));
    ui->tangoRoiWidthEdit->setText(QString::number(tangoDevice->readULongAttr(QString::fromAscii("roi-width"))));
    ui->tangoRoiHeightEdit->setText(QString::number(tangoDevice->readULongAttr(QString::fromAscii("roi-height"))));
}
