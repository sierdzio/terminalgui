#pragma once

#include "tglayout.h"

namespace Tg {
/*!
 * Arranges children of parent() Widget in a grid. By defaylt, the grid will
 * contain 2 columns - this can be changed by calling setColumnCount().
 *
 * Maximum number of rows cannot be set - it depends on columnCount() and the
 * number of children to lay out.
 */
class GridLayout : public Layout
{
public:
    GridLayout();

    void doLayout() override;

    /*!
     * Returns the maximal number of columns this grid will draw. If Widgets
     * do not fit, extra ones will be drawn in next row(s).
     */
    int columnCount() const;

    /*!
     * Sets the maximal \a number of columns which this grid will draw.
     */
    void setColumnCount(const int number);

private:
    int _columnCount = 2;
};
}
