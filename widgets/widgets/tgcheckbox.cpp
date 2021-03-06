#include "tgcheckbox.h"
#include "styles/tgstyle.h"

Tg::CheckBox::CheckBox(Tg::Widget *parent) : Tg::Button(parent)
{
    CheckBox::init();
}

Tg::CheckBox::CheckBox(Tg::Screen *screen) : Tg::Button(screen)
{
    CheckBox::init();
}

Tg::CheckBox::CheckBox(const QString &text, Tg::Widget *parent) : Tg::Button(text, parent)
{
    CheckBox::init();
}

Tg::CheckBox::CheckBox(const QString &text, Tg::Screen *screen) : Tg::Button(text, screen)
{
    CheckBox::init();
}

Qt::CheckState Tg::CheckBox::checkState() const
{
    return _checkState;
}

QString Tg::CheckBox::checkBoxText(const Qt::CheckState state,
                                   const StylePointer &style)
{
    switch (state) {
    case Qt::CheckState::Checked:
        return style->checkBoxChecked;
    case Qt::CheckState::PartiallyChecked:
        return style->checkBoxPartiallyChecked;
    case Qt::CheckState::Unchecked:
        return style->checkBoxUnChecked;
    }

    return {};
}

void Tg::CheckBox::setCheckState(const Qt::CheckState checkState)
{
    if (_checkState == checkState)
        return;

    _checkState = checkState;
    emit checkStateChanged(_checkState);

    setReservedText(checkBoxText());
    setHighlighted(_checkState != Qt::CheckState::Unchecked);
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
    setReservedText(checkBoxText());
    Button::init();

    CHECK(connect(this, &CheckBox::clicked,
                  this, &CheckBox::toggleState));
}

bool Tg::CheckBox::consumeKeyboardBuffer(const QString &keyboardBuffer)
{
    if (keyboardBuffer.contains(Tg::Key::space)) {
        setTextColor(pressedTextColor());
        setBackgroundColor(pressedBackgroundColor());
        emit clicked();
        return true;
    }

    return Button::consumeKeyboardBuffer(keyboardBuffer);
}

QString Tg::CheckBox::checkBoxText() const
{
    return checkBoxText(checkState(), style());
}
