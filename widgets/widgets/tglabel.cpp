#include "tglabel.h"
#include "tgscreen.h"
#include "utils/tghelpers.h"

#include <tgkey.h>
#include <tgcommand.h>

#include <QChar>
#include <QRect>
#include <QDebug>

#include <algorithm>

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
        QSize parentSize(current);
        if (parentWidget()) {
            parentSize = parentWidget()->contentsRectangle().size();
            parentSize.setHeight(parentSize.height() - effectiveBorderWidth());
            parentSize.setWidth(parentSize.width() - effectiveBorderWidth());
        }

        current.setWidth(std::min(qsizetype(parentSize.width()), qsizetype(text.length())));

        const auto shortLayout = generateTextLayout(QSize(current.width(), 1), _text);

        current.setHeight(std::min(qsizetype(parentSize.height()), qsizetype(shortLayout.text.size())));

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
    const auto result = generateTextLayout(contentsRectangle().size(), text());
    _laidOutTextCache = result.text;
    setWidgetOvershoot(result.overshoot);
}

Tg::Label::TextLayout Tg::Label::generateTextLayout(const QSize &size, const QString &text) const
{
    TextLayout result;

    const int width = size.width();
    const int height = size.height();
    const int reserved = reservedCharactersCount();

    // TODO: implement handling for _wrapMode
    // TODO: implement handling for newlines in short strings

    if ((text.size() + reserved) <= width) {
        QString txt;

        if (reserved != 0) {
            txt.append(reservedText());
        }

        txt.append(text);
        while (txt.length() < width) {
            // Fill with spaces
            txt.append(Tg::Key::space);
        }
        result.text.append(txt);

        if (height < 1) {
            result.overshoot = Overshoot::Vertical;
        } else {
            result.overshoot = Overshoot::None;
        }
    } else {
        int currentX = 0;
        int currentY = 0;
        QString currentString;

        if (currentX == 0 && currentY == 0 && reserved != 0) {
            currentString.append(reservedText());
            currentX += reserved;
        }

        const QStringList lines(text.split("\n"));
        for (const QString &line : lines) {
            const QStringList words(line.split(' '));
            for (const QString &word : words) {
                if (wrapMode() == Text::Wrap::Words) {
                    if (currentX + word.length() > width) {
                        breakLine(QChar(), &currentX, &currentY,
                                  &currentString, &result.text);
                    }
                }

                for (const QChar &character : word) {
                    if (currentY >= height) {
                        result.overshoot = result.overshoot | Overshoot::Vertical;
                        break;
                    }

                    if (currentX < width) {
                        currentString.append(character);
                        currentX++;
                    } else {
                        breakLine(character, &currentX, &currentY,
                                  &currentString, &result.text);
                    }
                }

                if (currentX < width) {
                    currentX++;
                    currentString.append(' ');
                }
            }

            breakLine(QChar(), &currentX, &currentY,
                      &currentString, &result.text);
        }

        while (currentString.length() < width) {
            // Fill with spaces
            currentString.append(Tg::Key::space);
        }
        result.text.append(currentString);
    }

    return result;
}

void Tg::Label::breakLine(const QChar &character,
                          int *currentX, int *currentY,
                          QString *currentString, QStringList *result) const
{
    result->append(*currentString);
    currentString->clear();
    currentY++;

    if (character.isNull()) {
        *currentX = 0;
    } else {
        currentString->append(character);
        // One because one character is already added, in line above
        *currentX = 1;
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

Tg::Text::Wrap Tg::Label::wrapMode() const
{
    return _wrapMode;
}

void Tg::Label::setWrapMode(const Text::Wrap newWrapMode)
{
    if (_wrapMode != newWrapMode) {
        _wrapMode = newWrapMode;
        layoutText();
    }
}

void Tg::Label::clear()
{
    setText(QString());
}

