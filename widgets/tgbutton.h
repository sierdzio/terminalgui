#pragma once

#include <widgets/tglabel.h>

namespace Tg {
class Button : public Label
{
    Q_OBJECT

public:
    Button(Widget *parent);
    Button(Screen *screen);
    Button(const QString &text = QString(), Widget *parent = nullptr);
    Button(const QString &text = QString(), Screen *screen = nullptr);

signals:
    void clicked() const;

protected:
    void init() override;
};
}
