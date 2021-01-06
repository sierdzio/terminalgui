#include "tghelpers.h"

#include "widgets/tgwidget.h"

#include <QRect>

Tg::WidgetPointer Tg::Helpers::topWidget(const Tg::WidgetList &widgets,
                                         const QPoint &pixel,
                                         const Tg::WidgetType type)
{
    const auto comparison = [](const WidgetPointer &left, const WidgetPointer &right) {
        return left->z() < right->z();
    };

    // TODO: sort by Z value...
    WidgetList affectedWidgets;
    for (const WidgetPointer &widget : widgets) {
        if (widget->visible()) {
            if ((type == WidgetType::TopLevel && widget->isTopLevel())
                    || type == WidgetType::All) {
                if (widget->boundingRectangle().contains(pixel)) {
                    affectedWidgets.append(widget);
                    // Keep the list sorted - highest Z value is last
                    std::sort(affectedWidgets.begin(), affectedWidgets.end(), comparison);
                }
            }
        }
    }

    // TODO: properly handle Z value...
    if (affectedWidgets.isEmpty()) {
        return nullptr;
    } else {
        // The list is sorted, so we can safely take the last element:
        return affectedWidgets.last();
    }
}
