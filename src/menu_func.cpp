#include "menu_func.h"
pthread_t Mouse_autoMoveThread;
int PlayFlag;
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
        if (y > 335 && y <= 385)
        {
            // 减速
            speed += 100;
            if (speed > 1000)
            {
                speed = 1000;
            }
            lcd_draw_img_jpeg(605, 335, "./img_resource/button_speed_de_active.jpg");
            usleep(100 * 1000);
            lcd_draw_img_jpeg(605, 335, "./img_resource/button_speed_de.jpg");
        }
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
        if (y > 335 && y <= 385)
        {
            // 加速
            speed -= 100;
            if (speed < 300)
            {
                speed = 300;
            }
            lcd_draw_img_jpeg(725, 335, "./img_resource/button_speed_add_active.jpg");
            usleep(100 * 1000);
            lcd_draw_img_jpeg(725, 335, "./img_resource/button_speed_add.jpg");
        }
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

int EndMenu(int x, int y)
{
    cout << "GameOverFlag:" << GameOverFlag << endl;
    if (GameOverFlag)
    {
        if (x > 250 && x <= 350)
        {
            if (y > 235 && y <= 285)
            {
                cout << "重试" << endl;
                ResetFlag = 1;
                lcd_draw_img_jpeg(0, 0, "./img_resource/menu.jpg");
                lcd_draw_img_jpeg(605, 100, "./img_resource/button_play.jpg");
                head.MouseReset();
                // 唤醒
                pthread_cond_signal(&Over_cond);
            }
            if (y > 290 && y <= 340)
            {
                cout << "退出" << endl;
                DestroyFlag = 1;
                lcd_draw_img_jpeg(0, 0, "./img_resource/menu.jpg");
                head.MouseDestroy();
                return 0;
                // 唤醒
                pthread_cond_signal(&Over_cond);
                // 等待线程自我回收
                usleep(100 * 1000);
            }
        }
    }
    else
    {
        return -1;
    }

} // 游戏结束菜单选择

int GameMenu(int x, int y)
{
    // 暂停开始
    if (x > 605 && x <= 665)
    {
        if (y > 100 && y <= 150)
        {
            if (PauseFlag)
            {
                PauseFlag = 0;
                cout << "开始" << endl;
                lcd_draw_img_jpeg(605, 100, "./img_resource/button_play.jpg");
                // 首次开始时初始化线程
                if (!PlayFlag)
                {
                    sign = "below";
                    // 随机生成一个奶酪
                    cheese.CheeseCreate();
                    // 创建鼠群自动移动线程
                    if (pthread_create(&Mouse_autoMoveThread, NULL, Mouse_autoMove, &head) == -1)
                    {
                        cout << "创建线程失败\n";
                        return -1;
                    }
                }
                pthread_cond_signal(&Pause_cond);
                PlayFlag = 1;
            }
            else
            {
                PauseFlag = 1;
                lcd_draw_img_jpeg(605, 100, "./img_resource/button_pause.jpg");
                usleep(100 * 1000); // 等待线程阻塞
                cout << "暂停" << endl;
            }
        }
    }
    // 重置
    if (x > 665 && x <= 725)
    {
        if (y > 100 && y <= 150)
        {
            // 只有开始时才可以重置进度
            if (PlayFlag)
            {
                head.MouseReset();
                lcd_draw_img_jpeg(0, 0, "./img_resource/menu.jpg");
                lcd_draw_img_jpeg(605, 100, "./img_resource/button_play.jpg");
                cheese.setExsit(0);
                cheese.CheeseCreate();
            }
        }
    }
}
void initdata()
{
    lcd_draw_img_jpeg(0, 0, "./img_resource/menu.jpg");
    // 初始化条件变量，互斥锁等
    pthread_cond_init(&Over_cond, NULL);
    pthread_mutex_init(&Over_mutex, NULL);
    pthread_cond_init(&Pause_cond, NULL);
    pthread_mutex_init(&Pause_mutex, NULL);
    speed = 500;
    PlayFlag = 0;
    PauseFlag = 1;
}