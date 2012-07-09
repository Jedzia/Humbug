#include "../stdafx.h"
#include "Hud.h"
#include "Filesystem/FileLoader.h"
#include "GUI/Components/Image.h"

//#include <build/cmake/include/debug.h>


Hud::Hud(const FileLoader& loader, CCanvas* pCanvas)
: m_pLoader(loader), m_pCanvas(pCanvas)
{
         dbgOut(__FUNCTION__ << std::endl);
		 
	//FileLoader fl("D:/E/Projects/C++/Humbug/build/Humbug/src/Debug/base_data");

    footer = new CCanvas( m_pLoader.LoadImg("footer.png") );
	std::cout << "The rect: |" << footer->GetDimension() << "|ends" << std::endl;
	footerImage = new CImage( footer ) ;
	dst = CPoint(0, m_pCanvas->GetHeight( ) - footer->GetHeight( ));
}

Hud::~Hud(void)
{
         dbgOut(__FUNCTION__ << std::endl);
		 delete footerImage;
		 delete footer;
}

void Hud::Draw() 
{
	/*FileLoader fl("D:/E/Projects/C++/Humbug/build/Humbug/src/Debug/base_data");

    CCanvas footer( fl.LoadImg("footer.png") );
	std::cout << "The rect: |" << footer.GetDimension() << "|ends" << std::endl;
	CImage footerImage( &footer ) ;*/
	footerImage->Put( m_pCanvas , dst ) ;

}

