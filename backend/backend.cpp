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

// TODO: use std::hash instead!
std::string Terminal::colorCode(const Terminal::Color color)
{
    switch (color) {
    case Terminal::Color::Black:
        return Colors::black;
    case Terminal::Color::Gray:
        return Colors::gray;
    case Terminal::Color::Red:
        return Colors::red;
    case Terminal::Color::Pink:
        return Colors::pink;
    case Terminal::Color::Green:
        return Colors::green;
    case Terminal::Color::LightGreen:
        return Colors::lightGreen;
    case Terminal::Color::Brown:
        return Colors::brown;
    case Terminal::Color::Yellow:
        return Colors::yellow;
    case Terminal::Color::Blue:
        return Colors::blue;
    case Terminal::Color::LightBlue:
        return Colors::lightBlue;
    case Terminal::Color::Purple:
        return Colors::purple;
    case Terminal::Color::LightPurple:
        return Colors::lightPurple;
    case Terminal::Color::Cyan:
        return Colors::cyan;
    case Terminal::Color::LightCyan:
        return Colors::lightCyan;
    case Terminal::Color::LightGray:
        return Colors::lightGray;
    case Terminal::Color::White:
        return Colors::white;
    }

    return std::string();
}

std::string Commands::moveToPosition(const int x, const int y)
{
    return "\033[" + std::to_string(y) + ";" + std::to_string(x) + "H";
}

