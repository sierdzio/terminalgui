#pragma once

#include <QtGlobal>
#include <QString>
#include <QObject>

namespace Terminal {
Q_NAMESPACE

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
    Q_ENUM_NS(Predefined);

    static QString code(const Color &foregroundColor,
                        const Color &backgroundColor = Color::Predefined::Empty);
    static QString end();

    Color(const Predefined predefined);
    Color(const quint8 red, const quint8 green, const quint8 blue);

    QString rgb() const;

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

namespace Key {
const QString up = "\033[A";
const QString down = "\033[B";
const QString right = "\033[C";
const QString left = "\033[D";

const QChar tab = '\t';
const QChar enter = '\n';
const QChar ret = '\r';
const int backspace = 0x007f;
const QString del = "\033[3~";
const QChar space = ' ';
}

// http://www.tldp.org/HOWTO/Bash-Prompt-HOWTO/x361.html
// https://en.wikipedia.org/wiki/ANSI_escape_code
namespace Command {
const QString up = "\033[1A";
const QString down = "\033[1B";

const QString forward = "\033[1C";
const QString backward = "\033[1D";

const QString clear = "\033[2J";
const QString erase = "\033[K";

const QString save = "\033[s";
const QString restore = "\033[u";

const QString colorEnd = "\033[0m";

const QString positionBegin = "\033[";
const QChar positionSeparator = ';';

const QString bold = "\033[1m";
const QString resetFontSettings = colorEnd;

/*!
 * Returns terminal command which will move the cursor to position \a x, \a y.
 *
 * \warning \a x and \a y start in top left corner of the screen and they both
 * start with `1` (one), not zero!
 */
QString moveToPosition(const int x, const int y);
}
}
