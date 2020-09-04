#include "tgcolumnlayout.h"
#include "tgwidget.h"

Tg::ColumnLayout::ColumnLayout() : Layout(Type::Column)
{
}

void Tg::ColumnLayout::doLayout()
{
    // TODO: LayoutSettings class!

    const int columns = 2;
    int currentColumn = 0;
    int currentRow = 0;
    int currentX = 0;
    int currentY = 0;

    if (type == Layout::Type::Column && parent) {
        for (const auto child : parent->children()) {
            auto widget = qobject_cast<Widget*>(child);
            if (widget) {
                widget->setPosition(QPoint(currentX, currentRow));
                const QSize size = widget->size();
                currentX = currentX + size.width();
                currentY = std::max(currentY, currentRow + size.height());
                currentColumn++;

                if (currentColumn >= columns) {
                    currentColumn = 0;
                    currentX = 0;
                    currentRow = currentY;
                }
            }
        }
    }
}
