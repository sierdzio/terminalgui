#include "tglabel.h"
#include "tgscreen.h"
#include "textstream.h"

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

std::string Tg::Label::drawPixel(const QPoint &pixel) const
{
    if (isBorder(pixel)) {
        return Tg::Widget::drawPixel(pixel);
    }

    std::string result;
    result.append(Terminal::colorCode(textColor(), backgroundColor()));

    const int charX = pixel.x() - position().x();
    const int charY = pixel.y() - position().y();

    const QStringList wrappedText(_laidOutTextCache);
    result.push_back(wrappedText.at(charY).at(charX).unicode());
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
        current.setHeight(_text.isEmpty()? 0 : 1);
        setSize(current);
    }

    emit textChanged(_text);
}

void Tg::Label::init()
{
    connect(this, &Label::textChanged,
            this, &Label::needsRedraw);
    connect(this, &Label::needsRedraw,
            this, &Label::layoutText);
}

void Tg::Label::layoutText()
{
    _laidOutTextCache.clear();

    const int width = size().width();
    const int height = size().height();
    if (text().size() <= width) {
        _laidOutTextCache.append(text());
        return;
    } else {
        int currentX = 0;
        int currentY = 0;
        QString currentString;
        for (const QChar &character : text()) {
            if (currentY > height) {
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
