/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the WormMover.h class.
 * \folder     $(folder)
 * \file       WormMover.h
 * \date       2013-11-22
 * \author     Jedzia.
 *
 * modified    2013-11-22, Jedzia
 */
/*---------------------------------------------------------*/
#pragma once

/** @class WormMover:
 *  Detailed description.
 *  @param sprite TODO
 * @param ticks TODO
 * @return TODO
 */
class WormMover {
    int add_;
    static int created;

public:

    WormMover() : add_(0) {
        dbgOut(__FUNCTION__ << " created:" << created << " (" << this << ")");
        created++;
    }
    ~WormMover(){
        dbgOut(__FUNCTION__ << " " << this);
    }
    /** $(fclass), operator ():
     *  Detailed description.
     *  @param sprite TODO
     * @param ticks TODO
     * @return TODO
     */
    void operator()(CSprite* sprite, int ticks, CSpriteModifierData& mdata) {
        //sprite->SetPos(CPoint(100 + ((ticks % 32) * 16), 420));
        const int sprMaxFrames = 40;
        int frame = (ticks % sprMaxFrames);
        int div = ( ticks % (sprMaxFrames * 4) ) / sprMaxFrames;
        //int movdelta = div * 40;
        int movdelta = 0;

        int deltaX = static_cast<int>( ( ( ticks % (sprMaxFrames * 4) ) * 4.3 ) );
        sprite->SetPosition( CPoint(10 + deltaX + movdelta, 420) );
        int sprframe;

        if ( frame < (sprMaxFrames / 2) ) {
            sprframe = frame;
        }
        else {
            sprframe = sprMaxFrames - frame;
        }

        sprite->SetSpriteOffset(sprframe);
    } // ()
};

int WormMover::created;
