/* $Id: qtangoplugin.h,v 1.21 2010/05/25 09:33:08 giacomo Exp $
 *
 * Qt Designer plugin for Qtcontrols
 * this part is based in part on the work of
 * the Qwt project (http://qwt.sf.net).
 */

#ifndef QTANGO_PLUGIN_H
#define QTANGO_PLUGIN_H

#include <qglobal.h>

#include <QDesignerCustomWidgetInterface>
#include <QDesignerTaskMenuExtension>
#include <QExtensionFactory>
#include <QScrollArea>
#include "TImage"
#include "TImageSnapshot"
#include <QAction>

//class EditSourceDialog;


class CustomWidgetInterface: public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    CustomWidgetInterface(QObject *parent);

    virtual bool isContainer() const { return false; }
    virtual bool isInitialized() const { return d_isInitialized; }
    virtual QIcon icon() const { return d_icon; }
    virtual QString codeTemplate() const { return d_codeTemplate; }
    virtual QString domXml() const { return d_domXml; }
    virtual QString group() const { return "TangoImageWidgets"; }
    virtual QString includeFile() const { return d_include; }
    virtual QString name() const { return d_name; }
    virtual QString toolTip() const { return d_toolTip; }
    virtual QString whatsThis() const { return d_whatsThis; }
    virtual void initialize(QDesignerFormEditorInterface *);

protected:
    QString d_name; 
    QString d_include; 
    QString d_toolTip; 
    QString d_whatsThis; 
    QString d_domXml; 
    QString d_codeTemplate;
    QIcon d_icon;

private:
    bool d_isInitialized;
};

class CustomWidgetCollectionInterface: public QObject, public QDesignerCustomWidgetCollectionInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)

public:
    CustomWidgetCollectionInterface(QObject *parent = NULL);

    virtual QList<QDesignerCustomWidgetInterface*> customWidgets() const;

private:
    QList<QDesignerCustomWidgetInterface*> d_plugins;
};

/* CustomWidgetInterface */

//*////My_code////
class TImageInterface: public CustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    TImageInterface(QObject *parent);
    //virtual QWidget *createWidget(QWidget *parent);
    virtual QWidget *createWidget(QWidget *parent);
};

class TImageSnpInterface: public CustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    TImageSnpInterface(QObject *parent);
    //virtual QWidget *createWidget(QWidget *parent);
    virtual QWidget *createWidget(QWidget *parent);
};
///////////  */

/* fine widget  */

class TaskMenuFactory: public QExtensionFactory
{
Q_OBJECT
public:
	TaskMenuFactory(QExtensionManager *parent = 0);

protected:
	QObject *createExtension(QObject *object, const QString &iid, QObject *parent) const;
};

class TaskMenuExtension: public QObject, public QDesignerTaskMenuExtension
{
Q_OBJECT
Q_INTERFACES(QDesignerTaskMenuExtension)

public:
	TaskMenuExtension(QWidget *widget, QObject *parent);

	QAction *preferredEditAction() const;
	QList<QAction *> taskActions() const;

private slots:
	void editTango();
    //void editAttributes();
	
protected:
	QWidget *d_widget;
	QAction *d_editTangoAction;
	QAction *d_editAction;
//	void setupSourceTargetDialog(QWidget *s);

//	EditSourceDialog *editSourceDialog;
};

#endif
