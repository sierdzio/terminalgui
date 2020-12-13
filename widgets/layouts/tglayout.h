#pragma once

#include "utils/tghelpers.h"

namespace Tg {
class Widget;

/*!
 * Helper class for Widget, manages positions and sizes of Widget's children.
 *
 * When subclassing, reimplement doLayout().
 *
 * \note Currently, all child Widgets will be sized equally by the layout.
 * Stretch and size hint functionality from QtWidgets are not implemented.
 */
class Layout
{
public:
    /*!
     * Type of a Layout. Each Layout subclass has a distinct Layout::Type.
     *
     * Default is Type::None, used by main Layout class.
     */
    enum class Type {
        //! Does not perform any adjustment of child Widgets.
        None,
        //! A single child Widget will fill the entirety of parent Widget.
        ChildFillsParent,
        //! Each child Widget will be put below previous one in a single column.
        //! All Widgets are as wide as the parent Widget.
        //! For example, when a Widget has 3 children, it will have 3 "rows",
        //! each occupying 33% of parent Widget's height. All 3 children will be
        //! as wide as the parent Widget.
        Column,
        //! Each child Widget will be put after previous one in a single row.
        //! All Widgets are as high as the parent Widget.
        //! For example, when a Widget has 3 children, it will have 3 "columns",
        //! each occupying 33% of parent Widget's width. All 3 children will be
        //! as high as the parent Widget.
        Row,
        //! Each child Widget will be put in a same-sized grid item.
        //! \todo Improve description (and implementation... ;-))
        Grid
        //Form?
    };

    Layout() {}
    virtual ~Layout() {}

    /*!
     * Returns the Type of this Layout.
     */
    Type type() const;

    /*!
     * Returns the parent Widget - on which Layout is working to resize and
     * position it's children.
     *
     * \sa setParent
     */
    Widget *parent() const;

    /*!
     * Sets the \a parent Widget.
     *
     * \sa parent
     */
    void setParent(Widget *parent);

    /*!
     * Lays out children of Widget (parent). It stretches first child to fill
     * the whole widget.
     */
    virtual void doLayout();

    /*!
     * Read this after calling doLayout() to check if all child widgets
     * fit nicely onto parent.
     */
    SizeOvershoot overshoot() const;

protected:
    /*!
     * Constructor used by subclasses to set Layout \a type they implement.
     */
    Layout(const Type type);

    /*!
     * Indicates whether children of Widget cannot fit the Widget, and in which
     * direction they fail to fit.
     */
    SizeOvershoot _overshoot = Overshoot::None;

    /*!
     * Parent Widget. Layout will work on correct positioning and resizing of
     * this Widget's children when doLayout() is called.
     */
    Widget *_parent = nullptr;

    /*!
     * Type of a Layout. Each subclass sets it's own Type.
     */
    const Type _type = Type::None;
};
}
