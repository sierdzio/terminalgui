#include "tgchildfillsparentlayout.h"
#include "tgwidget.h"

#include <QRect>

void Tg::ChildFillsParentLayout::doLayout()
{
    if (type == Layout::Type::ChildFillsParent && parent) {
        for (const auto child : parent->children()) {
            auto widget = qobject_cast<Widget*>(child);
            if (widget) {
                widget->setSize(parent->contentsRectangle().size());
                break;
            }
        }
    }
}
