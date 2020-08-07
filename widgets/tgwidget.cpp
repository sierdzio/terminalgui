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

QRect Tg::Widget::contentsRectangle() const
{
    QPoint pos = position();
    pos.setX(pos.x() + _borderWidth);
    pos.setY(pos.y() + _borderWidth);

    QSize siz = size();
    const int twiceBorderWidth = 2 * _borderWidth;
    siz.setWidth(siz.width() - twiceBorderWidth);
    siz.setHeight(siz.height() - twiceBorderWidth);
    return QRect(pos, siz);
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

bool Tg::Widget::borderVisible() const
{
    return _borderVisible;
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
    QString result;
    if (isBorder(pixel)) {
        result.append(QString::fromStdString(Colors::bgBrown));
    } else {
        result.append(QString::fromStdString(Colors::bgGreen));
    }
    result.append(' ');
    result.append(QString::fromStdString(Colors::end));
    return result;
}

bool Tg::Widget::isBorder(const QPoint &pixel) const
{
    if (borderVisible() == false) {
        return false;
    }

    const QRect rect = boundingRectangle();
    if (pixel.x() == rect.left() or pixel.x() == rect.right()) {
        return true;
    }

    if (pixel.y() == rect.top() or pixel.y() == rect.bottom()) {
        return true;
    }

    return false;
}

void Tg::Widget::setPosition(const QPoint &position)
{
    if (_position == position)
        return;

    if (position.x() == 0) {
        qWarning() << "Minimal x coordinate on terminal is 1, not 0";
    }

    if (position.y() == 0) {
        qWarning() << "Minimal y coordinate on terminal is 1, not 0";
    }

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

void Tg::Widget::setBorderVisible(bool borderVisible)
{
    if (_borderVisible == borderVisible)
        return;

    _borderVisible = borderVisible;
    emit borderVisibleChanged(_borderVisible);
}

void Tg::Widget::init()
{
    // TODO: do not emit signal if widget is not visible!
    connect(this, &Widget::sizeChanged,
            this, &Widget::needsRedraw);
    connect(this, &Widget::visibleChanged,
            this, &Widget::needsRedraw);
    connect(this, &Widget::borderVisibleChanged,
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

    if (_parentWidget) {
        setBorderVisible(false);
    }
}
