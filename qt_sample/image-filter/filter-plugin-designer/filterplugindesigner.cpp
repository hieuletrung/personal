#include "filterplugindesigner.h"

#include "filterwidget.h"

FilterPluginDesigner::FilterPluginDesigner(QObject* parent) :
    QObject(parent),
    QDesignerCustomWidgetInterface()
{

}

QString FilterPluginDesigner::name() const
{
    return "FilterWidget";
}
QString FilterPluginDesigner::group() const
{
    return "My Filter Group";
}
QString FilterPluginDesigner::toolTip() const
{
    return "A filtered picture";
}
QString FilterPluginDesigner::whatsThis() const
{
    return "The filter widget applies an image effect";
}

QIcon FilterPluginDesigner::icon() const
{
    return QIcon(":/icon.jpg");
}

bool FilterPluginDesigner::isContainer() const
{
    return false;
}

QString FilterPluginDesigner::includeFile() const
{
    return "filterwidget.h";
}

QWidget* FilterPluginDesigner::createWidget(QWidget* parent)
{
    return new FilterWidget(parent);
}

bool FilterPluginDesigner::isInitialized() const
{
    return mInitialized;
}

void FilterPluginDesigner::initialize(QDesignerFormEditorInterface*)
{
    if (mInitialized) {
        return;
    }

    mInitialized = true;
}
