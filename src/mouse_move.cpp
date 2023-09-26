#include "mouse.h"
// 全局变量
int MouseCount;        // 鼠群的数量
int CheeseCount;       // 奶酪的数量
Mouse head;            // 鼠头
string sign = "below"; // 指令

Mouse::Mouse(/* args */ int x, int y) : x(x), y(y)
{
    next = prev = NULL;
    cout << "mouse构建" << endl;
}

Mouse::~Mouse()
{
    cout << "mouse析构" << endl;
}
void Mouse::show()
{
    cout << "x:" << x << "\ty:" << y << endl;
}
void Mouse::setX(int x)
{
    this->x = x;
}
void Mouse::setY(int y)
{
    this->y = y;
}
int Mouse::getX()
{
    return x;
}
int Mouse::getY()
{
    return y;
}
Mouse *Mouse::getNext()
{
    return next;
}
Mouse *Mouse ::getPrev()
{
    return prev;
}

//----------------------------
void Mouse::operator+(string sign)
{
    // 判断移动方向
    if (sign.compare("up") == 0)
    {
        y -= 20;
        if (y <= 45)
        {
            // 先将之前的内容刷白
            for (int re_y = y + 20; re_y < y + 20 * 2; re_y++)
            {
                for (int re_x = x; re_x < x + 25; re_x++)
                {
                    lcd_draw_point(re_x, re_y, 0x00FFFFFF);
                }
            }
            lcd_draw_img_jpeg(x, y, "mouse_u.jpg");
            throw MouseOutRange();
        }
        else
        {
            if (next == NULL)
            {
                // 先将之前的内容刷白
                for (int re_y = y + 20; re_y < y + 20 * 2; re_y++)
                {
                    for (int re_x = x; re_x < x + 25; re_x++)
                    {
                        lcd_draw_point(re_x, re_y, 0x00FFFFFF);
                    }
                }
                lcd_draw_img_jpeg(x, y, "mouse_u.jpg");
            }
        }
    }
    else if (sign.compare("below") == 0)
    {
        y += 20;
        cout << "y---" << y << endl;
        if (y >= 445)
        {
            // 先将之前的内容刷白
            for (int re_y = y - 20; re_y < y; re_y++)
            {
                for (int re_x = x; re_x <= x + 25; re_x++)
                {
                    lcd_draw_point(re_x, re_y, 0x00FFFFFF);
                }
            }
            lcd_draw_img_jpeg(x, y, "mouse_b.jpg");
            throw MouseOutRange();
        }
        else
        {
            if (next == NULL)
            {
                // 先将之前的内容刷白
                for (int re_y = y - 20; re_y < y; re_y++)
                {
                    for (int re_x = x; re_x <= x + 25; re_x++)
                    {
                        lcd_draw_point(re_x, re_y, 0x00FFFFFF);
                    }
                }
                lcd_draw_img_jpeg(x, y, "mouse_b.jpg");
            }
        }
    }
    else if (sign.compare("left") == 0)
    {
        x -= 25;
        if (x <= 50)
        {
            // 先将之前的内容刷白
            for (int re_y = y; re_y < y + 20; re_y++)
            {
                for (int re_x = x + 25; re_x < x + 25 * 2; re_x++)
                {
                    lcd_draw_point(re_x, re_y, 0x00FFFFFF);
                }
            }
            lcd_draw_img_jpeg(x, y, "mouse_l.jpg");
            throw MouseOutRange();
        }
        else
        {
            if (next == NULL)
            {
                // 先将之前的内容刷白
                for (int re_y = y; re_y < y + 20; re_y++)
                {
                    for (int re_x = x + 25; re_x < x + 25 * 2; re_x++)
                    {
                        lcd_draw_point(re_x, re_y, 0x00FFFFFF);
                    }
                }
                lcd_draw_img_jpeg(x, y, "mouse_l.jpg");
            }
        }
    }
    else if (sign.compare("right") == 0)
    {
        x += 25;
        if (x >= 550)
        {
            // 先将之前的内容刷白
            for (int re_y = y; re_y < y + 20; re_y++)
            {
                for (int re_x = x - 25; re_x < x; re_x++)
                {
                    lcd_draw_point(re_x, re_y, 0x00FFFFFF);
                }
            }
            lcd_draw_img_jpeg(x, y, "mouse_r.jpg");
            throw MouseOutRange();
        }
        else
        {
            if (next == NULL)
            {
                // 先将之前的内容刷白
                for (int re_y = y; re_y < y + 20; re_y++)
                {
                    for (int re_x = x - 25; re_x < x; re_x++)
                    {
                        lcd_draw_point(re_x, re_y, 0x00FFFFFF);
                    }
                }
                lcd_draw_img_jpeg(x, y, "mouse_r.jpg");
            }
        }
    }
}

void *Mouse_autoMove(void *args)
{
    Mouse *head = (Mouse *)args;

#if 1
    while (1)
    {
        int y = head->getY();
        int x = head->getX();
        Mouse *next = head->getNext();
        Mouse *prev = head->getPrev();

        // 判断移动方向
        if (sign.compare("up") == 0)
        {
            head->setY(y - 20);
            cout << "mouse---y:" << head->getY() << endl;
            if (head->getY() < 45)
            {
                
                // 先将之前的内容刷白
                for (int re_y = head->getY() + 20; re_y < head->getY() + 20 * 2; re_y++)
                {
                    for (int re_x = head->getX(); re_x < head->getX() + 25; re_x++)
                    {
                        lcd_draw_point(re_x, re_y, 0x00FFFFFF);
                    }
                }
                //lcd_draw_img_jpeg(head->getX(), head->getY(), "mouse_u.jpg");
                throw MouseOutRange();
            }
            else
            {
                if (next == NULL)
                {
                    // 先将之前的内容刷白
                    for (int re_y = head->getY() + 20; re_y < head->getY() + 20 * 2; re_y++)
                    {
                        for (int re_x = head->getX(); re_x < head->getX() + 25; re_x++)
                        {
                            lcd_draw_point(re_x, re_y, 0x00FFFFFF);
                        }
                    }
                    lcd_draw_img_jpeg(head->getX(), head->getY(), "mouse_u.jpg");
                }
            }
        }
        else if (sign.compare("below") == 0)
        {
            head->setY(y + 20);

            if (head->getY() > 445)
            {
                // 先将之前的内容刷白
                for (int re_y = head->getY() - 20; re_y < head->getY(); re_y++)
                {
                    for (int re_x = head->getX(); re_x <= head->getX() + 25; re_x++)
                    {
                        lcd_draw_point(re_x, re_y, 0x00FFFFFF);
                    }
                }
                lcd_draw_img_jpeg(head->getX(), head->getY(), "mouse_b.jpg");
                //throw MouseOutRange();
            }
            else
            {
                if (next == NULL)
                {
                    //cout << "y---" << y << endl;
                    // 先将之前的内容刷白
                    for (int re_y = head->getY() - 20; re_y < head->getY(); re_y++)
                    {
                        for (int re_x = head->getX(); re_x <= head->getX() + 25; re_x++)
                        {
                            //cout << "re_y:" << re_y << "\tre:" << re_x << endl;
                            lcd_draw_point(re_x, re_y, 0x00FFFFFF);
                        }
                    }
                    lcd_draw_img_jpeg(head->getX(), head->getY(), "mouse_b.jpg");
                }
            }
        }
        else if (sign.compare("left") == 0)
        {
            head->setX(x - 25);
            if (head->getX() < 50)
            {
                // 先将之前的内容刷白
                for (int re_y = head->getY(); re_y < head->getY() + 20; re_y++)
                {
                    for (int re_x = head->getX() + 25; re_x < head->getX() + 25 * 2; re_x++)
                    {
                        lcd_draw_point(re_x, re_y, 0x00FFFFFF);
                    }
                }
                //lcd_draw_img_jpeg(head->getX(), head->getY(), "mouse_l.jpg");
                throw MouseOutRange();
            }
            else
            {
                if (next == NULL)
                {
                    // 先将之前的内容刷白
                    for (int re_y = head->getY(); re_y < head->getY() + 20; re_y++)
                    {
                        for (int re_x = head->getX() + 25; re_x < head->getX() + 25 * 2; re_x++)
                        {
                            lcd_draw_point(re_x, re_y, 0x00FFFFFF);
                        }
                    }
                    lcd_draw_img_jpeg(head->getX(), head->getY(), "mouse_l.jpg");
                }
            }
        }
        else if (sign.compare("right") == 0)
        {
            head->setX(x + 25);
            if (head->getX() > 550)
            {
                // 先将之前的内容刷白
                for (int re_y = head->getY(); re_y < head->getY() + 20; re_y++)
                {
                    for (int re_x = head->getX() - 25; re_x < head->getX(); re_x++)
                    {
                        lcd_draw_point(re_x, re_y, 0x00FFFFFF);
                    }
                }
                //lcd_draw_img_jpeg(head->getX(), head->getY(), "mouse_r.jpg");
                throw MouseOutRange();
            }
            else
            {
                if (next == NULL)
                {
                    // 先将之前的内容刷白
                    for (int re_y = head->getY(); re_y < head->getY() + 20; re_y++)
                    {
                        for (int re_x = head->getX() - 25; re_x < head->getX(); re_x++)
                        {
                            lcd_draw_point(re_x, re_y, 0x00FFFFFF);
                        }
                    }
                    lcd_draw_img_jpeg(head->getX(), head->getY(), "mouse_r.jpg");
                }
            }
        }
        usleep(500*1000);
    }
#endif
#if 0
    for(int y=0;y<200;y++){
        for(int x=0;x<100;x++){
            lcd_draw_point(x,y,0x00000000);
        }
    }
#endif
}