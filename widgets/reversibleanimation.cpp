#include "reversibleanimation.h"
#include "tghelpers.h"

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
}

void Tg::ReversibleAnimation::init()
{
    CHECK(connect(this, &ReversibleAnimation::finished,
                  this, &ReversibleAnimation::toggleDirection));
}
