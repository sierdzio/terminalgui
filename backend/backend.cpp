#include "backend.h"

QString Terminal::colorCode(const Terminal::Color4Bit foregroundColor,
                                const Terminal::Color4Bit backgroundColor)
{
    const int padding = (backgroundColor == Terminal::Color4Bit::Empty)? 0 : 10;

    return Command::positionBegin
            + QString::number(int(foregroundColor))
            + Command::positionSeparator
            + QString::number(int(backgroundColor) + padding)
            + "m";
}

QString Terminal::colorEnd()
{
    return Terminal::Command::colorEnd;
}

QString Terminal::Command::moveToPosition(const int x, const int y)
{
    return Command::positionBegin + QString::number(y)
            + Command::positionSeparator + QString::number(x) + "H";
}
