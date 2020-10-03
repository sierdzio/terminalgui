#pragma once

#include <QtGlobal>
#include <QString>

namespace Terminal {

struct Size {
    int width = 80;
    int height = 24;
};

struct Position {
    int x = 0;
    int y = 0;
};

Size updateSize();
Position currentPosition();

const Size defaultSize;
static Size size = updateSize();

class Color {
public:
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

    static QString code(const Color &foregroundColor,
                        const Color &backgroundColor = Color::Predefined::Empty);

    static QString code(const Color &color, const bool isBackground,
                        const bool forceTrueColor);

    static QString end();

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

private:
    int predefinedValue() const;

    quint8 _red = 0;
    quint8 _green = 0;
    quint8 _blue = 0;

    Predefined _predefined = Predefined::Invalid;
};

/*!
 * Returns number of characters available in keyboard buffer.
 */
int keyboardBufferSize();

int getChar();

class RawTerminalLocker {
public:
    RawTerminalLocker();
    ~RawTerminalLocker();
};

const int standardInputIndex = 0;

// http://www.tldp.org/HOWTO/Bash-Prompt-HOWTO/x361.html
// https://en.wikipedia.org/wiki/ANSI_escape_code
namespace Command {
const QString ansiEscape = "\033[";
const QChar ansiEscapeEnd = 'm';
const QChar ansiPositionEnd = 'H';

const QString up = ansiEscape + "1A";
const QString down = ansiEscape + "1B";

const QString forward = ansiEscape + "1C";
const QString backward = ansiEscape + "1D";

const QString clear = ansiEscape + "2J";
const QString erase = ansiEscape + 'K';

const QString save = ansiEscape + 's';
const QString restore = ansiEscape + 'u';

const QString colorEnd = ansiEscape + '0' + ansiEscapeEnd;

const QChar positionSeparator = ';';

const QString bold = ansiEscape + '1' + ansiEscapeEnd;
const QString resetFontSettings = colorEnd;

/*!
 * Returns terminal command which will move the cursor to position \a x, \a y.
 *
 * \warning \a x and \a y start in top left corner of the screen and they both
 * start with `1` (one), not zero!
 */
QString moveToPosition(const int x, const int y);
}

namespace Key {
const QString up = Command::ansiEscape + 'A';
const QString down = Command::ansiEscape + 'B';
const QString right = Command::ansiEscape + 'C';
const QString left = Command::ansiEscape + 'D';

const QChar tab = '\t';
const QChar enter = '\n';
const QChar ret = '\r';
const int backspace = 0x007f;
const QString del = Command::ansiEscape + "3~";
const QChar space = ' ';
}
}
