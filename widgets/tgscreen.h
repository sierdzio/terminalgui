#pragma once

#include <QObject>
#include <QSize>

namespace Tg {
class Screen : public QObject
{
    Q_OBJECT

    // TODO: differentiate between Terminal size and size of screen reserved
    // for application
    Q_PROPERTY(QSize size READ size NOTIFY sizeChanged)

public:
    Screen(QObject *parent = nullptr);
    ~Screen();

    void waitForQuit();

    QSize size() const;

signals:
    void sizeChanged(const QSize &size) const;

private:
    QSize _size;
};
}
