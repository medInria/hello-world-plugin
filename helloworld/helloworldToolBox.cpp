/*=========================================================================

 medInria

 Copyright (c) INRIA 2013. All rights reserved.
 See LICENSE.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#include "helloworldToolBox.h"

#include <medToolBoxFactory.h>
#include <medPluginManager.h>

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>


helloworldToolBox::helloworldToolBox ( QWidget *parent ) : medToolBox ( parent )
{
    this->setTitle("The hello world toolbox");
    this->setAboutPluginVisibility(true);
    this->setAboutPluginButton(this->plugin());

    // Fill the toolBox
    QWidget *helloworldToolBoxBody = new QWidget(this);
    QPushButton *helloworldButton = new QPushButton("Click here", helloworldToolBoxBody);
    QVBoxLayout *helloworldToolBoxLayout =  new QVBoxLayout(helloworldToolBoxBody);
    helloworldToolBoxLayout->addWidget(helloworldButton);
    helloworldToolBoxBody->setLayout(helloworldToolBoxLayout);
    this->addWidget(helloworldToolBoxBody);

    // Connections
    connect(helloworldButton, SIGNAL(clicked()), this, SLOT(talkToTheWorld()));
}

helloworldToolBox::~helloworldToolBox()
{

}


void helloworldToolBox::talkToTheWorld()
{
    QMessageBox::information(this,
                             "Hi !",
                             "Hello world !!!"
                             );
}

bool helloworldToolBox::registered()
{
    medToolBoxFactory* factory = medToolBoxFactory::instance();
    return factory->registerToolBox<helloworldToolBox> (
                "helloworld",
                "Hello world !!!",
                "Would I say : 'Hello World !!!' ?",
                QStringList()<<"helloworld"
                );
}


dtkPlugin* helloworldToolBox::plugin()
{
    medPluginManager* pm = medPluginManager::instance();
    dtkPlugin* plugin = pm->plugin ( "helloworldPlugin" );
    return plugin;
}


medToolBox *createHelloworldToolBox ( QWidget *parent )
{
    return new helloworldToolBox ( parent );
}
