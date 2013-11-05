/*=========================================================================

 medInria

 Copyright (c) INRIA 2013. All rights reserved.
 See LICENSE.txt for details.
 
  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#include "helloworld.h"
#include "helloworldPlugin.h"

#include <dtkLog/dtkLog.h>

// /////////////////////////////////////////////////////////////////
// helloworldPluginPrivate
// /////////////////////////////////////////////////////////////////

class helloworldPluginPrivate
{
public:
    // Class variables go here.
    static const char *s_Name;
};

const char * helloworldPluginPrivate::s_Name = "helloworld";

// /////////////////////////////////////////////////////////////////
// helloworldPlugin
// /////////////////////////////////////////////////////////////////

helloworldPlugin::helloworldPlugin(QObject *parent) : dtkPlugin(parent), d(new helloworldPluginPrivate)
{
    
}

helloworldPlugin::~helloworldPlugin()
{
    delete d;
    
    d = NULL;
}

bool helloworldPlugin::initialize()
{
    if(!helloworld::registered())
        dtkWarn() << "Unable to register helloworld type";
    
    return true;
}

bool helloworldPlugin::uninitialize()
{
    return true;
}

QString helloworldPlugin::name() const
{
    return "helloworldPlugin";
}

QString helloworldPlugin::description() const
{
    return tr("This is a small example to show how to create a project for a plugin and to build it with the medinria-superproject build on the side. "
              "The plugin create a new workspace that allow vizualiation and a toolbox with a button which popup a hello world message box.");
}

QString helloworldPlugin::version() const
{
    return HELLOWORLDPLUGIN_VERSION;
}

QString helloworldPlugin::contact() const
{
    return "medinria-userfeedback@inria.fr";
}

QStringList helloworldPlugin::authors() const
{
    return QStringList() << "René-paul Debroize";
}

QStringList helloworldPlugin::contributors() const
{
    return QStringList() << "René-paul Debroize";;
}

QString helloworldPlugin::identifier() const
{
    return helloworldPluginPrivate::s_Name;
}


QStringList helloworldPlugin::tags() const
{
    return QStringList() << "hello" << "world" << "example" << "how to";
}

QStringList helloworldPlugin::types() const
{
    return QStringList() << "helloworld";
}

QStringList helloworldPlugin::dependencies() const
{
    return QStringList();
}
Q_EXPORT_PLUGIN2(helloworldPlugin, helloworldPlugin)
