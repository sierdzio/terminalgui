#include "tglineedit.h"

#include "utils/tghelpers.h"
#include "styles/tgstyle.h"

#include <QRect>

Tg::LineEdit::LineEdit(Tg::Widget *parent) : Tg::Label(parent)
{
    LineEdit::init();
}

Tg::LineEdit::LineEdit(Tg::Screen *screen) : Tg::Label(screen)
{
    LineEdit::init();
}

Tg::LineEdit::LineEdit(const QString &placeholderText, Tg::Widget *parent)
    : Tg::Label(parent),
      _placeholderText(placeholderText)
{
    LineEdit::init();
    setSize(QSize(placeholderText.size(), 1));
}

Tg::LineEdit::LineEdit(const QString &placeholderText, Tg::Screen *screen)
    : Tg::Label(screen),
      _placeholderText(placeholderText)
{
    LineEdit::init();
    setSize(QSize(placeholderText.size(), 1));
}

QString Tg::LineEdit::placeholderText() const
{
    return _placeholderText;
}

int Tg::LineEdit::cursorPosition() const
{
    return _cursorPosition;
}

Tg::Color Tg::LineEdit::placeholderTextColor() const
{
    if (_placeholderTextColor.isEmpty()) {
        return style()->placeholderTextColor;
    } else {
        return _placeholderTextColor;
    }
}

Tg::Color Tg::LineEdit::placeholderBackgroundColor() const
{
    if (_placeholderBackgroundColor.isEmpty()) {
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

void Tg::LineEdit::setPlaceholderTextColor(const Tg::Color &placeholderTextColor)
{
    if (_placeholderTextColor == placeholderTextColor)
        return;

    _placeholderTextColor = placeholderTextColor;
    emit placeholderTextColorChanged(_placeholderTextColor);
}

void Tg::LineEdit::setPlaceholderBackgroundColor(const Tg::Color &placeholderBackgroundColor)
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

    CHECK(connect(this, &LineEdit::placeholderTextChanged,
                  this, &LineEdit::schedulePartialRedraw));
    CHECK(connect(this, &LineEdit::placeholderTextColorChanged,
                  this, &LineEdit::schedulePartialRedraw));
    CHECK(connect(this, &LineEdit::placeholderBackgroundColorChanged,
                  this, &LineEdit::schedulePartialRedraw));
    CHECK(connect(this, &LineEdit::cursorPositionChanged,
                  this, &LineEdit::schedulePartialRedraw));

    if (placeholderText().isEmpty() == false) {
        displayPlaceholderText();
    }
}

bool Tg::LineEdit::consumeKeyboardBuffer(const QString &keyboardBuffer)
{
    if (contentsRectangle().height() == 1) {
        // Up Arrow
        if (keyboardBuffer.contains(Tg::Key::up)) {
            emit moveFocusToPreviousWidget();
            return true;
        }

        // Down Arrow
        if (keyboardBuffer.contains(Tg::Key::down)) {
            emit moveFocusToNextWidget();
            return true;
        }
    } else {
        // TODO: set cursor position up/down
    }

    // Right Arrow
    if (const QString command(Tg::Key::right);
        keyboardBuffer.contains(command)) {
        if (cursorPosition() < _realText.size()) {
            setCursorPosition(cursorPosition() + 1);
        }
        return true;
    }

    // Left Arrow
    if (const QString command(Tg::Key::left);
        keyboardBuffer.contains(command)) {
        if (cursorPosition() > 0) {
            setCursorPosition(cursorPosition() - 1);
        }
        return true;
    }

    // Backspace!
    if (const QChar command(Tg::Key::backspace);
        keyboardBuffer.contains(command)) {
        if (_cursorPosition > 0) {
            setCursorPosition(cursorPosition() - 1);
            _realText.remove(cursorPosition(), 1);
            setText(_realText);

            if (_realText.isEmpty()) {
                displayPlaceholderText();
            }
        }
        return true;
    }

    // Delete!
    if (const QString command(Tg::Key::del);
        keyboardBuffer.contains(command)) {
        if (_realText.isEmpty() == false) {
            _realText.remove(cursorPosition(), 1);
            setText(_realText);

            if (_realText.isEmpty()) {
                displayPlaceholderText();
            }
        }
        return true;
    }

    if (_realText.isEmpty() && keyboardBuffer.isEmpty()) {
        displayPlaceholderText();
        return true;
    } else {
        _realText.insert(cursorPosition(), keyboardBuffer);
        setText(_realText);
        setCursorPosition(cursorPosition() + 1);
        setTextColor(style()->textColor);
        return true;
    }

    return false;
}

void Tg::LineEdit::displayPlaceholderText()
{
    setText(placeholderText());
    setTextColor(placeholderTextColor());
    setBackgroundColor(placeholderBackgroundColor());
}
