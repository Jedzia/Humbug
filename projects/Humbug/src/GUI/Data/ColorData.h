#ifndef COLORDATA_H
#define COLORDATA_H

#include "SDL.h"
#include "boost/smart_ptr/scoped_ptr.hpp"
#include "boost/pool/detail/singleton.hpp"

class ColorData {
public:

    static ColorData* Instance();

    /*static*/ SDL_Color* Wavemap();
    ColorData();
    ~ColorData();

protected:

private:
     //static ColorData* m_Instance;
     //static boost::scoped_ptr<ColorData> inst;
    struct ColorDataImpl;
    boost::scoped_ptr<ColorDataImpl> pimpl_;
    //static SDL_Color wavemap[]; 
};

/*class Global
{
public:
protected:
private:
    //static boost::details::pool::singleton_default<ColorData> m_colorData;
};*/

#endif // COLORDATA_H
