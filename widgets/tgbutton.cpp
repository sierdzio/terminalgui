#include "tgbutton.h"

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

void Tg::Button::init()
{
    setAcceptsFocus(true);

    Label::init();
}
