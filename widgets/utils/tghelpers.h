#pragma once

#include <QPointer>
#include <QFlag>

class QString;

/*!
 * Makes sure `condition` is true, otherwise crashes the application.
 *
 * This is useful when using connect(), QMetaObject::invokeMethod() and other
 * similar pieces of code which should ALWAYS return true, but if developer
 * makes a mistake they only print warnings which are easy to miss.
 *
 \\verbatim
CHECK(connect(object, &Class::someSignal,
              receiver, &OtherClass:someSlot,
              Qt::QueuedConnection));

CHECK(QMetaObject::invokeMethod(
    object, "functionName",
    Qt::QueuedConnection,
    Q_ARG(QVector, something));
 \\endverbatim
 *
 */
#if !defined(CHECK)
#if defined(DEBUG_BUILD)
#define CHECK(condition) if (!condition) qFatal("Check failed!")
#else
#define CHECK(condition) condition
#endif
#endif

namespace Helpers {
}

namespace Tg {
class Widget;
using WidgetPointer = QPointer<Widget>;

/*!
 * Describes situation when items in layout cannot fit into parent widget
 * or widget contents do not fit it's size.
 */
enum class Overshoot {
    //! There is no overshoot - widgets in layout fit nicely into the
    //! parent widget
    None = 0x00,
    //! Children widgets do not fit in the horizontal direction
    Horizontal = 0x01,
    //! Children widgets do not fit in the vertical direction
    Vertical = 0x02
};
Q_DECLARE_FLAGS(SizeOvershoot, Overshoot)
Q_DECLARE_OPERATORS_FOR_FLAGS(SizeOvershoot)

/*!
 * Specifies how much of the Tg::Screen needs to be redrawn.
 */
enum class RedrawType {
    //! Only redraw a part of the screen
    Partial,
    FulLWidget = Partial,
    //! Area where widget *used to be* should be redrawn
    PreviousPosition,
    //! Redraw everything
    Full
    // TODO: consider adding: FullWidget
};

}
