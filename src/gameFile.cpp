#include "gameFile.h"
void save()
{
    // 先保存鼠头信息
    ofstream out;
    // 每次写存档都是覆盖旧存档
    out.open("./save/save01.txt");
    if (out.is_open() == -1)
    {
        tip_font_show_text("写入存档失败", 200, 27, 200, 0, 25, 10, 1);
        usleep(500 * 1000);
        lcd_draw_img_jpeg(200, 0, "./img_resource/tip_hide.jpg");
        out.close();
        return;
    }
    char head_info[1024];
    char mouse_info[1024];
    char cheese_info[1024];
    char trap_info[1024];
    char cat_info[1024];
    sprintf(head_info, "head=>%d,%d,%d,%s,%d\n", head.getX(), head.getY(), head.getScore(), sign.c_str(), game_level);
    out.write(head_info, strlen(head_info));
    // 查看鼠头尾部是否还有老鼠
    Mouse *p = head.getNext();
    while (p != &head)
    {
        bzero(mouse_info, sizeof(mouse_info));
        sprintf(mouse_info, "mouse=>%d,%d\n", p->getX(), p->getY());
        out.write(mouse_info, strlen(mouse_info));
        p = p->getNext();
    }
    // 保存奶酪位置与陷阱位置
    bzero(cheese_info, sizeof(cheese_info));
    sprintf(cheese_info, "cheese=>%d,%d,%d\n", cheese.getX(), cheese.getY(), cheese.getBouns());
    out.write(cheese_info, strlen(cheese_info));

    for (Trap *p : Trap_v)
    {
        bzero(trap_info, sizeof(trap_info));
        sprintf(trap_info, "trap=>%d,%d\n", p->getX(), p->getY());
        out.write(trap_info, strlen(trap_info));
    }
    // 保存猫的位置
    bzero(cat_info, sizeof(cat_info));
    sprintf(cat_info, "cat=>%d,%d,%d\n", cat.getX(), cat.getY());
    out.write(cat_info, strlen(cat_info));
    //------------------
    tip_font_show_text("写入存档完毕", 200, 27, 200, 0, 25, 10, 1);
    usleep(500 * 1000);
    lcd_draw_img_jpeg(200, 0, "./img_resource/tip_hide.jpg");
    out.close();
}
void load()
{
    ifstream in;
    in.open("./save/save01.txt");
    if (in.is_open() == -1)
    {
        tip_font_show_text("读取存档失败", 200, 27, 200, 0, 25, 10, 1);
        usleep(500 * 1000);
        lcd_draw_img_jpeg(200, 0, "./img_resource/tip_hide.jpg");
        in.close();
        return;
    }
    // 重置鼠群信息
    head.MouseReset();
    // 重置陷阱信息
    // 先清空容器中的对象
    for (Trap *p : Trap_v)
    {
        delete p;
    }
    Trap_v.clear();
    // 分析鼠头
    char head_info[1024];
    char mouse_info[1024];
    in.getline(head_info, 1024);
    // 分割鼠头信息
    // 查询下x,y,score值
    int x, y, score, bouns;
    char *char_bouns;
    //----------------
    strtok(head_info, "=>");
    char *info = strtok(NULL, "=>");
    // cout << "info:" << info << endl;
    char *char_x = strtok(info, ",");
    // cout << "x" << char_x << endl;
    x = atoi(char_x);
    char *char_y = strtok(NULL, ",");
    y = atoi(char_y);
    char *char_score = strtok(NULL, ",");
    score = atoi(char_score);
    sign = strtok(NULL, ",");
    game_level = atoi(strtok(NULL, ","));
    // cout << "head---x:" << x << "\ty:" << y << "\tscore:" << score << endl;
    head.setX(x);
    head.setY(y);
    head.setScore(score);
    // 查看是否有剩余鼠群数据
    string ret;
    while (!in.eof())
    {
        ret.clear();
        bzero(mouse_info, sizeof(mouse_info));
        in.getline(mouse_info, 1024);
        cout << "mouse_info:" << mouse_info << endl;
        ret.assign(mouse_info);
        cout << "ret:" << ret << endl;
        if (mouse_info[0] != '\0')
        {
            // 读取鼠群数据
            if (ret.compare(0,5,"mouse")==0)
            {
                strtok(mouse_info, "=>");
                info = strtok(NULL, "=>");
                // cout << "info:" << info << endl;
                char_x = strtok(info, ",");
                // cout << "x" << char_x << endl;
                x = atoi(char_x);
                char_y = strtok(NULL, ",");
                y = atoi(char_y);
                //--------------------
                // 添加节点
                // 找到尾部
                Mouse *NewMouse = new Mouse();
                Mouse *tail = NULL;
                tail = head.getPrev();
                tail->setNext(NewMouse);
                NewMouse->setPrev(tail);
                NewMouse->setNext(&head);
                head.setPrev(NewMouse);
                NewMouse->setX(x);
                NewMouse->setY(y);
                mouse_v.push_back(NewMouse);
            }
            // 读取奶酪数据
            else if (ret.compare(0,6,"cheese")==0)
            {
                strtok(mouse_info, "=>");
                info = strtok(NULL, "=>");
                cout << "info:" << info << endl;
                char_x = strtok(info, ",");
                // cout << "x" << char_x << endl;
                x = atoi(char_x);
                char_y = strtok(NULL, ",");
                y = atoi(char_y);
                char_bouns = strtok(NULL, ",");
                bouns = atoi(char_bouns);
                //--------------------
                // 添加节点
                // 找到尾部
                cheese.setX(x);
                cheese.setY(y);
            }
            else if (ret.compare(0,4,"trap")==0)
            {
                strtok(mouse_info, "=>");
                info = strtok(NULL, "=>");
                // cout << "info:" << info << endl;
                char_x = strtok(info, ",");
                // cout << "x" << char_x << endl;
                x = atoi(char_x);
                char_y = strtok(NULL, ",");
                y = atoi(char_y);
                //--------------------
                // 添加节点
                // 找到尾部
                Trap *p = new Trap();
                p->setX(x);
                p->setY(y);
                Trap_v.push_back(p);
            }
            // 读取猫的数据
            else if (ret.compare(0,3,"cat")==0)
            {
                strtok(mouse_info, "=>");
                info = strtok(NULL, "=>");
                // cout << "info:" << info << endl;
                char_x = strtok(info, ",");
                // cout << "x" << char_x << endl;
                x = atoi(char_x);
                char_y = strtok(NULL, ",");
                y = atoi(char_y);
                cat.setX(x);
                cat.setY(y);
            }
        }
    }
    tip_font_show_text("读取存档完毕", 200, 27, 200, 0, 25, 10, 1);
    usleep(500 * 1000);
    lcd_draw_img_jpeg(200, 0, "./img_resource/tip_hide.jpg");
    // 重新显示积分
    char head_score[32];
    sprintf(head_score, "%d", head.getScore());
    Score_font_show_text(head_score, 100, 20, 673, 55, 20, 20, 0);
    // 重新显示奶酪和陷阱
    cheese.show_lcd();
    for (Trap *p : Trap_v)
    {
        p->show_lcd();
    }
    // 显示难度
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
    in.close();
}