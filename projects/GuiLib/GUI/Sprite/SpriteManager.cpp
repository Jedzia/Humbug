//
#include "stdafx.h"

//
#include "SpriteManager.h"
#include "boost/smart_ptr/weak_ptr.hpp"
namespace gui {
//#include <build/cmake/include/debug.h>
  typedef boost::shared_ptr<CSprite> SpriteShrp;
  class CSpriteHook {
      //CSprite *m_pSprite;
      SpriteShrp m_pSprite;
      const boost::function<void(CSprite *, int)> m_fncUpdate;

public:

      CSpriteHook( CSprite* sprite, const boost::function<void(CSprite *, int)> updfunc = NULL ) :
          m_pSprite(sprite),
          m_fncUpdate(updfunc){
          dbgOut(__FUNCTION__ << " " << this);

          //m_pSprite.reset(sprite);
      }
      ~CSpriteHook(){
          dbgOut(__FUNCTION__ << " " << this);
      }
      void DoIdle(int framenumber){
          if (m_fncUpdate != NULL) {
              //boost::weak_ptr<CSprite> wspr( m_pSprite );
              //if (!wspr.expired())
              //{
              m_fncUpdate(m_pSprite.get(), framenumber);

              //}
          }
      }
      //CSprite * Sprite() const { return m_pSprite; }
      SpriteShrp Sprite() const { return m_pSprite; }
  };

  CSpriteManager::CSpriteManager(/*SDL_Surface* screen*/){
      dbgOut(__FUNCTION__);
  }

  CSpriteManager::~CSpriteManager(void){
      dbgOut(__FUNCTION__);
  }

  void CSpriteManager::AddSprite(CSprite* sprite, const boost::function<void(CSprite *,
                                                                             int)>& updfunc){
      m_pvSprites.push_back( new CSpriteHook( sprite, updfunc) );

      //m_pvSprites.push_back(new CSpriteHook( sprite));
  }

  void CSpriteManager::OnDraw(){
      SprStorage::iterator end = m_pvSprites.end();
      for (SprStorage::iterator it = m_pvSprites.begin(); it < end; it++)
      {
          SpriteShrp sprite = it->Sprite();
          sprite->Draw();
      }
  }

  void CSpriteManager::OnIdle( int frameNumber ){
      SprStorage::iterator end = m_pvSprites.end();
      for (SprStorage::iterator it = m_pvSprites.begin(); it < end; it++)
      {
          //SpriteShrp sprite = it->Sprite();
          //dbgOut(__FUNCTION__ << " " << &it);
          (*it).DoIdle(frameNumber);
      }
  }

  std::ostream& operator<<(std::ostream& o, const CSpriteManager& r) {
      return o << "CSpriteManager[ X=" /*<< r.GetX() << ", Y=" << r.GetY()
                                          << ", W=" << r.GetW() << ", H=" << r.GetH()
                                          <<*/" ]";
  }
}
