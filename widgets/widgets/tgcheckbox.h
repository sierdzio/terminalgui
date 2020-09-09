#pragma once

#include <widgets/tgbutton.h>

namespace Tg {
class CheckBox : public Button
{
    Q_OBJECT

    Q_PROPERTY(Qt::CheckState checkState READ checkState WRITE setCheckState NOTIFY checkStateChanged)

public:
    CheckBox(Widget *parent);
    CheckBox(Screen *screen);
    CheckBox(const QString &text = QString(), Widget *parent = nullptr);
    CheckBox(const QString &text = QString(), Screen *screen = nullptr);

    Qt::CheckState checkState() const;

signals:
    void checkStateChanged(const Qt::CheckState checkState) const;

public slots:
    void setCheckState(const Qt::CheckState checkState);
    void toggleState();

protected:
    void init() override;
    //void consumeKeyboardBuffer(const QString &keyboardBuffer) override;

private:
    Qt::CheckState _checkState = Qt::CheckState::Unchecked;
};
}
