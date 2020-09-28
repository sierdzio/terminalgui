#pragma once

#include <widgets/tglabel.h>

namespace Tg {
class LineEdit : public Label
{
    Q_OBJECT

    Q_PROPERTY(QString placeholderText READ placeholderText WRITE setPlaceholderText NOTIFY placeholderTextChanged)
    Q_PROPERTY(int cursorPosition READ cursorPosition WRITE setCursorPosition NOTIFY cursorPositionChanged)

    Q_PROPERTY(Terminal::Color placeholderTextColor READ placeholderTextColor WRITE setPlaceholderTextColor NOTIFY placeholderTextColorChanged)
    Q_PROPERTY(Terminal::Color placeholderBackgroundColor READ placeholderBackgroundColor WRITE setPlaceholderBackgroundColor NOTIFY placeholderBackgroundColorChanged)

public:
    LineEdit(Widget *parent);
    LineEdit(Screen *screen);
    LineEdit(const QString &placeholderText = QString(), Widget *parent = nullptr);
    LineEdit(const QString &placeholderText = QString(), Screen *screen = nullptr);

    QString placeholderText() const;
    int cursorPosition() const;

    Terminal::Color placeholderTextColor() const;
    Terminal::Color placeholderBackgroundColor() const;

public slots:
    void setPlaceholderText(const QString &placeholderText);
    void setCursorPosition(const int cursorPosition);

    void setPlaceholderTextColor(const Terminal::Color placeholderTextColor);
    void setPlaceholderBackgroundColor(const Terminal::Color placeholderBackgroundColor);

signals:
    void placeholderTextChanged(const QString &placeholderText) const;
    void cursorPositionChanged(const int cursorPosition) const;
    void placeholderTextColorChanged(const Terminal::Color placeholderTextColor) const;
    void placeholderBackgroundColorChanged(const Terminal::Color placeholderBackgroundColor) const;

protected:
    void init() override;
    void consumeKeyboardBuffer(const QString &keyboardBuffer) override;

    void displayPlaceholderText();

private:
    QString _placeholderText;
    QString _realText;
    int _cursorPosition = 0;
    Terminal::Color _placeholderTextColor = Terminal::Color::Predefined::Empty;
    Terminal::Color _placeholderBackgroundColor = Terminal::Color::Predefined::Empty;
};
}
