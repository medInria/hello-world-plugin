/*=========================================================================

 medInria

 Copyright (c) INRIA 2013. All rights reserved.
 See LICENSE.txt for details.
 
  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#include "helloWorldWorkspace.h"
#include "helloWorldPlugin.h"
#include "helloWorldToolBox.h"
#include "helloWorldCannyProcess.h"

#include <dtkLog/dtkLog.h>

// /////////////////////////////////////////////////////////////////
// helloWorldPluginPrivate
// /////////////////////////////////////////////////////////////////

class helloWorldPluginPrivate
{
public:
    // Class variables go here.
    static const char *s_Name;
};

const char * helloWorldPluginPrivate::s_Name = "helloWorld";

// /////////////////////////////////////////////////////////////////
// helloWorldPlugin
// /////////////////////////////////////////////////////////////////

helloWorldPlugin::helloWorldPlugin(QObject *parent) : dtkPlugin(parent), d(new helloWorldPluginPrivate)
{
    
}

helloWorldPlugin::~helloWorldPlugin()
{
    delete d;
    
    d = NULL;
}

bool helloWorldPlugin::initialize()
{
    if(!helloWorldWorkspace::registered())
        dtkWarn() << "Unable to register helloWorld workspace";

    if(!helloWorldToolBox::registered())
        dtkWarn() << "Unable to register helloWorld toolboxe";

    if(!helloWorldCannyProcess::registered())
        dtkWarn() << "Unable to register helloWorldCannyProcess process";

    return true;
}

bool helloWorldPlugin::uninitialize()
{
    return true;
}

QString helloWorldPlugin::name() const
{
    return "helloWorldPlugin";
}

QString helloWorldPlugin::description() const
{
    return tr("This is a small example to show how to create a project for a plugin and to build it with the medinria-superproject build on the side. "
              "The plugin create a new workspace that allow vizualiation and a toolbox with a button which popup a hello world message box,"
              "and a button to run an itk Canny edge detection filter. The current view is updated with the output of the filter.");
}

QString helloWorldPlugin::version() const
{
    return HELLOWORLDPLUGIN_VERSION;
}

QString helloWorldPlugin::contact() const
{
    return "medinria-userfeedback@inria.fr";
}

QStringList helloWorldPlugin::authors() const
{
    return QStringList() << "Rene-paul Debroize";
}

QStringList helloWorldPlugin::contributors() const
{
    return QStringList() << "Rene-paul Debroize";;
}

QString helloWorldPlugin::identifier() const
{
    return helloWorldPluginPrivate::s_Name;
}


QStringList helloWorldPlugin::tags() const
{
    return QStringList() << "hello" << "world" << "example" << "how to";
}

QStringList helloWorldPlugin::types() const
{
    return QStringList() << "helloWorld";
}

QStringList helloWorldPlugin::dependencies() const
{
    return QStringList();
}
Q_EXPORT_PLUGIN2(helloWorldPlugin, helloWorldPlugin)
