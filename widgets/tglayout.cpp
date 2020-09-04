#include "tglayout.h"

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
        return;
    }
}

Tg::Layout::Layout(const Tg::Layout::Type atype) : type(atype)
{
}
