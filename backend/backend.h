#pragma once

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

// TODO: dedicated color class, supporting various color standards
enum class Color4Bit {
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

enum class ColorType {
    Foreground,
    Background
};

QString colorCode(const Color4Bit foregroundColor,
                  const Color4Bit backgroundColor = Color4Bit::Empty);
QString colorEnd();

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

const QString tab = "\t";
const QString enter = "\n";
const QString ret = "\r";
const int backspace = 0x007f;
const QString del = "\033[3~";
const QString space = " ";
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
const QString positionSeparator = ";";

/*!
 * Returns terminal command which will move the cursor to position \a x, \a y.
 *
 * \warning \a x and \a y start in top left corner of the screen and they both
 * start with `1` (one), not zero!
 */
QString moveToPosition(const int x, const int y);
}
}
