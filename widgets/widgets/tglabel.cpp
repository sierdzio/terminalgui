#include "tglabel.h"
#include "tgscreen.h"
#include "utils/tghelpers.h"

#include <tgkey.h>
#include <tgcommand.h>

#include <QRect>
#include <QDebug>

Tg::Label::Label(Tg::Widget *parent) : Tg::Widget(parent)
{
    Label::init();
}

Tg::Label::Label(Tg::Screen *screen) : Tg::Widget(screen)
{
    Label::init();
}

Tg::Label::Label(const QString &text, Widget *parent) : Tg::Widget(parent)
{
    setText(text, true);
    Label::init();
}

Tg::Label::Label(const QString &text, Tg::Screen *screen) : Tg::Widget(screen)
{
    setText(text, true);
    Label::init();
}

QString Tg::Label::text() const
{
    return _text;
}

QString Tg::Label::drawPixel(const QPoint &pixel) const
{
    if (isBorder(pixel)) {
        return drawBorderPixel(pixel);
    }

    QString result;
    result.append(Tg::Color::code(textColor(), backgroundColor()));

    const QRect contents = contentsRectangle();
    const int charX = pixel.x() - contents.x();
    const int charY = pixel.y() - contents.y();

    const QStringList wrappedText(_laidOutTextCache);

    if (charY < wrappedText.size()) {
        const QString line(wrappedText.at(charY));

        if (line.size() > charX) {
            if (highlighted()) {
                result.append(Tg::Command::bold);
            }
            result.append(line.at(charX).unicode());
        } else {
            result.append(Tg::Key::space);
        }
    } else {
        result.append(Tg::Key::space);
    }

    return result;
}

bool Tg::Label::highlighted() const
{
    return _highlighted;
}

void Tg::Label::setText(const QString &text, const bool expand)
{
    if (_text == text)
        return;

    _text = text;

    QSize current(size());
    if (expand && current.width() != _text.length()) {
        current.setWidth(text.length());
        current.setHeight(1);
        setSize(current);
    }

    emit textChanged(_text);
}

void Tg::Label::setHighlighted(const bool highlighted)
{
    if (_highlighted == highlighted)
        return;

    _highlighted = highlighted;
    emit highlightedChanged(_highlighted);
}

void Tg::Label::init()
{
    CHECK(connect(this, &Label::needsRedraw,
                  this, &Label::layoutText));
    CHECK(connect(this, &Label::textChanged,
                  this, &Label::schedulePartialRedraw));
    CHECK(connect(this, &Label::highlightedChanged,
                  this, &Label::schedulePartialRedraw));

    Widget::init();
}

void Tg::Label::layoutText()
{
    _laidOutTextCache.clear();
    SizeOvershoot overshoot = widgetOvershoot();

    const QRect contents = contentsRectangle();
    const int width = contents.width();
    const int height = contents.height();
    const int reserved = reservedCharactersCount();

    if ((text().size() + reserved) <= width) {
        QString txt;

        if (reserved != 0) {
            txt.append(reservedText());
        }

        txt.append(text());
        while (txt.length() < width) {
            // Fill with spaces
            txt.append(Tg::Key::space);
        }
        _laidOutTextCache.append(txt);
        return;
    } else {
        int currentX = 0;
        int currentY = 0;
        QString currentString;

        if (currentX == 0 && currentY == 0 && reserved != 0) {
            currentString.append(reservedText());
            currentX += reserved;
        }

        const QString &fullText(text());
        for (const QChar &character : fullText) {
            if (currentY > height) {
                overshoot = overshoot | Overshoot::Vertical;
                setWidgetOvershoot(overshoot);
                break;
            }

            if (currentX < width) {
                currentString.append(character);
                currentX++;
            } else {
                _laidOutTextCache.append(currentString);
                currentString.clear();
                currentY++;
                currentString.append(character);
                // One because one character is already added, in line above
                currentX = 1;
            }
        }

        while (currentString.length() < width) {
            // Fill with spaces
            currentString.append(Tg::Key::space);
        }
        _laidOutTextCache.append(currentString);
    }
}

int Tg::Label::reservedCharactersCount() const
{
    return _reservedText.length();
}

QString Tg::Label::reservedText() const
{
    return _reservedText;
}

void Tg::Label::setReservedText(const QString &reserved)
{
    if (_reservedText != reserved) {
        _reservedText = reserved;
        emit textChanged(text());
    }
}
