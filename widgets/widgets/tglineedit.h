#pragma once

#include <widgets/tglabel.h>

namespace Tg {
class LineEdit : public Label
{
    Q_OBJECT

    Q_PROPERTY(QString placeholderText READ placeholderText WRITE setPlaceholderText NOTIFY placeholderTextChanged)
    Q_PROPERTY(int cursorPosition READ cursorPosition WRITE setCursorPosition NOTIFY cursorPositionChanged)

    Q_PROPERTY(Tg::Color placeholderTextColor READ placeholderTextColor WRITE setPlaceholderTextColor NOTIFY placeholderTextColorChanged)
    Q_PROPERTY(Tg::Color placeholderBackgroundColor READ placeholderBackgroundColor WRITE setPlaceholderBackgroundColor NOTIFY placeholderBackgroundColorChanged)

public:
    LineEdit(Widget *parent);
    LineEdit(Screen *screen);
    LineEdit(const QString &placeholderText = QString(), Widget *parent = nullptr);
    LineEdit(const QString &placeholderText = QString(), Screen *screen = nullptr);

    QString placeholderText() const;
    int cursorPosition() const;

    Tg::Color placeholderTextColor() const;
    Tg::Color placeholderBackgroundColor() const;

public slots:
    void setPlaceholderText(const QString &placeholderText);
    void setCursorPosition(const int cursorPosition);

    void setPlaceholderTextColor(const Tg::Color &placeholderTextColor);
    void setPlaceholderBackgroundColor(const Tg::Color &placeholderBackgroundColor);

signals:
    void placeholderTextChanged(const QString &placeholderText) const;
    void cursorPositionChanged(const int cursorPosition) const;
    void placeholderTextColorChanged(const Tg::Color &placeholderTextColor) const;
    void placeholderBackgroundColorChanged(const Tg::Color &placeholderBackgroundColor) const;

protected:
    void init() override;
    void consumeKeyboardBuffer(const QString &keyboardBuffer) override;

    void displayPlaceholderText();

private:
    QString _placeholderText;
    QString _realText;
    int _cursorPosition = 0;
    Tg::Color _placeholderTextColor = Tg::Color::Predefined::Empty;
    Tg::Color _placeholderBackgroundColor = Tg::Color::Predefined::Empty;
};
}
