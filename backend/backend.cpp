#include "backend.h"

QString Terminal::Color::code(const Terminal::Color &foregroundColor,
                              const Terminal::Color &backgroundColor)
{
    const bool forceTrueColor = (foregroundColor.isPredefined() == false)
            || (backgroundColor.isPredefined() == false);

    return Command::ansiEscape
            + code(foregroundColor, false, forceTrueColor)
            + Command::positionSeparator
            + code(backgroundColor, true, forceTrueColor)
            + Command::ansiEscapeEnd;
}

QString Terminal::Color::code(const Terminal::Color &color,
                              const bool isBackground,
                              const bool forceTrueColor)
{
    // https://stackoverflow.com/questions/4842424/list-of-ansi-color-escape-sequences
    // and
    // https://gist.github.com/XVilka/8346728
    if (forceTrueColor || color.predefined() == Predefined::Invalid) {
        // ESC[ 38;2;⟨r⟩;⟨g⟩;⟨b⟩ m Select RGB foreground color
        // ESC[ 48;2;⟨r⟩;⟨g⟩;⟨b⟩ m Select RGB background color
        const int padding = isBackground? 10 : 0;
        return QString::number(38 + padding) + QStringLiteral(";2;") + color.rgb();
    } else {
        const int padding = (isBackground && color._predefined != Predefined::Empty)?
                    10 : 0;
        return QString::number(color.predefinedValue() + padding);
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
            + QString::number(_blue);
}

quint8 Terminal::Color::red() const
{
    return _red;
}

quint8 Terminal::Color::green() const
{
    return _green;
}

quint8 Terminal::Color::blue() const
{
    return _blue;
}

Terminal::Color::Predefined Terminal::Color::predefined() const
{
    return _predefined;
}

bool Terminal::Color::isEmpty() const
{
    if (isPredefined()) {
        return _predefined == Terminal::Color::Predefined::Empty;
    } else {
        //return _red == 0 && _green == 0 && _blue == 0;
        return false;
    }
}

bool Terminal::Color::isPredefined() const
{
    return _predefined != Terminal::Color::Predefined::Invalid;
}

bool Terminal::Color::isTrueColor() const
{
    return !isPredefined();
}

bool Terminal::Color::operator==(const Terminal::Color &other) const
{
    if (isPredefined() && other.isPredefined()) {
        return predefined() == other.predefined();
    } else {
        return (red() == other.red()
                && green() == other.green()
                && blue() == other.blue());
    }
}

int Terminal::Color::predefinedValue() const
{
    return int(_predefined);
}

QString Terminal::Command::moveToPosition(const int x, const int y)
{
    return Command::ansiEscape + QString::number(y)
            + Command::positionSeparator + QString::number(x)
            + Command::ansiPositionEnd;
}
