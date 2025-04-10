#pragma once

#include "Card.h"
#include <list>

namespace solitaire
{
    class GameLogic
    {
        // 8 x 5 grid of cards
        const int BOARD_ROWS = 8;
        const int BOARD_COLS = 5;
        const Gdiplus::RectF mCountRect { 885.f, 60.f, 120.f,122.f};

    private:
        std::unique_ptr<Gdiplus::Image> mBackground;
        std::list<Card> mDeck;

        int mFlipCount{}; 
    public:
        void Init();
        void Release();
        void Draw(Gdiplus::Graphics& graphics);
        void OnClick(int x, int y);
        // card area - 885.f x 60.f x 120.f x 30.f
    private:
        void CreateCard(); 

        
    };
}
