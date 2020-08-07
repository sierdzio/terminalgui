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

    enum class Color {
        Black,
        Gray,
        Red,
        Pink,
        Green,
        LightGreen,
        Brown,
        Yellow,
        Blue,
        LightBlue,
        Purple,
        LightPurple,
        Cyan,
        LightCyan,
        LightGray,
        White,
        Default = White
    };

    std::string colorCode(const Color color);
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

// http://www.tldp.org/HOWTO/Bash-Prompt-HOWTO/x329.html
/*!
 * To make text colorful, push chosen color to `stdout`, then your text
 * and then make sure your **end** the color declaration with `Colors::end`.
 *
 * This can be automated using Terminal::colorize RAII type.
 */
namespace Colors {
const std::string black = "\033[0;30m";
const std::string gray = "\033[1;30m";

const std::string red = "\033[0;31m";
const std::string pink = "\033[1;31m";

const std::string green = "\033[0;32m";
const std::string lightGreen = "\033[1;32m";

const std::string brown = "\033[0;33m";
const std::string yellow = "\033[1;33m";

const std::string blue = "\033[0;34m";
const std::string lightBlue = "\033[1;34m";

const std::string purple = "\033[0;35m";
const std::string lightPurple = "\033[1;35m";

const std::string cyan = "\033[0;36m";
const std::string lightCyan = "\033[1;36m";

const std::string lightGray = "\033[0;37m";
const std::string white = "\033[1;37m";

const std::string end = "\033[0m";

}

//#define CYAN(x) "\033[1;36m" << x << "\033[0m"
//#define BLUE(x) "\033[1;34m" << x << "\033[0m"
//#define RED(x) "\033[1;31m" << x << "\033[0m"
//#define GREEN(x) "\033[1;32m" << x << "\033[0m"
