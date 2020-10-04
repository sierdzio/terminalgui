#pragma once

#include <backend.h>

#include "tgborderstyle.h"

#include <QSharedPointer>

#include <QChar>
#include <QString>

namespace Tg {
class Style
{
public:
    BorderStyle *border = new BorderStyle;
    void setBorderStyleValues(const BorderStyle &borderStyle);

    // Screen
    QChar screenBackground = Terminal::Key::space;

    // Base widget
    Terminal::Color textColor =Terminal::Color::Predefined::White;
    Terminal::Color backgroundColor = Terminal::Color::Predefined::Black;
    QChar backgroundCharacter = Terminal::Key::space;

    // LineEdit
    Terminal::Color placeholderTextColor = Terminal::Color::Predefined::Gray;
    Terminal::Color placeholderBackgroundColor = Terminal::Color::Predefined::Black;

    // Button
    Terminal::Color activeTextColor = Terminal::Color::Predefined::Black;
    Terminal::Color activeBackgroundColor = Terminal::Color::Predefined::White;

    Terminal::Color inactiveTextColor = Terminal::Color::Predefined::White;
    Terminal::Color inactiveBackgroundColor = Terminal::Color::Predefined::Gray;

    Terminal::Color pressedTextColor = Terminal::Color::Predefined::Green;
    Terminal::Color pressedBackgroundColor = Terminal::Color::Predefined::LightWhite;

    // CheckBox
    QString checkBoxChecked = u8"\u2612 ";
    QString checkBoxPartiallyChecked = u8"\u25A3 ";
    QString checkBoxUnChecked = u8"\u2610 ";

    // RadioButton
    QString radioButtonChecked = u8"\u25C9 ";
    QString radioButtonUnChecked = u8"\u25CE ";

    // ScrollBar
    // https://decodeunicode.org/en/u+025C8
    QChar sliderCharacter = 0x025C8;
    Terminal::Color sliderColor = Terminal::Color::Predefined::White;
    Terminal::Color sliderBackgroundColor = Terminal::Color::Predefined::Gray;
    Terminal::Color sliderActiveColor = Terminal::Color::Predefined::Green;

    QChar backwardArrowUpCharacter = 0x025B2;
    QChar backwardArrowLeftCharacter = 0x025C0;
    Terminal::Color backwardArrowColor = Terminal::Color::Predefined::Green;
    Terminal::Color backwardArrowActiveColor = Terminal::Color::Predefined::Black;
    Terminal::Color backwardArrowInactiveColor = Terminal::Color::Predefined::White;
    Terminal::Color backwardArrowBackgroundColor = Terminal::Color::Predefined::Black;
    Terminal::Color backwardArrowActiveBackgroundColor = Terminal::Color::Predefined::Green;
    Terminal::Color backwardArrowInactiveBackgroundColor = Terminal::Color::Predefined::Gray;

    QChar forwardArrowDownCharacter = 0x025BC;
    QChar forwardArrowRightCharacter = 0x025B6;
    Terminal::Color forwardArrowColor = backwardArrowColor;
    Terminal::Color forwardArrowActiveColor = backwardArrowActiveColor;
    Terminal::Color forwardArrowInactiveColor = backwardArrowInactiveColor;
    Terminal::Color forwardArrowBackgroundColor = backwardArrowBackgroundColor;
    Terminal::Color forwardArrowActiveBackgroundColor = backwardArrowActiveBackgroundColor;
    Terminal::Color forwardArrowInactiveBackgroundColor = backwardArrowInactiveBackgroundColor;
};

using StylePointer = QSharedPointer<Tg::Style>;
}
