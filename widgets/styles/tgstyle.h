#pragma once

#include <backend/backend.h>

#include "tgborderstyle.h"

#include <QSharedPointer>

#include <QString>

namespace Tg {
class Style
{
public:
    BorderStyle *border = new BorderStyle;
    void setBorderStyleValues(const BorderStyle &borderStyle);

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

    // CheckBox
    QString checkBoxChecked = u8"\u2612 ";
    QString checkBoxPartiallyChecked = u8"\u25A3 ";
    QString checkBoxUnChecked = u8"\u2610 ";

    // RadioButton
    QString radioButtonChecked = u8"\u25C9 ";
    QString radioButtonUnChecked = u8"\u25CE ";
};

using StylePointer = QSharedPointer<Tg::Style>;
}
