#pragma once

#include <QString>
#include <QMetaType>

namespace Tg {
/*!
 * \brief Represents colors in a terminal.
 */
class Color {
public:
    /*!
     * Contains predefined colors supported by all terminals, including
     * the oldest ones. A terminal emulator can override these colors based
     * on user-chosen profile (TODO: verify this...).
     *
     * \note There is a difference between an Invalid color and an Empty one.
     * With Empty, the terminal will supply a default color in it's place
     * (usually black). With Invalid, code is specifically not defined and
     * should not be replaced by a default one.
     */
    enum class Predefined {
        Invalid = -1,
        Empty = 0,
        Black = 30,
        Red = 31,
        Green = 32,
        Yellow = 33,
        Blue = 34,
        Magenta = 35,
        Cyan = 36,
        White = 37,
        Gray = 90,
        Pink = 91,
        LightRed = Pink,
        LightGreen = 92,
        LightYellow = 93,
        LightBlue = 94,
        LightMagenta = 95,
        LightCyan = 96,
        LightWhite = 97
    };

    /*!
     * Returns ANSI-coded sequence, as understood by terminal, for given
     * \a foreground color and \a background color.
     *
     * For best results, it is recommended for both colors to be of the same
     * type (either Color::Predefined or 24-bit color).
     */
    static QString code(const Color &foreground,
                        const Color &background = Color::Predefined::Empty);

    /*!
     * Returns ANSI-coded sequence, as understood by terminal, for given
     * \a color. Depending on \a isBackground, color will be encoded as
     * background or foreground color (this is important only for
     * Color::Predefined colors).
     *
     * If \a forceTrueColor is `true`, returned sequence will use 24-bit color.
     */
    static QString code(const Color &color, const bool isBackground,
                        const bool forceTrueColor);

    /*!
     * Returns ANSI sequence which ends color definition.
     */
    static QString end();

    Color();
    Color(const Predefined predefined);
    Color(const quint8 red, const quint8 green, const quint8 blue);

    QString rgb() const;
    quint8 red() const;
    quint8 green() const;
    quint8 blue() const;
    Predefined predefined() const;

    bool isEmpty() const;
    bool isPredefined() const;
    bool isTrueColor() const;

    bool operator==(const Color &other) const;
    bool operator!=(const Color &other) const;

private:
    int predefinedValue() const;

    quint8 _red = 0;
    quint8 _green = 0;
    quint8 _blue = 0;

    Predefined _predefined = Predefined::Invalid;
};
}

Q_DECLARE_METATYPE(Tg::Color)
