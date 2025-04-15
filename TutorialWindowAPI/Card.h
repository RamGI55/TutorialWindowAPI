
// This is for the tutorial project of thd Windows API.

// Created by : RamGi

// Created Date : Mar. 26, 2025. 

#pragma once

#include <Windows.h>
#include<gdiplus.h>
#include <memory>

namespace solitaire
{
    enum class Type
    {
        Belka,
        Klukai,
        Mechty,
        Andoris
    };
    // Types of the cards. 

    class Card
    {
    private: 
        // back and front image
        std::unique_ptr<Gdiplus::Image> mBack;
        std::unique_ptr<Gdiplus::Image> mFront;
            // using smarter pointer to avoid memory leak.
        HWND mHwnd;
        int mIndex; 
        // size of the card - x y
        int mX;
        int mY;
        // check if it is front.
        bool isFront;
        Type mType;
        // type of the card
    
    public:
        // Constructor of the card - Type, x, y
        Card(HWND hwnd, int index, Type type, int x, int y); 
        // bool for checking it is clicked or not.
        bool isClicked(int x, int y); 
        // fliping logic
        void flipCard(bool isfront); 
        // drawing the card
        void Draw(Gdiplus::Graphics& graphics);
        // invalidate the card for drawing the front.
        void Invalidate();

        Type GetType() {return mType;}
        int GetIndex() {return mIndex;}
    };
}
