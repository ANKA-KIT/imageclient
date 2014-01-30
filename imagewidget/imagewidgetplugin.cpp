/* $Id: qtangoplugin.cpp,v 1.40 2010/10/21 08:57:21 giacomo Exp $ */

#include "imagewidgetplugin.h"
#include <QtDebug>
#include <QtPlugin>
#include <QDesignerFormEditorInterface>
#include <QDesignerFormWindowInterface>
#include <QDesignerFormWindowCursorInterface>
#include <QExtensionManager>
#include <QColorDialog>

//*//My_code
//#include <timage.h>
//#include <timagesnapshot.h>
/////////// */

#include <QTabWidget>

//#include <unistd.h>


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

//*///My_code///
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
    if (iid != Q_TYPEID(QDesignerTaskMenuExtension))
        return 0;

        //* ////My_code
        else if (TImage *tim = qobject_cast<TImage*>(object)) //!!!!!
                return new TaskMenuExtension((QWidget*)object, parent);       //!!!!!!!!

        else if (TImageSnapshot *tims = qobject_cast<TImageSnapshot*>(object)) //!!!!!
            return new TaskMenuExtension((QWidget*)object, parent);       //!!!!!!!!
        ///////////// */


    return QExtensionFactory::createExtension(object, iid, parent);
}
/* */

/* TaskMenuExtension */
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
/*
void TaskMenuExtension::setupSourceTargetDialog(QWidget *cb_widget)
{
        QString source = cb_widget->property("source").toString();
        QString targets = cb_widget->property("targets").toString();

    QDialog *w = new QDialog();
//	QDialog *wt = new QDialog();

    QGridLayout *grid = new QGridLayout(w);
    QTabWidget *tw = new QTabWidget(w);

    EditSourceDialog *wins = new EditSourceDialog(0);
    EditTargetDialog *wint = new EditTargetDialog(0);
    tw->addTab(wins, "Source");
    tw->addTab(wint, "Target");
    tw->setCurrentIndex(0);

    //* Creating source dialog /
    wins->ui.okButton->setHidden(true);
    wins->ui.cancelButton->setHidden(true);
        wins->ui.lineEdit->setText(source);

    //* Creating target dialog /
    wint->ui.okButton->setHidden(true);
    wint->ui.cancelButton->setHidden(true);
        wint->ui.listWidget->addItems(targets.split(";",QString::SkipEmptyParts));

    grid->setRowStretch(0, 2);
    grid->addWidget(tw, 0, 0, 1, 2);

    QPushButton *okb = new QPushButton("OK", w);
    QPushButton *cancb = new QPushButton("Cancel", w);
    grid->addWidget(okb, 1, 0);
    grid->addWidget(cancb, 1, 1);
    connect(okb, SIGNAL(clicked() ), w, SLOT(accept() ) );
    connect(cancb, SIGNAL(clicked() ), w, SLOT(reject() ) );

    if (w->exec() == QDialog::Accepted)
    {
        QDesignerFormWindowInterface *formWindow = 0;
        formWindow = QDesignerFormWindowInterface::findFormWindow(d_widget);
        formWindow->cursor()->setProperty("source", wins->ui.lineEdit->text());

        QString targets;
        foreach (QListWidgetItem *it, wint->ui.listWidget->findItems("*", Qt::MatchWildcard))
        {
            targets.append(it->text());
            targets.append(";");
        }
        formWindow->cursor()->setProperty("targets", targets);
    }
    else
        qDebug() << "Caso non accettato!";

    delete wins;
    delete wint;
    delete w;
}
*/
void TaskMenuExtension::editTango()
{
    QString stringaIniziale;
    bool edit_source = true;
    //* //My_code///
    if (TImage *tim = qobject_cast<TImage*>(d_widget)){}

           // stringaIniziale = tim->source();    /////!!
    ////////////  */
    else
        return;

    if (edit_source)
    {
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
/*
void TaskMenuExtension::editAttributes()
{
    if (TLabel *label = qobject_cast<TLabel*>(d_widget))
    {
        TLabelBoolEditor *w = new TLabelBoolEditor(label->trueString(), label->falseString(), label->trueColor(), label->falseColor());

        if (w->exec() == QDialog::Accepted)
        {
            QDesignerFormWindowInterface *formWindow = 0;
            formWindow = QDesignerFormWindowInterface::findFormWindow(label);
            formWindow->cursor()->setProperty("trueString", w->ui.lineEditTrue->text());
            formWindow->cursor()->setProperty("falseString", w->ui.lineEditFalse->text());
            formWindow->cursor()->setProperty("trueColor", w->ui.pushColorTrue->palette().color(QPalette::Button));
            formWindow->cursor()->setProperty("falseColor", w->ui.pushColorFalse->palette().color(QPalette::Button));
        }
    }
    else if (TTable *table = qobject_cast<TTable*>(d_widget))
    {
        TTableBoolEditor *w = new TTableBoolEditor(table->readNumRows(), table->readNumColumns(), table->trueStrings(), table->falseStrings(), table->trueColors(), table->falseColors(), table->getDisplayMask());

        if (w->exec() == QDialog::Accepted)
        {
            QDesignerFormWindowInterface *formWindow = 0;
            formWindow = QDesignerFormWindowInterface::findFormWindow(table);
            formWindow->cursor()->setProperty("numRows", w->ui.eFlagTrue->readNumRows());
            formWindow->cursor()->setProperty("numColumns", w->ui.eFlagTrue->readNumColumns());
            formWindow->cursor()->setProperty("trueStrings", w->ui.eFlagTrue->trueStrings());
            formWindow->cursor()->setProperty("falseStrings", w->ui.eFlagTrue->falseStrings());
            formWindow->cursor()->setProperty("trueColors", w->ui.eFlagTrue->trueColors());
            formWindow->cursor()->setProperty("falseColors", w->ui.eFlagTrue->falseColors());
            formWindow->cursor()->setProperty("displayMask", w->ui.lineMask->text());
        }
    }
    else if (TLed *led = qobject_cast<TLed*>(d_widget))
    {
        TLedBoolEditor *w = new TLedBoolEditor(led->trueColor(), led->falseColor());
        if (w->exec() == QDialog::Accepted)
        {
            QDesignerFormWindowInterface *formWindow = 0;
            formWindow = QDesignerFormWindowInterface::findFormWindow(led);
            formWindow->cursor()->setProperty("trueColor", w->ui.tLedTrue->trueColor());
            formWindow->cursor()->setProperty("falseColor", w->ui.tLedFalse->falseColor());
        }
    }
}
 */

Q_EXPORT_PLUGIN2(QTango, CustomWidgetCollectionInterface)
