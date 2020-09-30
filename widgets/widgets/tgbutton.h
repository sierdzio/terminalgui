#pragma once

#include <widgets/tglabel.h>

#include <QTimer>

namespace Tg {
class Button : public Label
{
    Q_OBJECT

    Q_PROPERTY(Terminal::Color activeTextColor READ activeTextColor WRITE setActiveTextColor NOTIFY activeTextColorChanged)
    Q_PROPERTY(Terminal::Color activeBackgroundColor READ activeBackgroundColor WRITE setActiveBackgroundColor NOTIFY activeBackgroundColorChanged)

    Q_PROPERTY(Terminal::Color inactiveTextColor READ inactiveTextColor WRITE setInactiveTextColor NOTIFY inactiveTextColorChanged)
    Q_PROPERTY(Terminal::Color inactiveBackgroundColor READ inactiveBackgroundColor WRITE setInactiveBackgroundColor NOTIFY inactiveBackgroundColorChanged)

    Q_PROPERTY(Terminal::Color pressedTextColor READ pressedTextColor WRITE setPressedTextColor NOTIFY pressedTextColorChanged)
    Q_PROPERTY(Terminal::Color pressedBackgroundColor READ pressedBackgroundColor WRITE setPressedBackgroundColor NOTIFY pressedBackgroundColorChanged)

public:
    Button(Widget *parent);
    Button(Screen *screen);
    Button(const QString &text = QString(), Widget *parent = nullptr);
    Button(const QString &text = QString(), Screen *screen = nullptr);

    Terminal::Color activeTextColor() const;
    Terminal::Color activeBackgroundColor() const;
    Terminal::Color inactiveTextColor() const;
    Terminal::Color inactiveBackgroundColor() const;
    Terminal::Color pressedTextColor() const;
    Terminal::Color pressedBackgroundColor() const;

public slots:
    void setActiveTextColor(const Terminal::Color &activeTextColor);
    void setActiveBackgroundColor(const Terminal::Color &activeBackgroundColor);
    void setInactiveTextColor(const Terminal::Color &inactiveTextColor);
    void setInactiveBackgroundColor(const Terminal::Color &inactiveBackgroundColor);
    void setPressedTextColor(const Terminal::Color &pressedTextColor);
    void setPressedBackgroundColor(const Terminal::Color &pressedBackgroundColor);

signals:
    void clicked() const;

    void activeTextColorChanged(const Terminal::Color &activeTextColor) const;
    void activeBackgroundColorChanged(const Terminal::Color &activeBackgroundColor) const;
    void inactiveTextColorChanged(const Terminal::Color &inactiveTextColor) const;
    void inactiveBackgroundColorChanged(const Terminal::Color &inactiveBackgroundColor) const;
    void pressedTextColorChanged(const Terminal::Color &pressedTextColor) const;
    void pressedBackgroundColorChanged(const Terminal::Color &pressedBackgroundColor) const;

protected:
    void init() override;
    void consumeKeyboardBuffer(const QString &keyboardBuffer) override;

protected slots:
    void onButtonPressTimeout();
    void onHasFocusChanged();

private:
    QTimer _buttonPressTimer;
    Terminal::Color _activeTextColor = Terminal::Color::Predefined::Empty;
    Terminal::Color _activeBackgroundColor = Terminal::Color::Predefined::Empty;
    Terminal::Color _inactiveTextColor = Terminal::Color::Predefined::Empty;
    Terminal::Color _inactiveBackgroundColor = Terminal::Color::Predefined::Empty;
    Terminal::Color _pressedTextColor = Terminal::Color::Predefined::Empty;
    Terminal::Color _pressedBackgroundColor = Terminal::Color::Predefined::Empty;
};
}
