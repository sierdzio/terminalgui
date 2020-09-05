#pragma once

#include "tgborderstyle.h"

#include <backend/backend.h>

namespace Tg {
class TableBorderStyle : public BorderStyle
{
public:
    TableBorderStyle() : BorderStyle()
    {
        width = 1;

        topLeft = "\u2554";
        topRight = "\u2557";
        bottomLeft = "\u255A";
        bottomRight = "\u255D";
        horizontal = "\u2550";
        vertical = "\u2551";

        textColor = Terminal::Color4Bit::White;
        backgroundColor = Terminal::Color4Bit::Black;
    }
};
}
