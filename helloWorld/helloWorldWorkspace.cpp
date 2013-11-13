/*=========================================================================

 medInria

 Copyright (c) INRIA 2013. All rights reserved.
 See LICENSE.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#include "helloWorldWorkspace.h"


#include <medTabbedViewContainers.h>
#include <medToolBox.h>
#include <medToolBoxFactory.h>
#include <QMessageBox>
#include <medAbstractView.h>

#include <medWorkspaceFactory.h>
#include <medSingleViewContainer.h>

#include <medDataIndex.h>
#include <medRunnableProcess.h>
#include <medJobManager.h>

#include "helloWorldCannyProcess.h"

#include <medDataManager.h>
#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractProcessFactory.h>

#include <medMessageController.h>

class helloWorldWorkspacePrivate
{
public:
    dtkSmartPointer <dtkAbstractData> inputData;
    dtkSmartPointer<dtkAbstractProcess> process;
};

// constructor of the workspace
helloWorldWorkspace::helloWorldWorkspace(QWidget *parent) : medWorkspace(parent), d(new helloWorldWorkspacePrivate)
{
    // Create suitable toolboxes and add them to the toolBox container of the workspace.
    foreach(QString tbName, medToolBoxFactory::instance()->toolBoxesFromCategory("helloWorld"))
    {
        medToolBox *tb = medToolBoxFactory::instance()->createToolBox(tbName);
        if (tb)
        {
            this->addToolBox(tb);
            connect(this, SIGNAL(dataValidForCanny(const bool)), tb, SLOT(enableCannyProcessButton(const bool)));
            connect(tb, SIGNAL(runCannyProcess()), this, SLOT(runCannyProcess()));
        }
    }
}

// destructor
helloWorldWorkspace::~helloWorldWorkspace(void)
{
    delete d;
    d = NULL;
}

// check if we do have an itkImage with 3 dimension
void helloWorldWorkspace::checkInput(const medDataIndex &index)
{
    if ( !index.isValid() )
        return;

    dtkAbstractData *inputData = medDataManager::instance()->data(index).data();

    if ( !inputData )
        return;

    QString type = QString (inputData->identifier());
    unsigned int nbDimension = type.right(1).toInt();
    if (!type.contains("itkData") || nbDimension != 3)
    {
        emit dataValidForCanny(false);
        return;
    }

    d->inputData = inputData;
    emit dataValidForCanny(true);
}

void helloWorldWorkspace::runCannyProcess()
{
     emit dataValidForCanny(false);

    d->process = dtkAbstractProcessFactory::instance()->createSmartPointer("helloWorldCannyProcess");
    d->process->setInput(d->inputData);

    medRunnableProcess *runProcess = new medRunnableProcess;
    runProcess->setProcess (d->process);

    medJobManager::instance()->registerJobItem(runProcess);
    connect(runProcess, SIGNAL(success(QObject*)), this, SLOT(setCannyOutput()));

    medMessageProgress *messageProgress = medMessageController::instance()->showProgress("Canny edge detection");

    messageProgress->setProgress(0);
    connect(runProcess, SIGNAL(progressed(int)), messageProgress, SLOT(setProgress(int)));
    connect(runProcess, SIGNAL(success(QObject*)), messageProgress, SLOT(success()));

    QThreadPool::globalInstance()->start(dynamic_cast<QRunnable*>(runProcess));
}



void helloWorldWorkspace::setCannyOutput()
{
    this->currentViewContainer()->view()->close();
    this->currentViewContainer()->open(d->process->output());
}

// Create a new tab in the view container of the workspace, where one can open views.
void helloWorldWorkspace::setupViewContainerStack()
{
    if (!this->stackedViewContainers()->count())
    {
        medSingleViewContainer *singleViewContainer = new medSingleViewContainer ();
        connect(singleViewContainer, SIGNAL(imageSet(medDataIndex)),
                    this, SLOT(checkInput(medDataIndex)));

        singleViewContainer->setMultiLayer(false);
        this->stackedViewContainers()->addContainer (identifier(), singleViewContainer);
        this->stackedViewContainers()->lockTabs();
        this->stackedViewContainers()->hideTabBar();
    }
}

QString helloWorldWorkspace::identifier() const {
    return "helloWorldWorkspace";
}

QString helloWorldWorkspace::description() const {
    return tr("Would I say : 'Hello World !!!' ?");
}

bool helloWorldWorkspace::isUsable(){
    return true;
}

// Your plugin can be dynamically load once you have implemented the registered method.
// It is called at the initialization of the plugin when the application starts.
bool helloWorldWorkspace::registered()
{
    // Here call a suitable factory, depending of the type of your plugin.
    // (ie: workspace, process, data, dataSource, etc.)
    return medWorkspaceFactory::instance()->registerWorkspace
            <helloWorldWorkspace>(
                "helloWorldWorkspace",
                "Hello world !!!",
                "Would I say : 'Hello World !!!' ?"
                );
}
