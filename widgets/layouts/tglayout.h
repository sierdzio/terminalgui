#pragma once

#include <QFlag>

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

    /*!
     * Describes situation when items in layout cannot fit into parent widget.
     */
    enum class Overshoot {
        //! There is no overshoot - widgets in layout fit nicely into the
        //! parent widget
        None = 0x00,
        //! Children widgets do not fit in the horizontal direction
        Horizontal = 0x01,
        //! Children widgets do not fit in the vertical direction
        Vertical = 0x02
    };
    Q_DECLARE_FLAGS(SizeOvershoot, Layout::Overshoot)


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

Q_DECLARE_OPERATORS_FOR_FLAGS(Layout::SizeOvershoot)
}
