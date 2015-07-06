/*=========================================================================

 medInria

 Copyright (c) INRIA 2013. All rights reserved.
 See LICENSE.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#pragma once

#include <medFilteringAbstractToolBox.h>

#include "helloWorldPluginExport.h"

class helloWorldToolBoxPrivate;
class medDataIndex;

class HELLOWORLDPLUGIN_EXPORT helloWorldToolBox : public medToolBox
{
    Q_OBJECT

    MED_TOOLBOX_INTERFACE("Hello World",
                          "Hello World !!!",
                          <<"helloWorld")

public:
    helloWorldToolBox(QWidget *parentToolBox = 0);
    ~helloWorldToolBox();

    static bool registered();
    dtkPlugin* plugin();

public slots:
    void enableCannyProcessButton(const bool enable);

private slots:
    void talkToTheWorld();

private:
    helloWorldToolBoxPrivate *d;

signals:
    void runCannyProcess();

};



