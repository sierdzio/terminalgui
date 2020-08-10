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
}

// http://www.tldp.org/HOWTO/Bash-Prompt-HOWTO/x361.html
// https://en.wikipedia.org/wiki/ANSI_escape_code
namespace Commands {
const std::string up = "\033[1A";
const std::string down = "\033[1B";

const std::string forward = "\033[1C";
const std::string backward = "\033[1D";

const std::string clear = "\033[2J";
const std::string erase = "\033[K";

const std::string save = "\033[s";
const std::string restore = "\033[u";

/*!
 * Returns terminal command which will move the cursor to position \a x, \a y.
 *
 * \warning \a x and \a y start in top left corner of the screen and they both
 * start with `1` (one), not zero!
 */
std::string moveToPosition(const int x, const int y);
}
