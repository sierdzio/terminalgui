#include "tglabel.h"
#include "tgscreen.h"
#include "textstream.h"

#include <backend/backend.h>

#include <QRect>
#include <QDebug>

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
    const int charPosition = pixel.x() - position().x();
    result.append(text().at(charPosition));
    result.append(QString::fromStdString(Colors::end));
    return result;
}

void Tg::Label::setText(const QString &text)
{
    if (_text == text)
        return;

    _text = text;

    QSize current(size());
    if (current.width() != _text.length()) {
        current.setWidth(text.length());
        // TODO: multiline labels!
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
