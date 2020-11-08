#include "tgterminal.h"

// For reading terminal size
// https://stackoverflow.com/questions/1022957/getting-terminal-width-in-c
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

QSize Tg::Terminal::updateSize()
{
    winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return QSize(w.ws_col, w.ws_row);
}

QPoint Tg::Terminal::currentPosition()
{
    winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return QPoint(w.ws_xpixel, w.ws_ypixel);
}

int Tg::Terminal::keyboardBufferSize()
{
    int i;
    ioctl(standardInputIndex, FIONREAD, &i);
    return i;
}

int Tg::Terminal::getChar()
{
    return getchar();
}

// TODO: use termios! Right?
//#include <termios.h>

Tg::RawTerminalLocker::RawTerminalLocker()
{
    //struct termios term;
    //tcgetattr(standardInputIndex, &term);
    //term.c_lflag &= ~ICANON;
    //tcsetattr(standardInputIndex, TCSANOW, &term);
    //setbuf(stdin, NULL);

    system("stty raw -echo");
}

Tg::RawTerminalLocker::~RawTerminalLocker()
{
    system("stty cooked echo");
}
