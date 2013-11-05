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

#include <QMessageBox>

#include <medWorkspaceFactory.h>

class helloworldPrivate
{
public:
    medToolBox *helloworldToolBox;

};

// constructor of the workspace
helloworld::helloworld(QWidget *parent) : medWorkspace(parent), d(new helloworldPrivate)
{
    // Create a ToolBox and add it to the toolBox container of the workspace.
    d->helloworldToolBox = new medToolBox(parent);
    this->addToolBox(d->helloworldToolBox);

    d->helloworldToolBox->setTitle("The hello world toolbox");

    // Fill the toolBox
    QWidget *helloworldToolBoxBody = new QWidget(d->helloworldToolBox);
    QPushButton *helloworldButton = new QPushButton("Click here", helloworldToolBoxBody);
    QVBoxLayout *helloworldToolBoxLayout =  new QVBoxLayout(helloworldToolBoxBody);
    helloworldToolBoxLayout->addWidget(helloworldButton);
    helloworldToolBoxBody->setLayout(helloworldToolBoxLayout);
    d->helloworldToolBox->addWidget(helloworldToolBoxBody);

    // Connections
    connect(helloworldButton, SIGNAL(clicked()), this, SLOT(talkToTheWorld()));

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
        const QString description = this->description();
        QString createdTab = addDefaultTypeContainer("Hello world tab");
        qDebug() << "Workspace" << this->description() << "created a new tab" << createdTab;
    }
}


void helloworld::talkToTheWorld()
{
    QMessageBox::information(d->helloworldToolBox,
                             "Hi !",
                             "Hello world !!!"
                             );
}


QString helloworld::identifier() const {
    return "Hello world !!!";
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
                "Hello world !!!",
                "Hello world !!!",
                "Would I say : 'Hello World !!!' ?"
                );
}
