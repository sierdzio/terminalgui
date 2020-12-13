#include "tgcolumnlayout.h"
#include "widgets/tgwidget.h"

#include <QRect>

Tg::ColumnLayout::ColumnLayout() : Layout(Type::Column)
{
}

void Tg::ColumnLayout::doLayout()
{
    // TODO: LayoutSettings class!

    if (_type == Layout::Type::Column && _parent) {
        _overshoot = Overshoot::None;
        const QSize contentsSize = _parent->contentsRectangle().size();
        const int width = contentsSize.width();
        const int height = contentsSize.height();
        int currentY = 0;

        for (const auto child : _parent->children()) {
            auto widget = qobject_cast<Widget*>(child);
            if (widget) {
                const QSize currentSize = widget->size();
                if ((currentY + currentSize.height()) > height) {
                    _overshoot = _overshoot | Overshoot::Vertical;
                    continue;
                }

                widget->setPosition(QPoint(0, currentY));
                // TODO: if height can get smaller due to width getting larger,
                // make it so!
                widget->setSize(QSize(width, currentSize.height()));

                if (widget->widgetOvershoot().testFlag(Overshoot::None) == false) {
                    _overshoot = _overshoot | widget->widgetOvershoot();
                }

                currentY += currentSize.height();
            }
        }
    }
}
