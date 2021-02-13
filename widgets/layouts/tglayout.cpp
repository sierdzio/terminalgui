#include "tglayout.h"
#include "widgets/tgwidget.h"

#include <QRect>

Tg::Layout::Type Tg::Layout::type() const
{
    return _type;
}

Tg::Widget *Tg::Layout::parent() const
{
    return _parent;
}

void Tg::Layout::setParent(Tg::Widget *parent)
{
    _parent = parent;
}

void Tg::Layout::doLayout()
{
    if (_type == Layout::Type::None) {
        _overshoot = Overshoot::None;
        const QSize contentsSize = _parent->contentsRectangle().size();
        const auto children = _parent->childrenWidgets();

        for (const auto &widget : children) {
            if (widget->size().width() > contentsSize.width()) {
                _overshoot = _overshoot | Overshoot::Horizontal;
            }

            if (widget->size().height() > contentsSize.height()) {
                _overshoot = _overshoot | Overshoot::Vertical;
            }
        }
    }
}

Tg::SizeOvershoot Tg::Layout::overshoot() const
{
    return _overshoot;
}

Tg::Layout::Layout(const Tg::Layout::Type atype) : _type(atype)
{
}
