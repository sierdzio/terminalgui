#pragma once

#include "tglayout.h"

namespace Tg {
class RowLayout : public Layout
{
public:
    RowLayout();

    void doLayout() override;
};
}
