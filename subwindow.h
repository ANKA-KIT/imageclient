#ifndef SUBWINDOW_H
#define SUBWINDOW_H

#include <QMdiSubWindow>
//#include <QScrollArea>
#include <QLabel>
#include <QMenu>
#include <imagewidget.h>

/*!
  \file subwindow.h
  \author Georgii Vasilev
  \class StartTangoWin
  \brief Parent class wor subwindows
  ///Parent class of subwindows
*/
class SubWindow : public QMdiSubWindow
{
    Q_OBJECT
protected:
    int _space;                /*!< static margin value for correct displaying picture in full picture mode*/
    QMenu contextMenu;         /*!< Context menu*/
    QAction *_setOffMarker;       /*!< Set Off marker*/


    /*!
        \brief Change picture mode
        \param mode - picture mode
    */
    void chImageMode(int mode);

    /*!
        \brief init property labels
        \param x - margin
    */
    void initLb(int x);

    /*!
        \brief Calculate new scale for current snapshot subwindow
        \param width of subwindow
        \param height of subwindow
    */
    void calcFullPictureScale(int width, int height);
public:
    ImageWidget *wgt;   /*!< widget for displaying picture*/
    QWidget *board;     /*!< widget for keeping wgt and image properties labels*/
    QLabel *lbRot;      /*!< Rotation label*/
    QLabel *lbBr;       /*!< Brightness label*/
    QLabel *lbCon;      /*!< Contrast label*/
    QLabel *lbGam;      /*!< Gamma label*/
    QLabel *lbScl;      /*!< Scale label*/
    QLabel *lbHorFl;    /*!< Horizontal fliping label*/
    QLabel *lbVerFl;    /*!< Vertical fliping label*/
    QScrollArea * scrollArea; /*!< scale widget with scrool, uses in siziable mode*/
    int dimX;           /*!< width value for calculating fullscreen mode*/
    int dimY;           /*!< height value for calculating fullscreen mode*/
    bool fullPictureMode;   /*!< is it full picture mode*/

    /*!
        \brief Constructor
    */
    explicit SubWindow(QMdiSubWindow *parent = 0);

    /*!
        \brief fill context menu
        \param acts - list of actions
    */
    void setActionMenu(QList<QAction *> acts);

    /*!
        \brief Destructor
    */
    virtual ~SubWindow();
signals:
    void send16BitData(vector <unsigned short>);        /*!< sending 16bit picture data,, uses in slider for display in histogram emited in subwindowrelatime::makeimg every time*/
    void send16BitDataDirect(vector <unsigned short>);  /*!< sending 16bit picture data, uses in slider for display in histogram emited in send16BitDataSlot (slot)*/
    void newPicture();                                  /*!< sending the signal about geting new image from tangoserver*/
    void DisplayModeChanged();                            /*!< on changing fullscreen/sizable mode*/
    void fullPictureModeChanged(SubWindow*);            /*!< Reconnect mainwindow widgets*/
public slots:
    /*!
        \brief set brightness label value
    */
    void setLbBr(QVariant val);

    /*!
        \brief set rotation label value
    */
    void setLbRot(QVariant val);

    /*!
        \brief set contrast label value
    */
    void setLbCon(QVariant val);

    /*!
        \brief set gamma label value
    */
    void setLbGam(QVariant val);

    /*!
        \brief set scale label value
    */
    void setLbScl(QVariant val);

    /*!
        \brief set horizostal fliping label value
    */
    void setLbHFlip(QVariant val);

    /*!
        \brief set vertical fliping label value
    */
    void setLbVFlip(QVariant val);

    /*!
        \brief Emit send16BitDataDirect(vector <unsigned short>)
    */
    void send16BitDataSlot();

    /*!
        \brief show context menu
        \param pos - cursor position
    */
    void ShowContextMenu(const QPoint& pos);

    /*!
        \brief void virtual function of set/unset fullpicture mode
        \param val - set/unset fullPictureMode (true - set fullPictureMode/ false - set siziable mode)
    */
    virtual void setFullPictureMode(bool val){}

    /*!
        \brief void slot On resize subwindow
        \param event  - resize event pointer
    */
    void resizeEvent ( QResizeEvent * event ){}

    /*!< \brief Set Off marker*/
    void setOffMarker();
};

#endif // SUBWINDOW_H
