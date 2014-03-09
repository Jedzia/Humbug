//
#include "stdafx.h"

//
#include "../Components/Canvas.h"
#include "../Components/Image.h"
#include "Filesystem/FileLoader.h"
#include "SDL.h"
#include "TileSet.h"
//#include <stdint.h>
#include <boost/cstdint.hpp>
#include <iostream>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

namespace gui {
CTileSet::CTileSet( const CCanvas * mainCanvas, CTileImage* tileImage, const CCanvas * background, CRectangle screen )
:  m_pMainCanvas(mainCanvas),
m_ctiTileImage(tileImage),
    m_pBackground(background),
    m_crScreen(screen){
   dbgOut(__FUNCTION__);
   // m_pSprImage(sprImage),
}


CTileSet::~CTileSet(void){
    delete m_ctiTileImage;
    m_ctiTileImage = NULL;
    dbgOut(__FUNCTION__);
}

void CTileSet::Draw(const CTile& tile){

    if (m_pBackground) {
        m_pBackground->Lock();
        //CRectangle updrectA = m_pSprImage->GetCanvas()->GetDimension() + m_cpPos;
        //CRectangle updrect = m_pSprImage->GetCanvas()->GetDimension() + m_cpOldPos;

        //CRectangle updrectR = updrect.Intersect(updrectA);
        //CRectangle updrect = m_pMainCanvas->GetDimension().Clip(CRectangle(0,0,1024, 768 - 314));
        // Todo: Use the hud size as parameter.
        //CRectangle updrect = m_pMainCanvas->GetDimension().Offset(CPoint(0,-314));
        //m_pBackground->Blit(updrect, *m_pMainCanvas, updrect);
//        m_pMainCanvas->Blit(updrect, *m_pBackground, updrect);
        //m_pBackground->AddUpdateRect(m_pSprImage->GetCanvas()->GetDimension() + m_cpOldPos);
        //m_pBackground->AddUpdateRect(m_pSprImage->GetCanvas()->GetDimension() + m_cpPos);
        //m_pMainCanvas->Blit(m_pMainCanvas->GetDimension(), m_ctiTileImage, m_ctiTileImage->GetDimension());
        // m_ctiTileImage->Draw(m_pBackground);
        m_pBackground->Unlock();
    }

    //m_pMainCanvas->FillRect(bluerectOld, CColor(0, 0, 0) );
    //CPoint spos( m_cpPos.GetX(), m_cpPos.GetY());
    //SDL_SetAlpha(m_pSprImage->GetCanvas()->GetSurface(), SDL_SRCALPHA , 128);
    //m_pSprImage->Put(m_pMainCanvas, m_cpPos);

    //m_pMainCanvas->AddUpdateRect(m_pSprImage->GetCanvas()->GetDimension() + m_cpOldPos);
    //m_pMainCanvas->AddUpdateRect(m_pSprImage->GetCanvas()->GetDimension() + m_cpPos);
    //m_pMainCanvas->AddUpdateRect(m_pSprImage->DstRect() + m_cpOldPos);
    //m_pMainCanvas->AddUpdateRect(m_pSprImage->DstRect() + m_cpPos);
    //m_cpOldPos = m_cpPos;
} // Draw

CTile CTileSet::CreateTile( int index ) const
{
    return CTile(*m_ctiTileImage ,index);
}

std::ostream& operator<<(std::ostream& o, const CTileSet& r) {
    return o << "CTileSet[ X=" /*<< r.GetX() << ", Y=" << r.GetY()
                                 << ", W=" << r.GetW() << ", H=" << r.GetH()
                                 <<*/" ]";
}


CTileMap::CTileMap( const std::string& mapData )
{
	std::stringstream htstrstr(mapData);

	uint16_t TileCount1, TileWidth1, TileHeight1;
	htstrstr >> TileCount1 >> TileWidth1 >> TileHeight1;

	uint32_t dummy1x, dummy2x, dummy3x, dummy4x, dummy5x;
	htstrstr >> dummy1x;
	htstrstr >> dummy2x;
	htstrstr >> dummy3x;
	htstrstr >> dummy4x;
	htstrstr >> dummy5x;


	std::string TileSetIdentifier1;
	htstrstr >> TileSetIdentifier1;

}

CTileMap::~CTileMap()
{

}

void CTileMap::ReadBinary( char *tilesdata, size_t length )
{
		//char buf[4096];
		/*for (int i = 0; i < finf.Size() ; i++)
		{
			buf[i] = tilesdata[i];
		}*/

		uint16_t data[] = {1234, 5678};
		char* dataPtr = (char*)&data;

		/*typedef boost::iostreams::basic_array_sink<char> ODevice;
		boost::iostreams::stream_buffer<ODevice> obuffer(buf, sizeof(buf));
		boost::archive::binary_oarchive oarchive(obuffer, boost::archive::no_header);

		std::basic_string<char> identifier("TheString");
		oarchive << identifier;*/

		/*char wbuffer[4096];

		boost::iostreams::basic_array_sink<char> sr(wbuffer, sizeof(wbuffer));  
		boost::iostreams::stream< boost::iostreams::basic_array_sink<char> > source(sr);

		boost::archive::binary_oarchive oa(source);
		oa << identifier;*/


		typedef boost::iostreams::basic_array_source<char> Device;
		//boost::iostreams::stream_buffer<Device> buffer(dataPtr, sizeof(data));
		boost::iostreams::stream<Device> buffer(tilesdata, length);
		boost::archive::binary_iarchive archive(buffer, boost::archive::no_header);

		uint16_t TileCount, TileWidth, TileHeight;
		archive >> TileCount >> TileWidth >> TileHeight;
		//std::cout << word1 << "," << word2 << std::endl;
 
		uint16_t dummy1, dummy2, dummy3, dummy4, dummy5;
		archive >> dummy1 >> dummy2 >> dummy3 >> dummy4 >> dummy5;
		//std::string TileSetIdentifier;
		std::basic_string<char> TileSetIdentifier;
		//archive >> TileSetIdentifier;
		//byte byte1[256];
		char byte1[256];
		size_t len =0;
		while (buffer.read((char*)&byte1[len], sizeof(char)) != 0)
		{
			if (byte1[len] == 0)
			{
				break;
			}

			len++;
			if (len > sizeof(byte1))
			{
				break;
			}
		}


		//std::basic_string<uint8_t> bla(byte1);
		std::string bla(byte1);

}

}