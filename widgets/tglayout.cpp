#include "tglayout.h"
#include "tgscreen.h"

#include <QDebug>

Tg::Layout::Layout(Tg::Layout *parent) : QObject(parent),
    _screen(parent->screen()),
    _parentLayout(parent)
{
}

Tg::Layout::Layout(Tg::Screen *parentScreen) : QObject(parentScreen),
    _screen(parentScreen),
    _parentLayout(nullptr)
{
}

QPoint Tg::Layout::position() const
{
    return _position;
}

QSize Tg::Layout::size() const
{
    return _size;
}

Tg::Screen *Tg::Layout::screen() const
{
    return _screen;
}

Tg::Layout *Tg::Layout::parentLayout() const
{
    return _parentLayout;
}

void Tg::Layout::setPosition(const QPoint &position)
{
    if (_position == position)
        return;

    if (parentLayout() == nullptr) {
        if (position.x() == 0) {
            qWarning() << "Minimal x coordinate on terminal is 1, not 0";
        }

        if (position.y() == 0) {
            qWarning() << "Minimal y coordinate on terminal is 1, not 0";
        }
    }

    _position = position;
    emit positionChanged(_position);
}

void Tg::Layout::setSize(const QSize &size)
{
    if (_size == size)
        return;

    _size = size;
    emit sizeChanged(_size);
}
