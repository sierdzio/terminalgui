#pragma once

#include <widgets/tgbutton.h>

namespace Tg {
class RadioButton : public Button
{
    Q_OBJECT

    Q_PROPERTY(bool checked READ checked WRITE setChecked NOTIFY checkedChanged)

public:
    RadioButton(Widget *parent);
    RadioButton(Screen *screen);
    RadioButton(const QString &text = QString(), Widget *parent = nullptr);
    RadioButton(const QString &text = QString(), Screen *screen = nullptr);

    void toggleState();

    bool checked() const;

public slots:
    void setChecked(const bool checked);

signals:
    void checkedChanged(const bool checked) const;

protected:
    void init() override;
    void consumeKeyboardBuffer(const QString &keyboardBuffer) override;
    QString radioButtonText() const;

private:
    bool _checked = true;
};
}
