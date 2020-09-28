#pragma once

#include "tgborderstyle.h"

#include <backend.h>

namespace Tg {
class TableBorderStyle : public BorderStyle
{
public:
    TableBorderStyle() : BorderStyle()
    {
        width = 1;

        topLeft = u8"\u2554";
        topRight = u8"\u2557";
        bottomLeft = u8"\u255A";
        bottomRight = u8"\u255D";
        horizontal = u8"\u2550";
        vertical = u8"\u2551";

        textColor = Terminal::Color::Predefined::White;
        backgroundColor = Terminal::Color::Predefined::Black;
    }
};
}
