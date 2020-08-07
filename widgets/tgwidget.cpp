#include "tgwidget.h"
#include "tgscreen.h"

#include <QRect>
#include <QDebug>

Tg::Widget::Widget(Widget *parent)
    : QObject(parent),
      _screen(parent->screen()),
      _parentWidget(parent)
{
    init();
}

Tg::Widget::Widget(Tg::Screen *parentScreen)
    : QObject(parentScreen),
      _screen(parentScreen),
      _parentWidget(nullptr)
{
    init();
}

Tg::Widget::~Widget()
{
    if (_screen) {
        _screen->deregisterWidget(this);
    }
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

QString Tg::Widget::drawPixel(const QPoint &pixel) const
{
    Q_UNUSED(pixel)
    return QString{};
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

    emit visibleChanged(_visible);
}

void Tg::Widget::init()
{
    // TODO: do not emit signal if widget is not visible!
    connect(this, &Widget::sizeChanged,
            this, &Widget::needsRedraw);
    connect(this, &Widget::visibleChanged,
            this, &Widget::needsRedraw);
    connect(this, &Widget::positionChanged,
            this, &Widget::needsRedraw);
    connect(this, &Widget::textColorChanged,
            this, &Widget::needsRedraw);
    connect(this, &Widget::backgroundColorChanged,
            this, &Widget::needsRedraw);

    if (_screen) {
        connect(this, &Widget::needsRedraw,
                _screen, &Screen::onNeedsRedraw);
        _screen->registerWidget(this);
    } else {
        qCritical() << "Screen is missing, can't draw the widget!" << this;
    }
}
