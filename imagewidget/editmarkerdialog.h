#ifndef EDITMARKERDIALOG_H
#define EDITMARKERDIALOG_H

#include <QDialog>

class ImageMarker;

namespace Ui {
class EditMarkerDialog;
}

class EditMarkerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditMarkerDialog(ImageMarker *marker, QWidget *parent = 0);
    ~EditMarkerDialog();

private:
    Ui::EditMarkerDialog *ui;
    ImageMarker *marker;
    QPixmap* colorIcon;
    QColor currentColor;

    void updateColorSelectorButton();

public slots:
    virtual void accept();

protected slots:
    void showColorSelector();
};

#endif // EDITMARKERDIALOG_H
