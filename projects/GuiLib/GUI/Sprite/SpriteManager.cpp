//
#include "stdafx.h"
#define BOOST_CHRONO_HEADER_ONLY 1
//
#include "SpriteManager.h"
#include "boost/smart_ptr/weak_ptr.hpp"
#include <boost/algorithm/cxx11/any_of.hpp>
#include <boost/algorithm/cxx11/none_of.hpp>
#include <boost/chrono/include.hpp>
#include <boost/foreach.hpp>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <set>
//
//#include <build/cmake/include/debug.h>

//#define GRIDFISHING_ENABLED

humbuglib::Log::Stream&duration_shortx(humbuglib::Log::Stream& os) {
    typedef boost::chrono::duration_punct<humbuglib::Log::Stream::char_type> Facet;
    std::locale loc = os.getloc();
    if(std::has_facet<Facet>(loc)) {
        const Facet& f = std::use_facet<Facet>(loc);
        if(f.is_long_name()) {
            os.imbue(std::locale(loc, new Facet(Facet::use_short, f)));
        }
    }
    else {
        os.imbue(std::locale(loc, new Facet(Facet::use_short)));
    }

    return os;
}

namespace gui {
using namespace components;

/** @class Profile:
 *  Detailed description.
 *  @param func TODO
 *  @return TODO
 */
class Profile {
    boost::chrono::high_resolution_clock::time_point start;
    boost::chrono::microseconds time;
    long callCount;

public:

    Profile() : time(0), callCount(0) {
    }

    void operator()(const boost::function<void(void)>& func) {
        start = boost::chrono::high_resolution_clock::time_point(boost::chrono::high_resolution_clock::now());
        func();
        time += boost::chrono::duration_cast<boost::chrono::microseconds>(boost::chrono::high_resolution_clock::now() - start);
        callCount++;
    }

    boost::chrono::microseconds Time() const {
        return time;
    }

    boost::chrono::microseconds Average() const {
        return time / callCount;
    }
};

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
    //std::vector<std::string> canCollideWithTags;
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

    std::map<std::string, std::set<int>> spriteTagToIdMap;
    SprLinkStorage m_vSpriteData;
#if defined(GRIDFISHING_ENABLED)

    std::map<int, int> spriteIdGridWidth;
    std::map<int, int> spriteIdGridHeight;

#endif

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
        sprite->SetName(tag);

        SpriteLinkData data;
        data.id = id;
        data.tag = tag;
        data.canCollideWithTags = canCollideWithTags;
        data.hitHandler = hitHandler;
        //data.sprite = sprite;
        data.sprite.reset(sprite);
        data.mainfunc = fnc;
        m_vSpriteData.insert(std::make_pair(id, data));

        BOOST_FOREACH(const std::vector<std::string>::value_type & collideTag, canCollideWithTags)
        {
            std::set<int>& collideIds = spriteTagToIdMap[collideTag];
            collideIds.insert(id);
        }

        return id;
    } // AddSpriteData

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
        callData.renderfunc = renderfunc;
        callData.initialpos = position;
        callData.pos = position;
        callData.offset = sprOffset;
        callData.hitHandler = hitHandler;
        //callData.id = data.callData.size();
        callData.id = (1024 * id) + data.callData.size();
        //callData.id = NewId();
        data.callData.push_back(callData);

        BOOST_FOREACH(const std::vector<std::string>::value_type & collideTag, canCollideWithTags)
        {
            std::set<int>& collideIds = spriteTagToIdMap[collideTag];
            collideIds.insert(callData.id);
        }
    } // AddSpriteDraw

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

    template<typename T>
    bool IsInBounds(const T& value, const T& low, const T& high) {
        return !(value < low) && (value < high);
    }

    // ReSharper disable CyclomaticComplexity
    bool CheckSpriteDrawCollision(const SpriteLinkData& checkedSprite_link_data, const std::vector<std::string>& canCollideWithTags,
            int canCollideWithId, int collideId, CSpriteModifierData& mdata, int& subSpritesChecked) {
        const bool returnsImmediately = false;
        CSprite* checkedSprite = checkedSprite_link_data.sprite.get();
        bool sprIsHit = false;
#if defined(GRIDFISHING_ENABLED)
        int collideGridWidth = spriteIdGridWidth[collideId];
        int collideGridHeight = spriteIdGridHeight[collideId];
#endif

        //return sprIsHit;
        // check against all registered sprites.
        BOOST_FOREACH(SprLinkStorage::value_type & curSpriteIt, m_vSpriteData)
        {
            SpriteLinkData& currentSprite_link_data = curSpriteIt.second;
            if(currentSprite_link_data.sprite == checkedSprite_link_data.sprite) {
                continue;
            }

            bool inBounds = true;

#if defined(GRIDFISHING_ENABLED)
            const CPoint& curPos = currentSprite_link_data.sprite->GetPosition();
            int curGridWidth = curPos.GetX() / 64;
            int curGridHeight = curPos.GetY() / 64;

            if(!IsInBounds(curGridWidth, collideGridWidth - 2, collideGridWidth + 2) &&
               !IsInBounds(curGridHeight, collideGridHeight - 2, collideGridHeight + 2)) {
                inBounds = false;
                //continue;
            }

#endif // if defined(GRIDFISHING_ENABLED)
            std::set<int>& collideIds = spriteTagToIdMap[currentSprite_link_data.tag];
            const bool is_in = collideIds.find(checkedSprite_link_data.id) != collideIds.end();

            // checkedSprite_link_data.id is canCollideWithId
//            if (canCollideWithId == currentSprite_link_data.id) {
//                continue;
//            }

            boost::shared_ptr<CSprite>& currentSprite = currentSprite_link_data.sprite;

//            if (!currentSprite->IsVisible()) {
//                continue;
//            }

            // skip if the current sprite == the sprite to check against
            subSpritesChecked++;
//            if (boost::algorithm::none_of_equal(canCollideWithTags, currentSprite_link_data.tag))
// {
//                continue;
//            }

            CRectangle checkedSpriteHitBox = checkedSprite->GetPaintHitbox();
            CRectangle currentSpriteHitBox = currentSprite->GetPaintHitbox();
            if(is_in && inBounds) {
                //if (!CanNotCollideWithTag(canCollideWithTags, currentSprite_link_data.tag)) {
                if(currentSprite->IsVisible()) {
                    bool isHit = checkedSpriteHitBox.Contains(currentSpriteHitBox);
                    if(isHit) {
                        if(checkedSprite_link_data.hitHandler) {
                            checkedSprite_link_data.hitHandler->HitBy(
                                    *currentSprite.get(), currentSpriteHitBox, collideId, currentSprite_link_data.tag, mdata);
                        }

                        sprIsHit = true;
                        if(returnsImmediately) {
                            return true;
                        }
                    }
                }
            }
            else {
                int xxxx = 0;
                xxxx++;
            }

//            dbgOut("mSpr(" << std::setfill('0') << std::setw(5) << checkedSprite_link_data.id <<
//                ") vs Spr(" << canCollideWithId << ")"
//                );

            //
            // test the sprite in checkedSprite_link_data against the clones of all sprites
            // (currentSprite) collision
            BOOST_FOREACH(SprDataStorage::value_type & clone, currentSprite_link_data.callData)
            {
                const CPoint& clonePos = clone.pos;
#if defined(GRIDFISHING_ENABLED)
                int cloneGridWidth = clonePos.GetX() / 64;
                int cloneGridHeight = clonePos.GetY() / 64;

                if(!IsInBounds(cloneGridWidth, collideGridWidth - 2, collideGridWidth + 2) &&
                   !IsInBounds(cloneGridHeight, collideGridHeight - 2, collideGridHeight + 2)) {
                    continue;
                }

#endif
                if(!is_in) {
                    continue;
                }

//                if(/*currentSprite_link_data.sprite->IsVisible() ||*/
// CanNotCollideWithTag(canCollideWithTags,
//                                                                              currentSprite_link_data.tag))
// {
//                    continue;
//                }

//                std::set<int>& collideIds = spriteTagToIdMap[currentSprite_link_data.tag];
//                const bool is_in = collideIds.find(canCollideWithId) != collideIds.end();
//                if (!is_in) {
//                    //continue;
//                    int xxxx = 0;
//                    xxxx++;
//                }
//                else {
//                    continue;
//                    int xxxx = 0;
//                    xxxx++;
//                }
//

                subSpritesChecked++;

                CPoint oldPos = currentSprite->GetPosition();
                currentSprite->SetPosition(clonePos);
                CRectangle currentCloneSpriteHitBox = currentSprite->GetPaintHitbox();
                bool isHit = checkedSpriteHitBox.Contains(currentCloneSpriteHitBox);
                if(isHit) {
                    if(checkedSprite_link_data.hitHandler) {
                        checkedSprite_link_data.hitHandler->HitBy(*currentSprite,
                                currentCloneSpriteHitBox,
                                clone.id,
                                currentSprite_link_data.tag, mdata);
                    }

                    if(clone.hitHandler) {
                        clone.hitHandler->HitBy(*checkedSprite,
                                currentCloneSpriteHitBox,
                                collideId,
                                checkedSprite_link_data.tag, mdata);
                    }

                    sprIsHit = true;
                    if(returnsImmediately) {
                        return true;
                    }
                }

                currentSprite->SetPosition(oldPos);
            }
        }
        if(returnsImmediately) {
            return false;
        }

        return sprIsHit;
    } // CheckSpriteDrawCollision
};

CSpriteManager::CSpriteManager(/*SDL_Surface* screen*/)
    : pimpl_(new CSpriteManagerImpl(this)), m_iTicks(0), m_bNotFirstRun(false) {
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

template<class Rep, class Period>
std::string short_duration_log(const boost::chrono::duration<Rep, Period>& t) {
    std::stringstream sst;
    sst << std::setfill('0') << std::setw(5);
    sst << boost::chrono::duration_short;
    sst << t;
    return sst.str();
}

#define StartProfile(name) name([&](void)
#define EndProfile  )

void CSpriteManager::OnIdle(int ticks) {
    boost::chrono::high_resolution_clock::time_point start(boost::chrono::high_resolution_clock::now());
    boost::chrono::microseconds t2(0);
    boost::chrono::microseconds t3(0);
    //HighResClock::time_point start(HighResClock::now());
    //StopWatchTimer tmr;
    int numSpritesChecked = 0;
    int subSpritesChecked = 0;

    m_iTicks = ticks;
    SprLinkStorage::iterator sprIt = pimpl_->m_vSpriteData.begin();
    Profile profTopLevel;

    while(sprIt != pimpl_->m_vSpriteData.end()) {
        CRectangle srcRect, dstRect;
        CSpriteModifierData mdata(&srcRect, &dstRect);
        SpriteLinkData& linkdata = (*sprIt).second;
        CSprite* sprite = linkdata.sprite.get();

        //profTopLevel([&](void) {

        StartProfile(profTopLevel) {
            if(m_bNotFirstRun) {
                mdata.isHit = pimpl_->CheckSpriteDrawCollision(linkdata,
                        linkdata.canCollideWithTags,
                        linkdata.id,
                        linkdata.id,
                        mdata,
                        subSpritesChecked);
            }
        }
        EndProfile;

        numSpritesChecked++;

        CPoint oldPos = sprite->GetPosition();
        int oldOffset = sprite->GetSpriteOffset();

        bool runMainIdle = linkdata.mainfunc != NULL && sprite->IsVisible();
        if(runMainIdle) {
            linkdata.mainfunc(sprite, ticks, mdata);

#if defined(GRIDFISHING_ENABLED)
            CPoint newPos = sprite->GetPosition();
            pimpl_->spriteIdGridWidth[linkdata.id] = newPos.GetX() / 64;
            pimpl_->spriteIdGridHeight[linkdata.id] = newPos.GetY() / 64;
#endif
        }

        if(mdata.markedForDeletion) {
            // if markedForDeletion, remove it
            sprIt = pimpl_->m_vSpriteData.erase(sprIt);
        }
        else {
            // children call data

            SprDataStorage::iterator subIt = linkdata.callData.begin();

            while(subIt != linkdata.callData.end()) {
                SpriteCallData& sprite_call_data = (*subIt);

//                std::set<int>& collideIds = pimpl_->spriteTagToIdMap[linkdata.tag];
//                const bool is_in = collideIds.find(sprite_call_data.id) != collideIds.end();
//                if (!is_in) {
//                    //continue;
//                    int xxxx = 0;
//                    xxxx++;
//                }
//                else {
//                    int xxxx = 0;
//                    xxxx++;
//                }
//
                sprite->SetPosition(sprite_call_data.pos);
                sprite->SetSpriteOffset(sprite_call_data.offset);
                //static CRectangle srcRect, dstRect;
                //CSpriteModifierData mdata(&srcRect, &dstRect);
                CSpriteModifierData childMdata(&srcRect, &dstRect);
                boost::chrono::high_resolution_clock::time_point start2(boost::chrono::high_resolution_clock::now());
                if(m_bNotFirstRun) {
                    childMdata.isHit = pimpl_->CheckSpriteDrawCollision(linkdata,
                            linkdata.canCollideWithTags, linkdata.id,
                            sprite_call_data.id, childMdata,
                            subSpritesChecked);
                }

                t2 += boost::chrono::duration_cast<boost::chrono::microseconds>(boost::chrono::high_resolution_clock::now() - start2);
                numSpritesChecked++;
                childMdata.initialpos = sprite_call_data.initialpos;

                //childMdata.isHit = mdata.isHit;
                boost::chrono::high_resolution_clock::time_point start3(boost::chrono::high_resolution_clock::now());
                sprite_call_data.updfunc(sprite, ticks, childMdata);
                sprite_call_data.pos = sprite->GetPosition();
                sprite_call_data.offset = sprite->GetSpriteOffset();
#if defined(GRIDFISHING_ENABLED)
                pimpl_->spriteIdGridWidth[sprite_call_data.id] = sprite_call_data.pos.GetX() / 64;
                pimpl_->spriteIdGridHeight[sprite_call_data.id] = sprite_call_data.pos.GetY() / 64;
#endif
                t3 += boost::chrono::duration_cast<boost::chrono::microseconds>(boost::chrono::high_resolution_clock::now() - start3);

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
    static boost::chrono::microseconds avg(0);
    static int runs = 0;
    runs++;

    auto t = boost::chrono::duration_cast<boost::chrono::microseconds>(boost::chrono::high_resolution_clock::now() - start);
    avg += t;

//   std::locale loc = humbuglib::LogManager::getSingleton().stream().getloc();
//   typedef boost::chrono::duration_punct<std::string> Facet;
//   const Facet& f = std::use_facet<Facet>(loc);
//   if (f.is_long_name())
//       os.imbue(std::locale(loc, new Facet(Facet::use_short, f)));

//   std::stringstream sst;
//   sst << boost::chrono::duration_short << t;
//   std::stringstream sst2;
//   sst2 << boost::chrono::duration_short << t2;
//   std::stringstream sst3;
//   sst3 << boost::chrono::duration_short << t3;
//   std::stringstream sst4;
//   sst4 << boost::chrono::duration_short << avg / runs;

    // duration_shortx <<
    dbgOut("[" << std::setfill('0') << std::setw(5) << runs << "]Spr=" << std::setw(3) << pimpl_->m_vSpriteData.size() <<
                ", all=" << std::setw(5) << numSpritesChecked <<
                ", Sub=" << std::setw(5) << subSpritesChecked <<
                ", OnIdle t: " << short_duration_log(t) <<
                ", top t: " << short_duration_log(profTopLevel.Time()) <<
                ", Sub check t: " << short_duration_log(t2) <<
                ", Sub updfunc t: " << short_duration_log(t3) <<
                ", Avg t: " << short_duration_log(avg / runs)
            );

    m_bNotFirstRun = true;
} // CSpriteManager::OnIdle

void CSpriteManager::Render() {
    // Profile()[
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
