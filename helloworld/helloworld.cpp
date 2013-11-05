/*=========================================================================

 medInria

 Copyright (c) INRIA 2013. All rights reserved.
 See LICENSE.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#include "helloworld.h"


#include <medTabbedViewContainers.h>
#include <medToolBox.h>
#include <medToolBoxFactory.h>
#include <QMessageBox>

#include <medWorkspaceFactory.h>

class helloworldPrivate
{
public:

};

// constructor of the workspace
helloworld::helloworld(QWidget *parent) : medWorkspace(parent), d(new helloworldPrivate)
{
    // Create suitable toolboxes and add them to the toolBox container of the workspace.
    foreach(QString tbName, medToolBoxFactory::instance()->toolBoxesFromCategory("helloworld"))
    {

        qDebug()<<"\n\ntbName: " << tbName;
        medToolBox *tb = medToolBoxFactory::instance()->createToolBox(tbName);
        if (tb)
            this->addToolBox(tb);
    }
}

// destructor
helloworld::~helloworld(void)
{
    delete d;
    d = NULL;
}

// Create a new tab in the view container of the workspace, where one can open views.
void helloworld::setupViewContainerStack()
{
    if (!stackedViewContainers()->count())
    {
        QString createdTab = addDefaultTypeContainer("Hello world tab");
        qDebug() << "Workspace" << this->identifier() << "created a new tab" << createdTab;
    }
}


QString helloworld::identifier() const {
    return "helloworld";
}

QString helloworld::description() const {
    return tr("Would I say : 'Hello World !!!' ?");
}

bool helloworld::isUsable(){
    return true;
}

// Your plugin could be dynamically load since you have implemented the registered methode.
// It is call at the initialization of the plugin when the application start.
bool helloworld::registered()
{
    // Here call a suitable factory, depending of the type of your plugin.
    // (ie: workspace, process, data, dataSource, etc.)
    return medWorkspaceFactory::instance()->registerWorkspace
            <helloworld>(
                "helloworld",
                "Hello world !!!",
                "Would I say : 'Hello World !!!' ?"
                );
}
