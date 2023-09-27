#include "menu_func.h"
void Button_Direct(int x, int y)
{

    // 方向键判断
    // 上下
    if (x > 665 && x <= 725)
    {
        if (y > 335 && y <= 385)
        {
            sign = "up";
            cout << sign << endl;

            lcd_draw_img_jpeg(665, 335, "./img_resource/button_up_active.jpg");
            usleep(100 * 1000);
            lcd_draw_img_jpeg(665, 335, "./img_resource/button_up.jpg");
            head.show();
        }
        if (y > 385 && y <= 435)
        {
            sign = "below";
            cout << sign << endl;

            lcd_draw_img_jpeg(665, 385, "./img_resource/button_below_active.jpg");
            usleep(100 * 1000);
            lcd_draw_img_jpeg(665, 385, "./img_resource/button_below.jpg");
            head.show();
        }
    }
    // 左
    if (x > 605 && x <= 665)
    {
        if (y > 385 && y <= 435)
        {
            sign = "left";
            cout << sign << endl;

            lcd_draw_img_jpeg(605, 385, "./img_resource/button_left_active.jpg");
            usleep(100 * 1000);
            lcd_draw_img_jpeg(605, 385, "./img_resource/button_left.jpg");
            head.show();
        }
    }
    // 右
    if (x > 725 && x <= 785)
    {
        if (y > 385 && y <= 435)
        {
            sign = "right";
            cout << sign << endl;

            lcd_draw_img_jpeg(725, 385, "./img_resource/button_right_active.jpg");
            usleep(100 * 1000);
            lcd_draw_img_jpeg(725, 385, "./img_resource/button_right.jpg");
            head.show();
        }
    }
}

void EndMenu(int x, int y)
{
    cout<<"GameOverFlag:"<<GameOverFlag<<endl;
    if (GameOverFlag)
    {
        if (x > 250 && x <= 350)
        {
            if (y > 235 && y <= 285)
            {
                cout << "重试" << endl;
                ResetFlag=1;
                lcd_draw_img_jpeg(0, 0, "./img_resource/menu.jpg");
                head.MouseReset();
                //唤醒
                pthread_cond_signal(&Over_cond);
            }
        }
    }

} // 游戏结束菜单选择