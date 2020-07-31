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
