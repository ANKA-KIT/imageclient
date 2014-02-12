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
    ui->markerXEdit->setText(QString::number(marker->_x));
    ui->markerXEdit->setText(QString::number(marker->_x));
}

EditMarkerDialog::~EditMarkerDialog()
{
    delete ui;
    delete colorIcon;
}

void EditMarkerDialog::accept()
{
    qDebug() << "Update marker!";
    QDialog::accept();
    // TODO
    marker->_x = ui->markerXEdit->text().toInt();
    marker->_y = ui->markerYEdit->text().toInt();
    marker->_width = ui->markerThicknessEdit->text().toInt();
    marker->resizeMarker(ui->markerSizeXEdit->text().toInt(), ui->markerSizeYEdit->text().toInt());
    marker->setMarkerColor(currentColor.rgb());
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

void EditMarkerDialog::updateColorSelectorButton()
{
    colorIcon->fill(currentColor);
    ui->markerColorSelectorButton->setIcon(*colorIcon);
}
