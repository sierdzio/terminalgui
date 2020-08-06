#include "tgwidget.h"
#include "tgscreen.h"

#include <QRect>

Tg::Widget::Widget(Widget *parent)
    : QObject(parent),
      _screen(parent->screen()),
      _parentWidget(parent)
{
}

Tg::Widget::Widget(Tg::Screen *parentScreen)
    : QObject(parentScreen),
      _screen(parentScreen),
      _parentWidget(nullptr)
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

QRect Tg::Widget::boundingRectangle() const
{
    return QRect(position(), size());
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

Tg::Screen *Tg::Widget::screen() const
{
    return _screen;
}

Tg::Widget *Tg::Widget::parentWidget() const
{
    return _parentWidget;
}

void Tg::Widget::setPosition(const QPoint &position)
{
    if (_position == position)
        return;

    _position = position;
    emit positionChanged(_position);
    draw();
}

void Tg::Widget::setSize(const QSize &size)
{
    if (_size == size)
        return;

    _size = size;
    emit sizeChanged(_size);
    draw();
}

void Tg::Widget::setBackgroundColor(const Terminal::Color backgroundColor)
{
    if (_backgroundColor == backgroundColor)
        return;

    _backgroundColor = backgroundColor;
    emit backgroundColorChanged(_backgroundColor);
    draw();
}

void Tg::Widget::setTextColor(const Terminal::Color textColor)
{
    if (_textColor == textColor)
        return;

    _textColor = textColor;
    emit textColorChanged(_textColor);
    draw();
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
//    if (visible()) {
//    }
}
