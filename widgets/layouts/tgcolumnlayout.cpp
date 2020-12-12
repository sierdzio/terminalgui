#include "tgcolumnlayout.h"
#include "widgets/tgwidget.h"

#include <QRect>

Tg::ColumnLayout::ColumnLayout() : Layout(Type::Row)
{
}

void Tg::ColumnLayout::doLayout()
{
    if (type == Layout::Type::Row && parent) {
        _overshoot = Overshoot::None;
        const QSize contentsSize = parent->contentsRectangle().size();
        const int width = contentsSize.width();
        const int height = contentsSize.height();
        int currentX = 0;

        for (const auto child : parent->children()) {
            auto widget = qobject_cast<Widget*>(child);
            if (widget) {
                const QSize currentSize = widget->size();
                if ((currentX + currentSize.width()) > width) {
                    _overshoot = _overshoot | Overshoot::Horizontal;
                    continue;
                }

                widget->setPosition(QPoint(currentX, 0));
                // TODO: if width can get smaller due to height getting larger,
                // make it so!
                widget->setSize(QSize(currentSize.width(), height));

                if (widget->widgetOvershoot().testFlag(Overshoot::None) == false) {
                    _overshoot = _overshoot | widget->widgetOvershoot();
                }

                currentX += currentSize.width();
            }
        }
    }
}
