#pragma once

#include <backend/backend.h>

#include <QSharedPointer>

namespace Tg {
class Style
{
public:
    // TODO: separate into class BorderStyle?
    // Borders
    int borderWidth = 1;

    std::string borderTopLeft = "\u256D";
    std::string borderTopRight = "\u256E";
    std::string borderBottomLeft = "\u2570";
    std::string borderBottomRight = "\u256F";
    std::string borderHorizontal = "\u2500";
    std::string borderVertical = "\u2502";

//    std::string borderTopLeft = "\u2554";
//    std::string borderTopRight = "\u2557";
//    std::string borderBottomLeft = "\u255A";
//    std::string borderBottomRight = "\u255D";
//    std::string borderHorizontal = "\u2550";
//    std::string borderVertical = "\u2551";

    Terminal::Color4Bit borderTextColor = Terminal::Color4Bit::Black;
    Terminal::Color4Bit borderBackgroundColor = Terminal::Color4Bit::Yellow;

    // Base widget
    Terminal::Color4Bit textColor = Terminal::Color4Bit::White;
    Terminal::Color4Bit backgroundColor = Terminal::Color4Bit::Black;

    // LineEdit
    Terminal::Color4Bit placeholderTextColor = Terminal::Color4Bit::Gray;
    Terminal::Color4Bit placeholderBackgroundColor = Terminal::Color4Bit::Black;

    // Button
    Terminal::Color4Bit activeTextColor = Terminal::Color4Bit::Black;
    Terminal::Color4Bit activeBackgroundColor = Terminal::Color4Bit::White;

    Terminal::Color4Bit inactiveTextColor = Terminal::Color4Bit::White;
    Terminal::Color4Bit inactiveBackgroundColor = Terminal::Color4Bit::Gray;

    Terminal::Color4Bit pressedTextColor = Terminal::Color4Bit::Green;
    Terminal::Color4Bit pressedBackgroundColor = Terminal::Color4Bit::LightWhite;
};

using StylePointer = QSharedPointer<const Tg::Style>;
}
