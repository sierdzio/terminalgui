#include "tgcolor.h"
#include "tgterminal.h"
#include "tgcommand.h"

Tg::Color::Color() : _predefined(Color::Predefined::Empty)
{
}

Tg::Color::Color(const Tg::Color::Predefined predefined)
    : _predefined(predefined)
{
}

Tg::Color::Color(const quint8 red, const quint8 green, const quint8 blue)
    : _red(red), _green(green), _blue(blue)
{
}

QString Tg::Color::code(const Tg::Color &foregroundColor,
                              const Tg::Color &backgroundColor)
{
    const bool forceTrueColor = (foregroundColor.isPredefined() == false)
            || (backgroundColor.isPredefined() == false);

    return Command::ansiEscape
            + code(foregroundColor, false, forceTrueColor)
            + Command::separator
            + code(backgroundColor, true, forceTrueColor)
            + Command::ansiEscapeEnd;
}

QString Tg::Color::code(const Tg::Color &color,
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

QString Tg::Color::end()
{
    return Command::colorEnd;
}

QString Tg::Color::rgb() const
{
    return QString::number(_red) + Command::separator
            + QString::number(_green) + Command::separator
            + QString::number(_blue);
}

quint8 Tg::Color::red() const
{
    return _red;
}

quint8 Tg::Color::green() const
{
    return _green;
}

quint8 Tg::Color::blue() const
{
    return _blue;
}

Tg::Color::Predefined Tg::Color::predefined() const
{
    return _predefined;
}

bool Tg::Color::isEmpty() const
{
    if (isPredefined()) {
        return _predefined == Tg::Color::Predefined::Empty;
    } else {
        // TODO: support empty true color
        //return _red == 0 && _green == 0 && _blue == 0;
        return false;
    }
}

bool Tg::Color::isPredefined() const
{
    return _predefined != Color::Predefined::Invalid;
}

bool Tg::Color::isTrueColor() const
{
    return !isPredefined();
}

bool Tg::Color::operator==(const Tg::Color &other) const
{
    if (isPredefined() && other.isPredefined()) {
        return predefined() == other.predefined();
    } else {
        return (red() == other.red()
                && green() == other.green()
                && blue() == other.blue());
    }
}

bool Tg::Color::operator!=(const Tg::Color &other) const
{
    return !operator==(other);
}

int Tg::Color::predefinedValue() const
{
    return int(_predefined);
}
