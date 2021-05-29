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
               int vx = 9,  int vy = 3,
               int dt = 2);
void Ball (int x, int y, int radius, const char text[],int Red = 0, int Green = 0, int Blue = 0);


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
               int  x,  int  y,
               int vx,  int vy,
               int dt)
    {

    int allIndentBall_1 = indent + borderSize + 16;
    int allIndentBall_2 = indent + borderSize + 21;

    int xBall_1  = x,        yBall_1  = y,       dtBall_1 = dt + 5, vxBall_1 =  vx, vyBall_1 =  vy;
    int xBall_2  = x + 600,  yBall_2  = y + 650, dtBall_2 = dt,     vxBall_2 = -vx, vyBall_2 =  -vy;

    while (! txGetAsyncKeyState (VK_ESCAPE))
        {
        Ball (xBall_1, yBall_1, 20, "1", 10, x+20, 10);
        Ball (xBall_2, yBall_2, 30, "2", y+20, 10, y+20);
        printf("x= %d  y= %d\n", x, y);

        xBall_1 += vxBall_1 * dtBall_1;
        yBall_1 += vyBall_1 * dtBall_1;

        xBall_2 += vxBall_2 * dtBall_2;
        yBall_2 += vyBall_2 * dtBall_2;

        if (xBall_1 > 1200 - allIndentBall_1)
            {
            vxBall_1 = -vxBall_1;
            xBall_1  = 1200 - allIndentBall_1;
            }

        if (yBall_1 >  700 - allIndentBall_1)
            {
            vyBall_1 = -vyBall_1;
            yBall_1  = 700 - allIndentBall_1;
            }

        if (xBall_1 <  0 + allIndentBall_1)
            {
            vxBall_1 = -vxBall_1;
            xBall_1  = 0 + allIndentBall_1;
            }

        if (yBall_1 <  0 + allIndentBall_1)
            {
            vyBall_1 = -vyBall_1;
            yBall_1  = 0 + allIndentBall_1;
            }

        //----------------
        if (xBall_2 > 1200 - allIndentBall_2)
            {
            vxBall_2 = -vxBall_2;
            xBall_2  = 1200 - allIndentBall_2;
            }

        if (yBall_2 >  700 - allIndentBall_2)
            {
            vyBall_2 = -vyBall_2;
            yBall_2  = 700 - allIndentBall_2;
            }

        if (xBall_2 <  0 + allIndentBall_2)
            {
            vxBall_2 = -vxBall_2;
            xBall_2  = 0 + allIndentBall_2;
            }

        if (yBall_2 <  0 + allIndentBall_2)
            {
            vyBall_2 = -vyBall_2;
            yBall_2  = 0 + allIndentBall_2;
            }

        //----------------
        int dR = (xBall_2 - xBall_1)*(xBall_2 - xBall_1) + (yBall_2 - yBall_1)*(yBall_2 - yBall_1);

        if (dR <= 50*50)
            {
            vxBall_1 = -vxBall_1;
            vyBall_1 = -vyBall_1;
            x += 10;

            vxBall_2 = -vxBall_2;
            vyBall_2 = -vyBall_2;
            y += 20;

            }


        txSleep(100);
        Field (indent, borderSize, TX_ORANGE);
        }

    }
//-----------------------------------------------------------------------------
void Ball (int x, int y, int radius, const char text[], int Red, int Green, int Blue)
    {
    txSetColor (TX_LIGHTGREEN, 2);
    txSetFillColor (RGB(255 - Red, 255 - Green, 255 - Blue));
    txCircle (x, y, radius);

    txSelectFont ("Arial", radius, radius/4*3, true);
    txSetColor (TX_BLACK);
    txTextOut (x-radius/2, y-radius/2, text);
    }
