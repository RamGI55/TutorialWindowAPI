
// This is for the tutorial project of thd Windows API.

// Created by : RamGi

// Created Date : Mar. 26, 2025. 

#include "Card.h"

solitaire::Card::Card(Type type, int x, int y):
mType(type), mX (x), mY (y), isFront (false)
{
    // initialise the status of the card. type, x, y and front status.
  
        // Switch function each types of the card (Wolf, Dragon , Bear)
    switch (type)
    {
        // Wolf

        // dragon

        // bear
    }
    // initialise the back and front image of the card as dynamic memory. (we used the smarter pointer) 
    
}

bool solitaire::Card::isClicked(int x, int y)
{
    // Always false unless the card has been clicked. 
    return false; 
}

void solitaire::Card::flipCard(bool isfront)
{
    // show the front image of the card. 
}

void solitaire::Card::Draw(Gdiplus::Graphics& graphics) 
{
    // if it is front, draw the front image of the card.

    // otherwise, draw the back image of the card. 
}
