#pragma once

#include "tglayout.h"

namespace Tg {
class GridLayout : public Layout
{
public:
    GridLayout();

    void doLayout() override;
};
}
