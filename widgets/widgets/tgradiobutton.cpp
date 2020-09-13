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
