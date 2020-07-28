#pragma once

#include <QObject>
#include <QPoint>
#include <QSize>

#include <QColor>

class ConsoleWidget : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QPoint position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(QSize size READ size WRITE setSize NOTIFY sizeChanged)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
    Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibleChanged)

public:
    explicit ConsoleWidget(QObject *parent = nullptr);

    virtual void show();

    QPoint position() const;
    QSize size() const;
    QColor backgroundColor() const;
    bool visible() const;

public slots:
    void setPosition(const QPoint &position);
    void setSize(const QSize &size);
    void setBackgroundColor(const QColor &backgroundColor);
    void setVisible(const bool visible);

signals:
    void positionChanged(const QPoint &position) const;
    void sizeChanged(const QSize &size) const;
    void backgroundColorChanged(const QColor &backgroundColor) const;
    void visibleChanged(const bool visible) const;

protected:
    virtual void draw();

private:
    QPoint _position = { 0, 0 };
    QSize _size = { 0, 0 };
    QColor _backgroundColor = Qt::GlobalColor::gray;
    bool _visible = false;
};

