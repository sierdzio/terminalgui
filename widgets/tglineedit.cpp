#include "tglineedit.h"

Tg::LineEdit::LineEdit(Tg::Widget *parent) : Tg::Label(parent)
{
    init();
}

Tg::LineEdit::LineEdit(Tg::Screen *screen) : Tg::Label(screen)
{
    init();
}

Tg::LineEdit::LineEdit(const QString &placeholderText, Tg::Widget *parent)
    : Tg::Label(parent),
      _placeholderText(placeholderText)
{
    init();
}

Tg::LineEdit::LineEdit(const QString &placeholderText, Tg::Screen *screen)
    : Tg::Label(screen),
      _placeholderText(placeholderText)
{
    init();
}

QString Tg::LineEdit::placeholderText() const
{
    return _placeholderText;
}

void Tg::LineEdit::setPlaceholderText(const QString &placeholderText)
{
    if (_placeholderText == placeholderText)
        return;

    _placeholderText = placeholderText;
    emit placeholderTextChanged(_placeholderText);
}

void Tg::LineEdit::init()
{
    setAcceptsFocus(true);
    Label::init();

    if (placeholderText().isEmpty() == false) {
        displayPlaceholderText();
    }
}

void Tg::LineEdit::consumeKeyboardBuffer(const QByteArray &keyboardBuffer)
{
    // TODO: backspace, delete support...

    if (_realText.isEmpty() && keyboardBuffer.isEmpty()) {
        displayPlaceholderText();
    } else {
        _realText.append(keyboardBuffer);
        setText(_realText);
        setTextColor(Terminal::Color4Bit::LightWhite);
    }
}

void Tg::LineEdit::displayPlaceholderText()
{
    setText(placeholderText());
    setTextColor(Terminal::Color4Bit::Gray);
}
