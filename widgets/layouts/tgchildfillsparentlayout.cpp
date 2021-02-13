#include "tgchildfillsparentlayout.h"
#include "widgets/tgwidget.h"

#include <QRect>

Tg::ChildFillsParentLayout::ChildFillsParentLayout() : Layout(Type::ChildFillsParent)
{
}

void Tg::ChildFillsParentLayout::doLayout()
{
    if (_type == Layout::Type::ChildFillsParent && _parent) {
        _overshoot = Overshoot::None;

        const auto children = _parent->childrenWidgets();
        for (const auto &widget : children) {
            widget->setSize(_parent->contentsRectangle().size());

            if (widget->widgetOvershoot().testFlag(Overshoot::None) == false) {
                _overshoot = widget->widgetOvershoot();
            }

            break;
        }
    }
}
