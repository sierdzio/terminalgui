#include "tggridlayout.h"
#include "widgets/tgwidget.h"

#include <QRect>

Tg::GridLayout::GridLayout() : Layout(Type::Grid)
{
}

void Tg::GridLayout::doLayout()
{
    // TODO: LayoutSettings class!

    if (type == Layout::Type::Grid && parent) {
        _overshoot = Overshoot::None;
        const int width = parent->contentsRectangle().size().width();
        const int columns = 2;
        const int itemWidth = width / columns;

        int currentColumn = 0;
        int currentRow = 0;
        int currentX = 0;
        int currentY = 0;

        for (const auto child : parent->children()) {
            auto widget = qobject_cast<Widget*>(child);
            if (widget) {
                widget->setPosition(QPoint(currentX, currentRow));
                const QSize size = widget->size();
                currentX = currentX + itemWidth;
                currentY = std::max(currentY, currentRow + size.height());
                currentColumn++;
                widget->setSize(QSize(itemWidth, currentY));

                if (currentColumn >= columns) {
                    currentColumn = 0;
                    currentX = 0;
                    currentRow = currentY;
                }
            }
        }
    }
}
