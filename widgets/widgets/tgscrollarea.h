#pragma once

#include <widgets/tgwidget.h>

namespace Tg {
class ScrollArea : public Widget
{
    Q_OBJECT

public:
    ScrollArea(Widget *parent);
    ScrollArea(Screen *screen);

    QString drawPixel(const QPoint &pixel) const override;

protected:
    void init() override;
    void consumeKeyboardBuffer(const QString &keyboardBuffer) override;
};
}
