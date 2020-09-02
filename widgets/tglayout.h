#pragma once

#include <QObject>
#include <QPointer>
#include <QPoint>
#include <QSize>

namespace Tg {
class Screen;

class Layout : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QPoint position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(QSize size READ size WRITE setSize NOTIFY sizeChanged)

    friend class Screen;

public:
    explicit Layout(Layout *parent);
    explicit Layout(Screen *parentScreen);
    ~Layout();

    QPoint position() const
    {
        return _position;
    }

    QSize size() const
    {
        return _size;
    }

public slots:
    void setPosition(const QPoint &position)
    {
        if (_position == position)
            return;

        _position = position;
        emit positionChanged(_position);
    }

    void setSize(const QSize &size)
    {
        if (_size == size)
            return;

        _size = size;
        emit sizeChanged(_size);
    }

signals:
    void positionChanged(const QPoint &position) const;
    void sizeChanged(const QSize &size) const;

private:
    QPointer<Screen> _screen;
    QPointer<Layout> _parentWidget;

    QPoint _position = { 1, 1 };
    QSize _size = { 1, 1 };
};
}
