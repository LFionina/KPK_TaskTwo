//{===========================================================================
//! @file       LFionina_TaskTwo.cpp
//!
//! @brief      Программируем движение шарика
//!
//!               $Date: 2021-05-29 $
//          (C) Фионина Людмила Евгеньевна, г. Самара, 2021
//}===========================================================================

# include "TXLib.h"
# include <stdlib.h>

void Field (int indent, int borderSize, COLORREF colorBorder);
void MoveBall (int indent,  int borderSize,
               int x = 300, int y = 100,
               int vx = 7,  int vy = 3,
               int dt = 2);
void Ball (int x, int y, int radius, const char text[]);


//===========================================================================
int main ()
    {
    txCreateWindow (1200, 700);

    int indent = 50, borderSize = 10;
    Field (indent, borderSize, TX_ORANGE);

    MoveBall (indent, borderSize);

    return 0;
    }

//-----------------------------------------------------------------------------
void Field (int indent, int borderSize, COLORREF colorBorder)
    {
    txSetFillColor (TX_WHITE);
    txClear();

    txSetColor (colorBorder, borderSize);
    txSetFillColor (RGB(0, 80, 0));
    txRectangle (0 + indent, 0 + indent, 1200 - indent, 700 - indent);

    }

//-----------------------------------------------------------------------------
void MoveBall (int indent,  int borderSize,
               int x, int y,
               int vx,  int vy,
               int dt)
    {

    int allIndent = indent + borderSize + 16;

    while (! txGetAsyncKeyState (VK_ESCAPE))
        {
        Ball (x, y, 20, "1");

        x += vx * dt;
        y += vy * dt;

        if (x > 1200 - allIndent)
            {
            vx = -vx;
            x = 1200 - allIndent;
            }

        if (y >  700 - allIndent)
            {
            vy = -vy;
            y =  700 - allIndent;
            }

        if (x <    0 + allIndent)
            {
            vx = -vx;
            x =    0 + allIndent;
            }

        if (y <    0 + allIndent)
            {
            vy = -vy;
            y =    0 + allIndent;
            }

        txSleep(100);
        Field (indent, borderSize, TX_ORANGE);
        }

    }
//-----------------------------------------------------------------------------
void Ball (int x, int y, int radius, const char text[])
    {
    txSetColor (TX_LIGHTGREEN, 2);
    txSetFillColor (TX_WHITE);
    txCircle (x, y, radius);

    txSelectFont ("Arial", radius, radius/4*3, true);
    txSetColor (TX_BLACK);
    txTextOut (x-radius/2, y-radius/2, text);
    }
