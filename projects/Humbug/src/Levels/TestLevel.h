#ifndef HUMBUG_LEVELS_TESTLEVEL_H
#define HUMBUG_LEVELS_TESTLEVEL_H
#include "../GUI/Components/Screen.h"
#include <boost/smart_ptr/scoped_ptr.hpp>

namespace gui { namespace components {
	class CCanvas;
	class CText;
	class CTextScroller;
}}
namespace gui {
	class CSprite;
}
class FileLoader;
class CSpriteManager;

class TestLevel : public gui::components::Screen {
public:

    TestLevel(FileLoader& loader, gui::components::CCanvas *background);
    ~TestLevel();

    virtual bool OnInit( int argc,char* argv[] );
    virtual void OnIdle(int frameNumber);

    virtual void OnDraw();

    virtual void OnUpdate();

private:
    struct TestLevelImpl;
    boost::scoped_ptr<TestLevelImpl> pimpl_;

    FileLoader& m_Loader;
	Uint8 x;
    gui::components::CColor mcol;
    TTF_Font *m_pArialfont;
    boost::shared_ptr<gui::components::CCanvas> m_pBackground;
    boost::scoped_ptr<gui::components::CText> m_pScrollText;
    boost::scoped_ptr<gui::components::CTextScroller> m_pScroller;
    boost::scoped_ptr<CSpriteManager> m_pSprMgr;
	gui::CSprite *m_pSprite;
};

#endif // HUMBUG_LEVELS_TESTLEVEL_H
