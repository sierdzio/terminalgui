#include "tglayout.h"

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
