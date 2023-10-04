#include"device_global.h"

int fd_lcd;
int *pb;
int fd;
int fd_touch;

int lcd_open()
{
    fd_lcd = open("/dev/fb0", O_RDWR);
    cout<<"fd_lcd:"<<fd_lcd<<endl;
    if (fd_lcd == -1)
    {
        perror("打开lcd失败\n");
        return -1;
    }
    pb = (int*)mmap(NULL,
              800 * 480 * 4,
              PROT_READ | PROT_WRITE,
              MAP_SHARED,
              fd_lcd,
              0);
    if (pb == NULL)
    {
        perror("mmap error\n");
        return -1;
    }
    return 0;
}

void lcd_draw_point(int x, int y, unsigned int color)
{
    *(pb + y * 800 + x) = color;
}

int lcd_close(void)
{
    if (fd_lcd > 0)
    {
        close(fd_lcd);
    }
    if (pb)
    {
        munmap(pb, 800 * 480 * 4);
    }
    return 0;
}
int inittouch_device(int *fd)
{
    *fd = open("/dev/input/event0", O_RDONLY);
    cout<<"touch:"<<*fd<<endl;
    if (fd < 0)
    {
        perror("触摸屏打开失败\n");
        return -1;
    }
    return 0;
}
