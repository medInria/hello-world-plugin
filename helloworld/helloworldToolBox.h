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

#include "helloworldPluginExport.h"

class helloworldToolBoxPrivate;
class medDataIndex;

class HELLOWORLDPLUGIN_EXPORT helloworldToolBox : public medToolBox
{
    Q_OBJECT

public:
    helloworldToolBox(QWidget *parentToolBox = 0);
    ~helloworldToolBox();

    static bool registered();
    dtkPlugin* plugin();

public slots:
    void enableCannyProcessButton(const bool enable);

private slots:
    void talkToTheWorld();

private:
    helloworldToolBoxPrivate *d;

};

medToolBox *createhelloworldToolBox(QWidget *parent);


