#include "backend.h"

// For reading terminal size
// https://stackoverflow.com/questions/1022957/getting-terminal-width-in-c
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

Terminal::Size Terminal::updateSize()
{
    winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    Terminal::Size result;
    result.width = w.ws_col;
    result.height = w.ws_row;
    return result;
}

Terminal::Position Terminal::currentPosition()
{
    winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    Terminal::Position result;
    result.x = w.ws_xpixel;
    result.y = w.ws_ypixel;
    return result;
}

std::string Terminal::colorCode(const Terminal::Color4Bit foregroundColor,
                                const Terminal::Color4Bit backgroundColor)
{
    const int padding = (backgroundColor == Terminal::Color4Bit::Empty)? 0 : 10;

    return "\033[" + std::to_string(int(foregroundColor))
        + ";" + std::to_string(int(backgroundColor) + padding)
        + "m";
}

std::string Terminal::colorEnd()
{
    return Terminal::Command::colorEnd;
}

std::string Terminal::Command::moveToPosition(const int x, const int y)
{
    return "\033[" + std::to_string(y) + ";" + std::to_string(x) + "H";
}

int Terminal::keyboardBufferSize()
{
    int i;
    ioctl(standardInputIndex, FIONREAD, &i);
    return i;
}

// TODO: use termios! Right?
//#include <termios.h>

Terminal::RawTerminalLocker::RawTerminalLocker()
{
    //struct termios term;
    //tcgetattr(standardInputIndex, &term);
    //term.c_lflag &= ~ICANON;
    //tcsetattr(standardInputIndex, TCSANOW, &term);
    //setbuf(stdin, NULL);

    system("stty raw -echo");
}

Terminal::RawTerminalLocker::~RawTerminalLocker()
{
    system("stty cooked echo");
}
