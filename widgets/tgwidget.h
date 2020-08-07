#pragma once

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPointer>

#include <QMetaEnum>

#include <backend/backend.h>

namespace Terminal {
    Q_NAMESPACE
    Q_ENUM_NS(Terminal::Color);
}

namespace Tg {
class Screen;

class Widget : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QPoint position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(QSize size READ size WRITE setSize NOTIFY sizeChanged)
    Q_PROPERTY(Terminal::Color backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
    Q_PROPERTY(Terminal::Color textColor READ textColor WRITE setTextColor NOTIFY textColorChanged)
    Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(bool borderVisible READ borderVisible WRITE setBorderVisible NOTIFY borderVisibleChanged)

public:
    explicit Widget(Widget *parent);
    explicit Widget(Screen *parentScreen);
    ~Widget();

    void show();

    QPoint position() const;
    QSize size() const;
    QRect boundingRectangle() const;
    QRect contentsRectangle() const;

    Terminal::Color backgroundColor() const;
    Terminal::Color textColor() const;
    bool visible() const;
    bool borderVisible() const;

    Screen *screen() const;
    Widget *parentWidget() const;

    virtual QString drawPixel(const QPoint &pixel) const;
    bool isBorder(const QPoint &pixel) const;

signals:
    void needsRedraw() const;
    void positionChanged(const QPoint &position) const;
    void sizeChanged(const QSize &size) const;
    void backgroundColorChanged(const Terminal::Color backgroundColor) const;
    void textColorChanged(const Terminal::Color textColor) const;
    void visibleChanged(const bool visible) const;
    void borderVisibleChanged(const bool borderVisible) const;

public slots:
    void setPosition(const QPoint &position);
    void setSize(const QSize &size);
    void setBackgroundColor(const Terminal::Color backgroundColor);
    void setTextColor(const Terminal::Color textColor);
    void setVisible(const bool visible);
    void setBorderVisible(bool borderVisible);

private:
    void init();

    QPointer<Screen> _screen;
    QPointer<Widget> _parentWidget;

    QPoint _position = { 1, 1 };
    QSize _size = { 1, 1 };
    Terminal::Color _backgroundColor = Terminal::Color::Default;
    Terminal::Color _textColor = Terminal::Color::Default;
    bool _visible = false;
    bool _borderVisible = true;
    const int _borderWidth = 1;
};
}
