#ifndef Template_H
#define Template_H
#include "GUI/Components/Screen.h"
#include "boost/smart_ptr/scoped_ptr.hpp"

class FileLoader;
class CCanvas;
class CText;
class CTextScroller;
class CSprite;
class CSpriteManager;

class Template : public Screen {
public:

    Template(FileLoader& loader, CCanvas *background);
    ~Template();

    virtual bool OnInit( int argc,char* argv[] );
    virtual void OnIdle(int frameNumber);

    virtual void OnDraw();

    virtual void OnUpdate();

private:
    struct TemplateImpl;
    boost::scoped_ptr<TemplateImpl> pimpl_;

    FileLoader& m_Loader;
	Uint8 x;
    CColor mcol;
    TTF_Font *m_pArialfont;
    boost::shared_ptr<CCanvas> m_pBackground;
    boost::scoped_ptr<CText> m_pScrollText;
    boost::scoped_ptr<CTextScroller> m_pScroller;
    boost::scoped_ptr<CSpriteManager> m_pSprMgr;
};

#endif // Template_H
