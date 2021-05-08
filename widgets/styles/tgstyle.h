#pragma once

#include <tgcolor.h>
#include <tgkey.h>

#include "tgborderstyle.h"

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
    QByteArray screenBackgroundCharacter = Tg::Key::space;

    /*!
     * Color drawn in empty space on a Screen.
     *
     * \todo implement ;-)
     */
    Tg::Color screenBackgroundColor = Tg::Color::Predefined::Empty;

    /*!
     * See Widget::textColor.
     */
    Tg::Color textColor =Tg::Color::Predefined::White;

    /*!
     * See Widget::backgroundColor
     */
    Tg::Color backgroundColor = Tg::Color::Predefined::Black;

    /*!
     * See ListView::alternativeBackgroundColor
     */
    Tg::Color alternativeBackgroundColor = Tg::Color::Predefined::Gray;

    /*!
     * See Widget::backgroundCharacter
     */
    QByteArray backgroundCharacter = Tg::Key::space;

    /*!
     * See LineEdit::placeholderTextColor
     */
    Tg::Color placeholderTextColor = Tg::Color::Predefined::Gray;

    /*!
     * See LineEdit::placeholderBackgroundColor
     */
    Tg::Color placeholderBackgroundColor = Tg::Color::Predefined::Black;

    /*!
     * See Button::activeTextColor
     */
    Tg::Color activeTextColor = Tg::Color::Predefined::Black;

    /*!
     * See Button::activeBackgroundColor
     */
    Tg::Color activeBackgroundColor = Tg::Color::Predefined::White;

    /*!
     * See Button::inactiveTextColor
     */
    Tg::Color inactiveTextColor = Tg::Color::Predefined::White;

    /*!
     * See Button::inactiveBackgroundColor
     */
    Tg::Color inactiveBackgroundColor = Tg::Color::Predefined::Gray;

    /*!
     * See Button::pressedTextColor
     */
    Tg::Color pressedTextColor = Tg::Color::Predefined::Green;

    /*!
     * See Button::pressedBackgroundColor
     */
    Tg::Color pressedBackgroundColor = Tg::Color::Predefined::LightWhite;

    // CheckBox
    // TODO: add these as properties to Tg:Checkbox!
    QString checkBoxChecked = u8"\u2612 ";
    QString checkBoxPartiallyChecked = u8"\u25A3 ";
    QString checkBoxUnChecked = u8"\u2610 ";

    // RadioButton
    // TODO: add these as properties to Tg:RadioButton!
    QString radioButtonChecked = u8"\u25C9 ";
    QString radioButtonUnChecked = u8"\u25CE ";

    // ScrollBar
    // https://decodeunicode.org/en/u+025C8
    QString sliderCharacter = u8"\u25C8";
    Tg::Color sliderColor = Tg::Color::Predefined::Yellow;
    Tg::Color sliderActiveColor = Tg::Color::Predefined::Green;
    Tg::Color sliderInactiveColor = Tg::Color::Predefined::Gray;
    Tg::Color sliderBackgroundColor = Tg::Color::Predefined::Black;
    Tg::Color sliderActiveBackgroundColor = Tg::Color::Predefined::Gray;
    Tg::Color sliderInactiveBackgroundColor = Tg::Color::Predefined::Black;

    QString backwardArrowUpCharacter = u8"\u25B2";
    QString backwardArrowLeftCharacter = u8"\u25C0";
    Tg::Color backwardArrowColor = Tg::Color::Predefined::Green;
    Tg::Color backwardArrowActiveColor = Tg::Color::Predefined::Black;
    Tg::Color backwardArrowInactiveColor = Tg::Color::Predefined::White;
    Tg::Color backwardArrowBackgroundColor = Tg::Color::Predefined::Black;
    Tg::Color backwardArrowActiveBackgroundColor = Tg::Color::Predefined::Green;
    Tg::Color backwardArrowInactiveBackgroundColor = Tg::Color::Predefined::Gray;

    QString forwardArrowDownCharacter = u8"\u25BC";
    QString forwardArrowRightCharacter = u8"\u25B6";
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
