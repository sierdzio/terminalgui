#pragma once

#include <widgets/tgwidget.h>

namespace Tg {
/*!
 * A modal widget, automatically centered on parent Screen.
 */
class Popup : public Tg::Widget
{
    Q_OBJECT

public:
    Popup(const QSize &size, Screen *parent);

private:
    void centerInParent();
};
}
