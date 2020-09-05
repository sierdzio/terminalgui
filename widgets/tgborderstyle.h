#pragma once

#include <backend/backend.h>

#include <QSharedPointer>

namespace Tg {
class BorderStyle
{
public:
    int width = 1;

    std::string topLeft = "\u256D";
    std::string topRight = "\u256E";
    std::string bottomLeft = "\u2570";
    std::string bottomRight = "\u256F";
    std::string horizontal = "\u2500";
    std::string vertical = "\u2502";

    Terminal::Color4Bit textColor = Terminal::Color4Bit::Black;
    Terminal::Color4Bit backgroundColor = Terminal::Color4Bit::Yellow;
};

using BorderStylePointer = QSharedPointer<Tg::BorderStyle>;
}
