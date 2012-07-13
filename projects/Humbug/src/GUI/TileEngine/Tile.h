/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2012, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Sprite.h class.
 * \folder     $(folder)
 * \file       Sprite.h
 * \date       2012-07-10
 * \author     Jedzia.
 *
 * modified    2012-07-10, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef HUMBUG_GUI_TILEENGINE_CTILE_H
#define HUMBUG_GUI_TILEENGINE_CTILE_H
#include "../Components/Point.h"
#include "../Components/Rectangle.h"
#include <string>


class CTile {
public:

    CTile( int index );
    ~CTile();
    void Draw();

    void SetPos(CPoint& pos);

    void SprOffset(int offset);

    friend std::ostream& operator<<(std::ostream& o, const CTile& r);

private:

   int m_iIndex;
};
std::ostream& operator<<(std::ostream& o, const CTile& r);

#endif // HUMBUG_GUI_TILEENGINE_CTILE_H guard
