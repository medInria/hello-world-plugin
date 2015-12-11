#include "helloWorldCannyProcess.h"

#include <medMetaDataKeys.h>
#include <medAbstractDataFactory.h>

#include <itkCannyEdgeDetectionImageFilter.h>
#include <itkCastImageFilter.h>

#include <dtkCore/dtkAbstractProcessFactory>

// /////////////////////////////////////////////////////////////////
// helloWorldCannyProcessPrivate
// /////////////////////////////////////////////////////////////////

class helloWorldCannyProcessPrivate
{
public:
    helloWorldCannyProcess *parent;
    helloWorldCannyProcessPrivate() :parent(NULL){}

    medAbstractData* input;
    medAbstractData* output;
    double variance;

    itk::CStyleCommand::Pointer callback;
    static void eventCallback(itk::Object* caller, const itk::EventObject& event, void* clientData);
};


void
helloWorldCannyProcessPrivate::eventCallback(itk::Object* caller, const itk::EventObject& event, void* clientData)
{
    helloWorldCannyProcessPrivate *d = reinterpret_cast<helloWorldCannyProcessPrivate *> (clientData);
    itk::ProcessObject * processObject = ( itk::ProcessObject* ) caller;
    d->parent->emitProgressed (static_cast<int>((processObject->GetProgress() * 95)));
}

// /////////////////////////////////////////////////////////////////
// helloWorldCannyProcess
// /////////////////////////////////////////////////////////////////

helloWorldCannyProcess::helloWorldCannyProcess(void) : medAbstractProcess(), d(new helloWorldCannyProcessPrivate())
{
    d->parent = this;
    d->variance = 50;

    d->input = NULL;
    d->output = NULL;
}

helloWorldCannyProcess::~helloWorldCannyProcess(void)
{
    delete d;
    d = NULL;
}

void helloWorldCannyProcess::emitProgressed(int progression)
{
    emit progressed(progression);
    qDebug() << "canny Progression" << progression;
}

bool helloWorldCannyProcess::registered(void)
{
    //return true;
    return dtkAbstractProcessFactory::instance()->registerProcessType("helloWorldCannyProcess", createhelloWorldCannyProcess);
}

QString helloWorldCannyProcess::description(void) const
{
    return "helloWorldCannyProcess";
}

void helloWorldCannyProcess::setInputData(medAbstractData *data)
{
    if ( !data )
        return;

    d->input = data;
}

void helloWorldCannyProcess::setVariance(unsigned int variance)
{
    d->variance = variance;
}

int helloWorldCannyProcess::update ( void )
{
    if ( !d->input )
    {
        qDebug() << "in update method : d->input is NULL";
        return -1;
    }

    d->callback = itk::CStyleCommand::New();
    d->callback->SetClientData((void*) d);
    d->callback->SetCallback(helloWorldCannyProcessPrivate::eventCallback);

    QString type = QString (d->input->identifier());

    if ( type == "itkDataImageChar3" )
    {
        runCanny<itk::Image<char, 3> >();
    }
    else if ( type == "itkDataImageUChar3" )
    {
       runCanny<itk::Image<unsigned char, 3> >();
    }
    else if ( type == "itkDataImageShort3" )
    {
        runCanny<itk::Image<short, 3> >();
    }
    else if ( type == "itkDataImageUShort3" )
    {
        runCanny<itk::Image<unsigned short, 3> >();
    }
    else if ( type == "itkDataImageInt3" )
    {
        runCanny<itk::Image<int, 3> >();
    }
    else if ( type == "itkDataImageUInt3" )
    {
        runCanny<itk::Image<unsigned int, 3> >();
    }
    else if ( type == "itkDataImageLong3" )
    {
        runCanny<itk::Image<long, 3> >();
    }
    else if ( type == "itkDataImageULong3" )
    {
        runCanny<itk::Image<unsigned long, 3> >();
    }
    else if ( type == "itkDataImageFloat3" )
    {
        runCanny<itk::Image<float, 3> >();
    }
    else if ( type == "itkDataImageDouble3" )
    {
        runCanny<itk::Image<double, 3> >();
    }
    return EXIT_SUCCESS;
}

template <class ImageType> void helloWorldCannyProcess::runCanny()
{
    //compute canny
    typedef itk::Image<float, 3> RealImageType;
    typedef itk::CastImageFilter <ImageType, RealImageType> CastFilter;
    typename CastFilter::Pointer castFilter = CastFilter::New();
    castFilter->SetInput(dynamic_cast<ImageType*>((itk::Object*)(d->input->data())));
    castFilter->Update();

    typedef itk::CannyEdgeDetectionImageFilter <RealImageType, RealImageType> CannyFilter;
    typename CannyFilter::Pointer cannyFilter = CannyFilter::New();
    cannyFilter->SetVariance(d->variance);
    cannyFilter->SetInput(castFilter->GetOutput());
    cannyFilter->AddObserver(itk::ProgressEvent(), d->callback);

    cannyFilter->Update();

    // update output data
    d->output = medAbstractDataFactory::instance()->create("itkDataImageFloat3");
    d->output->setData(cannyFilter->GetOutput());
    emit progressed(100);
}

medAbstractData *helloWorldCannyProcess::output( void )
{
    return ( d->output );
}

dtkAbstractProcess * createhelloWorldCannyProcess ( void )
{
    return new helloWorldCannyProcess;
}

