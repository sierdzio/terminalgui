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

        if (width < 0 || height < 0) {
            return;
        }

        const int cellWidth = width / _columnCount;
        const auto children = _parent->childrenWidgets();
        const int childrenCount = children.size();

        if (childrenCount < 1) {
            return;
        }

        const int cellHeight = height / std::max(childrenCount / _columnCount, 1);
        const QSize cellSize = QSize(cellWidth, cellHeight);

        int currentX = 0;
        int currentY = 0;

        for (const auto &widget : children) {
            widget->setPosition(QPoint(currentX, currentY));
            widget->setSize(cellSize);
            currentX = currentX + cellWidth;

            if (currentX > width) {
                currentX = 0;
                currentY += cellHeight;
            }

            if (widget->widgetOvershoot().testFlag(Overshoot::None) == false) {
                _overshoot = _overshoot | widget->widgetOvershoot();
            }
        }
    }
}

int Tg::GridLayout::columnCount() const
{
    return _columnCount;
}

void Tg::GridLayout::setColumnCount(const int count)
{
    _columnCount = count;
}
