#pragma once

#include <widgets/tglabel.h>

namespace Tg {
class LineEdit : public Label
{
    Q_OBJECT

    Q_PROPERTY(QString placeholderText READ placeholderText WRITE setPlaceholderText NOTIFY placeholderTextChanged)
    Q_PROPERTY(int cursorPosition READ cursorPosition WRITE setCursorPosition NOTIFY cursorPositionChanged)

    Q_PROPERTY(Terminal::Color4Bit placeholderTextColor READ placeholderTextColor WRITE setPlaceholderTextColor NOTIFY placeholderTextColorChanged)
    Q_PROPERTY(Terminal::Color4Bit placeholderBackgroundColor READ placeholderBackgroundColor WRITE setPlaceholderBackgroundColor NOTIFY placeholderBackgroundColorChanged)

public:
    LineEdit(Widget *parent);
    LineEdit(Screen *screen);
    LineEdit(const QString &placeholderText = QString(), Widget *parent = nullptr);
    LineEdit(const QString &placeholderText = QString(), Screen *screen = nullptr);

    QString placeholderText() const;
    int cursorPosition() const;

    Terminal::Color4Bit placeholderTextColor() const;
    Terminal::Color4Bit placeholderBackgroundColor() const;

public slots:
    void setPlaceholderText(const QString &placeholderText);
    void setCursorPosition(const int cursorPosition);

    void setPlaceholderTextColor(const Terminal::Color4Bit placeholderTextColor);
    void setPlaceholderBackgroundColor(const Terminal::Color4Bit placeholderBackgroundColor);

signals:
    void placeholderTextChanged(const QString &placeholderText) const;
    void cursorPositionChanged(const int cursorPosition) const;
    void placeholderTextColorChanged(const Terminal::Color4Bit placeholderTextColor) const;
    void placeholderBackgroundColorChanged(const Terminal::Color4Bit placeholderBackgroundColor) const;

protected:
    void init() override;
    void consumeKeyboardBuffer(const QString &keyboardBuffer) override;

    void displayPlaceholderText();

private:
    QString _placeholderText;
    QString _realText;
    int _cursorPosition = 0;
    Terminal::Color4Bit _placeholderTextColor = Terminal::Color4Bit::Empty;
    Terminal::Color4Bit _placeholderBackgroundColor = Terminal::Color4Bit::Empty;
};
}
