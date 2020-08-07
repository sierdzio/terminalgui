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
//    if (visible()) {
//        Tg::TextStream stream(stdout);

//        // TODO: do not clear here, but in screen painter!
//        stream << Commands::clear;

//        if (position().x() > 0 || position().y() > 0) {
//            stream << Commands::moveToPosition(position().x(), position().y());
//        }

//        stream << Terminal::colorCode(textColor());
//        if (boundingRectangle().right() > screen()->size().width()) {
//            QString clippedText = text();
//            clippedText.chop(boundingRectangle().right() - screen()->size().width());
//        } else {
//            stream << text();
//        }
//        stream << Colors::end;
//    }

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
        current.setHeight(1);
        setSize(current);
    }

    emit textChanged(_text);
}

void Tg::Label::init()
{
    connect(this, &Label::textChanged,
            this, &Label::needsRedraw);
}
