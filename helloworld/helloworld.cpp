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

helloworld::helloworld(QWidget *parent) : medWorkspace(parent), d(new helloworldPrivate)
{
    d->helloworldToolBox = new medToolBox(parent);
    this->addToolBox(d->helloworldToolBox);

    d->helloworldToolBox->setTitle("The hello world toolbox");

    QWidget *helloworldToolBoxBody = new QWidget(d->helloworldToolBox);
    QPushButton *helloworldButton = new QPushButton("Click here", helloworldToolBoxBody);
    QVBoxLayout *helloworldToolBoxLayout =  new QVBoxLayout(helloworldToolBoxBody);
    helloworldToolBoxLayout->addWidget(helloworldButton);
    helloworldToolBoxBody->setLayout(helloworldToolBoxLayout);

    d->helloworldToolBox->addWidget(helloworldToolBoxBody);

    connect(helloworldButton, SIGNAL(clicked()), this, SLOT(talkToTheWorld()));

}

void helloworld::setupViewContainerStack()
{
    if (!stackedViewContainers()->count())
    {
        const QString description = this->description();
        QString createdTab = addDefaultTypeContainer(description);
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


helloworld::~helloworld(void)
{
    delete d;
    d = NULL;
}

QString helloworld::identifier() const {
    return "Hello world !!!";
}

QString helloworld::description() const {
    return tr("  Would I say : 'Hello World !!!' ?  ");
}

bool helloworld::isUsable(){
    return true;
}



bool helloworld::registered()
{
    return medWorkspaceFactory::instance()->registerWorkspace
            <helloworld>(
                "Hello world !!!",
                "Hello world !!!",
                "  Would I say : 'Hello World !!!' ?  "
                );
}
