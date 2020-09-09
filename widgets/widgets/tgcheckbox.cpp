#include "tgcheckbox.h"

Tg::CheckBox::CheckBox(Tg::Widget *parent) : Tg::Button(parent)
{
    init();
}

Tg::CheckBox::CheckBox(Tg::Screen *screen) : Tg::Button(screen)
{
    init();
}

Tg::CheckBox::CheckBox(const QString &text, Tg::Widget *parent) : Tg::Button(text, parent)
{
    init();
}

Tg::CheckBox::CheckBox(const QString &text, Tg::Screen *screen) : Tg::Button(text, screen)
{
    init();
}

Qt::CheckState Tg::CheckBox::checkState() const
{
    return _checkState;
}

void Tg::CheckBox::setCheckState(const Qt::CheckState checkState)
{
    if (_checkState == checkState)
        return;

    _checkState = checkState;
    emit checkStateChanged(_checkState);
}

void Tg::CheckBox::toggleState()
{
    if (checkState() == Qt::CheckState::Unchecked
            || checkState() == Qt::CheckState::PartiallyChecked) {
        setCheckState(Qt::CheckState::Checked);
    } else {
        setCheckState(Qt::CheckState::Unchecked);
    }
}

void Tg::CheckBox::init()
{
    Button::init();

    CHECK(connect(this, &CheckBox::clicked,
                  this, &CheckBox::toggleState));
}
