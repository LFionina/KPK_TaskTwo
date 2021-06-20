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

    double vx, vy, dt;

    void Draw ();
    };

struct Truck
    {
    double x;
    double widthX;

    COLORREF color;

    void Draw ();
    void Control ();
    };

//-------------------   Ф У Н К Ц И И    К Л А С С О В    ---------------------

//- - - - - - - - - - - - рисование шарика  - - - - - - - - - - - - - - - - - -
void Ball::Draw ()
    {
    txSetColor     (color);
    txSetFillColor (color);
    txCircle (x, y - radius, radius);
    }

//- - - - - - - - - - - - рисование тележки - - - - - - - - - - - - - - - - - -
void Truck::Draw ()
    {
    txSetColor     (color);
    txSetFillColor (color);
    txRectangle (x, txGetExtentY() - 80 - 20, x + widthX, txGetExtentY() - 80 - 5);
    }

//- - - - - - - - - - - - управление тележкой - - - - - - - - - - - - - - - - -
void Truck::Control ()
    {
    if (txGetAsyncKeyState (VK_RIGHT) and (*this).x + (*this).widthX < txGetExtentX ()) (*this).x += 5;
    if (txGetAsyncKeyState (VK_LEFT ) and (*this).x > 0                               ) (*this).x -= 5;
    if (txGetAsyncKeyState (VK_UP   )                                                 ) (*this).widthX += 10;
    if (txGetAsyncKeyState (VK_DOWN )                                                 ) (*this).widthX -= 10;
    }


void MoveBall ();

void PhysicsBall  (Ball* proba, double x, double widthX,
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


//------------------- Ф У Н К Ц И Я      И Г Р ы ------------------------------
//-----------------------------------------------------------------------------
void MoveBall ()
    {
    Truck truckOne = {0, txGetExtentX ()*0.25 + 20, RGB( 0, 204, 0)};
    Ball proba = {100, 600, 10, TX_BLUE, 1, 1, 10};

    int score = 0;

    while (proba.y < 999)
        {
        proba.Draw ();
        truckOne.Draw ();

        PhysicsBall (&proba, truckOne.x, truckOne.widthX, &score);

        truckOne.Control ();

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
void PhysicsBall (Ball* proba, double x, double widthX, int* score)
    {
    proba->x = proba->x + proba->vx * proba->dt;
    proba->y = proba->y + proba->vy * proba->dt;

    if (proba->x > txGetExtentX() - 10)
        {
        proba->vx = -(proba->vx);
        proba->x  = txGetExtentX() - 10;
        txPlaySound ("Sounds/ball1.wav");
        }

    if (proba->x < 10)
        {
        proba->vx = -(proba->vx);
        proba->x  = 10;
        txPlaySound ("Sounds/ball1.wav");
        }

    if (proba->y < 120)
        {
        proba->vy = -(proba->vy);
        proba->y  = 120;
        txPlaySound ("Sounds/ball1.wav");
        }

    if (proba->y >  txGetExtentY() - 80 - 20)
        {
        switch (proba->x > x && proba->x < x + widthX)
            {
            case true:
                if (proba->x < x + widthX/2)
                    {
                    proba->vy = -(proba->vy);
                    proba->vx =   proba->vx + 0.1;
                    proba->y  = txGetExtentY() - 80 - 20;
                    *score  = *score + 1;
                    txPlaySound ("Sounds/ball1.wav");
                    }
                else
                    {
                    proba->vy = -(proba->vy);
                    proba->vx =   proba->vx - 0.1;
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
