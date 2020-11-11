#pragma once

#include <QString>
#include <QMetaType>

namespace Tg {
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

    Color();
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
