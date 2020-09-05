#include "tgrowlayout.h"
#include "tgwidget.h"

#include <QRect>

Tg::RowLayout::RowLayout() : Layout(Type::Row)
{
}

void Tg::RowLayout::doLayout()
{
    if (type == Layout::Type::Row && parent) {
        const int height = parent->contentsRectangle().size().height();
        int currentX = 0;

        for (const auto child : parent->children()) {
            auto widget = qobject_cast<Widget*>(child);
            if (widget) {
                const QSize currentSize = widget->size();
                widget->setPosition(QPoint(currentX, 0));
                // TODO: if width can get smaller due to height getting larger,
                // make it so!
                widget->setSize(QSize(currentSize.width(), height));
                currentX += currentSize.width();
            }
        }
    }
}
