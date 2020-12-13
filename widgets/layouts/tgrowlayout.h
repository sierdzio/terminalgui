#pragma once

#include "tglayout.h"

namespace Tg {
/*!
 * Arranges all children of parent() Widget in a single row.
 */
class RowLayout : public Layout
{
public:
    RowLayout();

    void doLayout() override;
};
}
