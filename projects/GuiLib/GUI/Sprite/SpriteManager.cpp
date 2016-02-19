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
//typedef boost::shared_ptr<CSprite> SpriteShrp;
/*class CSpriteHook {
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
};*/

/** @class SpriteCallData:
*  This branch of action stores the position outside the Sprite and restores it later. 
*  Makes it possible to render one sprite multiple times at different positions.
*/
struct SpriteCallData{
    CPoint pos;
    int offset;
    CSpriteManager::CSpriteModifierFunc updfunc;
    //CSpriteModifierData mdata;
};

typedef std::vector<SpriteCallData> SprDataStorage;

struct SpriteLinkData {
    int id = -1;
    boost::shared_ptr<CSprite> sprite;
    CSpriteManager::CSpriteModifierFunc mainfunc;
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

    int AddSpriteData(CSprite* sprite, const CSpriteModifierFunc& fnc) {
        int id = NewId();

        SpriteLinkData data;
        data.id = id;
        //data.sprite = sprite;
        data.sprite.reset(sprite);
        data.mainfunc = fnc;
        m_vSpriteData.insert(std::make_pair(id, data));
        return id;
    }

    void AddSpriteDraw(int id, const CSpriteModifierFunc& fnc, const CPoint& position, int sprOffset = 0) {
        SpriteLinkData& data = m_vSpriteData[id];;
        SpriteCallData callData;
        callData.updfunc = fnc;
        //callData.pos = data.sprite->GetPosition();
        //callData.offset = data.sprite->GetOffset();
        callData.pos = position;
        callData.offset = sprOffset;
        data.callData.push_back(callData);
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
    int id = pimpl_->AddSpriteData(sprite, updfunc);
    //m_pvSprites.push_back(new CSpriteHook(sprite, updfunc));
    return id;
}

void CSpriteManager::AddSpriteDraw(int id, const CPoint& position, const CSpriteModifierFunc& updfunc)
{
    pimpl_->AddSpriteDraw(id, updfunc, position);
}

void CSpriteManager::OnDraw() {
    BOOST_FOREACH(SprLinkStorage::value_type & it, pimpl_->m_vSpriteData)
    {
        if (it.second.sprite->IsVisible())
        {
            it.second.sprite->Draw();
        }
    }

}

void CSpriteManager::OnIdle(int ticks) {


    SprLinkStorage::iterator sprIt = pimpl_->m_vSpriteData.begin();
    while (sprIt != pimpl_->m_vSpriteData.end()) {

        static CRectangle srcRect, dstRect;
        CSpriteModifierData mdata(&srcRect, &dstRect);
        SpriteLinkData& linkdata = (*sprIt).second;
        CSprite* sprite = linkdata.sprite.get();
        bool runMainIdle = linkdata.mainfunc != NULL && linkdata.sprite->IsVisible();
        if (runMainIdle)
        {
            linkdata.mainfunc(sprite, ticks, mdata);
        }

        if (mdata.markedForDeletion) {
            // if markedForDeletion, remove it
            sprIt = pimpl_->m_vSpriteData.erase(sprIt);
        }
        else {
            // children call data
            CPoint oldPos = linkdata.sprite->GetPosition();
            int oldOffset = linkdata.sprite->GetOffset();

            SprDataStorage::iterator subIt = linkdata.callData.begin();
            while (subIt != linkdata.callData.end()) {
                SpriteCallData& sprite_call_data = (*subIt);
                linkdata.sprite->SetPosition(sprite_call_data.pos);
                linkdata.sprite->SprOffset(sprite_call_data.offset);
                //static CRectangle srcRect, dstRect;
                //CSpriteModifierData mdata(&srcRect, &dstRect);
                CSpriteModifierData childMdata(&srcRect, &dstRect);
                sprite_call_data.updfunc(sprite, ticks, childMdata);
                sprite_call_data.pos = linkdata.sprite->GetPosition();
                sprite_call_data.offset = linkdata.sprite->GetOffset();


                if (childMdata.markedForDeletion) {
                    // if markedForDeletion, remove it
                    subIt = linkdata.callData.erase(subIt);
                }
                else {
                    ++subIt;
                }
            }

            linkdata.sprite->SetPosition(oldPos);
            linkdata.sprite->SprOffset(oldOffset);

            ++sprIt;
        }
    }



    /*// this seems the best when iterating and deleting
    SprStorage::iterator sprIt = m_pvSprites.begin();
    while (sprIt != m_pvSprites.end()) {

        static CRectangle srcRect, dstRect;
        CSpriteModifierData mdata(&srcRect, &dstRect);
        (*sprIt).DoIdle(ticks, mdata);

        if (mdata.markedForDeletion) {
            // if markedForDeletion, remove it
            sprIt = m_pvSprites.erase(sprIt);
        }
        else {
            // SprDataStorage
            ++sprIt;
        }
    }*/

    /*
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
            // it has to be checked, if removing has no side effects. see CSpriteManager::OnIdle for a solution with "while".
            //removeList.push_back(it2);
            removeList.insert(removeList.begin(), it2);
            continue;
        }

        //if (mdata.isHandled) {
           // do something
        //   }
    }

    BOOST_FOREACH(SprLinkStorage::value_type & v, pimpl_->m_vSpriteData)
    {
        auto id = v.first;
        auto pos = v.second.sprite->GetPosition();
        id++;
    }

    // delete marked sprites
    BOOST_FOREACH(SprStorage::iterator itpos, removeList)
    {
        m_pvSprites.erase(itpos);
        //break;
    }*/

} // CSpriteManager::OnIdle

void CSpriteManager::Render() {
    /*SprStorage::iterator end = m_pvSprites.end();

    for(SprStorage::iterator it = m_pvSprites.begin(); it < end; ++it)
    {
        SpriteShrp sprite = it->Sprite();
        sprite->Render();
    }*/
    BOOST_FOREACH(SprLinkStorage::value_type & it, pimpl_->m_vSpriteData)
    {
        if (it.second.sprite->IsVisible())
        {
            it.second.sprite->Render();
        }
        
        CPoint oldPos = it.second.sprite->GetPosition();
        int oldOffset = it.second.sprite->GetOffset();

        BOOST_FOREACH(SprDataStorage::value_type & child, it.second.callData)
        {
            it.second.sprite->SetPosition(child.pos);
            it.second.sprite->SprOffset(child.offset);

            it.second.sprite->Render();
            
            it.second.sprite->SetPosition(oldPos);
            it.second.sprite->SprOffset(oldOffset);

        }
    }
}

std::ostream& operator<<(std::ostream& o, const CSpriteManager& r) {
    return o << "CSpriteManager[ X="   /*<< r.GetX() << ", Y=" << r.GetY()
                                          << ", W=" << r.GetW() << ", H=" << r.GetH()
                                          <<*/
           " ]";
}
}
