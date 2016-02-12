#pragma once

/** @class MenuScreen:
 *  Detailed description.
 *  @param parent TODO
 *  @param pChild TODO
 *  @param param TODO
 */
class DingensPainter : public controls::DetailedControlPainter {
    int x;
    int k;
    const Screen* m_pHost;
    CPoint lastPos;

    // overloads of the DetailedControlPainter
    void BeforeDrawChild(const controls::CControl& parent, controls::CControl* pChild,
            controls::ControlPainterParameters& param)  override {
        CPoint c_point = pChild->GetPosition();
        lastPos = c_point;
    }

    void DrawChild(const controls::CControl& parent, controls::CControl* pChild, controls::ControlPainterParameters& param)  override {
        const int varX = 1;
        int x1 = static_cast<int>(varX - cos(m_pHost->GetTicks() / 6.0f) * 4);
        int y1 = static_cast<int>(varX - sin(m_pHost->GetTicks() / 6.0f) * 4);
        pChild->SetPosition(CPoint(lastPos.GetX() + x1, lastPos.GetY() + y1));
        //param.SetDrawn(true);
        CColor sdl_color = CColor::LightMagenta();
        auto x2 = static_cast<int>(varX - sin(m_pHost->GetTicks() / 6.0f) * 32);
        auto rect = CRectangle(333 - x2, 393, 55, 55);
        //pChild->GetCanvas()->RenderFillRect(rect, &sdl_color);
       
        //CText text(m_pHost->m_pDebugfont, __FUNCTION__, sdl_color);
        //text.RenderPut(parent.GetCanvas(), rect);
    }

    void AfterDrawChild(const controls::CControl& parent, controls::CControl* pChild, controls::ControlPainterParameters& param)  override {
        //param.SetDrawn(true);
        pChild->SetPosition(lastPos);
    }

public:
    TTF_Font* font;

    explicit DingensPainter(const Screen* host)
        : DetailedControlPainter(), x(0), k(0), m_pHost(host), font(nullptr)
    {
    }

    virtual ~DingensPainter() {
    }

    void operator()(const controls::CControl& parent, controls::CControl* pChild, controls::ControlPainterParameters& param) {
        int rnd = 4 - (rand() % 4);
        x += rnd;
        k++;

        //auto label = static_cast<controls::CLabel>(pChild);
        auto label = dynamic_cast<controls::CLabel *>(pChild);

        if(label) {
            CColor cl = label->GetTextColor();
            CColor clred = CColor::Red();

            if(cl != clred) {
                //int rdegrees = (m_pHost->m_iTicks + r % 360);
                int degrees = (m_pHost->GetTicks()) * 8 % 360;
                const float PI = 3.14159265f;
                float radians = degrees * PI / 180.0f;
                float clock = degrees / PI;
                int corrector = 64 + static_cast<int>(sin(radians) * 64);

                int sval = static_cast<int>(cos(m_pHost->GetTicks() / 6.0f) * 4);
                int c = x % 200;
                //CColor color(c, c, c | 0xa0, c);
                CColor color(corrector, corrector, corrector | 0xa0, corrector);
                //const int kfac = parent.GetNumChildren();
                //CColor color((k % kfac) * 32 + corrector, (k % kfac) * 32, (k % kfac) * 32 | 0xa0,
                // corrector);
                label->SetTextColor(color);

                if (font)
                {
                    std::ostringstream outstring;
                    outstring << std::setfill('0') << std::setw(3) << std::fixed << std::setprecision(3)
                        << "degrees: " << degrees
                        << ", radians: " << radians
                        << ", clock: " << clock
                        << ", corrector: " << corrector

                        << "; color: r"
                        << static_cast<int>(color.GetR()) << ", g"
                        << static_cast<int>(color.GetG()) << ", b"
                        << static_cast<int>(color.GetB()) << ", a"
                        << static_cast<int>(color.GetA()) << " ";

                    auto rect = CRectangle(33, 393, 55, 55);
                    CText text(font, outstring.str(), color);
                    text.RenderPut(parent.GetCanvas(), rect);
                }

            }

            //pChild->GetCanvas()->SetColorKey(color);
        }

        const int varX = 1;
        //CPoint lastPos = pChild->GetPosition();
        //pChild->SetPosition(CPoint(lastPos.GetX() + (varX - sin(m_pHost->m_iTicks / 6.0f) * 4),
        // lastPos.GetY()));
        //pChild->Draw();
        //pChild->SetPosition(lastPos);
        //param.SetDrawn(true);

        CColor sdl_color = CColor::DarkMagenta();
        pChild->GetCanvas()->RenderFillRect(CRectangle(333 + x, 333, 55, 55), &sdl_color);
    } // ()
};

