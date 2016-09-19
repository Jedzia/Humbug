#include "stdafx.h"
#include "ColorData.h"

//#include <build/cmake/include/debug.h>

namespace gui {

//ColorData* ColorData::m_Instance = NULL;

struct ColorData::ColorDataImpl {

    static SDL_Color wavemap[]; 
    static SDL_Color* Wavemap() { return wavemap; }
};

SDL_Color ColorData::ColorDataImpl::wavemap[] = {
    {0,2,103}, {0,7,110}, {0,13,117}, {0,19,125},
    {0,25,133}, {0,31,141}, {0,37,150}, {0,43,158},
    {0,49,166}, {0,55,174}, {0,61,182}, {0,67,190},
    {0,73,198}, {0,79,206}, {0,86,214}, {0,96,220},
    {5,105,224}, {12,112,226}, {19,120,227}, {26,128,229},
    {33,135,230}, {40,143,232}, {47,150,234}, {54,158,236},
    {61,165,238}, {68,173,239}, {75,180,241}, {82,188,242},
    {89,195,244}, {96,203,246}, {103,210,248}, {112,218,250},
    {124,224,250}, {135,226,251}, {146,229,251}, {156,231,252},
    {167,233,252}, {178,236,252}, {189,238,252}, {200,240,252},
    {211,242,252}, {222,244,252}, {233,247,252}, {242,249,252},
    {237,250,252}, {209,251,252}, {174,251,252}, {138,252,252},
    {102,251,252}, {63,250,252}, {24,243,252}, {7,225,252},
    {4,203,252}, {3,181,252}, {2,158,252}, {1,136,251},
    {0,111,248}, {0,82,234}, {0,63,213}, {0,50,192},
    {0,39,172}, {0,28,152}, {0,17,132}, {0,7,114}
};

ColorData::ColorData()
: pimpl_(new ColorData::ColorDataImpl)
{
         //dbgOut(__FUNCTION__ << std::endl);
         //std::cout << "Bla" << std::endl;
}

ColorData::~ColorData(void)
{
         //dbgOut(__FUNCTION__ << std::endl);
    //ColorData a;
}

ColorData* ColorData::Instance()
{
    // Since it's a static variable, if the class has already been created,
    // It won't be created again.
    static ColorData myInstance;

    // Return a pointer to our mutex instance.
    return &myInstance;

    /*if (!m_Instance)
    {
        m_Instance = new ColorData;
        //inst.reset(new ColorData());
    }
    return m_Instance;*/
    //return inst.get();
}

SDL_Color* ColorData::Wavemap()
{
    return pimpl_->Wavemap();
    /*SDL_Color wavemap[] = {
        {0,2,103}, {0,7,110}, {0,13,117}, {0,19,125},
        {0,25,133}, {0,31,141}, {0,37,150}, {0,43,158},
        {0,49,166}, {0,55,174}, {0,61,182}, {0,67,190},
        {0,73,198}, {0,79,206}, {0,86,214}, {0,96,220},
        {5,105,224}, {12,112,226}, {19,120,227}, {26,128,229},
        {33,135,230}, {40,143,232}, {47,150,234}, {54,158,236},
        {61,165,238}, {68,173,239}, {75,180,241}, {82,188,242},
        {89,195,244}, {96,203,246}, {103,210,248}, {112,218,250},
        {124,224,250}, {135,226,251}, {146,229,251}, {156,231,252},
        {167,233,252}, {178,236,252}, {189,238,252}, {200,240,252},
        {211,242,252}, {222,244,252}, {233,247,252}, {242,249,252},
        {237,250,252}, {209,251,252}, {174,251,252}, {138,252,252},
        {102,251,252}, {63,250,252}, {24,243,252}, {7,225,252},
        {4,203,252}, {3,181,252}, {2,158,252}, {1,136,251},
        {0,111,248}, {0,82,234}, {0,63,213}, {0,50,192},
        {0,39,172}, {0,28,152}, {0,17,132}, {0,7,114}
    };
    return wavemap;*/
}


//boost::scoped_ptr<ColorData> ColorData::inst;

//ColorData ColorData::GlColorData;


//boost::details::pool::singleton_default<ColorData> Global::m_colorData;

}
