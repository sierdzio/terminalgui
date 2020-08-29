#include "tglineedit.h"

#include "tghelpers.h"

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

int Tg::LineEdit::cursorPosition() const
{
    return _cursorPosition;
}

void Tg::LineEdit::setPlaceholderText(const QString &placeholderText)
{
    if (_placeholderText == placeholderText)
        return;

    _placeholderText = placeholderText;
    emit placeholderTextChanged(_placeholderText);
}

void Tg::LineEdit::setCursorPosition(const int cursorPosition)
{
    if (_cursorPosition == cursorPosition)
        return;

    _cursorPosition = cursorPosition;
    emit cursorPositionChanged(_cursorPosition);
}

void Tg::LineEdit::init()
{
    setAcceptsFocus(true);
    Label::init();

    CHECK(connect(this, &LineEdit::cursorPositionChanged,
                  this, &LineEdit::scheduleRedraw));

    if (placeholderText().isEmpty() == false) {
        displayPlaceholderText();
    }
}

void Tg::LineEdit::consumeKeyboardBuffer(const QString &keyboardBuffer)
{
    //// Up Arrow
    //if (keyboardBuffer.contains("\033[A")) {
    //    emit moveFocusToPreviousWidget();
    //    return;
    //}
    //
    //// Down Arrow
    //if (keyboardBuffer.contains("\033[B")) {
    //    emit moveFocusToNextWidget();
    //    return;
    //}

    // Right Arrow
    if (const QString command(Helpers::toString(Terminal::Key::right));
        keyboardBuffer.contains(command)) {
        if (cursorPosition() <= _realText.size()) {
            setCursorPosition(cursorPosition() + 1);
        }
        return;
    }

    // Left Arrow
    if (const QString command(Helpers::toString(Terminal::Key::left));
        keyboardBuffer.contains(command)) {
        if (cursorPosition() > 0) {
            setCursorPosition(cursorPosition() - 1);
        }
        return;
    }

    // Backspace!
    if (const int command(Terminal::Key::backspace);
        keyboardBuffer.contains(command)) {
        if (_cursorPosition > 0) {
            setCursorPosition(cursorPosition() - 1);
            _realText.remove(cursorPosition(), 1);
            setText(_realText);
        }

        return;
    }

    // Delete!
    if (const QString command(Helpers::toString(Terminal::Key::del));
        keyboardBuffer.contains(command)) {
        if (_realText.isEmpty() == false) {
            _realText.remove(cursorPosition(), 1);
            setText(_realText);
        }
        return;
    }

    if (_realText.isEmpty() && keyboardBuffer.isEmpty()) {
        displayPlaceholderText();
    } else {
        // TODO: include cursor position!
        _realText.append(keyboardBuffer);
        setText(_realText);
        setCursorPosition(_realText.size());
        setTextColor(Terminal::Color4Bit::LightWhite);
    }
}

void Tg::LineEdit::displayPlaceholderText()
{
    setText(placeholderText());
    setTextColor(Terminal::Color4Bit::Gray);
}
