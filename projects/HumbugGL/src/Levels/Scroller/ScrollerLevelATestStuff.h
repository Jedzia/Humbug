#pragma once

//#include "boost/function.hpp"
//#include "boost/lambda/lambda.hpp"
//#include <cstdlib>
//#include "../../Input/PlayerKeys4.h"
//#include "PlayerShip.h"
//#include "EnemyShip.h"
//#include "GUI/DebugOverlay.h"
//#include "HumbugShared/GameObjects/Player.h"
//
//#include <GUI/Components/Rectangle.h>
//#include <GuiLib/Filesystem/FileLoader.h>
//#include <GuiLib/GUI/Components/CoordSystem.h>
//#include <GuiLib/GUI/Components/Shapes/Line.h>
//#include <GuiLib/GUI/Controls/Label.h>
//#include <GuiLib/GUI/Sprite/SpriteManager.h>
//#include <GuiLib/GUI/Components/TextScroller.h>
//#include <GuiLib/GUI/Controls/Button.h>
//#include <GuiLib/GUI/Controls/Label.h>
//
//#include <GuiLib/GUI/Components/CanvasRendererImpl.h>
//#include <GuiLib/GUI/Components/EasingFunctors.h>
//#include <GuiLib/GUI/Components/Color.h>
//#include <GuiLib/GUI/Components/Canvas.h>
//#include <GuiLib/GUI/Components/Image.h>
//#include <GuiLib/GUI/Components/Rectangle.h>
//#include <GuiLib/GUI/Components/SeamlessImage.h>
//#include <GuiLib/GUI/Components/Text.h>
//#include <GuiLib/GUI/Components/TextScroller.h>
//#include <GuiLib/GUI/Controls/Button.h>
//#include <GuiLib/GUI/Data/ColorData.h>
//#include <GuiLib/GUI/Sprite/Sprite.h>
//#include <GuiLib/GUI/Visual/EventHandler.h>
//#include <GuiLib/Timing.h>

using namespace gui::components;
using namespace gui;

/** @class CanvasStripeRendererA:
 *  Detailed description.
 *  @param source TODO
 *  @param target TODO
 *  @param dstRect TODO
 *  @param srcRect TODO
 *  @param color TODO
 */
class CanvasStripeRendererA {
    int m_iBoatcols;
    int m_iFrames;
    int m_iSteps;
    SDL_Color cmap[256];
    TTF_Font* m_pDebugFont;
    DebugOverlay* m_pDovl;
    boost::shared_ptr<controls::CLabel> label1;
    int label2;
    int label3;
    int label4;
    int label5;
    int label6;
    CCoordSystem cs;
    static int renderNum;

public:

    // this little bastard should render colored stripes when ready.
    explicit CanvasStripeRendererA(FileLoader& loader, int steps = 16, TTF_Font* debugFont = NULL, DebugOverlay* debug_overlay = NULL)
        : m_iBoatcols(0), m_iFrames(0), m_iSteps(steps), m_pDebugFont(debugFont), m_pDovl(debug_overlay),
        label1(nullptr), label2(0), label3(0), label4(0), cs("Coords", 400, 400, CPoint(100, 100)) {
        renderNum++;
        if(debug_overlay && debugFont) {
            /*if (!controls::CLabel::GetLabelFont())
               {
                controls::CLabel::SetLabelFont(debugFont);
               }*/
            cs.SetLoader(&loader);

            // manual label creation
            label1.reset(new controls::CLabel(debug_overlay, CRectangle(0, 0, -1, -1), 123, "Label 1", debugFont,
                            true, CColor::Black(), CColor::White()));
            Uint16 height = label1->GetHeight();
            label1->SetPosition(CPoint(600, height / 2));
            m_pDovl->AddChild(label1.get());

            // automatic labels
            label2 = m_pDovl->AddTextLabel();
            label3 = m_pDovl->AddTextLabel();
            label4 = m_pDovl->AddTextLabel();
            label5 = m_pDovl->AddTextLabel();
            label6 = m_pDovl->AddTextLabel();
        }
    }

    ~CanvasStripeRendererA() {
    }

    static void Render(CCanvas* source, const CCanvas* target,
            const CRectangle& dstRect, const CRectangle& srcRect, const CColor& color) {
        source->SetTextureColorMod(color);
        target->FinalRenderCopy(source->GetTexture(), &dstRect, &srcRect);
    }

    template<typename T>
    void PrintLabel(const int& id, const char* title, const T& degrees) const {
        if(id) {
            std::ostringstream labelText;
            labelText << "{" << renderNum << "}" << title << "(" << degrees << ")";
            m_pDovl->SetTextLabelText(id, labelText.str());
        }
    }

    float norm(float ceiling, float floor, float max, float min, float input) {
        return 1.0f;
    }

    void operator()(const CCanvas* target, CCanvas* source,
            CCanvasRenderModifierData& mdata) {
        m_iFrames++;

        if(!mdata.dstRect) {
            return;
        }

        CRectangle dstRect(*mdata.dstRect);
        CRectangle srcRect(source->GetDimension());

        CColor color1 = CColor::White();
        //CColor color1 = CColor::Red();
        CColor color2 = CColor::Green();

        /*if (m_iTicks % 16 > 8)
           {
            color1 = CColor::Green();
            color2 = CColor::Red();
           }*/

        const int stepsize = 16;
        const int colorstep = 256 / stepsize;
        srcRect.H() /= stepsize;
        dstRect.H() /= stepsize;

        int rdegrees = (m_iFrames % 360);
        int degrees = (m_iFrames * 8 % 360);
        const float PI = 3.14159265f;
        float radians = degrees * PI / 180.0f;
        float clock = degrees / PI;
        int corrector = static_cast<int>(64 + sin(radians) * 64);
        int stepcheck = static_cast<int>(stepsize + sin(((m_iFrames * 2 % 180) + 180) * PI / 180.0f) * stepsize);

        /*if (m_pDebugFont)
           {
            std::ostringstream labelText;
            //labelText << "deg(" << diffx << ", " << diffy << ")";
            labelText << "deg(" << degrees << ")";
            CText label(m_pDebugFont, (labelText.str()), CColor::DarkRed());
            label.RenderPut(source, CRectangle(20,100,0,0));
           }*/

        if(label1) {
            std::ostringstream labelText;
            labelText << "rad(" << radians << ")";
            label1->SetCaption(labelText.str());
        }

        PrintLabel(label2, "rad", radians);
        PrintLabel(label3, "deg", degrees);
        PrintLabel(label4, "clock", clock);

        // CCoordSystem ?
        target->SetRenderDrawBlendMode(BLENDMODE_NONE);
        CColor color = CColor::LightGreen();
        //target->RenderDrawLine(CPoint(20, 100 + degrees), CPoint(220, 100 + degrees), &color);
        gui::components::SLine::RenderDrawLine(target, CPoint(20, 100 + degrees), CPoint(220, 100 + degrees), &color);
        target->SetRenderDrawBlendMode(BLENDMODE_MOD);
        CRectangle rect = CRectangle(20, 100 + degrees, 100, 20);
        target->RenderFillRect(rect, &color);
        target->SetRenderDrawBlendMode(BLENDMODE_NONE);

        if(rdegrees == 0) {
            //cs.Reset();
        }

        for(int i = 0; i < stepsize; i++)
        {
            //int newColor = (colorstep * ((i * 8 + -m_iTicks / colorstep) % stepsize)) % 255;
            int newColorStep = (colorstep / 2 * i) + 1;
            int newColor = corrector + newColorStep;
            newColor = newColor > 255 ? 255 : newColor;
            newColor = newColor < 0 ? 0 : newColor;

            int newGreen = 25;

            //if ((m_iTicks % (i + 1)) > stepsize / 2)
            if(stepcheck == i) {
                newGreen ^= m_iFrames;
            }

            color2 = CColor(newColor, newGreen, 25);

            //CRectangle src_rect(*mdata.srcRect);
            Render(source, target, dstRect, srcRect, color2);
            srcRect.Y() += srcRect.H();
            dstRect.Y() += dstRect.H();
        }
        cs.AddDatapoint(CPoint(degrees, corrector));
        PrintLabel(label5, "Datapoints", cs.NumDatapoints());

        //cs.AddDatapoint(CPoint(rdegrees, rdegrees));
        //cs.AddDatapoint(CPoint(degrees, stepcheck));
        cs.RenderPut(target);

        //srcRect.Y() += srcRect.H();
        //dstRect.Y() += dstRect.H();
        //Render(source, target, dstRect, srcRect, color2);

        // prevent rendering the target canvas again.
        mdata.isHandled = true;
    } // ()
};

int CanvasStripeRendererA::renderNum = 0;

