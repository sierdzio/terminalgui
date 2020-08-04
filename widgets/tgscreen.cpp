#include "tgscreen.h"

#include <backend/backend.h>

#include <QDebug>

Tg::Screen::Screen(QObject *parent) : QObject(parent)
{
    const Terminal::Size size = Terminal::updateSize();
    _size.setWidth(size.width);
    _size.setHeight(size.height);
    emit sizeChanged(_size);

    _timer.setInterval(1000);
    _timer.setSingleShot(false);
    _timer.setTimerType(Qt::TimerType::VeryCoarseTimer);

    connect(&_timer, &QTimer::timeout,
            this, &Screen::checkIfQuit);

    _timer.start();

    qDebug() << "TgScreen info:" << _size.width() << _size.height();
}

Tg::Screen::~Screen()
{
}

void Tg::Screen::waitForQuit()
{
    _timer.start();
}

QSize Tg::Screen::size() const
{
    return _size;
}

void Tg::Screen::checkIfQuit()
{
    const int character = std::getchar();
    if (character == 'q') {
        emit end();
    }
}
