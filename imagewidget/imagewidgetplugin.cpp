#include "imagewidgetplugin.h"

#include <QtDebug>
#include <QtPlugin>
#include <QDesignerFormEditorInterface>
#include <QDesignerFormWindowInterface>
#include <QDesignerFormWindowCursorInterface>
#include <QExtensionManager>
#include <QColorDialog>
#include <QTabWidget>
#include "timage.h"

CustomWidgetInterface::CustomWidgetInterface(QObject *parent): QObject(parent), d_isInitialized(false)
{
    QColor c;
    for (int i = 0; i < 48; i++)
    {
    //    c = EColor((Elettra::colors)i);
     //   if (c.isValid())
      //      QColorDialog::setStandardColor(i, c.rgb());
    }
}

void CustomWidgetInterface::initialize(QDesignerFormEditorInterface *formEditor)
{
    if (d_isInitialized)
        return;

    QExtensionManager *manager = formEditor->extensionManager();
    if (manager)
        manager->registerExtensions(new TaskMenuFactory(manager), Q_TYPEID(QDesignerTaskMenuExtension));

    d_isInitialized = true;
}

TImageInterface::TImageInterface(QObject* parent) : CustomWidgetInterface(parent)
{
        d_name = "TImage";
        d_include = "TImage";
        d_icon = QPixmap(":pixmaps/timage.png");
        d_domXml =
        "<widget class=\"TImage\" name=\"timage\">\n"
        " <property name=\"geometry\">\n"
        "  <rect>\n"
        "   <x>0</x>\n"
        "   <y>0</y>\n"
        "   <width>87</width>\n"
        "   <height>28</height>\n"
        "  </rect>\n"
        " </property>\n"
        "</widget>\n";
}

QWidget* TImageInterface::createWidget(QWidget* parent)
{
    TImage * image = new TImage(parent);
    //image->setDesignerMode(true);
   // image->enableDrops();
    return image;
}

TImageSnpInterface::TImageSnpInterface(QObject* parent) : CustomWidgetInterface(parent)
{
        d_name = "TImageSnp";
        d_include = "TImageSnapshot";
        d_icon = QPixmap(":pixmaps/timage.png");
        d_domXml =
        "<widget class=\"TImageSnapshot\" name=\"timagesnp\">\n"
        " <property name=\"geometry\">\n"
        "  <rect>\n"
        "   <x>0</x>\n"
        "   <y>0</y>\n"
        "   <width>87</width>\n"
        "   <height>28</height>\n"
        "  </rect>\n"
        " </property>\n"
        "</widget>\n";

}

QWidget* TImageSnpInterface::createWidget(QWidget* parent)
{
    TImageSnapshot * image = new TImageSnapshot(parent);
//    image->enableDrops();
    return image;
}
///// */



CustomWidgetCollectionInterface::CustomWidgetCollectionInterface(QObject *parent): QObject(parent)
{

   //*//My_code//

    d_plugins.append(new TImageInterface(this));   //!!!!!!!!!
     d_plugins.append(new TImageSnpInterface(this));   //!!!!!!!!!
    ///   */
}

QList<QDesignerCustomWidgetInterface*> CustomWidgetCollectionInterface::customWidgets(void) const
{
    return d_plugins;
}

/* TaskMenuFactory */

TaskMenuFactory::TaskMenuFactory(QExtensionManager *parent): QExtensionFactory(parent)
{
}

QObject *TaskMenuFactory::createExtension(QObject *object, const QString &iid, QObject *parent) const
{
    if (iid != Q_TYPEID(QDesignerTaskMenuExtension)) {
        return 0;
    } else if (qobject_cast<TImage*>(object)) {
        return new TaskMenuExtension((QWidget*) object, parent);
    } else if (qobject_cast<TImageSnapshot*>(object)) {
        return new TaskMenuExtension((QWidget*) object, parent);
    }
    return QExtensionFactory::createExtension(object, iid, parent);
}

TaskMenuExtension::TaskMenuExtension(QWidget *widget, QObject *parent): QObject(parent), d_widget(widget), d_editTangoAction(0), d_editAction(0)//, editSourceDialog(0)
{
    d_editTangoAction = new QAction(tr("Edit Tango Connection..."), this);
    d_editAction = new QAction(tr("Edit Properties..."), this);
    connect(d_editTangoAction, SIGNAL(triggered()), this, SLOT(editTango()));
    connect(d_editAction, SIGNAL(triggered()), this, SLOT(editAttributes()));
}

QList<QAction *> TaskMenuExtension::taskActions() const
{
    QList<QAction *> list;
    QString cname(d_widget->metaObject()->className());
        if (/*My_code*/(cname == "TImageSnp") || (cname == "TImage") )
        list.append(d_editTangoAction);
        if (/*My_code */(cname == "TImage") || (cname == "TSimpleLabel") )
        list.append(d_editAction);
    return list;
}

QAction *TaskMenuExtension::preferredEditAction() const
{
    return d_editTangoAction;
}

void TaskMenuExtension::editTango()
{
    QString stringaIniziale;
    bool edit_source = true;
    if (qobject_cast<TImage*>(d_widget)) {
        // do nothing
    } else {
        return;
    }
    if (edit_source) {
        /*if (editSourceDialog == 0)
            editSourceDialog = new EditSourceDialog();

        editSourceDialog->ui.lineEdit->setText(stringaIniziale);
        if (editSourceDialog->exec() == QDialog::Accepted)
        {
            QDesignerFormWindowInterface *formWindow = 0;
            formWindow = QDesignerFormWindowInterface::findFormWindow(d_widget);
            formWindow->cursor()->setProperty("source", editSourceDialog->ui.lineEdit->text());
        }*/
    }
    else
    {
        /*EditTargetDialog *d = new EditTargetDialog();
        qDebug() << "stringa iniziale (prima di split): " << stringaIniziale;
        qDebug() << "listWidget: aggiungo: " << stringaIniziale.split(';');
        d->ui.listWidget->addItems(stringaIniziale.split(';'));
        if (d->exec() == QDialog::Accepted)
        {
            QDesignerFormWindowInterface *formWindow = 0;
            formWindow = QDesignerFormWindowInterface::findFormWindow(d_widget);
            QString targets;
            foreach (QListWidgetItem *it, d->ui.listWidget->findItems("*", Qt::MatchWildcard))
            {
                targets.append(it->text() + ";");
            }
            qDebug() << "targets sarebbero:" << targets;
            qDebug() << "formWindow:" << formWindow;
            formWindow->cursor()->setProperty("targets", targets);
        }
        */
    }
}

Q_EXPORT_PLUGIN2(QTango, CustomWidgetCollectionInterface)
