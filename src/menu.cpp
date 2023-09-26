#include "menu.h"
int x, y;
pthread_t Mouse_autoMoveThread;

int menu()
{
    lcd_draw_img_jpeg(0, 0, "./img_resource/menu.jpg");
    struct input_event buf; // 触摸屏数据结构体
    int count = 1;
    //随机生成一个奶酪
    cheese.CheeseCreate();
    //创建鼠群自动移动线程
    if(pthread_create(&Mouse_autoMoveThread,NULL,Mouse_autoMove,&head)==-1){
        cout<<"创建线程失败\n";
        return -1;
    }
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
                x = buf.value ;
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
                //对各个功能的进行触发判断
               Button_Direct(x,y,head);
            }
        }
        count++;
    }
}