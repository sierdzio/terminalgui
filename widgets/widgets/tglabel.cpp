#include "tglabel.h"
#include "tgscreen.h"
#include "utils/tghelpers.h"

#include <backend/backend.h>

#include <QRect>
#include <QDebug>

Tg::Label::Label(Tg::Widget *parent) : Tg::Widget(parent)
{
    init();
}

Tg::Label::Label(Tg::Screen *screen) : Tg::Widget(screen)
{
    init();
}

Tg::Label::Label(const QString &text, Widget *parent) : Tg::Widget(parent)
{
    setText(text);
    init();
}

Tg::Label::Label(const QString &text, Tg::Screen *screen) : Tg::Widget(screen)
{
    setText(text);
    init();
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
    result.append(Terminal::colorCode(textColor(), backgroundColor()));

    const QRect contents = contentsRectangle();
    const int charX = pixel.x() - contents.x();
    const int charY = pixel.y() - contents.y();

    const QStringList wrappedText(_laidOutTextCache);

    if (charY < wrappedText.size()) {
        const QString line(wrappedText.at(charY));

        if (line.size() > charX) {
            result.push_back(line.at(charX).unicode());
        } else {
            result.push_back(' ');
        }
    } else {
        result.push_back(' ');
    }

    return result;
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

void Tg::Label::init()
{
    CHECK(connect(this, &Label::needsRedraw,
                  this, &Label::layoutText));
    CHECK(connect(this, &Label::textChanged,
                  this, &Label::scheduleRedraw));

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
            txt.append(' ');
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

        for (const QChar &character : text()) {
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
            currentString.append(' ');
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
