#include "Animal.h"
// 全局变量
int MouseCount;  // 鼠群的数量
int CheeseCount; // 奶酪的数量
Mouse head;      // 鼠头
string sign;     // 指令
vector<Mouse *> mouse_v;
int GameOverFlag; // 游戏结束标志
pthread_cond_t Over_cond;
pthread_mutex_t Over_mutex;
pthread_cond_t Pause_cond;
pthread_mutex_t Pause_mutex;
int ResetFlag;   // 重置标志
int DestroyFlag; // 销毁标志
int speed;       // 速度
int PauseFlag;   // 暂停

//----------------------------
Mouse::Mouse(/* args */ int x, int y, int score) : x(x), y(y), score(score)
{
    next = prev = this;
    cout << "mouse构建" << endl;
}

Mouse::~Mouse()
{
    cout << "mouse析构" << endl;
}
void Mouse::show()
{
    cout << this << "\tx:" << x << "\ty:" << y << endl;
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
void Mouse::setNext(Mouse *next)
{
    this->next = next;
}
void Mouse::setPrev(Mouse *prev)
{
    this->prev = prev;
}
void Mouse::setScore(int score)
{
    this->score = score;
}
int Mouse::getScore()
{
    return score;
}
//----------------------------

//------------------------------
void Mouse::MouseReset()
{
    for (Mouse *m : mouse_v)
    {
        cout << "Mouse------x:" << m->getX() << "\ty:" << m->getY() << "---deleted" << endl;
        delete m;
    }
    mouse_v.clear();
    x = 50;
    y = 45;
    score = 0;
    next = prev = this;
    sign = "below";
}
void Mouse::MouseDestroy()
{
    for (Mouse *m : mouse_v)
    {
        cout << "Mouse------x:" << m->getX() << "\ty:" << m->getY() << "---deleted" << endl;
        delete m;
        mouse_v.clear();
    }
    next = prev = NULL;
}
void Mouse::MouseTailAdd(Mouse *other)
{
    // 先判断鼠头此时的朝向为？
    // Mouse *other = &other_mouse;
    // other->show();
    if (sign.compare("up") == 0)
    {
        // 找到尾部
        Mouse *p = this, *tail = NULL;
        tail = p->getPrev();
        tail->setNext(other);
        other->setPrev(tail);
        other->setNext(this);
        this->setPrev(other);
        other->setX(tail->getX());
        other->setY(tail->getY() + 20);
        // this->getNext()->show();
    }
    else if (sign.compare("below") == 0)
    {
        // 找到尾部
        Mouse *p = this, *tail = NULL;
        tail = p->getPrev();
        tail->setNext(other);
        other->setPrev(tail);
        other->setNext(this);
        this->setPrev(other);
        other->setX(tail->getX());
        other->setY(tail->getY() - 20);
        // this->getNext()->show();
    }
    else if (sign.compare("left") == 0)
    {
        // 找到尾部
        Mouse *p = this, *tail = NULL;
        tail = p->getPrev();
        tail->setNext(other);
        other->setPrev(tail);
        other->setNext(this);
        this->setPrev(other);
        other->setX(tail->getX() + 25);
        other->setY(tail->getY());
        // this->getNext()->show();
    }
    else if (sign.compare("right") == 0)
    {
        // 找到尾部
        Mouse *p = this, *tail = NULL;
        tail = p->getPrev();
        tail->setNext(other);
        other->setPrev(tail);
        other->setNext(this);
        this->setPrev(other);
        other->setX(tail->getX() - 25);
        other->setY(tail->getY());
        // this->getNext()->show();
    }
}
void GameOver(Mouse *head)
{
    GameOverFlag = 1;
    // 显示积分
    char score[32];
    sprintf(score, "%d", head->getScore());
    cout << "score:" << score << endl;
    if (head->getScore() >= 0 && head->getScore() <= 100)
    {
        lcd_draw_img_jpeg(200, 150, "./img_resource/game_overC.jpg");
    }
    else if (head->getScore() >= 100 && head->getScore() <= 200)
    {
        lcd_draw_img_jpeg(200, 150, "./img_resource/game_overB.jpg");
    }
    else if (head->getScore() >= 200 && head->getScore() <= 300)
    {
        lcd_draw_img_jpeg(200, 150, "./img_resource/game_overA.jpg");
    }
    Score_font_show_text(score, 100, 20, 250, 200, 20, 20, 0);
    // cout << "撞墙啦" << endl;
    pthread_cond_wait(&Over_cond, &Over_mutex);
    if (ResetFlag)
    {
        // 重新生成奶酪
        cheese.setExsit(0);
        cheese.CheeseCreate();
        // 重新生成陷阱
        LevelSelected(game_level);
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
        lcd_draw_img_jpeg(725, 100, "./img_resource/button_musicVoice.jpg");
        // 重新生成猫
        cat.reset();
        ResetFlag = 0;
        GameOverFlag = 0;
        // 唤醒
        pthread_cond_signal(&Cat_Pause_cond);
    }
    else if (DestroyFlag)
    {
        pthread_exit(NULL);
    }

} // 老鼠在撞墙后的处理函数

void cleanMouse(Mouse *head)
{
    Mouse *next = head->getNext();
    // 先刷白，再显示图片
    // 刷白头部
    for (int re_y = head->getY(); re_y < head->getY() + 20; re_y++)
    {
        for (int re_x = head->getX(); re_x < head->getX() + 25; re_x++)
        {
            lcd_draw_point(re_x, re_y, 0x00FFFFFF);
        }
    }
    Mouse *p = next;

    // 刷白尾部
    while (p != head)
    {
        for (int re_y = p->getY(); re_y < p->getY() + 20; re_y++)
        {
            for (int re_x = p->getX(); re_x < p->getX() + 25; re_x++)
            {
                lcd_draw_point(re_x, re_y, 0x00FFFFFF);
            }
        }
        p = p->getNext();
    }

} // 老鼠在移动前的清除函数
void eatCheese(Mouse *head)
{
    cout << "create" << endl;
    // 判断分数
    if (cheese.getBouns())
    {
        // 查看是否为额外奖励
        head->setScore(head->getScore() + cheese.getscore() * 2);
    }
    else
    {
        head->setScore(head->getScore() + cheese.getscore());
    }
    // 显示积分
    char score[32];
    sprintf(score, "%d", head->getScore());
    cout << "score:" << score << endl;
    Score_font_show_text(score, 100, 20, 673, 55, 20, 20, 0);
    // // 播放声效
    // try
    // {
    //     sfx_init();
    // }
    // catch (exception &e)
    // {
    //     e.what();
    // }
    //--------------------
    cheese.setExsit(0);
    cheese.CheeseCreate();
    Mouse *p = new Mouse();
    mouse_v.push_back(p);
    head->MouseTailAdd(p);
} // 判断是否吃到奶酪

int hitBody(Mouse *head)
{
    Mouse *p = head->getNext();
    while (p != head)
    {
        /* code */
        if (head->getX() == p->getX() && head->getY() == p->getY())
        {
            if (sign.compare("up") == 0)
            {
                lcd_draw_img_jpeg(head->getX(), head->getY(), "./img_resource/mouse_head_u_stun.jpg");
            }
            else if (sign.compare("below") == 0)
            {
                cout << "1" << endl;
                lcd_draw_img_jpeg(head->getX(), head->getY(), "./img_resource/mouse_head_b_stun.jpg");
            }
            else if (sign.compare("left") == 0)
            {
                lcd_draw_img_jpeg(head->getX(), head->getY(), "./img_resource/mouse_head_l_stun.jpg");
            }
            else if (sign.compare("right") == 0)
            {
                lcd_draw_img_jpeg(head->getX(), head->getY(), "./img_resource/mouse_head_r_stun.jpg");
            }
            usleep(500 * 1000);
            GameOver(head);
            return 0;
        }
        p = p->getNext();
    }
    return 1;

} // 身体碰撞判断

void adjustMove(Mouse *head, int x, int y)
{
    Mouse *next = head->getNext();
    Mouse *prev = head->getPrev();
    Mouse *p = prev;
    // cout << "next:" << endl;
    // p->show();
    //  头部尾部有对象
    while (p != head)
    {
        // cout << "adjust" << endl;
        // p->show();
        //  如果就一个尾部对象则上一个节点的值就是头部未修改前的值
        if (p->getPrev() == head)
        {
            p->setX(x);
            p->setY(y);
        }
        // 下一个获取上一个节点的值
        else
        {
            p->setX(p->getPrev()->getX());
            p->setY(p->getPrev()->getY());
        }
        if (sign.compare("up") == 0)
        {
            lcd_draw_img_jpeg(p->getX(), p->getY(), "./img_resource/mouse_u.jpg");
        }
        else if (sign.compare("below") == 0)
        {
            // cout << "1" << endl;
            lcd_draw_img_jpeg(p->getX(), p->getY(), "./img_resource/mouse_b.jpg");
        }
        else if (sign.compare("left") == 0)
        {
            lcd_draw_img_jpeg(p->getX(), p->getY(), "./img_resource/mouse_l.jpg");
        }
        else if (sign.compare("right") == 0)
        {
            lcd_draw_img_jpeg(p->getX(), p->getY(), "./img_resource/mouse_r.jpg");
        }

        p = p->getPrev();
    }
    // 显示头
    if (sign.compare("up") == 0)
    {
        lcd_draw_img_jpeg(p->getX(), p->getY(), "./img_resource/mouse_head_u.jpg");
    }
    else if (sign.compare("below") == 0)
    {
        lcd_draw_img_jpeg(p->getX(), p->getY(), "./img_resource/mouse_head_b.jpg");
    }
    else if (sign.compare("left") == 0)
    {
        lcd_draw_img_jpeg(p->getX(), p->getY(), "./img_resource/mouse_head_l.jpg");
    }
    else if (sign.compare("right") == 0)
    {
        lcd_draw_img_jpeg(p->getX(), p->getY(), "./img_resource/mouse_head_r.jpg");
    }

    // 判断是否吃到奶酪,鼠头和鼠身判断
    // 鼠头
    if (head->getX() == cheese.getX() && head->getY() == cheese.getY())
    {
        eatCheese(head);
    }

    // 鼠身
    p = next;
    while (p != head)
    {
        if (p->getX() == cheese.getX() && p->getY() == cheese.getY())
        {
            eatCheese(head);
            break;
        }
        else
        {
            p = p->getNext();
        }
    }

    // 身体碰撞判断
    if (!hitBody(head))
    {
        return;
    }
    // 判断是否碰到陷阱
    for (Trap *p : Trap_v)
    {
        if (head->getX() == p->getX() && head->getY() == p->getY())
        {
            GameOver(head);
            return;
        }
    }
    // 判断是否碰到猫
    if (head->getX() == cat.getX() && head->getY() == cat.getY())
    {
        GameOver(head);
        return;
    }
    // 鼠身
    p = next;
    while (p != head)
    {
        if (p->getX() == cat.getX() && p->getY() == cat.getY())
        {
            GameOver(head);
            break;
        }
        else
        {
            p = p->getNext();
        }
    }
}
void *Mouse_autoMove(void *args)
{
    pthread_detach(pthread_self());
    Mouse *head = (Mouse *)args;

#if 1
    while (1)
    {
        // 判断是否处于暂停
        if (PauseFlag)
        {
            pthread_cond_wait(&Pause_cond, &Pause_mutex);
        }
        int y = head->getY();
        int x = head->getX();
        Mouse *next = head->getNext();
        Mouse *prev = head->getPrev();

        // 判断移动方向
        if (sign.compare("up") == 0)
        {
            cleanMouse(head);
            head->setY(y - 20);

            if (head->getY() < 45)
            {
                lcd_draw_img_jpeg(x, y, "./img_resource/mouse_head_u_stun.jpg");
                usleep(500 * 1000);
                GameOver(head);
            }
            else
            {
                adjustMove(head, x, y);
            }
        }
        else if (sign.compare("below") == 0)
        {
            cleanMouse(head);
            head->setY(y + 20);

            if (head->getY() >= 445)
            {
                lcd_draw_img_jpeg(x, y, "./img_resource/mouse_head_b_stun.jpg");
                usleep(500 * 1000);
                GameOver(head);
            }
            else
            {
                adjustMove(head, x, y);
            }
        }
        else if (sign.compare("left") == 0)
        {

            cleanMouse(head);
            Mouse *p = next;
            head->setX(x - 25);
            if (head->getX() < 50)
            {
                lcd_draw_img_jpeg(x, y, "./img_resource/mouse_head_l_stun.jpg");
                usleep(500 * 1000);
                GameOver(head);
            }
            else
            {

                adjustMove(head, x, y);
            }
        }
        else if (sign.compare("right") == 0)
        {
            cleanMouse(head);
            Mouse *p = next;

            head->setX(x + 25);
            if (head->getX() >= 550)
            {
                lcd_draw_img_jpeg(x, y, "./img_resource/mouse_head_r_stun.jpg");
                usleep(500 * 1000);
                GameOver(head);
            }
            else
            {

                adjustMove(head, x, y);
            }
        }
        usleep(speed * 1000);
    }
#endif
}