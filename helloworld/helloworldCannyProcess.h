#pragma once

#include <dtkCore/dtkAbstractProcess.h>

#include "helloworldPluginExport.h"

class helloworldCannyProcessPrivate;

class HELLOWORLDPLUGIN_EXPORT helloworldCannyProcess : public dtkAbstractProcess
{
    Q_OBJECT

public:
   helloworldCannyProcess(void);
    virtual ~helloworldCannyProcess(void);

    virtual QString description(void) const;

    static bool registered(void);


public slots:

    //! Input data to the plugin is set through here
    void setInput(dtkAbstractData *data);

    //! Parameters are set through here, channel allows to handle multiple parameters
    void setParameter(double  data, int channel);

    //! Method to actually start the filter
    int update(void);

    //! The output will be available through here
    dtkAbstractData *output(void);

private:
   helloworldCannyProcessPrivate *d;

};

dtkAbstractProcess *createhelloworldCannyProcess();

