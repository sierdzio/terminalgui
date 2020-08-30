#pragma once

#include <widgets/tglabel.h>

#include <QTimer>

namespace Tg {
class Button : public Label
{
    Q_OBJECT

    Q_PROPERTY(Terminal::Color4Bit activeTextColor READ activeTextColor WRITE setActiveTextColor NOTIFY activeTextColorChanged)
    Q_PROPERTY(Terminal::Color4Bit activeBackgroundColor READ activeBackgroundColor WRITE setActiveBackgroundColor NOTIFY activeBackgroundColorChanged)

    Q_PROPERTY(Terminal::Color4Bit inactiveTextColor READ inactiveTextColor WRITE setInactiveTextColor NOTIFY inactiveTextColorChanged)
    Q_PROPERTY(Terminal::Color4Bit inactiveBackgroundColor READ inactiveBackgroundColor WRITE setInactiveBackgroundColor NOTIFY inactiveBackgroundColorChanged)

    Q_PROPERTY(Terminal::Color4Bit pressedTextColor READ pressedTextColor WRITE setPressedTextColor NOTIFY pressedTextColorChanged)
    Q_PROPERTY(Terminal::Color4Bit pressedBackgroundColor READ pressedBackgroundColor WRITE setPressedBackgroundColor NOTIFY pressedBackgroundColorChanged)

public:
    Button(Widget *parent);
    Button(Screen *screen);
    Button(const QString &text = QString(), Widget *parent = nullptr);
    Button(const QString &text = QString(), Screen *screen = nullptr);

    Terminal::Color4Bit activeTextColor() const;
    Terminal::Color4Bit activeBackgroundColor() const;
    Terminal::Color4Bit inactiveTextColor() const;
    Terminal::Color4Bit inactiveBackgroundColor() const;
    Terminal::Color4Bit pressedTextColor() const;
    Terminal::Color4Bit pressedBackgroundColor() const;

public slots:
    void setActiveTextColor(const Terminal::Color4Bit activeTextColor);
    void setActiveBackgroundColor(const Terminal::Color4Bit activeBackgroundColor);
    void setInactiveTextColor(const Terminal::Color4Bit inactiveTextColor);
    void setInactiveBackgroundColor(const Terminal::Color4Bit inactiveBackgroundColor);
    void setPressedTextColor(const Terminal::Color4Bit pressedTextColor);
    void setPressedBackgroundColor(const Terminal::Color4Bit pressedBackgroundColor);

signals:
    void clicked() const;

    void activeTextColorChanged(const Terminal::Color4Bit activeTextColor) const;
    void activeBackgroundColorChanged(const Terminal::Color4Bit activeBackgroundColor) const;
    void inactiveTextColorChanged(const Terminal::Color4Bit inactiveTextColor) const;
    void inactiveBackgroundColorChanged(const Terminal::Color4Bit inactiveBackgroundColor) const;
    void pressedTextColorChanged(const Terminal::Color4Bit pressedTextColor) const;
    void pressedBackgroundColorChanged(const Terminal::Color4Bit pressedBackgroundColor) const;

protected:
    void init() override;
    void consumeKeyboardBuffer(const QString &keyboardBuffer) override;

protected slots:
    void onButtonPressTimeout();
    void onHasFocusChanged();

private:
    QTimer _buttonPressTimer;
    Terminal::Color4Bit _activeTextColor = Terminal::Color4Bit::Empty;
    Terminal::Color4Bit _activeBackgroundColor = Terminal::Color4Bit::Empty;
    Terminal::Color4Bit _inactiveTextColor = Terminal::Color4Bit::Empty;
    Terminal::Color4Bit _inactiveBackgroundColor = Terminal::Color4Bit::Empty;
    Terminal::Color4Bit _pressedTextColor = Terminal::Color4Bit::Empty;
    Terminal::Color4Bit _pressedBackgroundColor = Terminal::Color4Bit::Empty;
};
}
