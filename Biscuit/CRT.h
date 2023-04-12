#ifndef CRT_H
#define CRT_H

#ifndef WIN32
#include <stdio.h>
#include <limits.h>
#include <errno.h>

#ifndef _MAX_PATH
#define _MAX_PATH FILENAME_MAX
#endif

typedef error_t errno_t;

static inline errno_t fopen_s(FILE **pFile, const char *filename, const char *mode)
{
    if (*pFile == NULL)
        return -1;

    *pFile = fopen(filename, mode);
    if (*pFile == NULL)
        return errno;
    return 0;
}

#include <unistd.h>
#include <termios.h>

char _getch(void)
{
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    printf("%c\n", buf);
    return buf;
}

#define _fseeki64 fseeko
#define _ftelli64 ftello

#endif
#endif
