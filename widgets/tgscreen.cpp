#include "tgscreen.h"

#include <backend/backend.h>

#include <QDebug>

TgScreen::TgScreen(QObject *parent) : QObject(parent)
{
    const Terminal::Size size = Terminal::updateSize();
    _size.setWidth(size.width);
    _size.setHeight(size.height);
    emit sizeChanged(_size);

    _timer.setInterval(1000);
    _timer.setSingleShot(false);
    _timer.setTimerType(Qt::TimerType::VeryCoarseTimer);

    connect(&_timer, &QTimer::timeout,
            this, &TgScreen::checkIfQuit);

    //qDebug() << "TgScreen info:" << position() << size();
}

TgScreen::~TgScreen()
{
}

void TgScreen::waitForQuit()
{
    _timer.start();
}

QSize TgScreen::size() const
{
    return _size;
}

void TgScreen::checkIfQuit()
{
    //noecho();
    const int character = std::getchar();
    if (character == 'q') {
        emit end();
    }
}
