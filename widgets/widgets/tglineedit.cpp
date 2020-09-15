#include "tglineedit.h"

#include "utils/tghelpers.h"

#include <QRect>

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

Terminal::Color4Bit Tg::LineEdit::placeholderTextColor() const
{
    if (isColorEmpty(_placeholderTextColor)) {
        return style()->placeholderTextColor;
    } else {
        return _placeholderTextColor;
    }
}

Terminal::Color4Bit Tg::LineEdit::placeholderBackgroundColor() const
{
    if (isColorEmpty(_placeholderBackgroundColor)) {
        return style()->placeholderBackgroundColor;
    } else {
        return _placeholderBackgroundColor;
    }
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

void Tg::LineEdit::setPlaceholderTextColor(const Terminal::Color4Bit placeholderTextColor)
{
    if (_placeholderTextColor == placeholderTextColor)
        return;

    _placeholderTextColor = placeholderTextColor;
    emit placeholderTextColorChanged(_placeholderTextColor);
}

void Tg::LineEdit::setPlaceholderBackgroundColor(const Terminal::Color4Bit placeholderBackgroundColor)
{
    if (_placeholderBackgroundColor == placeholderBackgroundColor)
        return;

    _placeholderBackgroundColor = placeholderBackgroundColor;
    emit placeholderBackgroundColorChanged(_placeholderBackgroundColor);
}

void Tg::LineEdit::init()
{
    setAcceptsFocus(true);
    Label::init();

    CHECK(connect(this, &LineEdit::cursorPositionChanged,
                  this, &LineEdit::schedulePartialRedraw));

    if (placeholderText().isEmpty() == false) {
        displayPlaceholderText();
    }
}

void Tg::LineEdit::consumeKeyboardBuffer(const QString &keyboardBuffer)
{
    if (contentsRectangle().height() == 1) {
        // Up Arrow
        if (keyboardBuffer.contains(Terminal::Key::up)) {
            emit moveFocusToPreviousWidget();
            return;
        }

        // Down Arrow
        if (keyboardBuffer.contains(Terminal::Key::down)) {
            emit moveFocusToNextWidget();
            return;
        }
    } else {
        // TODO: set cursor position up/down
    }

    // Right Arrow
    if (const QString command(Terminal::Key::right);
        keyboardBuffer.contains(command)) {
        if (cursorPosition() <= _realText.size()) {
            setCursorPosition(cursorPosition() + 1);
        }
        return;
    }

    // Left Arrow
    if (const QString command(Terminal::Key::left);
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
    if (const QString command(Terminal::Key::del);
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
        setTextColor(style()->textColor);
    }
}

void Tg::LineEdit::displayPlaceholderText()
{
    setText(placeholderText());
    setTextColor(placeholderTextColor());
    setBackgroundColor(placeholderBackgroundColor());
}
