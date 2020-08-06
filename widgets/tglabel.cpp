#include "tglabel.h"

#include "textstream.h"
#include <backend/backend.h>

Tg::Label::Label(const QString &text, QObject *parent) : Tg::Widget(parent)
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
        //stream << Colors::end;

        if (position().x() > 0 || position().y() > 0) {
            stream << Commands::moveToPosition(position().x(), position().y());
            //stream << Colors::end;
        }

        stream << Terminal::colorCode(textColor());
        //if (position().x() + text().size() > screen.size())
        stream << text();
        stream << Colors::end;
    }
}
