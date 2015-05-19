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
    updateSizeOf(m);
    ui->markerThicknessEdit->setText(QString::number(m->_width));
    ui->markerColorEdit->setText(colorStringOf(m));
    ui->roiWidthEdit->setText((QString::number(m->roiWidth)));
    ui->roiHeightEdit->setText((QString::number(m->roiHeight)));
    refreshCrosshairValues();
}

void SyncDialog::localMarkerRemoved()
{
    ui->markerXEdit->setText("");
    ui->markerYEdit->setText("");
    ui->markerSizeXEdit->setText("");
    ui->markerSizeYEdit->setText("");
    ui->markerThicknessEdit->setText("");
    ui->markerColorEdit->setText("");
    ui->roiWidthEdit->setText("");
    ui->roiHeightEdit->setText("");
    refreshCrosshairValues();
}

void SyncDialog::colorChanged(ImageMarker *m)
{
    ui->markerColorEdit->setText(colorStringOf(m));
    refreshCrosshairValues();
}

void SyncDialog::sizeChanged(ImageMarker *m)
{
    localMarkerSet(m);
}

QString SyncDialog::colorStringOf(ImageMarker *m)
{
    vector<int> color;
    color.push_back(qRed(m->_clr));
    color.push_back(qGreen(m->_clr));
    color.push_back(qBlue(m->_clr));
    return valuesAsString(color);
}

void SyncDialog::updateSizeOf(ImageMarker *m)
{
    ui->markerSizeXEdit->setText(QString::number(m->hLineLength));
    ui->markerSizeYEdit->setText(QString::number(m->vLineLength));
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
