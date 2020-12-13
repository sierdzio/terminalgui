#pragma once

#include "tglayout.h"

namespace Tg {
/*!
 * This Layout works only on a single child of parent() Widget and stretches
 * it to fill the parent().
 */
class ChildFillsParentLayout : public Layout
{
public:
    ChildFillsParentLayout();

    void doLayout() override;
};
}
