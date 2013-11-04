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
    return tr("");
}

QString helloworldPlugin::version() const
{
    return HELLOWORLDPLUGIN_VERSION;
}

QString helloworldPlugin::contact() const
{
    return "";
}

QStringList helloworldPlugin::authors() const
{
    QStringList list;
    return list;
}

QStringList helloworldPlugin::contributors() const
{
    QStringList list;
    return list;
}

QString helloworldPlugin::identifier() const
{
    return helloworldPluginPrivate::s_Name;
}


QStringList helloworldPlugin::tags() const
{
    return QStringList();
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
