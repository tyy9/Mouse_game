#include "cheese.h"
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

//-------------

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
        int r_x, r_y, r_bouns;
         srand((unsigned)time(NULL));
        r_x = 75 + (rand() % (18)) * 25; //[75,525)
        r_y = 65 + (rand() % (18)) * 20; //[65，425)
        r_bouns = rand() % (1 - 0) + 0;
        cout << "cheese--"
             << "x:" << r_x << "\ty:" << r_y << endl;
        x = r_x;
        y = r_y;
        bonus = r_bouns;
        lcd_draw_img_jpeg(x, y, "./img_resource/cheese.jpg");
    
}   