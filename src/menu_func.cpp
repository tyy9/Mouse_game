#include "menu_func.h"
void Button_Direct(int x, int y, Mouse &head)
{
    
    // 方向键判断
    // 上下
    if (x > 655 && x <= 705)
    {
        if (y > 335 && y <= 385)
        {
            sign = "up";
            cout<<sign<<endl;
            // try
            // {
            //     head + sign;
            // }
            // catch (exception &e)
            // {
            //     e.what();
            // }
            head.show();
        }
        if (y > 385 && y <= 435)
        {
            sign = "below";
            cout<<sign<<endl;
            // try
            // {
            //     head + sign;
            // }
            // catch (exception &e)
            // {
            //     e.what();
            // }
            head.show();
        }
    }
    // 左
    if (x > 605 && x <= 655)
    {
        if (y > 385 && y <= 435)
        {
            sign = "left";
            cout<<sign<<endl;
            // try
            // {
            //     head + sign;
            // }
            // catch (exception &e)
            // {
            //     e.what();
            // }
            head.show();
        }
    }
    // 右
    if (x > 705 && x <= 755)
    {
        if (y > 385 && y <= 435)
        {
            sign = "right";
            cout<<sign<<endl;
            // try
            // {
            //     head + sign;
            // }
            // catch (exception &e)
            // {
            //     e.what();
            // }
            head.show();
        }
    }
}