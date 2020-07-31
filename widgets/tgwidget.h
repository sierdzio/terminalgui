#pragma once

#include <QObject>
#include <QPoint>
#include <QSize>

#include <QMetaEnum>

#include <backend/backend.h>

namespace Terminal {
    Q_NAMESPACE
    Q_ENUM_NS(Terminal::Color);
}

class TgWidget : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QPoint position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(QSize size READ size WRITE setSize NOTIFY sizeChanged)
    Q_PROPERTY(Terminal::Color backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
    Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibleChanged)

public:
    explicit TgWidget(QObject *parent = nullptr);

    virtual void show();

    QPoint position() const;
    QSize size() const;
    Terminal::Color backgroundColor() const;
    bool visible() const;

public slots:
    void setPosition(const QPoint &position);
    void setSize(const QSize &size);
    void setBackgroundColor(const Terminal::Color backgroundColor);
    void setVisible(const bool visible);

signals:
    void positionChanged(const QPoint &position) const;
    void sizeChanged(const QSize &size) const;
    void backgroundColorChanged(const Terminal::Color backgroundColor) const;
    void visibleChanged(const bool visible) const;

protected:
    virtual void draw();

private:
    QPoint _position = { 0, 0 };
    QSize _size = { 0, 0 };
    Terminal::Color _backgroundColor = Terminal::Color::Default;
    bool _visible = false;
};

