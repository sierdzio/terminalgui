#include "tggridlayout.h"
#include "widgets/tgwidget.h"

#include <QRect>

Tg::GridLayout::GridLayout() : Layout(Type::Grid)
{
}

void Tg::GridLayout::doLayout()
{
    // TODO: LayoutSettings class!

    if (_type == Layout::Type::Grid && _parent) {
        _overshoot = Overshoot::None;
        const QSize contentsSize = _parent->contentsRectangle().size();
        const int width = contentsSize.width();
        const int height = contentsSize.height();

        const int columns = 2;
        const int itemWidth = width / columns;

        int currentColumn = 0;
        int currentRow = 0;
        int currentX = 0;
        int currentY = 0;

        for (const auto child : _parent->children()) {
            auto widget = qobject_cast<Widget*>(child);
            if (widget) {
                const QSize currentSize = widget->size();
                const bool tooTall = ((currentY + currentSize.height()) > height);
                const bool tooWide = ((currentX + currentSize.width()) > width);
                if (tooTall || tooWide) {
                    if (tooTall) {
                        _overshoot = _overshoot | Overshoot::Vertical;
                    }

                    if (tooWide) {
                        _overshoot = _overshoot | Overshoot::Horizontal;
                    }

                    continue;
                }

                widget->setPosition(QPoint(currentX, currentRow));
                currentX = currentX + itemWidth;
                currentY = std::max(currentY, currentRow + currentSize.height());
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
