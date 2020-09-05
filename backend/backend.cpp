#include "backend.h"



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
