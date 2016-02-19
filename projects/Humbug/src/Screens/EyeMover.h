/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the EyeMover.h class.
 * \folder     $(folder)
 * \file       EyeMover.h
 * \date       2013-11-22
 * \author     Jedzia.
 *
 * modified    2013-11-22, Jedzia
 */
/*---------------------------------------------------------*/
#pragma once

/** @class EyeMover:
 *  Detailed description.
 *  @param sprite TODO
 * @param ticks TODO
 * @return TODO
 */
class EyeMover {
    int h_;
    bool toggle_;
    int deltaY_;
    static int created;

public:

    EyeMover(int deltaY = 0) : deltaY_(deltaY), h_(0), toggle_(false){
        dbgOut(__FUNCTION__ << " created:" << created << " (" << this << ")");
        //static int created = 0;
        created++;
    }
    ~EyeMover(){
        dbgOut(__FUNCTION__ << " " << this);
    }
    /** $(fclass), operator ():
     *  Detailed description.
     *  @param sprite TODO
     * @param ticks TODO
     * @return TODO
     */
    void operator()(CSprite* sprite, int ticks, CSpriteModifierData& mdata) {
        double ss = std::sin(static_cast<double>(ticks) / 12);
        int ssin = static_cast<int>(ss * 155);

        sprite->SetPosition( CPoint(100 + ( (ticks % 128) * 6 ), 460 + h_ + deltaY_ + ssin) );
        sprite->SprOffset(ticks % 8);

        if (h_ >= 100) {
            toggle_ = false;
        }
        else if (h_ <= 0) {
            toggle_ = true;
        }

        if (toggle_) {
            h_++;
        }
        else {
            h_--;
        }
    } // ()
};

int EyeMover::created = 0;
