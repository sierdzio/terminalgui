#include "tgpopup.h"

#include "tgscreen.h"

Tg::Popup::Popup(const QSize &size, Screen *parent) : Widget(parent)
{
    setSize(size);
    centerInParent();
    setIsModal(true);
}

void Tg::Popup::centerInParent()
{
    const int width = size().width();
    const int height = size().height();

    int parentWidth = 0;
    int parentHeight = 0;

    if (isTopLevel()) {
        parentWidth = screen()->size().width();
        parentHeight = screen()->size().height();
    } else {
        parentWidth = parentWidget()->size().width();
        parentHeight = parentWidget()->size().height();
    }

    const int x = ((parentWidth - width) / 2);
    const int y = ((parentHeight - height) / 2);

    setPosition(QPoint(x, y));
}
