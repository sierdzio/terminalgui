#include "tgbutton.h"
#include "utils/tghelpers.h"

Tg::Button::Button(Tg::Widget *parent) : Tg::Label(parent)
{
    init();
}

Tg::Button::Button(Tg::Screen *screen) : Tg::Label(screen)
{
    init();
}

Tg::Button::Button(const QString &text, Tg::Widget *parent)
    : Tg::Label(text, parent)
{
    init();
}

Tg::Button::Button(const QString &text, Tg::Screen *screen)
    : Tg::Label(text, screen)
{
    init();
}

Terminal::Color Tg::Button::activeTextColor() const
{
    if (_activeTextColor.isEmpty()) {
        return style()->activeTextColor;
    } else {
        return _activeTextColor;
    }
}

Terminal::Color Tg::Button::activeBackgroundColor() const
{
    if (_activeBackgroundColor.isEmpty()) {
        return style()->activeBackgroundColor;
    } else {
        return _activeBackgroundColor;
    }
}

Terminal::Color Tg::Button::inactiveTextColor() const
{
    if (_inactiveTextColor.isEmpty()) {
        return style()->inactiveTextColor;
    } else {
        return _inactiveTextColor;
    }
}

Terminal::Color Tg::Button::inactiveBackgroundColor() const
{
    if (_inactiveBackgroundColor.isEmpty()) {
        return style()->inactiveBackgroundColor;
    } else {
        return _inactiveBackgroundColor;
    }
}

Terminal::Color Tg::Button::pressedTextColor() const
{
    if (_pressedTextColor.isEmpty()) {
        return style()->pressedTextColor;
    } else {
        return _pressedTextColor;
    }
}

Terminal::Color Tg::Button::pressedBackgroundColor() const
{
    if (_pressedBackgroundColor.isEmpty()) {
        return style()->pressedBackgroundColor;
    } else {
        return _pressedBackgroundColor;
    }
}

void Tg::Button::setActiveTextColor(const Terminal::Color &activeTextColor)
{
    if (_activeTextColor == activeTextColor)
        return;

    _activeTextColor = activeTextColor;
    emit activeTextColorChanged(_activeTextColor);
}

void Tg::Button::setActiveBackgroundColor(const Terminal::Color &activeBackgroundColor)
{
    if (_activeBackgroundColor == activeBackgroundColor)
        return;

    _activeBackgroundColor = activeBackgroundColor;
    emit activeBackgroundColorChanged(_activeBackgroundColor);
}

void Tg::Button::setInactiveTextColor(const Terminal::Color &inactiveTextColor)
{
    if (_inactiveTextColor == inactiveTextColor)
        return;

    _inactiveTextColor = inactiveTextColor;
    emit inactiveTextColorChanged(_inactiveTextColor);
}

void Tg::Button::setInactiveBackgroundColor(const Terminal::Color &inactiveBackgroundColor)
{
    if (_inactiveBackgroundColor == inactiveBackgroundColor)
        return;

    _inactiveBackgroundColor = inactiveBackgroundColor;
    emit inactiveBackgroundColorChanged(_inactiveBackgroundColor);
}

void Tg::Button::setPressedTextColor(const Terminal::Color &pressedTextColor)
{
    if (_pressedTextColor == pressedTextColor)
        return;

    _pressedTextColor = pressedTextColor;
    emit pressedTextColorChanged(_pressedTextColor);
}

void Tg::Button::setPressedBackgroundColor(const Terminal::Color &pressedBackgroundColor)
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

    // TODO: move these connects into setupPressTimer() somehow!
    CHECK(connect(this, &Button::clicked,
                  &_buttonPressTimer, qOverload<>(&QTimer::start)));
    CHECK(connect(&_buttonPressTimer, &QTimer::timeout,
                  this, &Button::onButtonPressTimeout));
    setupPressTimer(&_buttonPressTimer);


    CHECK(connect(this, &Button::hasFocusChanged,
                  this, &Button::onHasFocusChanged));

    CHECK(connect(this, &Button::activeTextColorChanged,
                  this, &Button::schedulePartialRedraw));
    CHECK(connect(this, &Button::activeBackgroundColorChanged,
                  this, &Button::schedulePartialRedraw));
    CHECK(connect(this, &Button::inactiveTextColorChanged,
                  this, &Button::schedulePartialRedraw));
    CHECK(connect(this, &Button::inactiveBackgroundColorChanged,
                  this, &Button::schedulePartialRedraw));
    CHECK(connect(this, &Button::pressedTextColorChanged,
                  this, &Button::schedulePartialRedraw));
    CHECK(connect(this, &Button::pressedBackgroundColorChanged,
                  this, &Button::schedulePartialRedraw));

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
    if (keyboardBuffer.contains(Terminal::Key::enter)
        || keyboardBuffer.contains(Terminal::Key::ret))
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
