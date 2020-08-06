#include "tglabel.h"
#include "tgscreen.h"
#include "textstream.h"

#include <backend/backend.h>

#include <QRect>

Tg::Label::Label(const QString &text, Widget *parent) : Tg::Widget(parent)
{
    setText(text);
}

Tg::Label::Label(const QString &text, Tg::Screen *screen) : Tg::Widget(screen)
{
    setText(text);
}

QString Tg::Label::text() const
{
    return _text;
}

void Tg::Label::setText(const QString &text)
{
    if (_text == text)
        return;

    _text = text;

    QSize current(size());
    if (current.width() != _text.length()) {
        current.setWidth(text.length());
        setSize(current);
    }

    emit textChanged(_text);
    draw();
}

void Tg::Label::draw()
{
    if (visible()) {
        Tg::TextStream stream(stdout);

        // TODO: do not clear here, but in screen painter!
        stream << Commands::clear;

        if (position().x() > 0 || position().y() > 0) {
            stream << Commands::moveToPosition(position().x(), position().y());
        }

        stream << Terminal::colorCode(textColor());
        if (boundingRectangle().right() > screen()->size().width()) {
            QString clippedText = text();
            clippedText.chop(boundingRectangle().right() - screen()->size().width());
        } else {
            stream << text();
        }
        stream << Colors::end;
    }
}
