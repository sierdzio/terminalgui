#include "backend.h"

QString Terminal::Color::code(const Terminal::Color &foregroundColor,
                              const Terminal::Color &backgroundColor)
{
    if (foregroundColor._predefined != Predefined::Invalid) {
        const int padding = (backgroundColor._predefined == Predefined::Empty)?
                    0 : 10;

        return Command::positionBegin
                + QString::number(foregroundColor.predefinedValue())
                + Command::positionSeparator
                + QString::number(backgroundColor.predefinedValue() + padding)
                + "m";
    } else {
        // ESC[ 38;2;⟨r⟩;⟨g⟩;⟨b⟩ m Select RGB foreground color
        // ESC[ 48;2;⟨r⟩;⟨g⟩;⟨b⟩ m Select RGB background color
        return Command::positionBegin
                + "38;2;" + foregroundColor.rgb()
                + Command::positionSeparator
                + "48;2;" + backgroundColor.rgb();
    }
}

QString Terminal::Color::end()
{
    return Terminal::Command::colorEnd;
}

Terminal::Color::Color(const Terminal::Color::Predefined predefined)
    : _predefined(predefined)
{
}

Terminal::Color::Color(const quint8 red, const quint8 green, const quint8 blue)
    : _red(red), _green(green), _blue(blue)
{
}

QString Terminal::Color::rgb() const
{
    return QString::number(_red) + Command::positionSeparator
            + QString::number(_green) + Command::positionSeparator
            + QString::number(_blue) + Command::positionSeparator;
}

int Terminal::Color::predefinedValue() const
{
    return int(_predefined);
}

QString Terminal::Command::moveToPosition(const int x, const int y)
{
    return Command::positionBegin + QString::number(y)
            + Command::positionSeparator + QString::number(x) + "H";
}
