#include "tgwidget.h"

ConsoleWidget::ConsoleWidget(QObject *parent) : QObject(parent)
{
}

void ConsoleWidget::show()
{
    setVisible(true);
}

QPoint ConsoleWidget::position() const
{
    return _position;
}

QSize ConsoleWidget::size() const
{
    return _size;
}

//QColor ConsoleWidget::backgroundColor() const
//{
//    return _backgroundColor;
//}

bool ConsoleWidget::visible() const
{
    return _visible;
}

void ConsoleWidget::setPosition(const QPoint &position)
{
    if (_position == position)
        return;

    _position = position;
    emit positionChanged(_position);
}

void ConsoleWidget::setSize(const QSize &size)
{
    if (_size == size)
        return;

    _size = size;
    emit sizeChanged(_size);
}

//void ConsoleWidget::setBackgroundColor(const QColor &backgroundColor)
//{
//    if (_backgroundColor == backgroundColor)
//        return;

//    _backgroundColor = backgroundColor;
//    emit backgroundColorChanged(_backgroundColor);
//}

void ConsoleWidget::setVisible(const bool visible)
{
    if (_visible == visible)
        return;

    _visible = visible;
    emit visibleChanged(_visible);
}

void ConsoleWidget::draw()
{
    if (visible()) {
    }
}

