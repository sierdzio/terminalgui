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
        const QSize contentsSize = parent->contentsRectangle().size();
        const int width = contentsSize.width();
        const int height = contentsSize.height();

        const int columns = 2;
        const int itemWidth = width / columns;

        int currentColumn = 0;
        int currentRow = 0;
        int currentX = 0;
        int currentY = 0;

        for (const auto child : parent->children()) {
            auto widget = qobject_cast<Widget*>(child);
            if (widget) {
                if (currentY >= height || currentX >= width) {
                    if (currentY >= height) {
                        _overshoot = _overshoot | Overshoot::Vertical;
                        widget->setClipped(true);
                    }

                    if (currentX >= width) {
                        _overshoot = _overshoot | Overshoot::Horizontal;
                        widget->setClipped(true);
                    }
                    continue;
                }

                widget->setPosition(QPoint(currentX, currentRow));
                const QSize size = widget->size();
                currentX = currentX + itemWidth;
                currentY = std::max(currentY, currentRow + size.height());
                currentColumn++;
                widget->setSize(QSize(itemWidth, currentY));

                if (widget->widgetOvershoot().testFlag(Overshoot::None) == false) {
                    _overshoot = _overshoot | widget->widgetOvershoot();
                }

                if (currentColumn >= columns) {
                    currentColumn = 0;
                    currentX = 0;
                    currentRow = currentY;
                }
            }
        }
    }
}
