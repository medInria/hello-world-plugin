/*=========================================================================

 medInria

 Copyright (c) INRIA 2013. All rights reserved.
 See LICENSE.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#pragma once

#include <QtCore>

#include <medWorkspace.h>

#include "helloWorldPluginExport.h"


class helloWorldWorkspacePrivate;
class medDataIndex;

class HELLOWORLDPLUGIN_EXPORT helloWorldWorkspace : public medWorkspace
{
    Q_OBJECT

public:
     helloWorldWorkspace(QWidget *parent = 0);
    ~helloWorldWorkspace();

    virtual void setupViewContainerStack();

    virtual QString identifier()  const;
    virtual QString description() const;
    static bool isUsable();

    static bool registered();

private slots:
    void checkInput(const medDataIndex &index);
    void runCannyProcess();
    void setCannyOutput();

signals:
    void dataValidForCanny(const bool valid);

private:
    helloWorldWorkspacePrivate *d;
};

