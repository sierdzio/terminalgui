#include "reversibleanimation.h"

#include <QDebug>

Tg::ReversibleAnimation::ReversibleAnimation(QObject *parent)
    : QPropertyAnimation(parent)
{
    init();
}

Tg::ReversibleAnimation::ReversibleAnimation(
    QObject *target, const QByteArray &property, QObject *parent)
    : QPropertyAnimation(target, property, parent)
{
    init();
}

void Tg::ReversibleAnimation::toggleDirection()
{
    if (direction() == ReversibleAnimation::Direction::Forward) {
        setDirection(ReversibleAnimation::Direction::Backward);
    } else {
        setDirection(ReversibleAnimation::Direction::Forward);
    }

    start();

    //qDebug() << "Direction reversed!";
}

void Tg::ReversibleAnimation::init()
{
    connect(this, &ReversibleAnimation::finished,
            this, &ReversibleAnimation::toggleDirection);

    //setLoopCount(-1);
}
