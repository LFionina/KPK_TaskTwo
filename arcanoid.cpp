//{===========================================================================
//! @file       arkanoid.cpp
//!
//! @brief
//!
//!               $Date: 2021-06-02 $
//          (C) Фионина Людмила Евгеньевна, г. Самара, 2021
//}===========================================================================

# include "TXLib.h"
# include <stdlib.h>

void Draw_Field ();
void Draw_Truck (double x, double widthX);
void Draw_Ball  (double x, double y, int radius, COLORREF color);

void ControlTruck (double* xTruck, double* widthX);
void MoveBall ();

void PhysicsBall (double*  xBall, double*  yBall,
                  double* vxBall, double* vyBall,
                  int dtBall,
                  double* xTruck, double* widthX,
                  int* score);

void TabloScore (int* score);
void TabloBottom ();

//-----------------------------------------------------------------------------
int main ()
    {
    txCreateWindow (500, 700);

    Draw_Field ();

    MoveBall ();
    return 0;
    }




//------------------- Ф У Н К Ц И И     Р И С О В А Н И Я ---------------------
//-----------------------------------------------------------------------------
void Draw_Field ()
    {
    txSetFillColor (TX_WHITE);
    txClear();

    txSetColor     (RGB(153, 102, 255));
    txSetFillColor (RGB(153, 102, 255));
    txRectangle (0,                   0, txGetExtentX(),           100);
    txRectangle (0, txGetExtentY() - 80, txGetExtentX(), txGetExtentY());
    }

//-----------------------------------------------------------------------------
void Draw_Truck (double x, double widthX)
    {
    txSetColor     (RGB(10, 150, 10));
    txSetFillColor (RGB( 0, 204,  0));
    txRectangle (x, txGetExtentY() - 80 - 20, x + widthX, txGetExtentY() - 80 - 5);
    }

//-----------------------------------------------------------------------------
void Draw_Ball (double x, double y, int radius, COLORREF color)
    {
    txSetColor (color);
    txSetFillColor (color);
    txCircle (x, y - radius, radius);
    }

//------------------- Ф У Н К Ц И И     У П Р А В Л Е Н И Я -------------------
//-----------------------------------------------------------------------------
void ControlTruck (double* xTruck, double* widthX)
    {
    //---- управление cкоростью 1 шарика----
    if (txGetAsyncKeyState (VK_RIGHT) and *xTruck + *widthX < txGetExtentX ()) (*xTruck) += 5;
    if (txGetAsyncKeyState (VK_LEFT)  and *xTruck > 0                        ) (*xTruck) -= 5;
    if (txGetAsyncKeyState (VK_UP)                                           ) (*widthX) += 10;
    if (txGetAsyncKeyState (VK_DOWN)                                       ) (*widthX) -= 10;
    }


//------------------- Ф У Н К Ц И Я      И Г Р ы ------------------------------
//-----------------------------------------------------------------------------
void MoveBall ()
    {

    double xTruck = 0;
    double widthX = txGetExtentX ()*0.25 + 20;

    double  xBall_1 = 100,  yBall_1 = 600,
           vxBall_1 =   1, vyBall_1 =   1, dtBall_1 = 10;

    int score = 0;

    while (yBall_1 < 999)
        {
        Draw_Truck (xTruck, widthX);

        Draw_Ball  (xBall_1, yBall_1, 10, TX_BLUE);


        PhysicsBall (&xBall_1, &yBall_1, &vxBall_1, &vyBall_1, dtBall_1, &xTruck, &widthX, &score);

        ControlTruck (&xTruck, &widthX);

        txSleep(20);
        Draw_Field ();

        TabloScore (&score);
        TabloBottom ();
        }

    txSetColor(TX_MAGENTA);
    txSelectFont ("Arial Black", 70);
    txTextOut (100, 350, "GAME OVER");

    }

//-----------------------------------------------------------------------------
void TabloScore (int* score)
    {
    txSetColor(TX_WHITE);
    txSelectFont ("Arial Black", 30);
    txTextOut (50, 25, "ОЧКИ : ");

    char strScore [20] = "";
    sprintf (strScore, "%d", *score);

    txSetColor(TX_YELLOW);
    txSelectFont ("Arial Black", 30);
    txTextOut (150, 25, strScore);
    }

//-----------------------------------------------------------------------------
void TabloBottom ()
    {
    txSetColor(TX_WHITE);
    txSelectFont ("Arial Black", 30);
    txTextOut (50, 640, "<=  влево");
    txTextOut (350, 640, "вправо  =>");
    txTextOut (215, 640, "ширина");

    txSelectFont ("Arial Black", 20);
    txTextOut (235, 625, "вверх +");
    txTextOut (235, 665, "вниз  -");

    }

//-----------------------------------------------------------------------------
void PhysicsBall (double*  xBall, double*  yBall,
                  double* vxBall, double* vyBall,
                  int dtBall,
                  double* xTruck, double *widthX,
                  int* score)
    {
    *xBall = *xBall + (*vxBall) * dtBall;
    *yBall = *yBall + (*vyBall) * dtBall;

    if (*xBall > txGetExtentX() - 10)
        {
        *vxBall = -(*vxBall);
        *xBall  = txGetExtentX() - 10;
        }

    if (*xBall < 10)
        {
        *vxBall = -(*vxBall);
        *xBall  = 10;
        }

    if (*yBall < 120)
        {
        *vyBall = -(*vyBall);
        *yBall  = 120;
        }

    if (*yBall >  txGetExtentY() - 80 - 20)
        {
        switch (*xBall > *xTruck && *xBall < *xTruck + *widthX)
            {
            case true:
                if (*xBall < *xTruck + *widthX/2)
                    {
                    *vyBall = -(*vyBall);
                    *vxBall = *vxBall + 0.1;
                    *yBall  = txGetExtentY() - 80 - 20;
                    *score  = *score + 1;
                    }
                else
                    {
                    *vyBall = -(*vyBall);
                    *vxBall = *vxBall - 0.1;
                    *yBall  = txGetExtentY() - 80 - 20;
                    *score  = *score + 1;
                    }
                break;

            case false:
                *yBall  = 1000;
                break;

            default:
                break;
            }

        }
    }
