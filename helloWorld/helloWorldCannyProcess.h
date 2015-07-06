#pragma once

#include <medAbstractProcess.h>

#include "helloWorldPluginExport.h"

class helloWorldCannyProcessPrivate;

class HELLOWORLDPLUGIN_EXPORT helloWorldCannyProcess : public medAbstractProcess
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
    void setInputData(medAbstractData *data);

    //! variance parameter of the canny edge detection filtrer.
    void setVariance(unsigned int variance);

    //! Method to actually start the filter
    int update(void);

    //! The output will be available through here
    medAbstractData *output(void);

private:
    template <class ImageType> void runCanny();
    helloWorldCannyProcessPrivate *d;

};
