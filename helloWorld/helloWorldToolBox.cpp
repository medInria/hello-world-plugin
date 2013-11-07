/*=========================================================================

 medInria

 Copyright (c) INRIA 2013. All rights reserved.
 See LICENSE.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#include "helloWorldToolBox.h"

#include <medToolBoxFactory.h>
#include <medPluginManager.h>

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>




class helloWorldToolBoxPrivate
{
public:
    QPushButton *runCanny;
};

helloWorldToolBox::helloWorldToolBox (QWidget *parent) : medToolBox (parent), d(new helloWorldToolBoxPrivate)
{
    this->setTitle("The hello world toolbox");
    this->setAboutPluginVisibility(true);
    this->setAboutPluginButton(this->plugin());

    // Fill the toolBox
    QWidget *helloWorldToolBoxBody = new QWidget(this);
    QPushButton *helloWorldButton = new QPushButton("Click here", helloWorldToolBoxBody);
    d->runCanny = new QPushButton("run canny edge detection", helloWorldToolBoxBody);
    d->runCanny->setDisabled(true);
    QVBoxLayout *helloWorldToolBoxLayout =  new QVBoxLayout(helloWorldToolBoxBody);
    helloWorldToolBoxLayout->addWidget(helloWorldButton);
    helloWorldToolBoxLayout->addWidget(d->runCanny);
    helloWorldToolBoxBody->setLayout(helloWorldToolBoxLayout);
    this->addWidget(helloWorldToolBoxBody);

    // Connections
    connect(helloWorldButton, SIGNAL(clicked()), this, SLOT(talkToTheWorld()));
    connect(d->runCanny, SIGNAL(clicked()), this, SIGNAL(runCannyProcess()));
}

helloWorldToolBox::~helloWorldToolBox()
{
    delete d;
    d = NULL;
}


void helloWorldToolBox::talkToTheWorld()
{
    QMessageBox::information(this,
                             "Hi !",
                             "Hello world !!!"
                             );
}

void helloWorldToolBox::enableCannyProcessButton(const bool enable)
{
    d->runCanny->setEnabled(enable);
}


bool helloWorldToolBox::registered()
{
    medToolBoxFactory* factory = medToolBoxFactory::instance();
    return factory->registerToolBox<helloWorldToolBox> ("helloWorld",
                                                        "Hello world !!!",
                                                        "Would I say : 'Hello World !!!' ?",
                                                        QStringList()<<"helloWorld"
                                                        );
}


dtkPlugin* helloWorldToolBox::plugin()
{
    medPluginManager* pm = medPluginManager::instance();
    dtkPlugin* plugin = pm->plugin ( "helloWorldPlugin" );
    return plugin;
}


medToolBox *createHelloworldToolBox (QWidget *parent)
{
    return new helloWorldToolBox (parent);
}
