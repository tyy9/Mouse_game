#include "Animal.h"
int cat_sign; // 猫的追踪方向,1:up,2:below,3:left,4:right
Cat cat;
vector<int> direct_v;
int MoveFlag;
pthread_cond_t Cat_Pause_cond;
pthread_mutex_t Cat_Pause_mutex;
Cat::Cat(int x, int y) : x(x), y(y)
{
    cout << "猫构造" << endl;
}
Cat::~Cat()
{
    cout << "猫析构" << endl;
}
void Cat::show()
{
    cout << this << "\tx:" << x << "\ty:" << y << endl;
}
void Cat::setX(int x)
{
    this->x = x;
}
void Cat::setY(int y)
{
    this->y = y;
}
int Cat::getX()
{
    return x;
}
int Cat::getY()
{
    return y;
}
void Cat::reset()
{
    x = 525;
    y = 425;
    //show_lcd(rand() % 4 + 1);
}
//----------------
void Cat::show_lcd(int direct)
{
#if 1
    switch (direct)
    {
    case 1:
        lcd_draw_img_jpeg(x, y, "./img_resource/cat.jpg");
        // 尾部清白
        for (int clear_y = y + 20; clear_y <= y + 40; clear_y++)
        {
            for (int clear_x = x; clear_x <= x + 25; clear_x++)
            {
                lcd_draw_point(clear_x, clear_y, 0x00FFFFFF);
            }
        }
        break;
    case 2:
        lcd_draw_img_jpeg(x, y, "./img_resource/cat.jpg");
        // 尾部清白
        for (int clear_y = y - 20; clear_y <= y; clear_y++)
        {
            for (int clear_x = x; clear_x <= x + 25; clear_x++)
            {
                lcd_draw_point(clear_x, clear_y, 0x00FFFFFF);
            }
        }
        break;
    case 3:
        lcd_draw_img_jpeg(x, y, "./img_resource/cat.jpg");
        // 尾部清白
        for (int clear_y = y; clear_y <= y + 20; clear_y++)
        {
            for (int clear_x = x + 25; clear_x <= x + 50; clear_x++)
            {
                lcd_draw_point(clear_x, clear_y, 0x00FFFFFF);
            }
        }
        break;
    case 4:
        lcd_draw_img_jpeg(x, y, "./img_resource/cat.jpg");
        // 尾部清白
        for (int clear_y = y; clear_y <= y + 20; clear_y++)
        {
            for (int clear_x = x - 25; clear_x <= x; clear_x++)
            {
                lcd_draw_point(clear_x, clear_y, 0x00FFFFFF);
            }
        }
        break;
    default:
        break;
    }
#endif
    // lcd_draw_img_jpeg(x, y, "./img_resource/cat.jpg");
    //  尾部清白
}
//---------
void CatMove_adjust(int direct, Cat *cat)
{
    int res, pass;
    switch (direct)
    {
    case 1:
        cout << "cat=>up" << endl;
        res = cat->getY() - 20;
        pass = 1; // 是否触及奶酪与陷阱
        if (res > 45)
        {
            if (cat->getX() != cheese.getX() && res != cheese.getY())
            {
                for (Trap *p : Trap_v)
                {
                    if (p->getX() == cat->getX() && p->getY() == res)
                    {
                        pass = 0;
                    }
                }
                if (pass)
                {
                    cout << "pass" << endl;
                    cat->setY(cat->getY() - 20);
                    MoveFlag = 1;
                    cat->show_lcd(direct);
                }
            }
        }
        else
        {
            cout << "越界" << endl;
        }
        break;
    case 2:
        cout << "cat=>below" << endl;
        res = cat->getY() + 20;
        pass = 1; // 是否触及奶酪与陷阱
        if (res < 445)
        {
            if (cat->getX() != cheese.getX() && res != cheese.getY())
            {
                for (Trap *p : Trap_v)
                {
                    if (p->getX() == cat->getX() && p->getY() == res)
                    {
                        pass = 0;
                    }
                }
                if (pass)
                {
                    cout << "pass" << endl;
                    cat->setY(cat->getY() + 20);
                    MoveFlag = 1;
                    cat->show_lcd(direct);
                }
            }
        }
        else
        {
            cout << "越界" << endl;
        }
        break;
    case 3:
        cout << "cat=>left" << endl;
        res = cat->getX() - 25;
        pass = 1; // 是否触及奶酪与陷阱
        if (res > 50)
        {
            cout << "1" << endl;
            if (res != cheese.getX() && cat->getY() != cheese.getY())
            {
                for (Trap *p : Trap_v)
                {
                    if (p->getX() == res && p->getY() == cat->getY())
                    {
                        pass = 0;
                    }
                }
                if (pass)
                {
                    cout << "pass" << endl;
                    cat->setX(res);
                    MoveFlag = 1;
                    cat->show_lcd(direct);
                }
            }
        }
        else
        {
            cout << "越界" << endl;
        }
        break;
    case 4:
        cout << "cat=>right" << endl;
        res = cat->getX() + 25;
        pass = 1; // 是否触及奶酪与陷阱
        if (res < 550)
        {
            if (res != cheese.getX() && cat->getY() != cheese.getY())
            {
                for (Trap *p : Trap_v)
                {
                    if (p->getX() == res && p->getY() == cat->getY())
                    {
                        pass = 0;
                    }
                }
                if (pass)
                {
                    cout << "pass" << endl;
                    cat->setX(cat->getX() + 25);
                    MoveFlag = 1;
                    cat->show_lcd(direct);
                }
            }
        }
        else
        {
            cout << "越界" << endl;
        }
        break;
    default:
        break;
    }
}
void *CatMove(void *args)
{
    pthread_detach(pthread_self());
    Cat *cat = (Cat *)args;
    while (1)
    {
        if (PauseFlag||GameOverFlag)
        {
            pthread_cond_wait(&Cat_Pause_cond, &Cat_Pause_mutex);
        }
        MoveFlag = 0;
        // 先清空方向判断容器
        direct_v.clear();
        // 先判断鼠头的位置，进行xy轴的跟踪
        // 判断x
        if (head.getX() > cat->getX())
        {
            cat_sign = 4;
        }
        else if (head.getX() < cat->getX())
        {
            cat_sign = 3;
        }
        // 判断y
        else
        {
            if (head.getY() > cat->getY())
            {
                cat_sign = 2;
            }
            else if (head.getY() < cat->getY())
            {
                cat_sign = 1;
            }
        }
        cout << "cat_sign:" << cat_sign << endl;
        cout<<"5"<<endl;
        // 判断下一次移动是否会碰撞到奶酪或陷阱
        // 算法：追踪方向移动概率占60%,其他方向占40%
        // 1.先让追踪方向加入到容器头部，其余放在尾部
        if (cat_sign == 1)
        {
            cout<<"4"<<endl;
            direct_v.push_back(cat_sign);
            direct_v.push_back(2);
            direct_v.push_back(3);
            direct_v.push_back(4);
        }
        else if (cat_sign == 2)
        {
            cout<<"4"<<endl;
            direct_v.push_back(cat_sign);
            direct_v.push_back(1);
            direct_v.push_back(3);
            direct_v.push_back(4);
        }
        else if (cat_sign == 3)
        {
            cout<<"4"<<endl;
            direct_v.push_back(cat_sign);
            direct_v.push_back(1);
            direct_v.push_back(2);
            direct_v.push_back(4);
        }
        else if (cat_sign == 4)
        {
            cout<<"4"<<endl;
            direct_v.push_back(cat_sign);
            direct_v.push_back(1);
            direct_v.push_back(2);
            direct_v.push_back(3);
        }
        cout<<"2"<<endl;
        // 判断下一次移动是否会碰撞到奶酪或陷阱
        srand((unsigned)time(NULL));
        int ret = rand() % (10) + 1;
        // 先判断跟踪方向的可行性，再去判断剩余的方向移动
        if (ret % 6 >= 0 && ret <= 6 && ret >= 1)
        {
            CatMove_adjust(cat_sign, cat);
        }
        cout<<"3"<<endl;
        // 其余方向的移动
        if (!MoveFlag)
        {
            cout << "other" << endl;
            int direct;
            ret = rand() % (3) + 1;
            cout << "direct:" << direct << endl;
            direct = direct_v.at(ret);
            CatMove_adjust(direct, cat);
        }
        usleep(300 * 1000);
    }
}
