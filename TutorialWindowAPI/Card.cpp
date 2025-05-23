﻿
// This is for the tutorial project of thd Windows API.

// Created by : RamGi

// Created Date : Mar. 26, 2025. 

#include "Card.h"
#include <string>

namespace solitaire
{
    solitaire::Card::Card(HWND hwnd, int index, Type type, int x, int y):
    mHwnd(hwnd), mIndex(index), mType(type), mX (x), mY (y), isFront (false)
    {
        // initialise the status of the card. type, x, y and front status.
        std::wstring filename;    
            // Switch function each types of the card (Wolf, Dragon , Bear)
        switch (mType)
        {
        case Type::Andoris:
            filename = L"404Andoris.png";
            break;
           
        case Type::Belka:
            filename = L"404Belka.png";
            break;
          
        case Type::Klukai:
            filename = L"404Klukai.png";
            break; 

        case Type::Mechty:
            filename = L"404Mechty.png";
            break;
          
        }
        mBack = std::make_unique<Gdiplus::Image>(L"404back.png");
        mFront = std::make_unique<Gdiplus::Image>(filename.c_str()); 
        // initialise the back and front image of the card as dynamic memory. (we used the smarter pointer) 
    }

    bool solitaire::Card::isClicked(int x, int y)
    {
        /*if (x >= mX && y >= mY && static_cast <UINT>(x) <=mX + mFront ->GetWidth() &&
            static_cast<UINT>(y) <=mY + mFront ->GetHeight())*/ // this if sentence is no longer needed if you use Rect. 
        Gdiplus::Rect rct (mX, mY, mFront->GetWidth(), mFront->GetHeight()); // Rect function can verify the area of the windows.
        if (rct.Contains(x, y))
        {
            flipCard(!isFront);
            return true;
        }
        
        // Always false unless the card has been clicked. 
        return false; 
    }

    void solitaire::Card::flipCard(bool inisfront)
    {
        // show the front image of the card.
        isFront = inisfront;
        Invalidate();
    }

    void solitaire::Card::Draw(Gdiplus::Graphics& graphics) 
    {
        if (isFront)
        {
            graphics.DrawImage(
                mFront.get(), mX, mY, mFront->GetWidth(), mFront->GetHeight());
        }
        else
        {
            graphics.DrawImage(
                mBack.get(), mX, mY, mBack->GetWidth(), mBack->GetHeight());
        }
        // if it is front, draw the front image of the card.

        // otherwise, draw the back image of the card. 
    }

    void Card::Invalidate()
    {
        RECT rect{mX, mY,
        static_cast<LONG> (mX+ mBack->GetWidth()),
        static_cast<LONG> (mY+ mBack->GetHeight())};

        InvalidateRect(mHwnd, &rect, false);
    }
    
}

