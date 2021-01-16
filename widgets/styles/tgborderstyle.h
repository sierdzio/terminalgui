#pragma once

#include <tgcolor.h>

#include <QString>
#include <QSharedPointer>

namespace Tg {
/*!
 * Defines colors, characters with which Widget draws it's borders.
 *
 * For information about styling of Widget contents, see Style.
 */
class BorderStyle
{
public:
    //! Border width. \warning Values other than `1` are not supported
    int width = 1;

    //! Character used to draw top left corner
    QString topLeft = u8"\u256D";

    //! Character used to draw top right corner
    QString topRight = u8"\u256E";

    //! Character used to draw bottom left corner
    QString bottomLeft = u8"\u2570";

    //! Character used to draw bottom right corner
    QString bottomRight = u8"\u256F";

    //! Character used to draw all horizontal edges
    QString horizontal = u8"\u2500";

    //! Character used to draw all vertical edges
    QString vertical = u8"\u2502";

    //! Character used to draw resizable corner "icon"
    QString resizableCorner = u8"\u25C6";

    //! Character used to draw horizontal overshoot (when Widget contents do not
    //! fit it's size)
    QChar horizontalOvershoot = uint(0x025BC);

    //! Character used to draw vertical overshoot (when Widget contents do not
    //! fit it's size)
    QChar verticalOvershoot = uint(0x025B6);

    //! Color used to draw border characters
    Tg::Color textColor = Tg::Color::Predefined::White;

    //! Color used to draw border background
    Tg::Color backgroundColor = Tg::Color::Predefined::Black;

    //! Color used to draw overshoot characters
    Tg::Color overshootTextColor = Tg::Color::Predefined::Red;

    //! Color used to draw overshoot background
    Tg::Color overshootBackgroundColor = Tg::Color::Predefined::Black;
};

using BorderStylePointer = QSharedPointer<Tg::BorderStyle>;
}
