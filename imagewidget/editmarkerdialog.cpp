#include "editmarkerdialog.h"
#include "ui_editmarkerdialog.h"

#include <QDebug>
#include <QColorDialog>

#include "imagemarker.h"

EditMarkerDialog::EditMarkerDialog(ImageMarker *marker, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditMarkerDialog),
    marker(marker),
    colorIcon(new QPixmap(24, 24)),
    currentColor(marker->getColor())
{
    ui->setupUi(this);
    ui->markerXEdit->setText(QString::number(marker->_x));
    ui->markerYEdit->setText(QString::number(marker->_y));
    ui->markerSizeXEdit->setText(QString::number(marker->hLineLength));
    ui->markerSizeYEdit->setText(QString::number(marker->vLineLength));
    ui->markerThicknessEdit->setText(QString::number(marker->_width));
    updateColorSelectorButton();
    ui->roiWidthEdit->setText(QString::number(marker->roiWidth));
    ui->roiHeightEdit->setText(QString::number(marker->roiHeight));
}

EditMarkerDialog::~EditMarkerDialog()
{
    delete ui;
    delete colorIcon;
}

void EditMarkerDialog::accept()
{
    QDialog::accept();
    marker->_x = ui->markerXEdit->text().toInt();
    marker->_xOnPic = marker->_x;
    marker->_y = ui->markerYEdit->text().toInt();
    marker->_yOnPic = marker->_y;
    marker->_width = ui->markerThicknessEdit->text().toInt();
    marker->roiWidth = ui->roiWidthEdit->text().toInt();
    marker->roiHeight = ui->roiHeightEdit->text().toInt();
    marker->resizeMarker(ui->markerSizeXEdit->text().toInt(), ui->markerSizeYEdit->text().toInt());
    marker->setMarkerColor(currentColor.rgb());
    marker->geometryChanged();
}

void EditMarkerDialog::showColorSelector()
{
    QColor newColor = QColorDialog::getColor(currentColor, this);
    qDebug() << newColor.name();
    if (!newColor.isValid()) {
        return;
    }
    currentColor = newColor;
    updateColorSelectorButton();
}

void EditMarkerDialog::autoFillRoiWidth()
{
    if (ui->roiWidthEdit->text().toInt() > 0) {
        return;
    }
    ui->roiWidthEdit->setText(ui->roiHeightEdit->text());
}

void EditMarkerDialog::autoFillRoiHeight()
{
    if (ui->roiHeightEdit->text().toInt() > 0) {
        return;
    }
    ui->roiHeightEdit->setText(ui->roiWidthEdit->text());
}

void EditMarkerDialog::updateColorSelectorButton()
{
    colorIcon->fill(currentColor);
    ui->markerColorSelectorButton->setIcon(*colorIcon);
}
