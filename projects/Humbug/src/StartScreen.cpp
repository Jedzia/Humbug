#include "stdafx.h"
#include "StartScreen.h"
#include "GUI/Visual/EventHandler.h"
//#include <build/cmake/include/debug.h>
#include "GUI/Components/Rectangle.h"
#include "GUI/Components/Text.h"
#include "GUI/Components/TextScroller.h"
#include "Filesystem/FileLoader.h"
#include <cstdlib>
#include "SDL_ttf.h"


StartScreen::StartScreen( FileLoader& loader, CCanvas *background)
: Screen(background), m_Loader(loader), m_pArialfont(NULL), m_iUpdateTimes(0), m_pScrollText(NULL), m_pScroller(NULL)
{
    dbgOut(__FUNCTION__ << " " << this << std::endl);
}

StartScreen::~StartScreen(void)
{
    if (m_pArialfont)
    {
        TTF_CloseFont(m_pArialfont);
    }
    delete m_pScrollText;
    delete m_pScroller;
    delete m_pBackground;
    dbgOut(__FUNCTION__ << " " << this << std::endl);
}

const char* StartScreen::language(int x) const
{
    return "AsciiDoc";
}

/*GroupId StartScreen::GetGroupID()
{
    static GroupId grpID = CreateNextGroupID();
    return grpID;
    //throw std::exception("The method or operation is not implemented.");
}*/

bool StartScreen::OnInit( int argc,char* argv[] )
{
   // Master()->GetMainCanvas();
    CMainCanvas* m_pMainCanvas = Master()->GetMainCanvas();
    //m_pBackground = CCanvas::CreateRGBCompatible(NULL, 1024, 768 - 320);
    //m_pBackground = CCanvas::CreateRGBCompatible(NULL, NULL, NULL);

    m_pArialfont = TTF_OpenFont("D:/E/Projects/C++/Humbug/build/Humbug/src/Debug/arial.ttf", 30);

    mcol = CColor::White();

    SDL_Surface* tmpfsurf = SDL_DisplayFormatAlpha( m_Loader.LoadImg("Intro/Intro.png") );
    //SDL_SetColorKey(tmpfsurf, SDL_SRCCOLORKEY, 0xff00ff);
    //SDL_SetColorKey(m_pMainCanvas->GetSurface(), SDL_SRCCOLORKEY, 0xff00ff);
    //SDL_SetAlpha(tmpfsurf, SDL_SRCALPHA, 0);
    //SDL_SetAlpha(m_pMainCanvas->GetSurface(), SDL_SRCALPHA, 128);
    m_pBackground = new CCanvas( tmpfsurf );
    //CCanvas tmpCanvas( tmpfsurf );
    m_Loader.FreeLast();
    //m_pMainCanvas->Blit(m_pMainCanvas->GetDimension(), tmpCanvas, tmpCanvas.GetDimension());
    //m_pBackground->Blit(m_pBackground->GetDimension(), tmpCanvas, tmpCanvas.GetDimension());
    m_pMainCanvas->AddUpdateRect(m_pBackground->GetDimension());
    //"\r\n"

    CColor m_colText = CColor::White();
    std::ostringstream outstring;
    outstring << "Bla fasel:" << CApplication::ShownFrames();
    outstring << " ";
    //std::string pstr;
    outstring << "Error error C2248: 'boost::noncopyable_::noncopyable::noncopyable' : cannot access private member " <<
        "declared in class " <<
        "'boost::noncopyable_::noncopyable'" << "\t" << "d:/e/projects/c++/humbug/projects/humbug/src/gui/visual/Hookable.h" <<
        "\t" << "48" << "\t" << "Humbug" << "\r\n" <<
        "\r\n" <<
        "Error" << "\t" << "3" << "\t" << "error C2248: 'boost::scoped_ptr<T>::scoped_ptr' : cannot access private member declared in " <<
        "class " <<
        "'boost::scoped_ptr<T>'" << "\t" <<
        "d:/e/projects/c++/humbug/projects/humbug/src/gui/visual/Hookable.h" << "\t" << "48" << "\t" << "Humbug" << "\r\n" <<
        "";
    //m_pScrollText.reset(new CCanvas(TTF_RenderText_Solid(m_pArialfont, outstring.str().c_str(), m_colText)));
    //m_pScrollText = new CCanvas(TTF_RenderText_Solid(m_pArialfont, outstring.str().c_str(), m_colText));
    m_pScrollText = new CText(m_pArialfont, outstring.str(), m_colText);
    m_pScroller = new CTextScroller(m_pMainCanvas, *m_pScrollText, CPoint(50, 100), 400);
    //int *test = new int(5);
    return Screen::OnInit(argc, argv);
    //return true;
}

void StartScreen::OnIdle()
{
    //x+= std::random()*5;
}

void StartScreen::OnDraw()
{
    static std::string subtext("A");
    CMainCanvas* m_pMainCanvas = Master()->GetMainCanvas();
    m_pMainCanvas->Lock();
    m_pMainCanvas->Blit(m_pMainCanvas->GetDimension(), *m_pBackground, m_pBackground->GetDimension() );

    CRectangle frect(400, 300, 85, 85);
    m_pMainCanvas->FillRect( frect, mcol );
    m_pMainCanvas->AddUpdateRect(frect);
    //mcol.SetR(x);
    //mcol.SetG(x/2);
    //mcol.SetB(x);
    //CCanvas* background = CCanvas::CreateRGBCompatible(NULL, 1024 * 5, 768 - 320);
    int textwidth = 800;
    int textheigth = m_pScrollText->GetCanvas()->GetHeight();
    int textposX = 100;
    int textposY = 600;
    //int fontheigth = TTF_FontHeight(m_pArialfont);

    static int xdelta = 0;
    static int xdelta1 = 0;
    CColor m_colText = CColor::White();
    CColor m_colText2 = CColor::LightYellow();
    CColor m_colTextBg = CColor::Green();

    int xx = xdelta1 % 0xff;
    Uint32 col = 0x0000ff * xx +0x00ff00 * xx + 0xff0000 * xx; 
    double msin = sin(((double)xdelta1-600)/50)+ 0.5;

    CColor fgtext(255,255,255);
    //SDL_se
    //SDL_SetColorKey(m_pcnvText.GetSurface(), SDL_SRCCOLORKEY, col);
    //SDL_SetColorKey(m_pcnvText.GetSurface(), SDL_SRCCOLORKEY, 0x7F007F );
    //SDL_SetAlpha(m_pcnvText.GetSurface(), SDL_SRCALPHA, 0x3F- xdelta);
    //SDL_SetAlpha(m_pcnvText.GetSurface(), SDL_SRCALPHA, 0xfF * msin);

    //CRectangle textDims(m_pScrollText->GetDimension());
    CRectangle textDims(xdelta1-xdelta,0, xdelta,textheigth);
    
    CRectangle showline(0,textposY,1024,textheigth);
    CRectangle dstRect( textposX,textposY, textwidth ,textheigth);
    CRectangle dstDims( textposX + textwidth - xdelta,textposY, xdelta,textheigth);

    //textDims.SetW(500);
    //m_pMainCanvas->Blit(m_pMainCanvas->GetDimension(), m_pcnvText, m_pcnvText.GetDimension());
    CPoint fpstextloc(150+xdelta1,600);
    static CRectangle oldtextloc(dstDims);

    m_pScrollText->Put(m_pMainCanvas,dstDims, textDims );
    //m_pMainCanvas->Blit(dstDims , *m_pScrollText, textDims );
    //m_pMainCanvas->AddUpdateRect(textDims + CRectangle(0,0,0,0) + oldfpstextloc);
    //m_pMainCanvas->AddUpdateRect(textDims + CRectangle(0,0,0,0) + fpstextloc);
    textDims.SetW(500);

    //CRectangle updaRect(dstDims);
    //updaRect.SetW(m_pMainCanvas->GetWidth());
    m_pMainCanvas->AddUpdateRect(dstDims);
    //m_pMainCanvas->AddUpdateRect(showline);

    xdelta1 +=4;
    if (xdelta1 >= m_pScrollText->GetCanvas()->GetWidth())
    {
        xdelta1 = 0;
    }
    xdelta =xdelta1;
    if (xdelta > textwidth)
    {
        //xdelta1 +=2;
        xdelta = textwidth;
    }
    if (xdelta % 6 == 0)
    {
        //subtext += "B";
    }
    oldtextloc = dstDims;
    m_iUpdateTimes = 0;


    m_pScroller->Scroll(6);
    m_pScroller->Draw();


    m_pMainCanvas->Unlock();
}

void StartScreen::OnDrawOld()
{
    static std::string subtext("A");
    CMainCanvas* m_pMainCanvas = Master()->GetMainCanvas();
    m_pMainCanvas->Lock();
    m_pMainCanvas->Blit(m_pMainCanvas->GetDimension(), *m_pBackground, m_pBackground->GetDimension() );

    CRectangle frect(400, 300, 85, 85);
    m_pMainCanvas->FillRect( frect, mcol );
    m_pMainCanvas->AddUpdateRect(frect);
    //mcol.SetR(x);
    //mcol.SetG(x/2);
    //mcol.SetB(x);
    //CCanvas* background = CCanvas::CreateRGBCompatible(NULL, 1024 * 5, 768 - 320);
    int textwidth = 600;

    static int xdelta = textwidth;
    static int xdelta1 = textwidth;
    std::string m_sCaption("Older depp");
    std::ostringstream outstring;
    outstring << "Bla fasel:" << CApplication::ShownFrames();
    outstring << " ";
    outstring << subtext;
    CColor m_colText = CColor::White();
    CColor m_colText2 = CColor::LightYellow();
    CColor m_colTextBg = CColor::Green();

    int xx = xdelta1 % 0xff;
    Uint32 col = 0x0000ff * xx +0x00ff00 * xx + 0xff0000 * xx; 
    double msin = sin(((double)xdelta1-600)/50)+ 0.5;

    CColor fgtext(255,255,255);
    //CCanvas m_pcnvText(TTF_RenderText_Blended(m_pArialfont, outstring.str().c_str(), m_colText));
    //CCanvas m_pcnvText(TTF_RenderText_Blended(m_pArialfont, outstring.str().c_str(), m_colText));
    CCanvas m_pcnvText(TTF_RenderText_Solid(m_pArialfont, outstring.str().c_str(), m_colText));
    //SDL_se
    //SDL_SetColorKey(m_pcnvText.GetSurface(), SDL_SRCCOLORKEY, col);
    //SDL_SetColorKey(m_pcnvText.GetSurface(), SDL_SRCCOLORKEY, 0x7F007F );
    //SDL_SetAlpha(m_pcnvText.GetSurface(), SDL_SRCALPHA, 0x3F- xdelta);
    SDL_SetAlpha(m_pcnvText.GetSurface(), SDL_SRCALPHA, 0xfF * msin);

    //m_pMainCanvas->Blit(m_pMainCanvas->GetDimension(), m_pcnvText, m_pcnvText.GetDimension());
    CPoint fpstextloc(150+xdelta,600);
    static CPoint oldfpstextloc(fpstextloc);
    m_pMainCanvas->Blit(m_pcnvText.GetDimension()+ fpstextloc, m_pcnvText, m_pcnvText.GetDimension() );
    m_pMainCanvas->AddUpdateRect(m_pcnvText.GetDimension() + CRectangle(0,0,0,0) + oldfpstextloc);
    m_pMainCanvas->AddUpdateRect(m_pcnvText.GetDimension() + CRectangle(0,0,0,0) + fpstextloc);

    CPoint updtextloc(150+xdelta1,650);
    static CPoint oldupdtextloc(updtextloc);
    outstring.str("");
    outstring << "Updates:" << m_iUpdateTimes;
    CCanvas m_pcnvText2(TTF_RenderText_Blended(m_pArialfont, outstring.str().c_str(), m_colText2));
    //m_pMainCanvas->Blit(m_pMainCanvas->GetDimension(), m_pcnvText, m_pcnvText.GetDimension());
    m_pMainCanvas->Blit(m_pcnvText2.GetDimension()+ updtextloc, m_pcnvText2, m_pcnvText2.GetDimension() );
    m_pMainCanvas->AddUpdateRect(m_pcnvText2.GetDimension() + oldupdtextloc);
    m_pMainCanvas->AddUpdateRect(m_pcnvText2.GetDimension() + updtextloc);

    xdelta -=5;
    if (xdelta < 0)
    {
        xdelta = textwidth;
        subtext = "";
    }
    xdelta1 -=2;
    if (xdelta1 < 0)
    {
        xdelta1 = textwidth;
    }
    if (xdelta % 6 == 0)
    {
        subtext += "B";
    }
    oldfpstextloc = fpstextloc;
    oldupdtextloc=updtextloc;
    m_iUpdateTimes = 0;
    m_pMainCanvas->Unlock();
}

void StartScreen::OnUpdate()
{
    Screen::OnUpdate();
    x += 1 + (rand() << 21);
    mcol.SetR(rand());
    mcol.SetG(rand());
    mcol.SetB(rand());
    m_iUpdateTimes++;
}

