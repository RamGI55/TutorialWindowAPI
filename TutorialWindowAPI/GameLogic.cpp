#include "GameLogic.h"
#include <string>

namespace solitaire
{
    void GameLogic::Init()
    {
        mBackground = std::make_unique<Gdiplus::Image>(L"404Background.png");
        CreateCard(); 
    }

    void GameLogic::Release()
    {
        mDeck.clear();

        mBackground.reset();
    }

    void GameLogic::Draw(Gdiplus::Graphics& graphics)
    {
        graphics.DrawImage(mBackground.get(), 0, 0, mBackground->GetWidth(), mBackground->GetHeight());

        for (auto& card: mDeck)
        {
            card.Draw(graphics); 
        }

        Gdiplus::PointF pos(895.f, 20.f);
        
        Gdiplus::SolidBrush brush(Gdiplus::Color (255,79, 64)); 
        Gdiplus::Font font (L"Microsoft Sans Serif", 20);

        graphics.DrawString(L"# of Clicks: ", -1, &font, pos, &brush);
        Gdiplus::StringFormat format;

        format.SetAlignment(Gdiplus::StringAlignmentCenter);
        format.SetAlignment(Gdiplus::StringAlignmentCenter);
        graphics.DrawString(std::to_wstring(mFlipCount).c_str(), -1, &font, mCountRect, &format, &brush);
        
    }

    void GameLogic::OnClick(int x, int y)
    {
        for (auto& card: mDeck)
        {
            if (card.isClicked(x,y))
            {
                // todo
            }
        }
    }

    void GameLogic::CreateCard()
    {
        // todo
        mDeck.push_back(solitaire::Card(solitaire::Type::Andoris, 0, 0));
        mDeck.push_back(solitaire::Card(solitaire::Type::Belka, 250, 0));
        mDeck.push_back(solitaire::Card(solitaire::Type::Klukai,  550, 0));
        mDeck.push_back(solitaire::Card(solitaire::Type::Mechty, 750, 0));
    
    }
}
