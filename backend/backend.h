#pragma once

#include <string>

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

std::string colorCode(const Color4Bit foregroundColor,
                      const Color4Bit backgroundColor = Color4Bit::Empty);
std::string colorEnd();

/*!
 * Returns number of characters available in keyboard buffer.
 */
int keyboardBufferSize();

class RawTerminalLocker {
public:
    RawTerminalLocker();
    ~RawTerminalLocker();
};

const int standardInputIndex = 0;

namespace Key {
const std::string up = "\033[A";
const std::string down = "\033[B";
const std::string right = "\033[C";
const std::string left = "\033[D";

const std::string tab = "\t";
const std::string enter = "\n";
const std::string ret = "\r";
const int backspace = 0x007f;
const std::string del = "\033[3~";
}

// http://www.tldp.org/HOWTO/Bash-Prompt-HOWTO/x361.html
// https://en.wikipedia.org/wiki/ANSI_escape_code
namespace Command {
const std::string up = "\033[1A";
const std::string down = "\033[1B";

const std::string forward = "\033[1C";
const std::string backward = "\033[1D";

const std::string clear = "\033[2J";
const std::string erase = "\033[K";

const std::string save = "\033[s";
const std::string restore = "\033[u";

const std::string colorEnd = "\033[0m";

/*!
 * Returns terminal command which will move the cursor to position \a x, \a y.
 *
 * \warning \a x and \a y start in top left corner of the screen and they both
 * start with `1` (one), not zero!
 */
std::string moveToPosition(const int x, const int y);
}
}
