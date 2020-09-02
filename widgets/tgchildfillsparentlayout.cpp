#include "tgchildfillsparentlayout.h"
#include "tgwidget.h"

#include <QRect>

void Tg::ChildFillsParentLayout::doLayout()
{
    if (type == Layout::Type::ChildFillsParent && parent) {
        const auto children = parent->findChildren<Widget *>(
                    QString(), Qt::FindChildOption::FindDirectChildrenOnly);
        if (children.isEmpty() == false) {
            children.at(0)->setSize(parent->contentsRectangle().size());
        }
    }
}
