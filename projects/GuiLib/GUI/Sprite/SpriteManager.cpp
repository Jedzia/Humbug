//
#include "stdafx.h"

//
#include "SpriteManager.h"
#include "boost/smart_ptr/weak_ptr.hpp"
#include <boost/foreach.hpp>

namespace gui {
//#include <build/cmake/include/debug.h>
  typedef boost::shared_ptr<CSprite> SpriteShrp;
  class CSpriteHook {
      //CSprite *m_pSprite;
      SpriteShrp m_pSprite;
      const CSpriteManager::CSpriteModifierFunc m_fncUpdate;

public:

    CSpriteHook(CSprite* sprite, const CSpriteManager::CSpriteModifierFunc updfunc = NULL) :
          m_pSprite(sprite),
          m_fncUpdate(updfunc){
          dbgOut(__FUNCTION__ << " " << this);

          //m_pSprite.reset(sprite);
      }
      ~CSpriteHook(){
          dbgOut(__FUNCTION__ << " " << this);
      }
      void DoIdle(int framenumber, CSpriteModifierData& mdata) const
      {
          if (m_fncUpdate != NULL) {
              //boost::weak_ptr<CSprite> wspr( m_pSprite );
              //if (!wspr.expired())
              //{
              m_fncUpdate(m_pSprite.get(), framenumber, mdata);
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

  void CSpriteManager::AddSprite(CSprite* sprite, const CSpriteModifierFunc& updfunc){
      m_pvSprites.push_back( new CSpriteHook( sprite, updfunc) );

      //m_pvSprites.push_back(new CSpriteHook( sprite));
  }

  void CSpriteManager::OnDraw(){
      SprStorage::iterator end = m_pvSprites.end();
      for (SprStorage::iterator it = m_pvSprites.begin(); it < end; ++it)
      {
          SpriteShrp sprite = it->Sprite();
          sprite->Draw();
      }
  }

  void CSpriteManager::OnIdle( int ticks ){


      std::vector<SprStorage::iterator> removeList;
      SprStorage::iterator end = m_pvSprites.end();
      for (SprStorage::iterator it = m_pvSprites.begin(); it < end; ++it)
      {
          //SpriteShrp sprite = it->Sprite();
          //dbgOut(__FUNCTION__ << " " << &it);
          static CRectangle srcRect, dstRect;
          CSpriteModifierData mdata(&srcRect, &dstRect);
          (*it).DoIdle(ticks, mdata);
          // fill deletion list
          if (mdata.markedForDeletion) {
              SprStorage::iterator it2 = it;
              removeList.push_back(it2);
          }
          /*if (mdata.isHandled) {
          // do something
          }*/
      }
      // delete marked sprites
      BOOST_FOREACH(SprStorage::iterator itpos, removeList)
      {
          m_pvSprites.erase(itpos);
      }

  }

    void CSpriteManager::Render()
    {
        SprStorage::iterator end = m_pvSprites.end();
        for (SprStorage::iterator it = m_pvSprites.begin(); it < end; ++it)
        {
            SpriteShrp sprite = it->Sprite();
            sprite->Render();
        }
    }

    std::ostream& operator<<(std::ostream& o, const CSpriteManager& r) {
      return o << "CSpriteManager[ X=" /*<< r.GetX() << ", Y=" << r.GetY()
                                          << ", W=" << r.GetW() << ", H=" << r.GetH()
                                          <<*/" ]";
  }
}
