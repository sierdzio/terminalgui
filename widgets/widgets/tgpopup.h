#pragma once

#include <widgets/tgwidget.h>

namespace Tg {
class Popup : public Tg::Widget
{
    Q_OBJECT

public:
    Popup(const QSize &size, Widget *parent);
    Popup(const QSize &size, Screen *parent);

private:
    void centerInParent();
};
}
