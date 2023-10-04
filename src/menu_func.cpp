#include "menu_func.h"
pthread_t Mouse_autoMoveThread;
pthread_t Cat_autoMoveThread;
int PlayFlag;
int MuteFlag; // 静音标志

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
            if (speed <= 0)
            {
                speed = 100;
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
                // 重新生成陷阱
                // LevelSelected(game_level);
                // 唤醒
                pthread_cond_signal(&Over_cond);
            }
            if (y > 290 && y <= 340)
            {
                DestroyFlag = 1;
                cout << "退出" << endl;
                // 关闭popen创建的文件
                if (mapler_fp_music)
                {
                    pclose(mapler_fp_music);
                    // 防止mplayer还没有完全退出，再尝试灭掉mplayer进程
                    system("killall -9 mplayer\n");
                }
                mapler_fp_music = NULL; // 防止野指针
                // 关闭管道文件
                close(fd_music);
                PauseFlag = 1;
                head.MouseDestroy();
                pthread_cond_signal(&Over_cond);
                // 等待线程自我回收
                usleep(100 * 1000);
                return 0;
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

    if (x > 605 && x <= 665)
    {
        // 暂停开始
        if (y > 100 && y <= 150)
        {
            if (PauseFlag)
            {
                GamePlay();
            }
            else
            {
                GamePause();
            }
        }
        // 存档
        if (y > 150 && y <= 200)
        {
            // 游戏开始后才可以存档
            if (PlayFlag)
            {
                cout << "存档" << endl;
                GamePause();
                save();
                GamePlay();
            }
        }
        if (y > 200 && y <= 250)
        {
            cout << "退出" << endl;
            // 关闭popen创建的文件
            if (mapler_fp_music)
            {
                pclose(mapler_fp_music);
                // 防止mplayer还没有完全退出，再尝试灭掉mplayer进程
                system("killall -9 mplayer\n");
            }
            mapler_fp_music = NULL; // 防止野指针
            // 关闭管道文件
            close(fd_music);
            PauseFlag = 1;
            head.MouseDestroy();
            pthread_cond_signal(&Over_cond);
            // 等待线程自我回收
            usleep(100 * 1000);
            return 0;
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
                lcd_draw_img_jpeg(725, 100, "./img_resource/button_musicVoice.jpg");
                cheese.setExsit(0);
                cheese.CheeseCreate();
                // 重新生成陷阱
                LevelSelected(game_level);
                switch (game_level)
                {
                case 1:
                    lcd_draw_img_jpeg(725, 150, "./img_resource/button_game_levelEasy.jpg");
                    break;
                case 2:
                    lcd_draw_img_jpeg(725, 150, "./img_resource/button_game_levelNoraml.jpg");
                    break;
                case 3:
                    lcd_draw_img_jpeg(725, 150, "./img_resource/button_game_levelHard.jpg");
                    break;
                default:
                    break;
                }
                // 猫重置
                cat.reset();
            }
        }
        // 读档
        if (y > 150 && y <= 200)
        {
            if (PlayFlag)
            {
                cout << "读档" << endl;
                GamePause();
                // 刷新背景
                lcd_draw_img_jpeg(50, 45, "./img_resource/background.jpg");
                load();
                // // 重新生成奶酪
                // cheese.setExsit(0);
                // cheese.CheeseCreate();
                // //重新生成陷阱
                // LevelSelected(game_level);
                sleep(1);
                GamePlay();
            }
        }
    }

    if (x > 725 && x <= 785)
    {
        // 音乐选项
        if (y > 100 && y <= 150)
        {
            // 只有开始时才可以调整音量
            if (PlayFlag)
            {
                switch (MuteFlag)
                {
                case 1:
                    send_cmd_music("volume 20 1\n");
                    lcd_draw_img_jpeg(725, 100, "./img_resource/button_musicVoice.jpg");
                    MuteFlag = 0;
                    break;
                case 0:
                    send_cmd_music("volume 0 1\n");
                    lcd_draw_img_jpeg(725, 100, "./img_resource/button_musicMute.jpg");
                    MuteFlag = 1;
                    break;
                default:
                    cout << "muteflag错误" << endl;
                    break;
                }
            }
        }
        // 难度选择
        if (y > 150 && y <= 200)
        {
            if (PlayFlag)
            {
                game_level++;
                if (game_level > 3)
                {
                    game_level = 1;
                }
                head.MouseReset();
                lcd_draw_img_jpeg(0, 0, "./img_resource/menu.jpg");
                lcd_draw_img_jpeg(605, 100, "./img_resource/button_play.jpg");
                lcd_draw_img_jpeg(725, 100, "./img_resource/button_musicVoice.jpg");
                cheese.setExsit(0);
                cheese.CheeseCreate();
                switch (game_level)
                {
                case 1:
                    lcd_draw_img_jpeg(725, 150, "./img_resource/button_levelEasy.jpg");
                    break;
                case 2:
                    lcd_draw_img_jpeg(725, 150, "./img_resource/button_levelNoraml.jpg");
                    break;
                case 3:
                    lcd_draw_img_jpeg(725, 150, "./img_resource/button_levelHard.jpg");
                    break;
                default:
                    break;
                }
                LevelSelected(game_level);
                // 猫重置
                cat.reset();
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
    pthread_cond_init(&Cat_Pause_cond, NULL);
    pthread_mutex_init(&Cat_Pause_mutex, NULL);
    speed = 500;
    PlayFlag = 0;
    PauseFlag = 1;
    game_level = 1; // 默认等级为1
}

void GamePause()
{
    PauseFlag = 1;
    MuteFlag = 1;
    send_cmd_music("pause\n");
    lcd_draw_img_jpeg(725, 100, "./img_resource/button_musicMute.jpg");
    lcd_draw_img_jpeg(605, 100, "./img_resource/button_pause.jpg");
    usleep(100 * 1000); // 等待线程阻塞
    cout << "暂停" << endl;
}
void GamePlay()
{
    PauseFlag = 0;
    cout << "开始" << endl;
    lcd_draw_img_jpeg(605, 100, "./img_resource/button_play.jpg");
    // 首次开始时初始化线程
    if (!PlayFlag)
    {
        sign = "below";
        // 随机生成一个奶酪
        cout << "随机生成奶酪" << endl;
        cheese.CheeseCreate();
        // 生成陷阱
        LevelSelected(game_level);
        // 创建鼠群自动移动线程
        if (pthread_create(&Mouse_autoMoveThread, NULL, Mouse_autoMove, &head) == -1)
        {
            cout << "创建线程失败\n";
            return;
        }
        // 创建猫线程
        if (pthread_create(&Cat_autoMoveThread, NULL, CatMove, &cat) == -1)
        {
            cout << "创建线程失败\n";
            return;
        }
        // 创建音乐进程
        try
        {
            music_init();
        }
        catch (exception &e)
        {
            e.what();
        }
    }
    else
    {
        send_cmd_music("pause\n");
        sleep(1);
        pthread_cond_signal(&Pause_cond);
        pthread_cond_signal(&Cat_Pause_cond);
    }
    lcd_draw_img_jpeg(725, 100, "./img_resource/button_musicVoice.jpg");
    MuteFlag = 0;
    PlayFlag = 1;
}