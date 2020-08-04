#pragma once

#include <string>

namespace Terminal {
    struct Size {
        int width = 80;
        int height = 24;
    };

    Size updateSize();

    const Size defaultSize;
    static Size size = updateSize();

    enum class Color {
        Default,
        Red,
        Cyan,
        Green
    };
}

// http://www.tldp.org/HOWTO/Bash-Prompt-HOWTO/x361.html
namespace Commands {
const char * const up = "\033[1A";
const char * const down = "\033[1B";

const char * const forward = "\033[1C";
const char * const backward = "\033[1D";

const char * const clear = "\033[2J";
const char * const erase = "\033[K";

const char * const save = "\033[s";
const char * const restore = "\033[u";
}

// http://www.tldp.org/HOWTO/Bash-Prompt-HOWTO/x329.html
namespace Colors {

}
