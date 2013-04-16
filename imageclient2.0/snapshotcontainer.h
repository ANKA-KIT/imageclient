#ifndef SnapshotContainer_H
#define SnapshotContainer_H

#include <QObject>
#include <snapshotsubwindow.h>

class SnapshotContainer : public QObject
{
    Q_OBJECT
private:
    QList<SnapshotSubWindow *> snapshotList;
    int curSnapshot;
    int snapshotLast;
public:
    explicit SnapshotContainer(QObject *parent = 0);
    void add(SnapshotSubWindow *snp){snapshotList.push_back(snp);}
    int getSnapshotLastVal(){return snapshotLast;}
signals:
    
public slots:
    void snapshotChanged(SubWindow* curSnapWin);
    void onCloseSnapshot(QObject *pointer);
};

#endif // SnapshotContainer_H
