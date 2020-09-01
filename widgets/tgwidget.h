#pragma once

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPointer>
#include <QSharedPointer>

#include <QMetaEnum>

#include <backend/backend.h>

#include "tgstyle.h"
#include "tglayout.h"

#include <string>

namespace Terminal {
    Q_NAMESPACE
    Q_ENUM_NS(Terminal::Color4Bit);
}

namespace Tg {

class Widget : public Layout
{
    Q_OBJECT

    Q_PROPERTY(Terminal::Color4Bit backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
    Q_PROPERTY(Terminal::Color4Bit textColor READ textColor WRITE setTextColor NOTIFY textColorChanged)
    Q_PROPERTY(Terminal::Color4Bit borderTextColor READ borderTextColor WRITE setBorderTextColor NOTIFY borderTextColorChanged)
    Q_PROPERTY(Terminal::Color4Bit borderBackgroundColor READ borderBackgroundColor WRITE setBorderBackgroundColor NOTIFY borderBackgroundColorChanged)

    Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(bool borderVisible READ borderVisible WRITE setBorderVisible NOTIFY borderVisibleChanged)
    Q_PROPERTY(bool acceptsFocus READ acceptsFocus NOTIFY acceptsFocusChanged)
    Q_PROPERTY(bool hasFocus READ hasFocus NOTIFY hasFocusChanged)
    Q_PROPERTY(bool propagatesStyle READ propagatesStyle NOTIFY propagatesStyleChanged)

    friend class Screen;

public:
    explicit Widget(Widget *parent);
    explicit Widget(Screen *parentScreen);
    ~Widget();

    QRect boundingRectangle() const;
    QRect globalBoundingRectangle() const;
    QRect contentsRectangle() const;

    Terminal::Color4Bit backgroundColor() const;
    Terminal::Color4Bit textColor() const;
    Terminal::Color4Bit borderTextColor() const;
    Terminal::Color4Bit borderBackgroundColor() const;

    bool visible() const;
    bool borderVisible() const;
    bool acceptsFocus() const;
    bool hasFocus() const;

    void setAcceptsFocus(const bool acceptsFocus);
    void setHasFocus(const bool hasFocus);

    Screen *screen() const;
    Widget *parentWidget() const;

    virtual std::string drawBorderPixel(const QPoint &pixel) const;
    virtual std::string drawPixel(const QPoint &pixel) const;
    bool isBorder(const QPoint &pixel) const;

    bool verticalArrowsMoveFocus() const;

    QPoint mapFromGlobal(const QPoint &position) const;
    QPoint mapToGlobal(const QPoint &position) const;

    bool propagatesStyle() const;
    void setStyle(const StylePointer &style, const bool propagate = true);

signals:
    void needsRedraw() const;
    void backgroundColorChanged(const Terminal::Color4Bit backgroundColor) const;
    void textColorChanged(const Terminal::Color4Bit textColor) const;
    void borderTextColorChanged(const Terminal::Color4Bit borderColor) const;
    void borderBackgroundColorChanged(const Terminal::Color4Bit borderBackgroundColor) const;
    void visibleChanged(const bool visible) const;
    void borderVisibleChanged(const bool borderVisible) const;
    void acceptsFocusChanged(const bool acceptsFocus) const;
    void hasFocusChanged(const bool hasFocus) const;
    void moveFocusToPreviousWidget() const;
    void moveFocusToNextWidget() const;
    void propagatesStyleChanged(const bool propagatesStyle) const;

public slots:
    void setBackgroundColor(const Terminal::Color4Bit backgroundColor);
    void setTextColor(const Terminal::Color4Bit textColor);
    void setBorderTextColor(Terminal::Color4Bit borderColor);
    void setBorderBackgroundColor(const Terminal::Color4Bit borderBackgroundColor);
    void setVisible(const bool visible);
    void show();
    void hide();
    void setBorderVisible(const bool borderVisible);

protected:
    int effectiveBorderWidth() const;
    bool isColorEmpty(const Terminal::Color4Bit color) const;

    virtual void init();
    virtual void consumeKeyboardBuffer(const QString &keyboardBuffer);

    void setVerticalArrowsMoveFocus(const bool verticalArrowsMoveFocus);
    void setPropagatesStyle(const bool propagatesStyle);

    StylePointer style() const;

protected slots:
    void scheduleRedraw() const;

private:
    const int _borderWidth = 1;

//    QPointer<Screen> _screen;
//    QPointer<Widget> _parentWidget;
    StylePointer _style;

    // TODO: use 256 bit colors by default. Introduce some "Terminal::Color"
    // class which will dynamically switch between color types based
    // on user settings or terminal capabilities
    Terminal::Color4Bit _backgroundColor = Terminal::Color4Bit::Empty;
    Terminal::Color4Bit _textColor = Terminal::Color4Bit::Empty;
    Terminal::Color4Bit _borderTextColor = Terminal::Color4Bit::Empty;
    Terminal::Color4Bit _borderBackgroundColor = Terminal::Color4Bit::Empty;

    bool _visible = false;
    bool _borderVisible = true;
    bool _acceptsFocus = false;
    bool _hasFocus = false;
    bool _verticalArrowsMoveFocus = false;
    bool _propagatesStyle = true;
};
}
