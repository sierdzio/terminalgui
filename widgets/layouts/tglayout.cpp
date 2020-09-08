#include "tglayout.h"
#include "widgets/tgwidget.h"

#include <QRect>

Tg::Layout::Layout() : type(Type::None)
{
}

Tg::Layout::~Layout()
{
    // Nothing
}

void Tg::Layout::doLayout()
{
    if (type == Layout::Type::None) {
        _overshoot = Overshoot::None;
        const QSize contentsSize = parent->contentsRectangle().size();
        for (const auto child : parent->children()) {
            const auto widget = qobject_cast<Widget*>(child);
            if (widget) {
                if (widget->size().width() > contentsSize.width()) {
                    _overshoot = _overshoot | Overshoot::Horizontal;
                }

                if (widget->size().height() > contentsSize.height()) {
                    _overshoot = _overshoot | Overshoot::Vertical;
                }
            }
        }
    }
}

Tg::SizeOvershoot Tg::Layout::overshoot() const
{
    return _overshoot;
}

Tg::Layout::Layout(const Tg::Layout::Type atype) : type(atype)
{
}
