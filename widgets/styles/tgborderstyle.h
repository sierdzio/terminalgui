#pragma once

#include <backend.h>

#include <QSharedPointer>

namespace Tg {
class BorderStyle
{
public:
    int width = 1;

    QString topLeft = u8"\u256D";
    QString topRight = u8"\u256E";
    QString bottomLeft = u8"\u2570";
    QString bottomRight = u8"\u256F";
    QString horizontal = u8"\u2500";
    QString vertical = u8"\u2502";

    QString horizontalOvershoot = u8"\u25BC";
    QString verticalOvershoot = u8"\u25B6";

    Terminal::Color4Bit textColor = Terminal::Color4Bit::White;
    Terminal::Color4Bit backgroundColor = Terminal::Color4Bit::Black;

    Terminal::Color4Bit overshootTextColor = Terminal::Color4Bit::Red;
    Terminal::Color4Bit overshootBackgroundColor = Terminal::Color4Bit::Black;
};

using BorderStylePointer = QSharedPointer<Tg::BorderStyle>;
}
