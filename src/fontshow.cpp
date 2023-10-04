#include "fontshow.h"

struct LcdDevice *init_lcd(const char *device)
{
    // 申请空间
    struct LcdDevice *lcd = (struct LcdDevice *)malloc(sizeof(struct LcdDevice));
    if (lcd == NULL)
    {
        return NULL;
    }

    // 打开LCD设备
    // 打开LCD设备
    lcd->fd = open(device, O_RDWR);
    cout << "font_lcd:" << lcd->fd << endl;
    // 映射
    lcd->mp = (unsigned int *)mmap(NULL, 800 * 480 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, lcd->fd, 0);

    return lcd;
}
// 积分显示
int Score_font_show_text(char *text, int b_length, int b_width,
                         int b_x, int b_y, int text_size, int text_x, int text_y)
{
    struct LcdDevice *lcd = init_lcd("/dev/fb0"); // 初始化画板
                                                  // 歌曲名显示
    char buf[256];
    memset(buf, 0, sizeof(buf));
    strncpy(buf, text, strlen(text));
    //  加载字体
    char p[] = "./other/simfang.ttf";
    font *f = fontLoad(p);
    // 字体大小的设置
    fontSetSize(f, text_size);
    bitmap *bm = createBitmapWithInit(b_length, b_width, 4, getColor(0, 255, 255, 255));
    fontPrint(f, bm, text_x, text_y, buf, getColor(0, 0, 0, 0), 0);
    show_font_to_lcd(lcd->mp, b_x, b_y, bm);
    fontUnload(f);
    destroyBitmap(bm);
    close(lcd->fd);
    free(lcd);
    return 0;
}

// 提示显示
int tip_font_show_text(char *text, int b_length, int b_width,
                       int b_x, int b_y, int text_size, int text_x, int text_y)
{
    struct LcdDevice *lcd = init_lcd("/dev/fb0"); // 初始化画板
                                                  // 歌曲名显示
    char buf[256];
    memset(buf, 0, sizeof(buf));
    strncpy(buf, text, strlen(text));
    //  加载字体
    char p[] = "./other/simfang.ttf";
    font *f = fontLoad(p);
    // 字体大小的设置
    fontSetSize(f, text_size);
    bitmap *bm = createBitmapWithInit(b_length, b_width, 4, getColor(0, 0, 0, 0));
    fontPrint(f, bm, text_x, text_y, buf, getColor(0, 255, 255, 255), 0);
    show_font_to_lcd(lcd->mp, b_x, b_y, bm);
    fontUnload(f);
    destroyBitmap(bm);
    close(lcd->fd);
    free(lcd);
    return 0;
}