#pragma once

#include "utils/tghelpers.h"

namespace Tg {
class Widget;

class Layout
{
public:
    enum class Type {
        None,
        ChildFillsParent,
        Column,
        Row,
        Grid
        //Form?
    };

    Layout();
    virtual ~Layout();

    const Type type = Type::None;
    Widget *parent = nullptr;

    /*!
     * Lays out child widgets of widget. It stretches first child to fill
     * the whole widget.
     */
    virtual void doLayout();

    /*!
     * Read this after calling doLayout() to check if all child widgets
     * fit nicely onto parent.
     */
    SizeOvershoot overshoot() const;

protected:
    Layout(const Type type);

    SizeOvershoot _overshoot = Overshoot::None;
};
}
