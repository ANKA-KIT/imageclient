#ifndef SYNCDIALOG_H
#define SYNCDIALOG_H

#include <QDialog>
#include <vector>

namespace Ui {
class SyncDialog;
}

class ImageTangoDevice;
class ImageMarker;

class SyncDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SyncDialog(ImageTangoDevice *tangoDevice, QWidget *parent = 0);
    ~SyncDialog();
public slots:
    void refreshCrosshair();
    void localMarkerSet(ImageMarker *m);
    void localMarkerRemoved();

protected:
    virtual void showEvent (QShowEvent* event);

private:
    ImageTangoDevice *tangoDevice;
    Ui::SyncDialog *ui;

    void refreshCrosshairValues();
    template<typename T>
    QString valuesAsString(std::vector<T> values)
    {
        QString result = "[";
        for (typename std::vector<T>::iterator it = values.begin(); it != values.end(); ++it) {
            result += QString::number(*it);
            result += ",";
        }
        result.replace(result.length() - 1, 1, QChar(']'));
        return result;
    }
};

#endif // SYNCDIALOG_H
