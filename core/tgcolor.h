#pragma once

#include <QString>
#include <QMetaType>

namespace Tg {
/*!
 * \brief Represents colors in a terminal.
 *
 * In terminals, color is used mainly in 2 places:
 * \li foreground (text color)
 * \li background (background color - painted behind text)
 *
 * Each character ("pixel") inside the terminal can have these 2 colors set
 * completely independently. Use Color::code() to get a ready-made
 *
 * Terminal GUI supports 2 color schemes: Predefined and 24 bit (true color).
 * Currently Color class does not convert colors of one type to another.
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
     *
     * \todo Add automatic conversion between Predefined and 24 bit colors.
     */
    enum class Predefined {
        //! Color is not defined and cannot be drawn. Used to indicate unset colors
        Invalid = -1,
        //! Color is defined as empty - default terminal color will be used
        Empty = 0,
        //! Default black color, depends on terminal settings
        Black = 30,
        //! Default red color, depends on terminal settings
        Red = 31,
        //! Default green color, depends on terminal settings
        Green = 32,
        //! Default yellow color, depends on terminal settings
        Yellow = 33,
        //! Default blue color, depends on terminal settings
        Blue = 34,
        //! Default magenta color, depends on terminal settings
        Magenta = 35,
        //! Default cyan color, depends on terminal settings
        Cyan = 36,
        //! Default white color, depends on terminal settings
        White = 37,
        //! Default gray color, depends on terminal settings
        Gray = 90,
        //! Default pink color, depends on terminal settings
        Pink = 91,
        LightRed = Pink,
        //! Default lighter green color, depends on terminal settings
        LightGreen = 92,
        //! Default lighter yellow color, depends on terminal settings
        LightYellow = 93,
        //! Default lighter blue color, depends on terminal settings
        LightBlue = 94,
        //! Default lighter magenta color, depends on terminal settings
        LightMagenta = 95,
        //! Default lighter cyan color, depends on terminal settings
        LightCyan = 96,
        //! Default lighter white color, depends on terminal settings. How can
        //! white be any lighter? It's usually ligter than Predefined::Gray,
        //! but not as white as Predefined::White. It's weird
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

    /*!
     * Constructs a color of type Predefined (it's set to Predefined::Invalid).
     */
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
