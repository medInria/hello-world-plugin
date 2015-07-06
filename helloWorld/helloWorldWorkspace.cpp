/*=========================================================================

 medInria

 Copyright (c) INRIA 2013. All rights reserved.
 See LICENSE.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#include "helloWorldWorkspace.h"

#include <QMessageBox>

#include <medTabbedViewContainers.h>
#include <medToolBox.h>
#include <medToolBoxFactory.h>
#include <medAbstractView.h>
#include <medWorkspaceFactory.h>
#include <medDataIndex.h>
#include <medRunnableProcess.h>
#include <medJobManager.h>
#include <medDataManager.h>
#include <medMessageController.h>
#include <medAbstractProcess.h>
#include <medViewContainer.h>
#include <medAbstractImageView.h>

#include <dtkCore/dtkAbstractProcessFactory>
#include <dtkCore/dtkSmartPointer>
#include <dtkCore/dtkAbstractProcess>


#include "helloWorldCannyProcess.h"


class helloWorldWorkspacePrivate
{
public:
    medAbstractData *inputData;
    dtkSmartPointer<helloWorldCannyProcess> process;
    medViewContainer *inputContainer;
};

// constructor of the workspace
helloWorldWorkspace::helloWorldWorkspace(QWidget *parent) : medAbstractWorkspace(parent), d(new helloWorldWorkspacePrivate)
{

    d->process = new helloWorldCannyProcess;
    qDebug() << d->process->description();

    d->inputContainer = NULL;

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
    delete d->process;

    delete d;
    d = NULL;
}

// check if we do have an itkImage with 3 dimension
void helloWorldWorkspace::checkInput()
{
    bool valid = true;

    medAbstractImageView *inputView = dynamic_cast<medAbstractImageView *>(d->inputContainer->view());
    if(!inputView)
        valid = false;

    medAbstractData *inputData = inputView->layerData(inputView->currentLayer());
    if(!inputData)
        valid = false;
    else
    {
        QString type = QString (inputData->identifier());
        unsigned int nbDimension = type.right(1).toInt();
        if (!type.contains("itkData") || nbDimension != 3)
            valid = false;
    }
    emit dataValidForCanny(valid);
}

void helloWorldWorkspace::runCannyProcess()
{
    emit dataValidForCanny(false);
    medAbstractImageView *inputView = dynamic_cast<medAbstractImageView *>(d->inputContainer->view());

    qDebug() << d->process->description();

    d->process->setInputData(inputView->layerData(inputView->currentLayer()));

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
    medAbstractData* data = d->process->output();
    medDataManager::instance()->importData(data);

    d->inputContainer->setView(0);
    d->inputContainer->addData(data);
}

// Create a new tab in the view container of the workspace, where one can open views.
void helloWorldWorkspace::setupViewContainerStack()
{
    if (!this->stackedViewContainers()->count())
    {

        d->inputContainer = this->stackedViewContainers()->addContainerInTab(this->name());
        QLabel *inputLabel = new QLabel("INPUT");
        inputLabel->setAlignment(Qt::AlignCenter);
        d->inputContainer->setDefaultWidget(inputLabel);

        d->inputContainer->setClosingMode(medViewContainer::CLOSE_VIEW);
        d->inputContainer->setUserSplittable(false);
        d->inputContainer->setMultiLayered(false);

        this->stackedViewContainers()->lockTabs();
        this->stackedViewContainers()->hideTabBar();
        d->inputContainer->setSelected(true);

        connect(d->inputContainer, SIGNAL(viewContentChanged()), this, SLOT(checkInput()));
    }
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
    return medWorkspaceFactory::instance()->registerWorkspace<helloWorldWorkspace>();
}
