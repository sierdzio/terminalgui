#pragma once

#include "tglayout.h"

namespace Tg {
class ColumnLayout : public Layout
{
public:
    ColumnLayout();

    void doLayout() override;
};
}
