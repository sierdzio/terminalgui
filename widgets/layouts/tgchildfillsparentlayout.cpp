#include "tgchildfillsparentlayout.h"
#include "widgets/tgwidget.h"

#include <QRect>

Tg::ChildFillsParentLayout::ChildFillsParentLayout() : Layout(Type::ChildFillsParent)
{
}

void Tg::ChildFillsParentLayout::doLayout()
{
    if (type == Layout::Type::ChildFillsParent && parent) {
        _overshoot = Overshoot::None;
        for (const auto child : parent->children()) {
            auto widget = qobject_cast<Widget*>(child);
            if (widget) {
                widget->setSize(parent->contentsRectangle().size());
                // TODO: set overshoot if the widget cannot fill the given space!
                break;
            }
        }
    }
}
