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

    QPoint position() const;
    QSize size() const;

    Screen *screen() const;
    Layout *parentLayout() const;

public slots:
    void setPosition(const QPoint &position);
    void setSize(const QSize &size);

signals:
    void positionChanged(const QPoint &position) const;
    void sizeChanged(const QSize &size) const;

private:
    QPointer<Screen> _screen;
    QPointer<Layout> _parentLayout;

    QPoint _position = { 1, 1 };
    QSize _size = { 1, 1 };
};
}
