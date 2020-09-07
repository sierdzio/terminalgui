#include "tgcolumnlayout.h"
#include "widgets/tgwidget.h"

#include <QRect>

Tg::ColumnLayout::ColumnLayout() : Layout(Type::Column)
{
}

void Tg::ColumnLayout::doLayout()
{
    // TODO: LayoutSettings class!

    if (type == Layout::Type::Column && parent) {
        _overshoot = Overshoot::None;
        const QSize contentsSize = parent->contentsRectangle().size();
        const int width = contentsSize.width();
        int currentY = 0;

        for (const auto child : parent->children()) {
            auto widget = qobject_cast<Widget*>(child);
            if (widget) {
                const QSize currentSize = widget->size();
                widget->setPosition(QPoint(0, currentY));
                // TODO: if height can get smaller due to width getting larger,
                // make it so!
                widget->setSize(QSize(width, currentSize.height()));
                currentY += currentSize.height();
            }
        }
    }
}
