#include "tgrowlayout.h"
#include "widgets/tgwidget.h"

#include <QRect>

Tg::RowLayout::RowLayout() : Layout(Type::Row)
{
}

void Tg::RowLayout::doLayout()
{
    if (_type == Layout::Type::Row && _parent) {
        _overshoot = Overshoot::None;
        const QSize contentsSize = _parent->contentsRectangle().size();
        const int width = contentsSize.width();
        const int height = contentsSize.height();
        int currentX = 0;

        const auto children = _parent->childrenWidgets();
        for (const auto &widget : children) {
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
