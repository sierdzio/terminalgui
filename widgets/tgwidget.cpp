#include "tgwidget.h"

Tg::Widget::Widget(QObject *parent) : QObject(parent)
{
}

void Tg::Widget::show()
{
    setVisible(true);
}

QPoint Tg::Widget::position() const
{
    return _position;
}

QSize Tg::Widget::size() const
{
    return _size;
}

Terminal::Color Tg::Widget::backgroundColor() const
{
    return _backgroundColor;
}

Terminal::Color Tg::Widget::textColor() const
{
    return _textColor;
}

bool Tg::Widget::visible() const
{
    return _visible;
}

void Tg::Widget::setPosition(const QPoint &position)
{
    if (_position == position)
        return;

    _position = position;
    emit positionChanged(_position);
}

void Tg::Widget::setSize(const QSize &size)
{
    if (_size == size)
        return;

    _size = size;
    emit sizeChanged(_size);
}

void Tg::Widget::setBackgroundColor(const Terminal::Color backgroundColor)
{
    if (_backgroundColor == backgroundColor)
        return;

    _backgroundColor = backgroundColor;
    emit backgroundColorChanged(_backgroundColor);
}

void Tg::Widget::setTextColor(const Terminal::Color textColor)
{
    if (_textColor == textColor)
        return;

    _textColor = textColor;
    emit textColorChanged(_textColor);
}

void Tg::Widget::setVisible(const bool visible)
{
    if (_visible == visible)
        return;

    _visible = visible;

    if (visible)
        draw();

    emit visibleChanged(_visible);
}

void Tg::Widget::draw()
{
    if (visible()) {
    }
}
