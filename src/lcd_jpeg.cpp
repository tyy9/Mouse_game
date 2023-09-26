#include "lcd_jpeg.h"
int lcd_draw_point_jpeg(int x, int y, unsigned int color)
{
    *(pb + y * 800 + x) = color;
}

int lcd_draw_img_jpeg(int x, int y, const char *pjpg_path)
{
    struct jpeg_decompress_struct cinfo; // 定义jpeg信息结构体
    struct jpeg_error_mgr jerr;          // 定义错误结构体、
    unsigned int color = 0;
    unsigned int x_s = x;
    unsigned int y_s = y;
    FILE *pjpg_file;
    int jpg_fd;
    unsigned int jpg_size;
    unsigned int jpg_width;
    unsigned int jpg_height;
    if ((pjpg_file = fopen(pjpg_path, "rb")) == NULL)
    {
        perror("打开jpeg文件失败\n");
        return -1;
        ;
    }
    // 注册出错处理
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo); // 创建解码
    // 指定解码数据来源
    jpeg_stdio_src(&cinfo, pjpg_file);
    // 读取头部信息
    jpeg_read_header(&cinfo, TRUE);
    // cinfo.scale_num = 1;
    // cinfo.scale_denom = 2;
    // 开始解码
    jpeg_start_decompress(&cinfo);

    unsigned char *p = (unsigned char *)calloc(1, cinfo.output_width * 3);
    unsigned char *pcolor_buf = p;
    // 读解码信息，逐行读取
    while (cinfo.output_scanline < cinfo.output_height)
    {
        // printf("%d,%d\n",cinfo.output_scanline,cinfo.output_height);
        // scanline：已扫描的行数
        pcolor_buf = p;
        // 读取jpg一行的rgb值
        jpeg_read_scanlines(&cinfo, &pcolor_buf, 1);
        // printf("success!\n");
        for (int i = 0; i < cinfo.output_width; i++)
        {
            // 获取rgb值
            color = *(pcolor_buf + 2);              // 因为jpeg读取顺序位rgb,
                                                    // 第一个自然而然就是r，但lcd读取是argb，
                                                    // 所以b需要移动位置
            color = color | *(pcolor_buf + 1) << 8; // g
            color = color | *(pcolor_buf) << 16;    // r
            lcd_draw_point_jpeg(x, y, color);
            pcolor_buf += 3;
            x++;
        }
        // 换行
        y++;
        x = x_s;
    }
    // 解码结束
    jpeg_finish_decompress(&cinfo);
    // 释放资源
    jpeg_destroy_decompress(&cinfo);
    // 释放指针
    free(p);
    fclose(pjpg_file);
    return 0;
}

int lcd_draw_img_jpeg_chat(int x, int y, const char *pjpg_path)
{
    struct jpeg_decompress_struct cinfo; // 定义jpeg信息结构体
    struct jpeg_error_mgr jerr;          // 定义错误结构体、
    unsigned int color = 0;
    unsigned int x_s = x;
    unsigned int y_s = y;
    FILE *pjpg_file;
    int jpg_fd;
    unsigned int jpg_size;
    unsigned int jpg_width;
    unsigned int jpg_height;
    if ((pjpg_file = fopen(pjpg_path, "rb")) == NULL)
    {
        perror("打开jpeg文件失败\n");
        return -1;
        ;
    }
    // 注册出错处理
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo); // 创建解码
    // 指定解码数据来源
    jpeg_stdio_src(&cinfo, pjpg_file);
    // 读取头部信息
    jpeg_read_header(&cinfo, TRUE);
    // 对表情包进行缩小
    printf("jpg--height:%d,width:%d\n", cinfo.image_height, cinfo.image_height);
    int img_height = cinfo.image_height;
    int scale_denom = 0;
    while (img_height > 50)
    {
        img_height = img_height / 2;
        scale_denom += 2;
        printf("缩小:img_height:%d\n",img_height);
    }
    cinfo.scale_num = 1;
    cinfo.scale_denom = scale_denom;
    // 开始解码
    jpeg_start_decompress(&cinfo);
    unsigned char *p = (unsigned char *)calloc(1, cinfo.output_width * 3);
    unsigned char *pcolor_buf = p;
    // 读解码信息，逐行读取
    while (cinfo.output_scanline < cinfo.output_height)
    {
        // printf("%d,%d\n",cinfo.output_scanline,cinfo.output_height);
        // scanline：已扫描的行数
        pcolor_buf = p;
        // 读取jpg一行的rgb值
        jpeg_read_scanlines(&cinfo, &pcolor_buf, 1);
        // printf("success!\n");
        for (int i = 0; i < cinfo.output_width; i++)
        {
            // 获取rgb值
            color = *(pcolor_buf + 2);              // 因为jpeg读取顺序位rgb,
                                                    // 第一个自然而然就是r，但lcd读取是argb，
                                                    // 所以b需要移动位置
            color = color | *(pcolor_buf + 1) << 8; // g
            color = color | *(pcolor_buf) << 16;    // r
            lcd_draw_point_jpeg(x, y, color);
            pcolor_buf += 3;
            x++;
        }
        // 换行
        y++;
        x = x_s;
    }
    // 解码结束
    jpeg_finish_decompress(&cinfo);
    // 释放资源
    jpeg_destroy_decompress(&cinfo);
    // 释放指针
    free(p);
    fclose(pjpg_file);
    return 0;
}