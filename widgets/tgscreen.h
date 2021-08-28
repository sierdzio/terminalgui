#pragma once

#include <QObject>
#include <QPointer>
#include <QList>
#include <QSize>
#include <QRect>
#include <QTimer>

#include "utils/tghelpers.h"

/*!
 * All Terminal GUI classes (both core and widgets) are defined within the Tg
 * namespace. Additionally, all source and header files are prefixed with "tg",
 * followed by class name written all in lower case.
 */
namespace Tg {
class Terminal;

/*!
 * Screen is the "canvas" on which widgets (subclasses of Widget) are drawn.
 *
 * Every top-level Widget needs to be a child of Screen. This is done using
 * Widget constructor, which internally calls registerWidget(). When a Widget is
 * deleted, deregisterWidget() is called to notify the Screen.
 *
 * Internally, Screen uses Terminal to know available space, and to interact
 * with the console.
 */
class Screen : public QObject
{
    Q_OBJECT

    /*!
     * Size of the Screen. This can be different than size of the actual
     * terminal window (for example, you can have 2 screens drawn in a single
     * terminal).
     *
     * \warning More than one Screen is not yet supported. Sorry!
     *
     * \todo Differentiate between Terminal size and size of screen reserved
     * for application
     */
    Q_PROPERTY(QSize size READ size NOTIFY sizeChanged)

    /*!
     * When `true`, widgets can be dragged around on the Screen using a mouse.
     * To drag, click and hold your mouse over Widget's border, then move the
     * mouse.
     */
    Q_PROPERTY(bool canDragWidgets READ canDragWidgets WRITE setCanDragWidgets NOTIFY canDragWidgetsChanged)

    /*!
     * When `true`, mouse movements will be tracked, allowing for mouse clicking
     * of buttons, drag & drop etc.
     */
    Q_PROPERTY(bool mouseTracking READ mouseTracking WRITE setMouseTracking NOTIFY mouseTrackingChanged)

    friend class Widget;

public:
    /*!
     * Constructs a Screen. A Screen is parent for all Widget objects drawn
     * within it's size(). \a parent is usually `nullptr`.
     *
     * \a style object will be used as base style of all widgets registered
     * under this Screen. If `nullptr` is passed, a default Style will be
     * constructed.
     */
    Screen(QObject *parent = nullptr, const StylePointer &style = nullptr);

    /*!
     * Returns the size of this Screen.
     *
     * \note Screen size might be different than terminal window size.
     */
    QSize size() const;

    /*!
     * Returns the default style, shared with all Widget instances.
     */
    StylePointer style() const;

    bool canDragWidgets() const;

    bool mouseTracking() const;
    void setMouseTracking(const bool enable);

public slots:
    /*!
     * Schedules a redraw of \a widget using \a type.
     *
     * Draw operations are not performed immediately, but rather use
     * compressRedraws() to only draw Screen changes once in a while.
     *
     * To force an immedate redraw, call draw().
     *
     * \sa draw, compressRedraws
     */
    void scheduleRedraw(const RedrawType type, const Widget *widget);

    /*!
     * Finds next Widget ready to accept keyboard focus and moves the focus to
     * it.
     *
     * See Widget::setAcceptsFocus().
     */
    void moveFocusToPreviousWidget();

    /*!
     * Finds previous Widget ready to accept keyboard focus and moves the focus
     * to it.
     *
     * See Widget::setAcceptsFocus().
     */
    void moveFocusToNextWidget();

    void setCanDragWidgets(const bool canDragWidgets);

signals:
    /*!
     * Emitted when Screen's \a size is modified.
     */
    void sizeChanged(const QSize &size) const;

    void canDragWidgetsChanged(const bool canDragWidgets) const;

    void mouseTrackingChanged() const;

private slots:
    void draw();
    void checkKeyboard();
    void setSize(const QSize &size);

private:
    enum class DragType {
        Unknown,
        Move,
        Resize
    };

    /*!
     * Registers \a widget with this Screen. When contents are being drawn,
     * Screen uses the list of registered widgets to delegate drawing to
     * appropriate Widget (based on z-value, position and size of each Widget).
     *
     * \sa draw
     */
    void registerWidget(Widget *widget);
    void deregisterWidget(Widget *widget);

    void registerCurrentModalWidget(Widget *widget);
    void deregisterCurrentModalWidget(Widget *widget);

    void updateRedrawRegions(const RedrawType type, const Widget *widget);
    void updateRedrawRegion(const QRect &region);

    /*!
     * Runs a timer which ensures that Screen is not redrawn too often.
     *
     * \sa scheduleRedraw, draw
     */
    void compressRedraws();
    void setActiveFocusWidget(const WidgetPointer &widget);
    void clearActiveFocusWidget();

    void handleDrag(const QPoint &point, const bool isPressActive);

    QTimer _keyboardTimer;
    QTimer _redrawTimer;
    QVector<QRect> _redrawRegions;
    QSize _size;

    WidgetList _widgets;
    WidgetPointer _activeFocusWidget;
    WidgetPointer _activeModalWidget;
    StylePointer _style;
    QPointer<Terminal> _terminal;

    bool _canDragWidgets = true;
    DragType _dragType = DragType::Unknown;
    WidgetPointer _dragWidget;
    QPoint _dragRelativePosition;
};
}
