#include "../stdafx.h"
#include "Filesystem/FileLoader.h"
#include "GUI/Components/Image.h"
#include "Hud.h"

//#include <build/cmake/include/debug.h>
/*Hud::Hud(const FileLoader& loader, CCanvas* pCanvas) :
    CControl(pCanvas),
    m_pLoader(loader) //, m_pCanvas(pCanvas)
        {
    dbgOut(__FUNCTION__ << std::endl);

        Init();
   }*/
HudBackground::HudBackground(const FileLoader& loader, std::string filename) :
    m_pFooter(NULL){
    dbgOut(__FUNCTION__ << std::endl);
    m_pFooter = new CCanvas( loader.LoadImg( filename.c_str() ) );
}

HudBackground::~HudBackground(void){
    dbgOut(__FUNCTION__ << std::endl);
    delete m_pFooter;
}

CCanvas * HudBackground::GetCanvas() {
    return m_pFooter;
}

Hud::Hud(const FileLoader& loader, CControl* pParent, HudBackground* bkg, Uint32 id) :
    CControl(pParent, bkg->GetCanvas()->GetDimension(), id),
    m_pLoader(loader),
    m_pBackground(bkg){
    dbgOut(__FUNCTION__ << std::endl);

    //Init(pParent);
    //FileLoader fl("D:/E/Projects/C++/Humbug/build/Humbug/src/Debug/base_data");
    //footer = new CCanvas( m_pLoader.LoadImg("footer.png") );
    CCanvas* footer = bkg->GetCanvas();
    std::cout << "The rect: |" << footer->GetDimension() << "|ends" << std::endl;
    footerImage = new CImage( footer );
    CPoint dst( 0, pParent->GetCanvas()->GetHeight( ) - footer->GetHeight( ) );
    CControl::SetPosition(dst);
    oldstate = !HasMouseHover();
    // BringToFront();
    //SetMouseHover(this);
        footerImage->Put( GetCanvas(), CPoint(0, 0) );
        CControl::GetMainControl()->GetCanvas()->AddUpdateRect(CRectangle(0,0,1024,768));
        Invalidate();
}

Hud::~Hud(void){
    delete footerImage;
    delete m_pBackground;
    dbgOut(__FUNCTION__ << std::endl);
}

void Hud::Init(CControl* pParent){}

CRectangle Hud::InitRect(const FileLoader& loader){
    /*footer = new CCanvas( m_pLoader.LoadImg("footer.png") );
       std::cout << "The rect: |" << footer->GetDimension() << "|ends" << std::endl;
       //CControl::set
       footerImage = new CImage( footer );
       dst = CPoint( 0, GetCanvas()->GetHeight( ) - footer->GetHeight( ) );*/
    return CRectangle(0, 0, 1024, 354);
}

void Hud::OnDraw(){
    /*FileLoader fl("D:/E/Projects/C++/Humbug/build/Humbug/src/Debug/base_data");

       CCanvas footer( fl.LoadImg("footer.png") );
       std::cout << "The rect: |" << footer.GetDimension() << "|ends" << std::endl;
       CImage footerImage( &footer ) ;*/

    //footerImage->Put( GetCanvas(), dst );
    /*if( HasMouseHover() &&  oldstate == false) {
        //clear to light gray
        GetCanvas()->FillRect( CRectangle( 0, 0, GetWidth(), GetHeight() ), CColor(155, 255, 155) );
        CControl::GetMainControl()->GetCanvas()->AddUpdateRect(CRectangle(0,0,1024,768));
        m_ptIsDirty = true;
    }
    else if(!HasMouseHover() &&  oldstate == true) {
        footerImage->Put( GetCanvas(), CPoint(0, 0) );
        //GetParent()->Update();
        CControl::GetMainControl()->GetCanvas()->AddUpdateRect(CRectangle(0,0,1024,768));
        m_ptIsDirty = true;
    }*/
    static bool xset = false;
    if(!xset) {
        xset = true;
    }


    oldstate = HasMouseHover();
    CControl::OnDraw();
}

bool Hud::OnMouseMove(Uint16 x, Uint16 y, Sint16 relx, Sint16 rely, bool bLeft, bool bRight,
        bool bMiddle){
    bool res = CControl::OnMouseMove( x, y, relx, rely, bLeft, bRight, bMiddle);

    //if(GetMouseHover()==NULL) SetMouseHover(this);
    /*if(HasMouseHover())
        {
                //clear to light gray
                GetCanvas()->FillRect(CRectangle(0,0,GetWidth(),GetHeight()),CColor(155,255,155));
       }*/
    return res;
}

