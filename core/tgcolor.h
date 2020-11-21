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

    /*!
     * Constructs a Color with one of the \a predefined colors.
     *
     * \note Automatic conversion between Predefined and 24 bit color is
     * not supported (yet?).
     */
    Color(const Predefined predefined);

    /*!
     * Constructs a 24 bit color using \a red, \b green and \a blue components.
     *
     * Each variable should be a number between 0 and 255.
     *
     * \note Automatic conversion between 24 bit and Predefined color is
     * not supported (yet?).
     */
    Color(const quint8 red, const quint8 green, const quint8 blue);

    /*!
     * Returns 24 bit color information in a format understood by the terminal.
     * Resulting string looks like this:
     \code
     123;123;123
     \endcode
     *
     * \warning Will return `0;0;0` when Color type is Predefined.
     */
    QString rgb() const;

    /*!
     * Returns intensity of red color.
     *
     * \warning Returns 0 when Color type is Predefined.
     */
    quint8 red() const;

    /*!
     * Returns intensity of green color.
     *
     * \warning Returns 0 when Color type is Predefined.
     */
    quint8 green() const;

    /*!
     * Returns intensity of blue color.
     *
     * \warning Returns 0 when Color type is Predefined.
     */
    quint8 blue() const;

    /*!
     * Returns a Predefined color value if Color is not 24 bit, or
     * Predefined::Invalid otherwise.
     */
    Predefined predefined() const;

    /*!
     * Returns true if a Predefined color is Predefined::Empty. In such case,
     * the terminal will provide a default color.
     */
    bool isEmpty() const;

    /*!
     * Returns true is Color type is Predefined (as opposed to 24 bit color).
     *
     * \sa isTrueColor
     */
    bool isPredefined() const;

    /*!
     * Returns true if Color is 24 bit (as opposed to Predefined).
     *
     * \sa isPredefined
     */
    bool isTrueColor() const;

    /*!
     * Returns true is \a other is the same.
     */
    bool operator==(const Color &other) const;

    /*!
     * Returns true if \a other is different.
     */
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
