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

    Q_PROPERTY(bool fillParent READ fillParent WRITE setFillParent NOTIFY fillParentChanged)

    friend class Screen;

public:
    explicit Layout(Layout *parent);
    explicit Layout(Screen *parentScreen);

    Screen *screen() const;
    Layout *parentLayout() const;

    QPoint position() const;
    QSize size() const;
    bool fillParent() const;


public slots:
    void setPosition(const QPoint &position);
    void setSize(const QSize &size);
    void setFillParent(const bool fillParent);

signals:
    void positionChanged(const QPoint &position) const;
    void sizeChanged(const QSize &size) const;
    void fillParentChanged(const bool fillParent) const;

private:
    QPointer<Screen> _screen;
    QPointer<Layout> _parentLayout;

    QPoint _position = { 1, 1 };
    QSize _size = { 1, 1 };
    bool _fillParent = false;
};
}
