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

QString Tg::Label::drawPixel(const QPoint &pixel) const
{
    QString result;
    result.append(QString::fromStdString(Terminal::colorCode(textColor())));

    const int charX = pixel.x() - position().x();
    const int charY = pixel.y() - position().y();
    // TODO: optimize. Do text layout only once!
    const QStringList wrappedText(layoutText());
    result.append(wrappedText.at(charY).at(charX));
    result.append(QString::fromStdString(Colors::end));
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
}

QStringList Tg::Label::layoutText() const
{
    QStringList result;

    const int width = size().width();
    const int height = size().height();
    if (text().size() <= width) {
        result.append(text());
        return result;
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
                result.append(currentString);
                currentString.clear();
                currentString.append(character);
                currentY++;
                currentX = 0;
            }
        }

        // Make sure last row is inserted:
        if (result.contains(currentString) == false) {
            while (currentString.length() < width) {
                // Fill with spaces
                currentString.append(' ');
            }
            result.append(currentString);
        }
    }

    return result;
}
