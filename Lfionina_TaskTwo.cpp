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

void BallDraw (int x, int y, int radius, const char text[],int Red = 0, int Green = 0, int Blue = 0);

void PhysicsBall (int* xBall, int* yBall, int* vxBall, int* vyBall, int dtBall, int allIndentBall);

void ControlBallOne (int* dtBall_1);
void ControlBallTwo (int* dtBall);

//===========================================================================
int main ()
    {
    txCreateWindow (1200, 700);

    int indent = 50, borderSize = 10;
    Field (indent, borderSize, TX_ORANGE);

    MoveBall (indent, borderSize);

    return 0;
    }

//{-----------------------------------------------------------------------------
//!   Функция рисования бильярдного поля
//!
//!@param indent        - отступ от края окна
//!@param borderSize    - ширина бортика прямоугольного поля
//!@param colorBorder   - цвет бортика прямоугольного поля
//!
//!@par  Пример использования:
//!@code
//!         Field (50, 15, TX_ORANGE);
//!@endcode
//}-----------------------------------------------------------------------------

void Field (int indent, int borderSize, COLORREF colorBorder)
    {
    txSetFillColor (TX_WHITE);
    txClear();

    txSetColor (colorBorder, borderSize);
    txSetFillColor (RGB(0, 80, 0));
    txRectangle (0 + indent, 0 + indent, 1200 - indent, 700 - indent);

    }

//-----------------------------------------------------------------------------
void MoveBall (int indent,  int borderSize, int x, int y, int vx,  int vy, int dt)
    {

    int allIndentBall_1 = indent + borderSize + 16;
    int allIndentBall_2 = indent + borderSize + 21;

    int xBall_1  = x,       yBall_1  = y,       dtBall_1 = dt + 5, vxBall_1 =  vx, vyBall_1 =  vy;
    int xBall_2  = x + 600, yBall_2  = y + 650, dtBall_2 = dt,     vxBall_2 = -vx, vyBall_2 = -vy;

    int Red   = rand() % 255, Green = rand() % 255, Blue  = rand() % 255;


    while (! txGetAsyncKeyState (VK_ESCAPE))
        {
        BallDraw (xBall_1, yBall_1, 20, "1", Red, Green, Blue);
        BallDraw (xBall_2, yBall_2, 30, "2", Blue, Green, Red);

        PhysicsBall (&xBall_1, &yBall_1, &vxBall_1, &vyBall_1, dtBall_1, allIndentBall_1);
        PhysicsBall (&xBall_2, &yBall_2, &vxBall_2, &vyBall_2, dtBall_2, allIndentBall_2);

        //-----------столкновение-----
        int dR = (xBall_2 - xBall_1)*(xBall_2 - xBall_1) + (yBall_2 - yBall_1)*(yBall_2 - yBall_1);

        if (dR <= 50*50)
            {
            vxBall_1 = -vxBall_1;
            vyBall_1 = -vyBall_1;

            vxBall_2 = -vxBall_2;
            vyBall_2 = -vyBall_2;

            Red   = rand() % 255;
            Green = rand() % 255;
            Blue  = rand() % 255;

            }

   //     ControlBallOne (&dtBall_1);
        ControlBallTwo (&dtBall_2);

        txSleep(100);
        Field (indent, borderSize, TX_ORANGE);
        }

    }
//-----------------------------------------------------------------------------
void ControlBallTwo (int* dtBall)
    {
    //---- управление cкоростью 2 шарика----
    if (txGetAsyncKeyState ('A')) (*dtBall)++;
    if (txGetAsyncKeyState ('D')) (*dtBall)--;
    }

//-----------------------------------------------------------------------------
/*void ControlBallOne (int* dtBall)
    {
    //---- управление cкоростью 1 шарика----
    if (txGetAsyncKeyState (VK_RIGHT)) (*dtBall)++;
    if (txGetAsyncKeyState (VK_LEFT))  (*dtBall)--;
    }
*/
//-----------------------------------------------------------------------------
void BallDraw (int x, int y, int radius, const char text[], int Red, int Green, int Blue)
    {
    txSetColor (TX_LIGHTGREEN, 2);
    txSetFillColor (RGB(255 - Red, 255 - Green, 255 - Blue));
    txCircle (x, y, radius);

    txSelectFont ("Arial", radius, radius/4*3, true);
    txSetColor (TX_BLACK);
    txTextOut (x-radius/2, y-radius/2, text);
    }

//-----------------------------------------------------------------------------
void PhysicsBall (int* xBall, int* yBall, int* vxBall, int* vyBall, int dtBall, int allIndentBall)
    {
    *xBall = *xBall + (*vxBall) * dtBall;
    *yBall = *yBall + (*vyBall) * dtBall;

    if (*xBall > 1200 - allIndentBall)
        {
        *vxBall = -(*vxBall);
        *xBall  = 1200 - allIndentBall;
        }

    if (*yBall >  700 - allIndentBall)
        {
        *vyBall = -(*vyBall);
        *yBall  = 700 - allIndentBall;
        }

    if (*xBall <  0 + allIndentBall)
        {
        *vxBall = -(*vxBall);
        *xBall  = 0 + allIndentBall;
        }

    if (*yBall <  0 + allIndentBall)
        {
        *vyBall = -(*vyBall);
        *yBall  = 0 + allIndentBall;
        }
    }
