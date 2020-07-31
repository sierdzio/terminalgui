#pragma once

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
