#pragma once

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPointer>

#include <QMetaEnum>

#include <backend/backend.h>

#include <string>

namespace Terminal {
    Q_NAMESPACE
    Q_ENUM_NS(Terminal::Color4Bit);
}

namespace Tg {
class Screen;

class Widget : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QPoint position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(QSize size READ size WRITE setSize NOTIFY sizeChanged)
    Q_PROPERTY(Terminal::Color4Bit backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
    Q_PROPERTY(Terminal::Color4Bit textColor READ textColor WRITE setTextColor NOTIFY textColorChanged)
    Q_PROPERTY(Terminal::Color4Bit borderColor READ borderColor WRITE setBorderColor NOTIFY borderColorChanged)
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

    Terminal::Color4Bit backgroundColor() const;
    Terminal::Color4Bit textColor() const;
    Terminal::Color4Bit borderColor() const;

    bool visible() const;
    bool borderVisible() const;

    Screen *screen() const;
    Widget *parentWidget() const;

    virtual std::string drawPixel(const QPoint &pixel) const;
    bool isBorder(const QPoint &pixel) const;

signals:
    void needsRedraw() const;
    void positionChanged(const QPoint &position) const;
    void sizeChanged(const QSize &size) const;
    void backgroundColorChanged(const Terminal::Color4Bit backgroundColor) const;
    void textColorChanged(const Terminal::Color4Bit textColor) const;
    void borderColorChanged(const Terminal::Color4Bit borderColor) const;
    void visibleChanged(const bool visible) const;
    void borderVisibleChanged(const bool borderVisible) const;

public slots:
    void setPosition(const QPoint &position);
    void setSize(const QSize &size);
    void setBackgroundColor(const Terminal::Color4Bit backgroundColor);
    void setTextColor(const Terminal::Color4Bit textColor);
    void setBorderColor(Terminal::Color4Bit borderColor);
    void setVisible(const bool visible);
    void setBorderVisible(const bool borderVisible);

private:
    void init();
    int effectiveBorderWidth() const;

    QPointer<Screen> _screen;
    QPointer<Widget> _parentWidget;

    QPoint _position = { 1, 1 };
    QSize _size = { 1, 1 };
    // TODO: use 256 bit colors by default. Introduce some "Terminal::Color"
    // class which will dynamically switch between color types based
    // on user settings or terminal capabilities
    Terminal::Color4Bit _backgroundColor = Terminal::Color4Bit::Gray;
    Terminal::Color4Bit _textColor = Terminal::Color4Bit::White;
    Terminal::Color4Bit _borderColor = Terminal::Color4Bit::LightBlue;
    bool _visible = false;
    bool _borderVisible = true;
    const int _borderWidth = 1;
};
}
