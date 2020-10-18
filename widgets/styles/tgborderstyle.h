#pragma once

#include <backend.h>

#include <QString>
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

    QChar horizontalOvershoot = 0x025BC;
    QChar verticalOvershoot = 0x025B6;

    Terminal::Color textColor = Terminal::Color::Predefined::White;
    Terminal::Color backgroundColor = Terminal::Color::Predefined::Black;

    Terminal::Color overshootTextColor = Terminal::Color::Predefined::Red;
    Terminal::Color overshootBackgroundColor = Terminal::Color::Predefined::Black;
};

using BorderStylePointer = QSharedPointer<Tg::BorderStyle>;
}
