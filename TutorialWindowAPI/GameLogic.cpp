#include "GameLogic.h"
#include <string>
#include <vector>
#include <random>

namespace solitaire
{
    void GameLogic::Init(HWND hwnd)
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
        // graphics.DrawImage(mBackground.get(), 0, 0, mBackground->GetWidth(), mBackground->GetHeight());

        for (auto& card: mDeck)
        {
            card.Draw(graphics); 
        }

        Gdiplus::PointF pos(1300.f, 20.f);
        
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
        Card *pCard {}; 
        for (auto& card: mDeck)
        {
            if (card.isClicked(x,y))
            {
                pCard = &card;
                break; 
            }
        }

        if (pCard)
        {
            mFlipCount++;
            RECT rct = {static_cast<LONG> (mCountRect.GetLeft()),
            static_cast<LONG> (mCountRect.GetTop()),
            static_cast<LONG> (mCountRect.GetRight()),
            static_cast<LONG> (mCountRect.GetBottom())};
            InvalidateRect(mHwnd, &rct, false);

            if (mpSelectedCard == nullptr)
            {
                mpSelectedCard = pCard;
            }
            else
            {
                if (mpSelectedCard == pCard)
                    mpSelectedCard = nullptr;
                else
                {
                    if (pCard->GetType() == mpSelectedCard->GetType())
                    {
                        pCard->Invalidate();
                        mpSelectedCard->Invalidate();

                        mDeck.remove_if( [&](Card& card) {return card.GetIndex() == mpSelectedCard->GetIndex();} );
                        mDeck.remove_if([&](Card& card) {return card.GetIndex() == pCard->GetIndex();} );
                        mpSelectedCard = nullptr;
                    }
                    else
                    {
                        UpdateWindow(mHwnd);
                        Sleep(500);
                        pCard->flipCard(false);
                        mpSelectedCard->flipCard(false);

                        mpSelectedCard = nullptr;
                    }
                }
            }
        }
    }

    void GameLogic::CreateCard()
    {
        std::vector<Type> types;
        while (types.size() < static_cast<size_t> (BOARD_COLS * BOARD_ROWS))
        {
            int modulator = types.size() % 8;
            switch (modulator)
            {
            case 0:
                types.push_back(Type::Andoris);
                types.push_back(Type::Andoris);
                break;
            case 2:
                types.push_back(Type::Belka);
                types.push_back(Type::Belka);
                break;
            case 4:
                types.push_back(Type::Klukai);
                types.push_back(Type::Klukai);
                break;
            case 6:
                types.push_back(Type::Mechty);
                types.push_back(Type::Mechty);
                break;
            }
        }
        std::random_device rd;
        std::mt19937 gen(rd());

        std::shuffle(types.begin(), types.end(), gen);

        
        int posX { 15 }, posY { 10 };
        int index = 0;

        for (int x = 0 ; x <BOARD_ROWS; ++x)
        {
            posY = 10;
            for (int y = 0 ; y <BOARD_COLS; ++y)
            {
                mDeck.push_back(Card(mHwnd, index, types[index++], posX , posY ));
                posY += 150 + 10; 
            }
            posX += 150 + 10;
        }
    }
}
