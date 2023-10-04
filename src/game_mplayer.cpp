#include "game_mplayer.h"
FILE *mapler_fp_music; // 音乐进程
FILE *mapler_fp_sfx;   // 音效进程
int fd_music;          // 音乐有名管道标识符
int fd_sfx;            // 音效有名管道标识符

void mplayer_init(int *fd, char *FIFO_PATH)
{
    if (access(FIFO_PATH, F_OK) < 0)
    {
        mkfifo(FIFO_PATH, 0777);
    }
    *fd = open(FIFO_PATH, O_RDWR | O_TRUNC);
    cout << "music_fd:" << *fd << endl;
    // 扩大管道大小
    int newPipeSize = 4096;
    int result = fcntl(*fd, F_SETPIPE_SZ, newPipeSize);
    if (result == -1)
    {
        close(*fd);
        cout << "修改管道大小失败" << endl;
        throw CustomException();
    }
}
void send_cmd_music(char *cmd)
{
    write(fd_music, cmd, strlen(cmd));
}
void music_init()
{
    try
    {
        /* code */
        mplayer_init(&fd_music, FIFO_FILE_MUSIC);
    }
    catch (exception &e)
    {
        e.what();
    }

    if (fd_music < 0)
    {
        close(fd_music);
        cout << "music有名管道打开失败" << endl;
        throw CustomException();
    }

    // 创建music进程
    char buf[256];
    //使用虚拟声卡0
    sprintf(buf, "mplayer -slave -quiet  -input file=%s -loop 0  %s&", FIFO_FILE_MUSIC, MUSIC_FILE);
    mapler_fp_music = popen(buf, "r");
    if (mapler_fp_music == NULL)
    {
        fclose(mapler_fp_music);
        cout << "创建音乐进程失败" << endl;
        throw CustomException();
    }
    send_cmd_music("volume 20 1\n");
}
void send_cmd_sfx(char *cmd)
{
    write(fd_sfx, cmd, 1024);
}
void sfx_init()
{
    try
    {
        /* code */
        mplayer_init(&fd_sfx, FIFO_FILE_SFX);
    }
    catch (exception &e)
    {
        e.what();
    }

    if (fd_sfx < 0)
    {
        close(fd_sfx);
        cout << "sfx有名管道打开失败" << endl;
        throw CustomException();
    }

    // 创建music进程
    char buf[256];
    //使用虚拟声卡1
    sprintf(buf, "mplayer -slave -quiet  -input file=%s  %s&", FIFO_FILE_SFX, SFX_FILE);
    mapler_fp_sfx = popen(buf, "r");
    if (mapler_fp_sfx == NULL)
    {
        fclose(mapler_fp_sfx);
        cout << "创建音效进程失败" << endl;
        throw CustomException();
    }
}