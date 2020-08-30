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

    std::string borderTopLeft = "\u25E2";
    std::string borderTopRight = "\u25E3";
    std::string borderBottomLeft = "\u25E5";
    std::string borderBottomRight = "\u25E4";
    std::string borderHorizontal = "\u25AA";
    std::string borderVertical = "\u25AA";

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
