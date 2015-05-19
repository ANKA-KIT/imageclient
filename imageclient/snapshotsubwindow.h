#ifndef SNAPSHOTSUBWINDOW_H
#define SNAPSHOTSUBWINDOW_H

#include <timagesnapshot.h>
#include <realtimesubwindow.h>

class SnapshotSubWindow : public SubWindow
{
public:
    enum SNAPSHOT_TYPE {
        WHOLE,
        VISIBLE
    };
    TImageSnapshot *snp;
    SnapshotSubWindow(TImage*, int);
};

#endif // SNAPSHOTSUBWINDOW_H
