#pragma once

#include <widgets/tglabel.h>

namespace Tg {
class LineEdit : public Label
{
    Q_OBJECT

    Q_PROPERTY(QString placeholderText READ placeholderText WRITE setPlaceholderText NOTIFY placeholderTextChanged)
    Q_PROPERTY(int cursorPosition READ cursorPosition WRITE setCursorPosition NOTIFY cursorPositionChanged)

public:
    LineEdit(Widget *parent);
    LineEdit(Screen *screen);
    LineEdit(const QString &placeholderText = QString(), Widget *parent = nullptr);
    LineEdit(const QString &placeholderText = QString(), Screen *screen = nullptr);

    QString placeholderText() const;
    int cursorPosition() const;

public slots:
    void setPlaceholderText(const QString &placeholderText);
    void setCursorPosition(const int cursorPosition);

signals:
    void placeholderTextChanged(const QString &placeholderText) const;
    void cursorPositionChanged(const int cursorPosition) const;

protected:
    void init() override;
    void consumeKeyboardBuffer(const QString &keyboardBuffer) override;

    void displayPlaceholderText();

private:
    QString _placeholderText;
    QString _realText;
    int _cursorPosition = 0;
};
}
