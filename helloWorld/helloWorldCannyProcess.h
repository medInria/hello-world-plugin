#pragma once

#include <dtkCore/dtkAbstractProcess.h>

#include "helloWorldPluginExport.h"

class helloWorldCannyProcessPrivate;

class HELLOWORLDPLUGIN_EXPORT helloWorldCannyProcess : public dtkAbstractProcess
{
    Q_OBJECT

public:
   helloWorldCannyProcess(void);
    virtual ~helloWorldCannyProcess(void);

    virtual QString description(void) const;

    static bool registered(void);

    void emitProgressed(int progression);


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
    template <class ImageType> void runCanny();
    helloWorldCannyProcessPrivate *d;

};

dtkAbstractProcess *createhelloWorldCannyProcess();

