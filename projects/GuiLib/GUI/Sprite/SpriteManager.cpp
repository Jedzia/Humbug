//
#include "stdafx.h"

//
#include "SpriteManager.h"
#include "boost/smart_ptr/weak_ptr.hpp"
#include <boost/foreach.hpp>
//
//#include <build/cmake/include/debug.h>

namespace gui {
using namespace components;
typedef boost::shared_ptr<CSprite> SpriteShrp;
/** @class CSpriteHook:
 *  Detailed description.
 *  @param framenumber TODO
 *  @param mdata TODO
 */
class CSpriteHook {
    //CSprite *m_pSprite;
    SpriteShrp m_pSprite;
    const CSpriteManager::CSpriteModifierFunc m_fncUpdate;

public:

    CSpriteHook(CSprite* sprite, const CSpriteManager::CSpriteModifierFunc updfunc = NULL) :
        m_pSprite(sprite),
        m_fncUpdate(updfunc) {
        dbgOut(__FUNCTION__ << " " << this);

        //m_pSprite.reset(sprite);
    }

    ~CSpriteHook() {
        dbgOut(__FUNCTION__ << " " << this);
    }

    void DoIdle(int framenumber, CSpriteModifierData& mdata) const {
        if(m_fncUpdate != NULL) {
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

/** @class SpriteCallData:
*  This branch of action stores the position outside the Sprite and restores it later. 
*  Makes it possible to render one sprite multiple times at different positions.
*/
struct SpriteCallData{
    CPoint pos;
    CSpriteManager::CSpriteModifierFunc updfunc;
    //CSpriteModifierData mdata;
};

typedef std::vector<SpriteCallData> SprDataStorage;

struct SpriteLinkData {
    int id = -1;
    CSprite* sprite;
    SprDataStorage callData;
};

typedef std::map<int, SpriteLinkData> SprLinkStorage;

struct CSpriteManager::CSpriteManagerImpl {
private:

    int currentId;
    CSpriteManager* host;

public:

    SprLinkStorage m_vSpriteData;

    //boost::shared_ptr<hspriv::LaserMover> updfunc2;
    //boost::shared_ptr<hspriv::SaucerMover> updfunc3;
    // boost::shared_ptr<PlayerShip> m_pPlayerShip;

    explicit CSpriteManagerImpl(CSpriteManager* host)
        : currentId(0), host{host}
    {}

    void Draw() const {
        //auto aaaa = host->m_pBackground->GetDimension();
    }

    int NewId() {
        return currentId++;
    }

    int AddSpriteData(CSprite* sprite) {
        int id = NewId();

        SpriteLinkData data;
        data.id = id;
        data.sprite = sprite;
        //data.callData = NULL;
        m_vSpriteData.insert(std::make_pair(id, data));
        return id;
    }
};

CSpriteManager::CSpriteManager(/*SDL_Surface* screen*/)
    : pimpl_(new CSpriteManagerImpl(this)) {
    dbgOut(__FUNCTION__);
}

CSpriteManager::~CSpriteManager(void) {
    dbgOut(__FUNCTION__);
}

int CSpriteManager::AddSprite(CSprite* sprite, const CSpriteModifierFunc& updfunc) {
    int id = pimpl_->AddSpriteData(sprite);
    m_pvSprites.push_back(new CSpriteHook(sprite, updfunc));
    return id;
}

void CSpriteManager::OnDraw() {
    SprStorage::iterator end = m_pvSprites.end();

    for(SprStorage::iterator it = m_pvSprites.begin(); it < end; ++it)
    {
        SpriteShrp sprite = it->Sprite();
        sprite->Draw();
    }
}

void CSpriteManager::OnIdle(int ticks) {
    std::vector<SprStorage::iterator> removeList;
    SprStorage::iterator end = m_pvSprites.end();

    for(SprStorage::iterator it = m_pvSprites.begin(); it < end; ++it)
    {
        //SpriteShrp sprite = it->Sprite();
        //dbgOut(__FUNCTION__ << " " << &it);
        static CRectangle srcRect, dstRect;
        CSpriteModifierData mdata(&srcRect, &dstRect);
        (*it).DoIdle(ticks, mdata);
        // fill deletion list
        if(mdata.markedForDeletion) {
            SprStorage::iterator it2 = it;
            //removeList.push_back(it2);
            removeList.insert(removeList.begin(), it2);
        }

        /*if (mdata.isHandled) {
           // do something
           }*/
    }

    BOOST_FOREACH(SprLinkStorage::value_type & v, pimpl_->m_vSpriteData)
    {
        auto pos = v.second.sprite->GetPosition();
    }

    // delete marked sprites
    BOOST_FOREACH(SprStorage::iterator itpos, removeList)
    {
        m_pvSprites.erase(itpos);
        //break;
    }

} // CSpriteManager::OnIdle

void CSpriteManager::Render() {
    SprStorage::iterator end = m_pvSprites.end();

    for(SprStorage::iterator it = m_pvSprites.begin(); it < end; ++it)
    {
        SpriteShrp sprite = it->Sprite();
        sprite->Render();
    }
}

std::ostream& operator<<(std::ostream& o, const CSpriteManager& r) {
    return o << "CSpriteManager[ X="   /*<< r.GetX() << ", Y=" << r.GetY()
                                          << ", W=" << r.GetW() << ", H=" << r.GetH()
                                          <<*/
           " ]";
}
}
