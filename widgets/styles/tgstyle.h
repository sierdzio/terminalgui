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
};

using StylePointer = QSharedPointer<Tg::Style>;
}
