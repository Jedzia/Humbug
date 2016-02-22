//
#include "stdafx.h"

//
#include "SpriteManager.h"
#include "boost/smart_ptr/weak_ptr.hpp"
#include <boost/algorithm/cxx11/any_of.hpp>
#include <boost/algorithm/cxx11/none_of.hpp>
#include <boost/foreach.hpp>
#include <iostream>
#include <chrono>
//#include <chrono_io>
#include <ctime>
#include <iomanip>
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
struct SpriteCallData {
    CPoint pos;
    CPoint initialpos;
    int offset;
    int id;
    CSpriteManager::CSpriteModifierFunc updfunc;
    CSpriteManager::CSpriteRenderFunc renderfunc;
    std::vector<std::string> canCollideWithTags;
    HitHandler* hitHandler;
    //CSpriteModifierData mdata;
};

typedef std::vector<SpriteCallData> SprDataStorage;

struct SpriteLinkData {
    int id = -1;
    std::string tag;
    boost::shared_ptr<CSprite> sprite;
    CSpriteManager::CSpriteModifierFunc mainfunc;
    SprDataStorage callData;
    std::vector<std::string> canCollideWithTags;
    HitHandler* hitHandler;
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

    int AddSpriteData(
            CSprite* sprite,
            const std::string& tag,
            const CSpriteModifierFunc& fnc,
            HitHandler* hitHandler,
            const std::vector<std::string>& canCollideWithTags
            ) {
        int id = NewId();

        SpriteLinkData data;
        data.id = id;
        data.tag = tag;
        data.canCollideWithTags = canCollideWithTags;
        data.hitHandler = hitHandler;
        //data.sprite = sprite;
        data.sprite.reset(sprite);
        data.mainfunc = fnc;
        m_vSpriteData.insert(std::make_pair(id, data));
        return id;
    }

    void AddSpriteDraw(
            int id,
            const CPoint& position,
            const CSpriteModifierFunc& fnc,
            const std::vector<std::string>& canCollideWithTags,
            HitHandler* hitHandler,
            const CSpriteRenderFunc& renderfunc, int sprOffset = 0) {
        SpriteLinkData& data = m_vSpriteData[id];
        SpriteCallData callData;
        callData.updfunc = fnc;
        callData.canCollideWithTags = canCollideWithTags;
        callData.renderfunc = renderfunc;
        //callData.pos = data.sprite->GetPosition();
        //callData.offset = data.sprite->GetSpriteOffset();
        callData.initialpos = position;
        callData.pos = position;
        callData.offset = sprOffset;
        callData.hitHandler = hitHandler;
        callData.id = data.callData.size();
        data.callData.push_back(callData);
    }

    static bool CanNotCollideWithTag(const std::vector<std::string>& canCollideWithTags, const std::string& tag) {
        const bool emptyTaglistMeansCollideWithAll = false;
        bool tagListIsNotEmpty = !canCollideWithTags.empty();
        bool tagOption = tagListIsNotEmpty || !emptyTaglistMeansCollideWithAll;
        bool tagOptionNotMet = tagOption && boost::algorithm::none_of_equal(canCollideWithTags, tag);
        if(boost::algorithm::any_of_equal(canCollideWithTags, "ALL")) {
            tagOptionNotMet = false;
        }

        return tagOptionNotMet;
    }

    // ReSharper disable CyclomaticComplexity
    bool CheckSpriteDrawCollision(SpriteLinkData& checkedSprite_link_data, const std::vector<std::string>& canCollideWithTags,
            int collideId) {
        const bool returnsImmediately = false;
        CSprite* checkedSprite = checkedSprite_link_data.sprite.get();
        bool sprIsHit = false;
        //return sprIsHit;
        // check against all registered sprites.
        BOOST_FOREACH(SprLinkStorage::value_type & curSpriteIt, m_vSpriteData)
        {
            SpriteLinkData& currentSprite_link_data = curSpriteIt.second;
            boost::shared_ptr<CSprite>& currentSprite = currentSprite_link_data.sprite;

//            if (!currentSprite->IsVisible()) {
//                continue;
//            }

            // skip if the current sprite == the sprite to check against
            if(currentSprite_link_data.sprite == checkedSprite_link_data.sprite) {
                continue;
            }

//            if (boost::algorithm::none_of_equal(canCollideWithTags, currentSprite_link_data.tag))
// {
//                continue;
//            }

            CRectangle checkedSpriteHitBox = checkedSprite->GetPaintHitbox();
            CRectangle currentSpriteHitBox = currentSprite->GetPaintHitbox();
            if(currentSprite->IsVisible() && !CanNotCollideWithTag(canCollideWithTags, currentSprite_link_data.tag)) {
                bool isHit = checkedSpriteHitBox.Contains(currentSpriteHitBox);
                if(isHit) {
                    // if (currentSprite_link_data.hitHandler) {
                    //     currentSprite_link_data.hitHandler->HitBy(*linkdataSprite,
                    // linkdataSpriteHitBox, collideId, checkedSprite_link_data.tag);
                    //  }
                    if(checkedSprite_link_data.hitHandler) {
                        checkedSprite_link_data.hitHandler->HitBy(
                                *currentSprite.get(), currentSpriteHitBox, collideId, currentSprite_link_data.tag);
                    }

                    sprIsHit = true;
                    if (returnsImmediately)
                        return true;
                }
            }

            //
            // test the sprite in checkedSprite_link_data against the clones of all sprites
            // (currentSprite) collision
            //BOOST_FOREACH(SprDataStorage::value_type & clone, curSpriteIt.second.callData)
            BOOST_FOREACH(SprDataStorage::value_type & clone, currentSprite_link_data.callData)
            {
//                if ((!clone.canCollideWithTags.empty() && !emptyTaglistMeansCollideWithAll)
//                    && boost::algorithm::none_of_equal(clone.canCollideWithTags,
// currentSprite_link_data.tag)) {
//                    continue;
//                }
//                if (boost::algorithm::none_of_equal(clone.canCollideWithTags,
// currentSprite_link_data.tag)) {
//                    continue;
//                }
                if(CanNotCollideWithTag(canCollideWithTags, currentSprite_link_data.tag)) {
                    continue;
                }

                CPoint oldPos = currentSprite->GetPosition();
                currentSprite->SetPosition(clone.pos);
                CRectangle currentCloneSpriteHitBox = currentSprite->GetPaintHitbox();
                bool isHit = checkedSpriteHitBox.Contains(currentCloneSpriteHitBox);
                if(isHit) {
                    if(checkedSprite_link_data.hitHandler) {
                        checkedSprite_link_data.hitHandler->HitBy(*checkedSprite,
                                currentCloneSpriteHitBox,
                                clone.id,
                                currentSprite_link_data.tag);
                    }
                    if (clone.hitHandler) {
                        clone.hitHandler->HitBy(*currentSprite,
                            currentCloneSpriteHitBox,
                            checkedSprite_link_data.id,
                            checkedSprite_link_data.tag);
                    }

                    sprIsHit = true;
                    if (returnsImmediately)
                        return true;
                }
                currentSprite->SetPosition(oldPos);
            }
        }
        if (returnsImmediately)
            return false;
        return sprIsHit;
    } // CheckSpriteDrawCollision
};

CSpriteManager::CSpriteManager(/*SDL_Surface* screen*/)
    : pimpl_(new CSpriteManagerImpl(this)) {
    dbgOut(__FUNCTION__);
}

CSpriteManager::~CSpriteManager(void) {
    dbgOut(__FUNCTION__);
}

int CSpriteManager::AddSprite(CSprite* sprite,
        const std::string& tag,
        const CSpriteModifierFunc& updfunc,
        HitHandler* hitHandler,
        const std::vector<std::string>& canCollideWithTags) {
    int id = pimpl_->AddSpriteData(sprite, tag, updfunc, hitHandler, canCollideWithTags);
    //m_pvSprites.push_back(new CSpriteHook(sprite, updfunc));
    return id;
}

void CSpriteManager::AddSpriteDraw(int id,
        const CPoint& position,
        const CSpriteModifierFunc& updfunc,
        const std::vector<std::string>& canCollideWithTags,
        HitHandler* hitHandler,
        const CSpriteRenderFunc& renderfunc) {
    pimpl_->AddSpriteDraw(id, position, updfunc, canCollideWithTags, hitHandler, renderfunc);
}

void CSpriteManager::OnDraw() {
    // do not use, use Render()
    BOOST_FOREACH(SprLinkStorage::value_type & it, pimpl_->m_vSpriteData)
    {
        if(it.second.sprite->IsVisible()) {
            it.second.sprite->Draw();
        }
    }
}

struct HighResClock
{
    typedef long long                               rep;
    typedef std::nano                               period;
    typedef std::chrono::duration<rep, period>      duration;
    typedef std::chrono::time_point<HighResClock>   time_point;
    static const bool is_steady = true;

    static time_point now();
};
namespace
{
    const long long g_Frequency = []() -> long long
    {
        LARGE_INTEGER frequency;
        QueryPerformanceFrequency(&frequency);
        return frequency.QuadPart;
    }();

/*    template<typename Clock, typename Duration>
    std::ostream &operator<<(std::ostream &stream,
        const std::chrono::time_point<Clock, Duration> &time_point) {
        const time_t time = Clock::to_time_t(time_point);
#if __GNUC__ > 4 || \
    ((__GNUC__ == 4) && __GNUC_MINOR__ > 8 && __GNUC_REVISION__ > 1)
        // Maybe the put_time will be implemented later?
        struct tm tm;
        localtime_r(&time, &tm);
        return stream << std::put_time(&tm, "c");
#else
        char buffer[26];
        ctime_r(&time, buffer);
        buffer[24] = '\0';  // Removes the newline that is added
        return stream << buffer;
#endif
    }*/

}

HighResClock::time_point HighResClock::now()
{
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return time_point(duration(count.QuadPart * static_cast<rep>(period::den) / g_Frequency));
}

class StopWatchTimer
{
public:
    StopWatchTimer() : beg_(clock_::now()) {}
    void reset() { beg_ = clock_::now(); }
    double elapsed() const {
        return std::chrono::duration_cast<second_>
            (clock_::now() - beg_).count();
    }

private:
    typedef std::chrono::high_resolution_clock clock_;
    typedef std::chrono::duration<double, std::ratio<1> > second_;
    std::chrono::time_point<clock_> beg_;
}; 

void CSpriteManager::OnIdle(int ticks) {
    //std::chrono::high_resolution_clock::time_point start(std::chrono::high_resolution_clock::now());
    HighResClock::time_point start(HighResClock::now());
    //StopWatchTimer tmr;

    m_iTicks = ticks;
    SprLinkStorage::iterator sprIt = pimpl_->m_vSpriteData.begin();

    while(sprIt != pimpl_->m_vSpriteData.end()) {
        CRectangle srcRect, dstRect;
        CSpriteModifierData mdata(&srcRect, &dstRect);
        SpriteLinkData& linkdata = (*sprIt).second;
        CSprite* sprite = linkdata.sprite.get();
        mdata.isHit = pimpl_->CheckSpriteDrawCollision(linkdata, linkdata.canCollideWithTags, -1);
        //mdata.initialpos = linkdata.initialpos;

        /*BOOST_FOREACH(SprLinkStorage::value_type & it, pimpl_->m_vSpriteData)
           {
            if (!it.second.sprite->IsVisible() || it.second.sprite.get() == sprite)
            {
                continue;
            }

            bool isHit = sprite->GetPaintHitbox().Contains(it.second.sprite->GetPaintHitbox());
            //bool isHit = false;
            if (isHit)
            {
                mdata.isHit = true;
                break;
            }
           }*/

        bool runMainIdle = linkdata.mainfunc != NULL && sprite->IsVisible();
        if(runMainIdle) {
            linkdata.mainfunc(sprite, ticks, mdata);
        }

        if(mdata.markedForDeletion) {
            // if markedForDeletion, remove it
            sprIt = pimpl_->m_vSpriteData.erase(sprIt);
        }
        else {
            // children call data
            CPoint oldPos = sprite->GetPosition();
            int oldOffset = sprite->GetSpriteOffset();

            SprDataStorage::iterator subIt = linkdata.callData.begin();

            while(subIt != linkdata.callData.end()) {
                SpriteCallData& sprite_call_data = (*subIt);
                sprite->SetPosition(sprite_call_data.pos);
                sprite->SetSpriteOffset(sprite_call_data.offset);
                //static CRectangle srcRect, dstRect;
                //CSpriteModifierData mdata(&srcRect, &dstRect);
                CSpriteModifierData childMdata(&srcRect, &dstRect);
//                childMdata.isHit = pimpl_->CheckSpriteDrawCollision(linkdata, sprite_call_data.canCollideWithTags, sprite_call_data.id);
                childMdata.initialpos = sprite_call_data.initialpos;

                //childMdata.isHit = mdata.isHit;
                sprite_call_data.updfunc(sprite, ticks, childMdata);
                sprite_call_data.pos = sprite->GetPosition();
                sprite_call_data.offset = sprite->GetSpriteOffset();

                // restore original sprite data.
                sprite->SetPosition(oldPos);
                sprite->SetSpriteOffset(oldOffset);

                if(childMdata.markedForDeletion) {
                    // if markedForDeletion, remove it
                    subIt = linkdata.callData.erase(subIt);
                }
                else {
                    ++subIt;
                }
            }
            ++sprIt;
        }
    }
    //auto time = std::chrono::high_resolution_clock::now() - start;
    //auto t = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start);
    auto time = HighResClock::now() - start;
    auto t = std::chrono::duration_cast<std::chrono::microseconds>(HighResClock::now() - start);
    //auto t = std::chrono::duration_cast<std::chrono::milliseconds>(HighResClock::now() - start);
    dbgOut("CSpriteManager, OnIdle Time: " << t.count());
    
    //dbgOut("CSpriteManager, OnIdle Time: " << std::chrono::duration_fmt(std::chrono::symbol) << t.count());
    //dbgOut("CSpriteManager(" << std::chrono::system_clock::now() << "), OnIdle Time: " << t);
    //dbgOut("CSpriteManager(), OnIdle Time: " << t);


    //std::cout << std::chrono::system_clock::now() << std::endl;

    //dbgOut("CSpriteManager, OnIdle Time: " << tmr.elapsed());


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
            // it has to be checked, if removing has no side effects. see CSpriteManager::OnIdle for
               a solution with "while".
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
        if(it.second.sprite->IsVisible()) {
            it.second.sprite->Render();
        }

        CPoint oldPos = it.second.sprite->GetPosition();
        int oldOffset = it.second.sprite->GetSpriteOffset();

        BOOST_FOREACH(SprDataStorage::value_type & child, it.second.callData)
        {
            it.second.sprite->SetPosition(child.pos);
            it.second.sprite->SetSpriteOffset(child.offset);

            it.second.sprite->Render();
        }
        it.second.sprite->SetPosition(oldPos);
        it.second.sprite->SetSpriteOffset(oldOffset);
    }
} // CSpriteManager::Render

std::ostream& operator<<(std::ostream& o, const CSpriteManager& r) {
    return o << "CSpriteManager[ X="   /*<< r.GetX() << ", Y=" << r.GetY()
                                          << ", W=" << r.GetW() << ", H=" << r.GetH()
                                          <<*/
           " ]";
}
}
