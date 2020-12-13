#pragma once

#include <tgcolor.h>
#include <tgkey.h>

#include "tgborderstyle.h"

#include <QChar>
#include <QString>

namespace Tg {
/*!
 * Defines how Widget (and all it's subclasses) draw their contents.
 *
 * Colors and characters composing borders are handled by BorderStyle.
 */
class Style
{
public:
    /*!
     * Style object used to draw Widget borders.
     */
    BorderStyle *border = new BorderStyle;

    /*!
     * Copies all information from \a borderStyle into border object held by
     * this Style object.
     */
    void setBorderStyleValues(const BorderStyle &borderStyle);

    /*!
     * Character drawn in empty space on a Screen.
     *
     * \todo implement ;-)
     */
    QChar screenBackground = Tg::Key::space;

    // Base widget
    Tg::Color textColor =Tg::Color::Predefined::White;
    Tg::Color backgroundColor = Tg::Color::Predefined::Black;
    Tg::Color alternativeBackgroundColor = Tg::Color::Predefined::Gray;
    QChar backgroundCharacter = Tg::Key::space;

    // LineEdit
    Tg::Color placeholderTextColor = Tg::Color::Predefined::Gray;
    Tg::Color placeholderBackgroundColor = Tg::Color::Predefined::Black;

    // Button
    Tg::Color activeTextColor = Tg::Color::Predefined::Black;
    Tg::Color activeBackgroundColor = Tg::Color::Predefined::White;

    Tg::Color inactiveTextColor = Tg::Color::Predefined::White;
    Tg::Color inactiveBackgroundColor = Tg::Color::Predefined::Gray;

    Tg::Color pressedTextColor = Tg::Color::Predefined::Green;
    Tg::Color pressedBackgroundColor = Tg::Color::Predefined::LightWhite;

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
    Tg::Color sliderColor = Tg::Color::Predefined::Yellow;
    Tg::Color sliderActiveColor = Tg::Color::Predefined::Green;
    Tg::Color sliderInactiveColor = Tg::Color::Predefined::Gray;
    Tg::Color sliderBackgroundColor = Tg::Color::Predefined::Black;
    Tg::Color sliderActiveBackgroundColor = Tg::Color::Predefined::Gray;
    Tg::Color sliderInactiveBackgroundColor = Tg::Color::Predefined::Black;

    QChar backwardArrowUpCharacter = 0x025B2;
    QChar backwardArrowLeftCharacter = 0x025C0;
    Tg::Color backwardArrowColor = Tg::Color::Predefined::Green;
    Tg::Color backwardArrowActiveColor = Tg::Color::Predefined::Black;
    Tg::Color backwardArrowInactiveColor = Tg::Color::Predefined::White;
    Tg::Color backwardArrowBackgroundColor = Tg::Color::Predefined::Black;
    Tg::Color backwardArrowActiveBackgroundColor = Tg::Color::Predefined::Green;
    Tg::Color backwardArrowInactiveBackgroundColor = Tg::Color::Predefined::Gray;

    QChar forwardArrowDownCharacter = 0x025BC;
    QChar forwardArrowRightCharacter = 0x025B6;
    Tg::Color forwardArrowColor = backwardArrowColor;
    Tg::Color forwardArrowActiveColor = backwardArrowActiveColor;
    Tg::Color forwardArrowInactiveColor = backwardArrowInactiveColor;
    Tg::Color forwardArrowBackgroundColor = backwardArrowBackgroundColor;
    Tg::Color forwardArrowActiveBackgroundColor = backwardArrowActiveBackgroundColor;
    Tg::Color forwardArrowInactiveBackgroundColor = backwardArrowInactiveBackgroundColor;

    // ListView
    Tg::Color currentIndexColor = Tg::Color::Predefined::Cyan;
};
}
