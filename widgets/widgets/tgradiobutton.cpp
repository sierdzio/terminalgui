#include "tgradiobutton.h"

Tg::RadioButton::RadioButton(Tg::Widget *parent) : Tg::Button(parent)
{
    init();
}

Tg::RadioButton::RadioButton(Tg::Screen *screen) : Tg::Button(screen)
{
    init();
}

Tg::RadioButton::RadioButton(const QString &text, Tg::Widget *parent) : Tg::Button(text, parent)
{
    init();
}

Tg::RadioButton::RadioButton(const QString &text, Tg::Screen *screen) : Tg::Button(text, screen)
{
    init();
}

void Tg::RadioButton::toggleState()
{
    setChecked(!checked());
}

bool Tg::RadioButton::checked() const
{
    return _checked;
}

void Tg::RadioButton::setChecked(const bool checked)
{
    if (_checked == checked)
        return;

    _checked = checked;
    emit checkedChanged(_checked);

    setReservedText(radioButtonText());
}

void Tg::RadioButton::init()
{
    setReservedText(radioButtonText());
    Button::init();

    CHECK(connect(this, &RadioButton::clicked,
                  this, &RadioButton::toggleState));
}

void Tg::RadioButton::consumeKeyboardBuffer(const QString &keyboardBuffer)
{
    if (keyboardBuffer.contains(' ')) {
        setTextColor(pressedTextColor());
        setBackgroundColor(pressedBackgroundColor());
        emit clicked();
        return;
    }

    Button::consumeKeyboardBuffer(keyboardBuffer);
}

QString Tg::RadioButton::radioButtonText() const
{
    if (checked()) {
        return style()->radioButtonChecked;
    } else {
        return style()->radioButtonUnChecked;
    }
}
