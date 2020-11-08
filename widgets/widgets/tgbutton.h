#pragma once

#include <widgets/tglabel.h>

#include <QTimer>

namespace Tg {
class Button : public Label
{
    Q_OBJECT

    Q_PROPERTY(Tg::Color activeTextColor READ activeTextColor WRITE setActiveTextColor NOTIFY activeTextColorChanged)
    Q_PROPERTY(Tg::Color activeBackgroundColor READ activeBackgroundColor WRITE setActiveBackgroundColor NOTIFY activeBackgroundColorChanged)

    Q_PROPERTY(Tg::Color inactiveTextColor READ inactiveTextColor WRITE setInactiveTextColor NOTIFY inactiveTextColorChanged)
    Q_PROPERTY(Tg::Color inactiveBackgroundColor READ inactiveBackgroundColor WRITE setInactiveBackgroundColor NOTIFY inactiveBackgroundColorChanged)

    Q_PROPERTY(Tg::Color pressedTextColor READ pressedTextColor WRITE setPressedTextColor NOTIFY pressedTextColorChanged)
    Q_PROPERTY(Tg::Color pressedBackgroundColor READ pressedBackgroundColor WRITE setPressedBackgroundColor NOTIFY pressedBackgroundColorChanged)

public:
    Button(Widget *parent);
    Button(Screen *screen);
    Button(const QString &text = QString(), Widget *parent = nullptr);
    Button(const QString &text = QString(), Screen *screen = nullptr);

    Tg::Color activeTextColor() const;
    Tg::Color activeBackgroundColor() const;
    Tg::Color inactiveTextColor() const;
    Tg::Color inactiveBackgroundColor() const;
    Tg::Color pressedTextColor() const;
    Tg::Color pressedBackgroundColor() const;

    void click();

public slots:
    void setActiveTextColor(const Tg::Color &activeTextColor);
    void setActiveBackgroundColor(const Tg::Color &activeBackgroundColor);
    void setInactiveTextColor(const Tg::Color &inactiveTextColor);
    void setInactiveBackgroundColor(const Tg::Color &inactiveBackgroundColor);
    void setPressedTextColor(const Tg::Color &pressedTextColor);
    void setPressedBackgroundColor(const Tg::Color &pressedBackgroundColor);

signals:
    void clicked() const;

    void activeTextColorChanged(const Tg::Color &activeTextColor) const;
    void activeBackgroundColorChanged(const Tg::Color &activeBackgroundColor) const;
    void inactiveTextColorChanged(const Tg::Color &inactiveTextColor) const;
    void inactiveBackgroundColorChanged(const Tg::Color &inactiveBackgroundColor) const;
    void pressedTextColorChanged(const Tg::Color &pressedTextColor) const;
    void pressedBackgroundColorChanged(const Tg::Color &pressedBackgroundColor) const;

protected:
    void init() override;
    void consumeKeyboardBuffer(const QString &keyboardBuffer) override;

protected slots:
    void onButtonPressTimeout();
    void onHasFocusChanged();

private:
    QTimer _buttonPressTimer;
    Tg::Color _activeTextColor = Tg::Color::Predefined::Empty;
    Tg::Color _activeBackgroundColor = Tg::Color::Predefined::Empty;
    Tg::Color _inactiveTextColor = Tg::Color::Predefined::Empty;
    Tg::Color _inactiveBackgroundColor = Tg::Color::Predefined::Empty;
    Tg::Color _pressedTextColor = Tg::Color::Predefined::Empty;
    Tg::Color _pressedBackgroundColor = Tg::Color::Predefined::Empty;
};
}
