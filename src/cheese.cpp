// #include "cheese.h"
#include "item.h"
Cheese cheese;

Cheese::Cheese(int x, int y, int bonus, int score, int exsit) : x(x), y(y), bonus(bonus), score(score), exsit(exsit)
{
}

Cheese::~Cheese()
{
}

void Cheese::setX(int x)
{
    this->x = x;
}
void Cheese::setY(int y)
{
    this->y = y;
}
int Cheese::getX()
{
    return x;
}
int Cheese::getY()
{
    return y;
}
int Cheese::getBouns()
{
    return bonus;
}
void Cheese::setBouns(int bouns)
{
    this->bonus = bouns;
}
void Cheese::setExsit(int exsit)
{
    this->exsit = exsit;
}
int Cheese::getExsit()
{
    return exsit;
}
int Cheese::getscore()
{
    return score;
}

//-------------
void Cheese::show_lcd(){
    if (bonus)
    {
        lcd_draw_img_jpeg(x, y, "./img_resource/cheese_bouns.jpg");
    }
    else
    {
        lcd_draw_img_jpeg(x, y, "./img_resource/cheese.jpg");
    }
}
void Cheese::CheeseCreate()
{
    // 如果不存在则要清白然后再生成
    if (exsit == 0)
    {
        for (int y = this->y; y < this->y + 20; y++)
        {
            for (int x = this->x; x < this->x; x++)
            {
                lcd_draw_point(x, y, 0x00FFFFFF);
            }
        }
    }
    cout << "生成奶酪" << endl;
    int r_x = 0, r_y = 0, r_bouns;
    srand((unsigned)time(NULL));
    // 奶酪的生成方向必须与鼠头方向相反，且生成在鼠头上或下

    r_x = 75 + (rand() % (18)) * 25;

    r_y = 65 + (rand() % (18)) * 20; //[65，425)

    // 防止奶酪的生成与陷阱重复
    for (Trap *temp : Trap_v)
    {
        while (temp->getX() == r_x && temp->getY() == r_y)
        {
            r_x = 75 + (rand() % (18)) * 25;
            r_y = 65 + (rand() % (18)) * 20; //[65，425)
        }
    }

    r_bouns = rand()%2+0;
    cout << "cheese--"
         << "x:" << r_x << "\ty:" << r_y << endl;
    x = r_x;
    y = r_y;
    bonus = r_bouns;
    cout<<"bouns:"<<bonus<<endl;
    if (r_bouns)
    {
        lcd_draw_img_jpeg(x, y, "./img_resource/cheese_bouns.jpg");
    }
    else
    {
        lcd_draw_img_jpeg(x, y, "./img_resource/cheese.jpg");
    }
}