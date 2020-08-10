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
    return "\033[" + std::to_string(int(foregroundColor))
        + ";" + std::to_string(int(backgroundColor) + 10) + "m";
}

std::string Terminal::colorEnd()
{
    return "\033[0m";
}

std::string Commands::moveToPosition(const int x, const int y)
{
    return "\033[" + std::to_string(y) + ";" + std::to_string(x) + "H";
}



