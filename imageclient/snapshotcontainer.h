#ifndef SnapshotContainer_H
#define SnapshotContainer_H

#include <QObject>

class MainWindow;
class SnapshotSubWindow;
class SubWindow;

class SnapshotContainer : public QObject
{
    Q_OBJECT
private:
    MainWindow* windowElement;

public:
    explicit SnapshotContainer(MainWindow *parent = 0);

public slots:
    void windowActivated(SubWindow* curSnapWin);
    void windowDeactivated(SubWindow* curSnapWin);
    void onCloseSnapshot(QObject *pointer);
};

#endif // SnapshotContainer_H
