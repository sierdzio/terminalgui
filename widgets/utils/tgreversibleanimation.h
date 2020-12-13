#pragma once

#include <QPropertyAnimation>

namespace Tg {
/*!
 * Small convenience class: a property animation which goes backwards after
 * it reaches it's end, thus forming a "to and from" looped animation.
 */
class ReversibleAnimation : public QPropertyAnimation
{
    Q_OBJECT

public:
    /*!
     * Constructs an empty animation with \a parent.
     */
    explicit ReversibleAnimation(QObject *parent = nullptr);

    /*!
     * Constructs an animation on a particular \a property of \a target.
     * The QObject \a parent is here only for standard Qt parent-child
     * hierarchy.
     */
    explicit ReversibleAnimation(QObject *target, const QByteArray &property,
                                 QObject *parent = nullptr);

private slots:
    void toggleDirection();

private:
    void init();
};
}
