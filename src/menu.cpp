#include "menu.h"
int x, y;
pthread_t Mouse_autoMoveThread;

void initdata()
{
    lcd_draw_img_jpeg(0, 0, "./img_resource/menu.jpg");

    sign = "below";
    // 随机生成一个奶酪
    cheese.CheeseCreate();
    // 初始化条件变量，互斥锁等
    pthread_cond_init(&Over_cond, NULL);
    pthread_mutex_init(&Over_mutex, NULL);
    speed = 500;
}
int menu()
{
    initdata();
    // 创建鼠群自动移动线程
    if (pthread_create(&Mouse_autoMoveThread, NULL, Mouse_autoMove, &head) == -1)
    {
        cout << "创建线程失败\n";
        return -1;
    }
    int count = 1;
    struct input_event buf; // 触摸屏数据结构体
    while (1)
    {
        // 读取触摸屏数据
        read(fd_touch, &buf, sizeof(buf));
        if (buf.type == EV_ABS)
        {
            // 如果事件类型为绝对位置事件，判断为触摸
            // 第一次返回X值，第二次返回Y值
            if (buf.code == ABS_X)
            {
                x = buf.value;
                printf("x=%d\n", x);
                printf("count=%d\n", count);
            }
            if (buf.code == ABS_Y)
            {
                y = buf.value;
                printf("y=%d\n", y);
                printf("count=%d\n", count);
            }
        }
        // 判断当前点击操作是否释放
        if (buf.type == EV_KEY && buf.code == BTN_TOUCH)
        {
            // 处于按键或触摸状态
            if (buf.value)
            {
            }
            else
            {
                // 对各个功能的进行触发判断
                Button_Direct(x, y);
                if (EndMenu(x, y) == 0)
                {
                    cout << "退出" << endl;
                    break;
                }
            }
        }
        count++;
    }
    // 销毁条件变量和互斥锁
    pthread_cond_destroy(&Over_cond);
    pthread_mutex_destroy(&Over_mutex);
    return 0;
}