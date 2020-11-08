#pragma once

#include "tgborderstyle.h"

#include <tgcolor.h>

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

        textColor = Tg::Color::Predefined::White;
        backgroundColor = Tg::Color::Predefined::Black;
    }
};
}
