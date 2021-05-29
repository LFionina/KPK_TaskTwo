# KPK_TaskTwo
Курсы повышения квалификации  по проектному программированию на языке С++

#  ПРОЕКТ 2.  КОМПЬЮТЕРНАЯ ИГРА.
--------------------------------------------------------------------------

## Задание 1. Движение бильярдного шарика по полю.

В программе рисуется бильярдное поле с указанными размерами и заданной границей.
>void Field (int indent, int borderSize, COLORREF colorBorder)
>    {
>    txSetFillColor (TX_WHITE);
>    txClear();
>
>    txSetColor (colorBorder, borderSize);
>    txSetFillColor (RGB(0, 80, 0));
>    txRectangle (0 + indent, 0 + indent, 1200 - indent, 700 - indent);
>    }