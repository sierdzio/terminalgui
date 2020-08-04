#pragma once

#include <QPropertyAnimation>

namespace Tg {
class ReversibleAnimation : public QPropertyAnimation
{
    Q_OBJECT

public:
    explicit ReversibleAnimation(QObject *parent = nullptr);
    explicit ReversibleAnimation(QObject *target, const QByteArray &property,
                                 QObject *parent = nullptr);

public slots:
    void toggleDirection();

private:
    void init();
};
}
