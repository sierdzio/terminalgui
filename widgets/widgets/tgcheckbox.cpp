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
    setReservedCharactersCount(2);
    Button::init();

    CHECK(connect(this, &CheckBox::clicked,
                  this, &CheckBox::toggleState));
}

void Tg::CheckBox::consumeKeyboardBuffer(const QString &keyboardBuffer)
{
    if (keyboardBuffer.contains(' ')) {
        setTextColor(pressedTextColor());
        setBackgroundColor(pressedBackgroundColor());
        emit clicked();
        return;
    }

    Button::consumeKeyboardBuffer(keyboardBuffer);
}

QChar Tg::CheckBox::reservedCharacter(const int index) const
{
    if (index == 0) {
        switch (checkState()) {
        case Qt::CheckState::Checked:
            return singleChar(style()->checkBoxChecked);
        case Qt::CheckState::PartiallyChecked:
            return singleChar(style()->checkBoxPartiallyChecked);
        case Qt::CheckState::Unchecked:
            return singleChar(style()->checkBoxUnChecked);
        }
    } else if (index == 1) {
        return ' ';
    }

    return QChar();
}

QChar Tg::CheckBox::singleChar(const std::string &string) const
{
    return QString::fromStdString(string).at(0);
}
