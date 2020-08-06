#include "tgscreen.h"

#include <backend/backend.h>

#include <QDebug>

Tg::Screen::Screen(QObject *parent) : QObject(parent)
{
    const Terminal::Size size = Terminal::updateSize();
    _size.setWidth(size.width);
    _size.setHeight(size.height);
    emit sizeChanged(_size);

    qDebug() << "TgScreen info:" << _size.width() << _size.height();
}

Tg::Screen::~Screen()
{
}

QSize Tg::Screen::size() const
{
    return _size;
}
