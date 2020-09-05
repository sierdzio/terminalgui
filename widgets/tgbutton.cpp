#include "tgbutton.h"
#include "tghelpers.h"

Tg::Button::Button(Tg::Widget *parent) : Tg::Label(parent)
{
    init();
}

Tg::Button::Button(Tg::Screen *screen) : Tg::Label(screen)
{
    init();
}

Tg::Button::Button(const QString &text, Tg::Widget *parent) : Tg::Label(text, parent)
{
    init();
}

Tg::Button::Button(const QString &text, Tg::Screen *screen) : Tg::Label(text, screen)
{
    init();
}

Terminal::Color4Bit Tg::Button::activeTextColor() const
{
    if (isColorEmpty(_activeTextColor)) {
        return style()->activeTextColor;
    } else {
        return _activeTextColor;
    }
}

Terminal::Color4Bit Tg::Button::activeBackgroundColor() const
{
    if (isColorEmpty(_activeBackgroundColor)) {
        return style()->activeBackgroundColor;
    } else {
        return _activeBackgroundColor;
    }
}

Terminal::Color4Bit Tg::Button::inactiveTextColor() const
{
    if (isColorEmpty(_inactiveTextColor)) {
        return style()->inactiveTextColor;
    } else {
        return _inactiveTextColor;
    }
}

Terminal::Color4Bit Tg::Button::inactiveBackgroundColor() const
{
    if (isColorEmpty(_inactiveBackgroundColor)) {
        return style()->inactiveBackgroundColor;
    } else {
        return _inactiveBackgroundColor;
    }
}

Terminal::Color4Bit Tg::Button::pressedTextColor() const
{
    if (isColorEmpty(_pressedTextColor)) {
        return style()->pressedTextColor;
    } else {
        return _pressedTextColor;
    }
}

Terminal::Color4Bit Tg::Button::pressedBackgroundColor() const
{
    if (isColorEmpty(_pressedBackgroundColor)) {
        return style()->pressedBackgroundColor;
    } else {
        return _pressedBackgroundColor;
    }
}

void Tg::Button::setActiveTextColor(const Terminal::Color4Bit activeTextColor)
{
    if (_activeTextColor == activeTextColor)
        return;

    _activeTextColor = activeTextColor;
    emit activeTextColorChanged(_activeTextColor);
}

void Tg::Button::setActiveBackgroundColor(const Terminal::Color4Bit activeBackgroundColor)
{
    if (_activeBackgroundColor == activeBackgroundColor)
        return;

    _activeBackgroundColor = activeBackgroundColor;
    emit activeBackgroundColorChanged(_activeBackgroundColor);
}

void Tg::Button::setInactiveTextColor(const Terminal::Color4Bit inactiveTextColor)
{
    if (_inactiveTextColor == inactiveTextColor)
        return;

    _inactiveTextColor = inactiveTextColor;
    emit inactiveTextColorChanged(_inactiveTextColor);
}

void Tg::Button::setInactiveBackgroundColor(const Terminal::Color4Bit inactiveBackgroundColor)
{
    if (_inactiveBackgroundColor == inactiveBackgroundColor)
        return;

    _inactiveBackgroundColor = inactiveBackgroundColor;
    emit inactiveBackgroundColorChanged(_inactiveBackgroundColor);
}

void Tg::Button::setPressedTextColor(const Terminal::Color4Bit pressedTextColor)
{
    if (_pressedTextColor == pressedTextColor)
        return;

    _pressedTextColor = pressedTextColor;
    emit pressedTextColorChanged(_pressedTextColor);
}

void Tg::Button::setPressedBackgroundColor(const Terminal::Color4Bit pressedBackgroundColor)
{
    if (_pressedBackgroundColor == pressedBackgroundColor)
        return;

    _pressedBackgroundColor = pressedBackgroundColor;
    emit pressedBackgroundColorChanged(_pressedBackgroundColor);
}

void Tg::Button::init()
{
    setAcceptsFocus(true);
    setVerticalArrowsMoveFocus(true);

    Label::init();

    _buttonPressTimer.setInterval(500);
    _buttonPressTimer.setSingleShot(true);

    CHECK(connect(this, &Button::clicked,
                  &_buttonPressTimer, qOverload<>(&QTimer::start)));
    CHECK(connect(&_buttonPressTimer, &QTimer::timeout,
                  this, &Button::onButtonPressTimeout));
    CHECK(connect(this, &Button::hasFocusChanged,
                  this, &Button::onHasFocusChanged));

    CHECK(connect(this, &Button::activeTextColorChanged,
                  this, &Button::scheduleRedraw));
    CHECK(connect(this, &Button::activeBackgroundColorChanged,
                  this, &Button::scheduleRedraw));
    CHECK(connect(this, &Button::inactiveTextColorChanged,
                  this, &Button::scheduleRedraw));
    CHECK(connect(this, &Button::inactiveBackgroundColorChanged,
                  this, &Button::scheduleRedraw));
    CHECK(connect(this, &Button::pressedTextColorChanged,
                  this, &Button::scheduleRedraw));
    CHECK(connect(this, &Button::pressedBackgroundColorChanged,
                  this, &Button::scheduleRedraw));

    if (hasFocus()) {
        setBackgroundColor(activeBackgroundColor());
        setTextColor(activeTextColor());
    } else {
        setBackgroundColor(inactiveBackgroundColor());
        setTextColor(inactiveTextColor());
    }
}

void Tg::Button::consumeKeyboardBuffer(const QString &keyboardBuffer)
{
    if (keyboardBuffer.contains(Helpers::toString(Terminal::Key::enter))
        or keyboardBuffer.contains(Helpers::toString(Terminal::Key::ret)))
    {
        setTextColor(pressedTextColor());
        setBackgroundColor(pressedBackgroundColor());

        emit clicked();
    }
}

void Tg::Button::onButtonPressTimeout()
{
    onHasFocusChanged();
}

void Tg::Button::onHasFocusChanged()
{
    if (hasFocus()) {
        setTextColor(activeTextColor());
        setBackgroundColor(activeBackgroundColor());
    } else {
        setTextColor(style()->inactiveTextColor);
        setBackgroundColor(style()->inactiveBackgroundColor);
    }
}
