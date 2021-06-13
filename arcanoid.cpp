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

# include "ArcanoidSDK\ArcanoidLib.h"

struct Ball
    {
    double x, y;
    int radius ;
    COLORREF color;
    };

void Draw_Ball  (Ball proba);
void ControlTruck (double* xTruck, double* widthX);
void MoveBall ();

void PhysicsBall (Ball* proba,
                  double* vxBall, double* vyBall,
                  int dtBall,
                  double* xTruck, double* widthX,
                  int* score);

void TabloScore (int* score);



//-----------------------------------------------------------------------------
int main ()
    {
    txCreateWindow (500, 700);

    DrawField ();

    MoveBall ();
    return 0;
    }


//------------------- Ф У Н К Ц И И     Р И С О В А Н И Я ---------------------


//-----------------------------------------------------------------------------
void Draw_Ball (Ball proba)
    {
    txSetColor (proba.color);
    txSetFillColor (proba.color);
    txCircle (proba.x, proba.y - proba.radius, proba.radius);
    }



//------------------- Ф У Н К Ц И И     У П Р А В Л Е Н И Я -------------------
//-----------------------------------------------------------------------------
void ControlTruck (double* xTruck, double* widthX)
    {
    //---- управление cкоростью 1 шарика----
    if (txGetAsyncKeyState (VK_RIGHT) and *xTruck + *widthX < txGetExtentX ()) (*xTruck) += 5;
    if (txGetAsyncKeyState (VK_LEFT)  and *xTruck > 0                        ) (*xTruck) -= 5;
    if (txGetAsyncKeyState (VK_UP)                                           ) (*widthX) += 10;
    if (txGetAsyncKeyState (VK_DOWN)                                         ) (*widthX) -= 10;
    }


//------------------- Ф У Н К Ц И Я      И Г Р ы ------------------------------
//-----------------------------------------------------------------------------
void MoveBall ()
    {

    double xTruck = 0;
    double widthX = txGetExtentX ()*0.25 + 20;

    double  vxBall_1 =   1, vyBall_1 =   1, dtBall_1 = 10;

    Ball proba = {100, 600, 10, TX_BLUE};

    int score = 0;

    while (proba.y < 999)
        {
        DrawTruck (xTruck, widthX);

        Draw_Ball (proba);

        PhysicsBall (&proba, &vxBall_1, &vyBall_1, dtBall_1, &xTruck, &widthX, &score);

        ControlTruck (&xTruck, &widthX);

        txSleep(20);
        DrawField ();

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
void PhysicsBall (Ball* proba,
                  double* vxBall, double* vyBall,
                  int dtBall,
                  double* xTruck, double *widthX,
                  int* score)
    {
    proba->x = proba->x + (*vxBall) * dtBall;
    proba->y = proba->y + (*vyBall) * dtBall;

    if (proba->x > txGetExtentX() - 10)
        {
        *vxBall = -(*vxBall);
        proba->x  = txGetExtentX() - 10;
        txPlaySound ("Sounds/ball1.wav");
        }

    if (proba->x < 10)
        {
        *vxBall = -(*vxBall);
        proba->x  = 10;
        txPlaySound ("Sounds/ball1.wav");
        }

    if (proba->y < 120)
        {
        *vyBall = -(*vyBall);
        proba->y  = 120;
        txPlaySound ("Sounds/ball1.wav");
        }

    if (proba->y >  txGetExtentY() - 80 - 20)
        {
        switch (proba->x > *xTruck && proba->x < *xTruck + *widthX)
            {
            case true:
                if (proba->x < *xTruck + *widthX/2)
                    {
                    *vyBall = -(*vyBall);
                    *vxBall = *vxBall + 0.1;
                    proba->y  = txGetExtentY() - 80 - 20;
                    *score  = *score + 1;
                    txPlaySound ("Sounds/ball1.wav");
                    }
                else
                    {
                    *vyBall = -(*vyBall);
                    *vxBall = *vxBall - 0.1;
                    proba->y  = txGetExtentY() - 80 - 20;
                    *score  = *score + 1;
                    txPlaySound ("Sounds/ball1.wav");
                    }
                break;

            case false:
                proba->y  = 1000;
                txPlaySound ("Sounds/gameOver.wav");
                break;

            default:
                break;
            }

        }
    }
