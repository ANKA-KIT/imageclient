#include "snapshotcontainer.h"

#include <QDebug>
#include "mainwindow.h"
#include "snapshotsubwindow.h"

SnapshotContainer::SnapshotContainer(MainWindow *parent) :
    QObject(parent)
{
    windowElement = parent;
}

void SnapshotContainer::windowActivated(SubWindow* curSnapWin)
{
    qDebug() << "MainWindow::SnapshotChanged -> activated " << curSnapWin;
    SnapshotSubWindow* snapWindow = dynamic_cast<SnapshotSubWindow*>(curSnapWin);
    if (!snapWindow) {
        qDebug() << "Wrong window type passed. Doing nothing.";
        return;
    }
    qDebug() << "MainWindow::SnapshotChanged connecting signals";
    connect(snapWindow->snp, SIGNAL(mousePosition(QPoint)), windowElement, SLOT(curPosition(QPoint)), Qt::UniqueConnection);
    connect(snapWindow->snp, SIGNAL(greyscaleImageColor(int)), windowElement, SLOT(curColor(int)), Qt::UniqueConnection);
    connect(snapWindow->snp, SIGNAL(rgbImageColor(int, int, int)), windowElement, SLOT(curColor(int, int, int)), Qt::UniqueConnection);
    qDebug() << "MainWindow::SnapshotChanged finished connecting signals";
}

void SnapshotContainer::windowDeactivated(SubWindow* curSnapWin)
{
    qDebug() << "MainWindow::SnapshotChanged -> deactivated " << curSnapWin;
    SnapshotSubWindow* snapWindow = dynamic_cast<SnapshotSubWindow*>(curSnapWin);
    if (!snapWindow) {
        qDebug() << "Wrong window type passed. Doing nothing.";
        return;
    }
    qDebug() << "MainWindow::SnapshotChanged disconnecting signals";
    disconnect(snapWindow->snp, SIGNAL(mousePosition(QPoint)), windowElement, SLOT(curPosition(QPoint)));
    disconnect(snapWindow->snp, SIGNAL(greyscaleImageColor(int)), windowElement, SLOT(curColor(int)));
    disconnect(snapWindow->snp, SIGNAL(rgbImageColor(int, int, int)), windowElement, SLOT(curColor(int, int, int)));
}

// XXX: perhaps obsolete
void SnapshotContainer::onCloseSnapshot(QObject *pointer){
    qDebug("Erase Snapshot Subwin");
}
