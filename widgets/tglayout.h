#pragma once

namespace Tg {
class Widget;

class Layout
{
public:
    enum class Type {
        None,
        ChildFillsParent,
        Column,
        //Row,
        //Form,
        //Grid
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

protected:
    Layout(const Type type);
};
}
