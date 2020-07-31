#include "tgwidget.h"

TgWidget::TgWidget(QObject *parent) : QObject(parent)
{
}

void TgWidget::show()
{
    setVisible(true);
}

QPoint TgWidget::position() const
{
    return _position;
}

QSize TgWidget::size() const
{
    return _size;
}

Terminal::Color TgWidget::backgroundColor() const
{
    return _backgroundColor;
}

bool TgWidget::visible() const
{
    return _visible;
}

void TgWidget::setPosition(const QPoint &position)
{
    if (_position == position)
        return;

    _position = position;
    emit positionChanged(_position);
}

void TgWidget::setSize(const QSize &size)
{
    if (_size == size)
        return;

    _size = size;
    emit sizeChanged(_size);
}

void TgWidget::setBackgroundColor(const Terminal::Color backgroundColor)
{
    if (_backgroundColor == backgroundColor)
        return;

    _backgroundColor = backgroundColor;
    emit backgroundColorChanged(_backgroundColor);
}

void TgWidget::setVisible(const bool visible)
{
    if (_visible == visible)
        return;

    _visible = visible;

    if (visible)
        draw();

    emit visibleChanged(_visible);
}

void TgWidget::draw()
{
    if (visible()) {
    }
}

