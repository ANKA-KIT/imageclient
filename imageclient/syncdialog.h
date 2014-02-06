#ifndef SYNCDIALOG_H
#define SYNCDIALOG_H

#include <QDialog>

namespace Ui {
class SyncDialog;
}

class ImageTangoDevice;

class SyncDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SyncDialog(ImageTangoDevice* tangoDevice, QWidget *parent = 0);
    ~SyncDialog();
public slots:
    void refreshCrosshair();

protected:
    virtual void showEvent (QShowEvent* event);

private:
    ImageTangoDevice *tangoDevice;
    Ui::SyncDialog *ui;

    void refreshCrosshairValues();
};

#endif // SYNCDIALOG_H
