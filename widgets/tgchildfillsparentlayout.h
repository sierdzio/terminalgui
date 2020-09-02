#pragma once

#include "tglayout.h"

namespace Tg {
class ChildFillsParentLayout : public Layout
{
public:
    void doLayout() override;
};
}
