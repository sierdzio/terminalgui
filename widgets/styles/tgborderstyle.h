#pragma once

#include <tgcolor.h>

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

    Tg::Color textColor = Tg::Color::Predefined::White;
    Tg::Color backgroundColor = Tg::Color::Predefined::Black;

    Tg::Color overshootTextColor = Tg::Color::Predefined::Red;
    Tg::Color overshootBackgroundColor = Tg::Color::Predefined::Black;
};

using BorderStylePointer = QSharedPointer<Tg::BorderStyle>;
}
