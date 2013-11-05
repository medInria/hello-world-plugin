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

class helloworldToolBoxPrivate;

class helloworldToolBox : public medToolBox
{
    Q_OBJECT

public:
    helloworldToolBox(QWidget *parentToolBox = 0);
    ~helloworldToolBox();

public:
    static bool registered();
    dtkPlugin* plugin();

private slots:
    void talkToTheWorld();

};

medToolBox *createhelloworldToolBox(QWidget *parent);


