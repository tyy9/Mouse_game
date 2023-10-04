// #include "trap.h"
#include "item.h"
vector<Trap *> Trap_v;
int game_level;
Trap::Trap()
{
    cout << "trap构造" << endl;
}
Trap::~Trap()
{
    cout << "trap析构" << endl;
}
//------------
void Trap::setX(int x)
{
    this->x = x;
}
void Trap::setY(int y)
{
    this->y = y;
}
int Trap::getX()
{
    return x;
}
int Trap::getY()
{
    return y;
}
void Trap::show_lcd()
{
    lcd_draw_img_jpeg(x, y, "./img_resource/trap.jpg");
}
//----------------
void TrapCreate()
{
    int r_x = 0, r_y = 0;
    Trap *p = new Trap();
    srand((unsigned)time(NULL));
    // 防止生成位置与奶酪重合
    r_x = 75 + (rand() % (18)) * 25;
    r_y = 65 + (rand() % (18)) * 20; //[65，425)
    cout << "trap-->cheese:x" << cheese.getX() << "\ty:" << cheese.getY() << endl;
    cout << "before:trap--x:" << r_x << "\ty:" << r_y << endl;
    while (r_x == cheese.getX() && r_y == cheese.getY())
    {
        cout << "1" << endl;
        r_x = 75 + (rand() % (18)) * 25;
        r_y = 65 + (rand() % (18)) * 20; //[65，425)
    }
    // 防止陷阱之间的位置重合
    for (Trap *temp : Trap_v)
    {
        while (temp->getX() == r_x && temp->getY() == r_y)
        {
            r_x = 75 + (rand() % (18)) * 25;
            r_y = 65 + (rand() % (18)) * 20; //[65，425)
            while (r_x == cheese.getX() && r_y == cheese.getY())
            {
                r_x = 75 + (rand() % (18)) * 25;
                r_y = 65 + (rand() % (18)) * 20; //[65，425)
            }
        }
    }
    p->setX(r_x);
    p->setY(r_y);
    cout << "after:trap--x:" << p->getX() << "\ty:" << p->getY() << endl;
    lcd_draw_img_jpeg(p->getX(), p->getY(), "./img_resource/trap.jpg");
    Trap_v.push_back(p);
}
void LevelSelected(int level)
{
    game_level = level;
    // 先清空容器中的对象
    for (Trap *p : Trap_v)
    {
        delete p;
    }
    Trap_v.clear();
    //---------------

    switch (level)
    {
        // 生成5个陷阱
    case 1:
        for (int i = 0; i < 5; i++)
        {
            TrapCreate();
        }
        break;
    case 2:
        for (int i = 0; i < 10; i++)
        {
            TrapCreate();
        }
        break;
    case 3:
        for (int i = 0; i < 20; i++)
        {
            TrapCreate();
        }
        break;
    default:
        break;
    }
}