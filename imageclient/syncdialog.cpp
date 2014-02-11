#include "syncdialog.h"
#include "ui_syncdialog.h"

#include "etangodevice.h"
#include "imagemarker.h"

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

void SyncDialog::localMarkerSet(ImageMarker *m)
{
    qDebug("Setting local marker values");
    ui->markerXEdit->setText(QString::number(m->_x));
    ui->markerYEdit->setText(QString::number(m->_y));
    ui->markerSizeXEdit->setText(QString::number(m->hLineLength));
    ui->markerSizeYEdit->setText(QString::number(m->vLineLength));
    ui->markerThicknessEdit->setText(QString::number(m->_width));
    vector<int> color;
    color.push_back(qRed(m->_clr));
    color.push_back(qGreen(m->_clr));
    color.push_back(qBlue(m->_clr));
    QString colorString = valuesAsString(color);
    ui->markerColorEdit->setText(colorString);
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
    QString position = valuesAsString(crosshairPosition);
    ui->tangoCrosshairPositionEdit->setText(position);
    ui->tangoCrosshairThicknessEdit->setText(QString::number(tangoDevice->readULongAttr(QString::fromAscii("CrosshairThickness"))));
    vector<uchar> crosshairColor = tangoDevice->readUCharSpectrumAttr(QString::fromAscii("CrosshairColor"));
    QString color = valuesAsString(crosshairColor);
    ui->tangoCrosshairColorEdit->setText(color);
    ui->tangoRoiXEdit->setText(QString::number(tangoDevice->readULongAttr(QString::fromAscii("roi-x0"))));
    ui->tangoRoiYEdit->setText(QString::number(tangoDevice->readULongAttr(QString::fromAscii("roi-y0"))));
    ui->tangoRoiWidthEdit->setText(QString::number(tangoDevice->readULongAttr(QString::fromAscii("roi-width"))));
    ui->tangoRoiHeightEdit->setText(QString::number(tangoDevice->readULongAttr(QString::fromAscii("roi-height"))));
}
