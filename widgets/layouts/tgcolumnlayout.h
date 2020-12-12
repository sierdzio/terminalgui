#pragma once

#include "tglayout.h"

namespace Tg {
/*!
 * Arranges all children of parent() Widget in a single column.
 */
class ColumnLayout : public Layout
{
public:
    ColumnLayout();

    void doLayout() override;
};
}
