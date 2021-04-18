#pragma once

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPointer>

#include <QMetaEnum>

#include <tgcolor.h>

#include "utils/tghelpers.h"
#include "layouts/tglayout.h"

class QTimer;

namespace Tg {
class Screen;
class Layout;

/*!
 * Base class for all widgets in a Terminal Gui application.
 *
 * Plain Widget, when drawn on screen, will draw its border and an empty
 * interior. If it is a child of another Widget, or when borderVisible() is
 * `false`, it only draw empty contents.
 *
 * \section subclassing Subclassing
 *
 * Widget subclasses reimplement its drawPixel() method to draw actual contents.
 * It is also very important to reimplement init() method and put initialization
 * code there, plus all signal and slot connections necessary to update the
 * Screen when Widget changes.
 *
 * Every Widget subclass should contain at least 2 constructors:
 * \li one taking Screen pointer - used when subclass is a top-level widget
 * \li one taking Widget pointer - used when subclass is not a top-level widget
 *
 * If a subclass needs keyboard interaction, it should call setAcceptsFocus() in
 * its init() override, and implement consumeKeyboardBuffer() with logic
 * responding to key presses. See Key namespace for helper constants which make
 * detection of particular clicks easier.
 *
 * \section diff Differences from Qt Widgets
 *
 * Unlike QWidget which relies on a separate class to do layouting (QLayout),
 * Widget can lay its children automatically. This can be controlled using
 * setLayoutType().
 *
 * \section style Styling
 *
 * Widget (and all its subclasses) can be styled in several ways. By default,
 * Widget inherits Style from its parent (or Screen class) unless
 * propagatesStyle() returns `false`. A custom Style can be set (either for this
 * Widget only, or also for all its children) using setStyle(). Alternatively,
 * each individual style-related property can be overriden using various
 * setters (for example: setBackgroundColor(), setTextColor() etc.). These
 * setters always work only for this single Widget and have no effect on its
 * children.
 *
 * \since 0.1.0
 */
class Widget : public QObject
{
    Q_OBJECT

    /*!
     * Position of Widget.
     *
     * Position is relative either to the Screen or to its parent Widget.
     */
    Q_PROPERTY(QPoint position READ position WRITE setPosition NOTIFY positionChanged)

    /*!
     * Size of the Widget.
     *
     * If the Widget is a child of another one, with layout set, the size will
     * be modified automatically to fit the layout.
     */
    Q_PROPERTY(QSize size READ size WRITE setSize NOTIFY sizeChanged)

    /*!
     * Widget position on the `z` axis - this is used to control which Widgets
     * should be displayed above and which below if they overlap.
     */
    Q_PROPERTY(int z READ z WRITE setZ NOTIFY zChanged)

    /*!
     * Color of the background of Widget's interior (contentsRectangle()).
     *
     * \note If no color is set (or Color::Predefined::Invalid is set), a default
     * color will be taken from Style object (see style()).
     *
     * \note When this property is modified, it only affects this object. Other
     * Widgets, including children, will still get their colors from propagated
     * Style object.
     */
    Q_PROPERTY(Tg::Color backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)

    /*!
     * This is the character which fills the *empty* background. By default it
     * is *space*, so no character is shown at all (only backgroundColor()).
     *
     * \note When this property is modified, it only affects this object. Other
     * Widgets, including children, will still get baground character from
     * propagated Style object.
     */
    Q_PROPERTY(QChar backgroundCharacter READ backgroundCharacter WRITE setBackgroundCharacter NOTIFY backgroundCharacterChanged)

    /*!
     * Color of the characters ("foreground color") printed inside of the
     * Widget (see contentsRectangle()).
     *
     * \note If no color is set (or Color::Predefined::Invalid is set), a default
     * color will be taken from Style object (see style()).
     *
     * \note When this property is modified, it only affects this object. Other
     * Widgets, including children, will still get their colors from propagated
     * Style object.
     */
    Q_PROPERTY(Tg::Color textColor READ textColor WRITE setTextColor NOTIFY textColorChanged)

    /*!
     * Widget title, displayed on top border (if border is visible).
     */
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)

    // TODO: customizable title color!

    /*!
     * Color of the characters ("foreground color") printed on the borders of
     * the Widget (see boundingRectangle()).
     *
     * \note If no color is set (or Color::Predefined::Invalid is set), a default
     * color will be taken from Style object (see style()).
     *
     * \note When this property is modified, it only affects this object. Other
     * Widgets, including children, will still get their colors from propagated
     * Style object.
     */
    Q_PROPERTY(Tg::Color borderTextColor READ borderTextColor WRITE setBorderTextColor NOTIFY borderTextColorChanged)

    /*!
     * Color of the background of Widget's border (see boundingRectangle()).
     *
     * \note If no color is set (or Color::Predefined::Invalid is set), a default
     * color will be taken from Style object (see style()).
     *
     * \note When this property is modified, it only affects this object. Other
     * Widgets, including children, will still get their colors from propagated
     * Style object.
     */
    Q_PROPERTY(Tg::Color borderBackgroundColor READ borderBackgroundColor WRITE setBorderBackgroundColor NOTIFY borderBackgroundColorChanged)

    /*!
     * A visible Widget is visible. Right?
     */
    Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibleChanged)

    /*!
     * Controls whether border is drawn.
     *
     * When border is visible, Widget contents
     * are drawn inside of it (call contentsRectangle() to get the are inside of
     * the borders).
     *
     * When border is not visible, contents fill the whole boundingRectangle()
     * (thus contentsRectangle() and boundingRectangle() return the same data).
     *
     * \sa boundingRectangle, globalBoundingRectangle,
     * globalPreviousBoundingRectangle, contentsRectangle, effectiveBorderWidth
     */
    Q_PROPERTY(bool borderVisible READ borderVisible WRITE setBorderVisible NOTIFY borderVisibleChanged)

    /*!
     * When true, Widget will receive keyboard signals (Screen will call
     * consumeKeyboardBuffer()) when its turn comes.
     */
    Q_PROPERTY(bool acceptsFocus READ acceptsFocus NOTIFY acceptsFocusChanged)

    /*!
     * Returns `true` when Widget is currently actively listening to keyboard
     * signals.
     *
     * \sa acceptsFocus
     */
    Q_PROPERTY(bool hasFocus READ hasFocus NOTIFY hasFocusChanged)

    /*!
     * If `true`, Widget will set its Style object on its children widgets.
     * If `false`, WIdget will keep its Style to itself (child widgets will
     * inherit Style from Screen instead).
     */
    Q_PROPERTY(bool propagatesStyle READ propagatesStyle NOTIFY propagatesStyleChanged)

    friend class Screen;
    friend class ScrollArea;

public:
    /*!
     * Constructs Widget as a child of \a parent. By default, a child Widget
     * does not have a border.
     *
     * \sa setBorderVisible
     */
    explicit Widget(Widget *parent);

    /*!
     * Constructs a top-level Widget on a given \a screen. A top-level does have
     * a border by default.
     *
     * There can be many top-level Widgets registered under the same Screen.
     *
     * \sa setBorderVisible
     */
    explicit Widget(Screen *screen);

    /*!
     * Deregisters the Widget from parent Screen, then destroys the Widget
     * object.
     */
    ~Widget();

    /*!
     * Returns current position of the Widget (relative).
     *
     * \sa mapToGlobal, boundingRectangle, globalBoundingRectangle
     */
    QPoint position() const;

    /*!
     * Returns current size of the Widget.
     *
     * \sa boundingRectangle
     */
    QSize size() const;

    /*!
     * Returns the rectangle constructed from position() and size().
     *
     * This rectangle includes Widget border and contents.
     */
    QRect boundingRectangle() const;

    /*!
     * Returns the rectangle contructed from position() (mapped to global
     * coordinates using mapToGlobal()) and size().
     *
     * This rectangle includes Widget border and contents.
     */
    QRect globalBoundingRectangle() const;

    /*!
     * Returns the rectangle which holds Widget interior. It is similar to
     * boundingRectangle() but with Widget border removed.
     */
    QRect contentsRectangle() const;

    /*!
     * Returns current background color - either taken from Style or value set
     * using setBackgroundColor().
     *
     * \sa style, setBackgroundColor
     */
    Tg::Color backgroundColor() const;

    /*!
     * Returns character drawn on empty space in this Widget.
     */
    QChar backgroundCharacter() const;

    /*!
     * Returns current text color - either taken from Style or value set using
     * setTextColor().
     *
     * \sa style, setTextColor
     */
    Tg::Color textColor() const;

    /*!
     * Returns Widget's title.
     */
    QString title() const;

    /*!
     * Returns current border text color - either taken from Style or value set
     * using setBorderTextColor().
     *
     * The "text" on Widget border are the lines (characters) used to draw the
     * border. They are defined in BorderStyle.
     *
     * \sa style, setBorderTextColor
     */
    Tg::Color borderTextColor() const;

    /*!
     * Returns current border background color - either taken from Style or
     * value set using setBorderBackgroundColor().
     *
     * \sa style, setBorderBackgroundColor
     */
    Tg::Color borderBackgroundColor() const;

    /*!
     * Returns `true` when Widget is visible.
     */
    bool visible() const;

    /*!
     * Returns `true` when Widget's border is visible. A top-level Widget has
     * border visible by default. It can be overriden using setBorderVisible().
     *
     * \sa setBorderVisible
     */
    bool borderVisible() const;

    /*!
     * Returns `true` when Widget is set to accept focus (keyboard or mouse).
     *
     * \sa setAcceptsFocus, hasFocus
     */
    bool acceptsFocus() const;

    /*!
     * Returns `true` when Widget actively holds focus (is receiving keyboard
     * events).
     *
     * \sa setHasFocus, acceptsFocus
     */
    bool hasFocus() const;

    /*!
     * If this Widget accepts focus (acceptsFocus() returns `true`), calling
     * this method will make it the currect active focus widget.
     *
     * If Widget does not accepts focus, or if it already has active focus,
     * this method does nothing.
     */
    void setActiveFocus();

    /*!
     * When \a accept is `true`, this Widget will receive keyboard events from
     * Screen instance - but only when it actively holds focus (see hasFocus()).
     *
     * In order to be able to "do something" with keyboard events, reimplement
     * consumeKeyboardBuffer().
     *
     * \sa hasFocus, acceptsFocus
     */
    void setAcceptsFocus(const bool accept);

    /*!
     * Returns the Screen on which this Widget is being drawn.
     */
    Screen *screen() const;

    /*!
     * Returns the parent Widget. If returned pointer is a `nullptr`, it means
     * this Widget is a top level Widget, usually drawn with border (unless
     * setBorderVisible() has overriden the default behavior).
     *
     * \sa setBorderVisible, topLevelParentWidget
     */
    Widget *parentWidget() const;

    /*!
     * Returns top-level parent of current Widget. If current Widget is already
     * top-level, it will return a pointer to itself.
     *
     * This function will never return a `nullptr`.
     *
     * \sa parentWidget, isTopLevel
     */
    Widget *topLevelParentWidget() const;

    /*!
     * Returns `true` if this Widget is top-level. This means that
     * parentWidget() returns `nullptr`.
     */
    bool isTopLevel() const;

    /*!
     * Returns `true` when \a pixel lies within the border of the Widget.
     *
     * If border is not visible, it will always return `false`.
     *
     * \sa borderVisible
     */
    bool isBorder(const QPoint &pixel) const;

    /*!
     * Returns `true` if this Widget ignores up and down arrows on keyboard.
     * Also returns `true` if Widget does not accept focus at all.
     */
    bool verticalArrowsMoveFocus() const;

    /*!
     * Returns \a position mapped from global coordinates into local one
     * (coordinates within the Widget, where (0,0) is top-left corner).
     */
    QPoint mapFromGlobal(const QPoint &position) const;

    /*!
     * Returns \a position mapped from local coordinates into global ones
     * (coordinates within parent Screen).
     */
    QPoint mapToGlobal(const QPoint &position) const;

    /*!
     * Returns \a position mapped into \a child coordinate system.
     */
    QPoint mapToChild(const WidgetPointer &child, const QPoint &position) const;

    /*!
     * Returns `true` if this Widget automatically applies its Style to all
     * children Widgets. This is `true` by default.
     */
    bool propagatesStyle() const;

    /*!
     * Sets a new Style on this Widget. If \a propagate is `true`, this new
     * Style pointer will also be set on all children (recursively).
     */
    void setStyle(const StylePointer &style, const bool propagate = true);

    /*!
     * Returns Layout type. It specifies how Widget places, paints and treats
     * children Widgets.
     */
    Layout::Type layoutType() const;

    /*!
     * Sets the way this Widget places, paints and treats children widgets to
     * \a type.
     */
    void setLayoutType(const Layout::Type type);

    /*!
     * Returns current overshoot of layout inside this Widget.
     *
     * If Widgets within the Layout do not fit the Widget, SizeOvershoot will
     * indicate whether Widget is too small horizontally or vertically.
     *
     * Visually, it is represented by drawing red arrows on Widget border (by
     * default - see BorderStyle::horizontalOvershoot,
     * BorderStyle::verticalOvershoot, BorderStyle::overshootTextColor and
     * BorderStyle::overshootBackgroundColor).
     */
    SizeOvershoot layoutOvershoot() const;

    /*!
     * Returns current overshoot of contents of this Widget.
     *
     * It is very similar to layoutOvershoot() but overshoot is reported when
     * Widget contents (not children Widgets arranged by a layout) fo not fit.
     * For example, when a Label has text which is too long to fit.
     *
     * \sa layoutOvershoot
     */
    SizeOvershoot widgetOvershoot() const;

    /*!
     * Returns the z value - position of this Widget on z order stack.
     */
    int z() const;

signals:
    /*!
     * Indicates that \a widget (usually `this`) needs to be redrawn using
     * redraw \a type.
     */
    void needsRedraw(const RedrawType type, const Widget *widget) const;

    /*!
     * Emitted when Widget's \a position changes.
     */
    void positionChanged(const QPoint &position) const;

    /*!
     * Emitted when Widget's \a size is changed.
     */
    void sizeChanged(const QSize &size) const;

    /*!
     * Indicates that Widget's background \a color has changed.
     */
    void backgroundColorChanged(const Tg::Color &color) const;

    /*!
     * Indicates that Widget's background \a character has changed.
     */
    void backgroundCharacterChanged(const QChar &character) const;

    /*!
     * Indicates that Widget's text \a color has changed.
     */
    void textColorChanged(const Tg::Color &color) const;

    /*!
     * Indicates that Widget's \a title has changed.
     */
    void titleChanged(const QString &title);

    /*!
     * Indicates that Widget's border text \a color has changed.
     */
    void borderTextColorChanged(const Tg::Color &color) const;

    /*!
     * Indicates that Widget's border background \a color has changed.
     */
    void borderBackgroundColorChanged(const Tg::Color &color) const;

    /*!
     * Indicates that Widget is shown or hidden (depening on \a visible).
     */
    void visibleChanged(const bool visible) const;

    /*!
     * Indicates that Widget's border is now \a visible (or not).
     */
    void borderVisibleChanged(const bool visible) const;

    /*!
     * Indicates that Widget now \a accepts focus (or not).
     */
    void acceptsFocusChanged(const bool accepts) const;

    /*!
     * Indicates that Widget now \a hasFocus (or not).
     */
    void hasFocusChanged(const bool hasFocus) const;

    /*!
     * Indicates that active focus should be moved to the previous Widget ready
     * to receive it.
     */
    void moveFocusToPreviousWidget() const;

    /*!
     * Indicates that active focus should be moved to the next Widget ready to
     * receive it.
     */
    void moveFocusToNextWidget() const;

    /*!
     * Indicates that Widget either stopped or resumed (\a propagates)
     * propagating its Style object to its children.
     */
    void propagatesStyleChanged(const bool propagates) const;

    /*!
     * Emitted when Widget's Style object is changed.
     */
    void styleChanged() const;

    /*!
     * Emitted when layout \a overshoot has changed.
     */
    void layoutOvershootChanged(const SizeOvershoot overshoot) const;

    /*!
     * Emitted when Widget \a overshoot has changed.
     */
    void widgetOvershootChanged(const SizeOvershoot overshoot) const;

    /*!
     * Emitted when a \a child Widget has been added.
     */
    void childAdded(Widget *child) const;

    /*!
     * Emitted when a child Widget has been removed.
     */
    void childRemoved() const;

    /*!
     * Emitted when \a z value changes.
     */
    void zChanged(const int z) const;

public slots:
    /*!
     * Moves Widget to a new \a position. The position is relative to parent
     * Widget, or to Screen if this Widget is top-level.
     */
    void setPosition(const QPoint &position);

    /*!
     * Resizes Widget to a new \a size.
     */
    void setSize(const QSize &size);

    /*!
     * Changes background \a color.
     */
    void setBackgroundColor(const Tg::Color &color);

    /*!
     * Changes \a character drawn in the empty space of this Widget.
     */
    void setBackgroundCharacter(const QChar &character);

    /*!
     * Changes text \a color.
     */
    void setTextColor(const Tg::Color &color);

    /*!
     * Changes Widget's \a title.
     */
    void setTitle(const QString &title);

    /*!
     * Changes border text \a color.
     */
    void setBorderTextColor(const Tg::Color &color);

    /*!
     * Changes border background \a color.
     */
    void setBorderBackgroundColor(const Tg::Color &color);

    /*!
     * Makes Widget \a visible (or not).
     *
     * \sa show, hide
     */
    void setVisible(const bool visible);

    /*!
     * Makes Widget visible.
     *
     * \sa setVisible, hide
     */
    void show();

    /*!
     * Makes Widget hidden.
     *
     * \sa setVisible, show
     */
    void hide();

    /*!
     * Makes Widget's border \a visible (or not).
     */
    void setBorderVisible(const bool visible);

    void setZ(const int z);

    /*!
     * Returns all children of this Widget which can be cast to Widget.
     */
    WidgetList childrenWidgets() const;

protected:
    /*!
     * Initializes Widget and it's connections. All subclasses should call
     * init() of its parent class. If a subclass has any properties or signals
     * which affect the visual look of the Widget, it should reimplement init()
     * and connect such signal to schedulePartialRedraw() slot.
     *
     * \sa schedulePartialRedraw
     */
    virtual void init();

    /*!
     * Sets this Widget to hold \a active focus (or not). This method is
     * typically only called by Screen. Setting it manually may lead to side
     * effects.
     */
    void setHasFocus(const bool active);

    /*!
     * Called when Widget accepts focus and \a keyboardBuffer is not empty.
     *
     * \sa acceptsFocus
     */
    virtual bool consumeKeyboardBuffer(const QString &keyboardBuffer);

    /*!
     * Returns ANSI-encoded string, used by Screen to draw the \a pixel.
     *
     * "Draws" the border at position \a pixel. The \a pixel is expected to be
     * in local coordinate system (where (0,0) denotes the top-left corner of
     * the border).
     *
     * \sa drawPixel, effectiveBorderWidth
     */
    virtual QString drawBorderPixel(const QPoint &pixel) const;

    /*!
     * Returns ANSI-encoded string, used by Screen to draw the \a pixel.
     *
     * "Draws" the internal contents of the Widget. Default implementation
     * draws the border (see drawBorderPixel()), any child Widgets (if present),
     * in accordance with layoutType(). If there is any empty space left, it is
     * filled with backgroundCharacter().
     *
     * \sa drawBorderPixel, layoutType, setLayoutType, backgroundCharacter,
     * children
     */
    virtual QString drawPixel(const QPoint &pixel) const;

    /*!
     * Returns Widget's last position (before it was moved), in global
     * coordinates. If Widget has not been moved, it will return same location
     * as position() mapped to global coordinate system.
     *
     * \sa previousSize
     */
    QPoint previousGlobalPosition() const;

    /*!
     * Returns Widget's previous size (before it was resized). If Widget has not
     * been resized, it will return same result as size().
     *
     * \sa previousGlobalPosition
     */
    QSize previousSize() const;

    /*!
     * Returns globalBoundingRectangle() recorded last time when widget was
     * moved or its size has been changed.
     */
    QRect globalPreviousBoundingRectangle() const;

    /*!
     * If borders are visible, it returns border width. Otherwise, it returns 0.
     *
     * \note Currently, setting custom border width is not supported, so this
     * method only return `0` (zero) or `1`.
     *
     * \sa borderVisible
     */
    int effectiveBorderWidth() const;

    /*!
     * If \a enable is `true`, clicking up arrow or down arrow on keyboard will
     * be intercepted by parent Screen and used to switch focus to previous or
     * next Widget. This Widget will not receive a call to
     * consumeKeyboardBuffer().
     *
     * \sa consumeKeyboardBuffer, hasFocus, acceptsFocus
     */
    void setVerticalArrowsMoveFocus(const bool enable);

    /*!
     * When \a propagate is `true`, this Widget will set its style() object on
     * its children whenever it changes. This means that Widget and all its
     * children will use the same Style object and draw their UI in the same
     * way.
     *
     * \note Each visual property can be locally (only for this Widget)
     * overriden by setting it to a value other than default. For example,
     * calling `setTextColor(Color::Predefined::Red);` will set the text color
     * of this Widget (but not its children!) to red.
     */
    void setPropagatesStyle(const bool propagate);

    /*!
     * Propagates style() to \a child. Both Widgets will use the same Style
     * object.
     */
    void propagateStyleToChild(Widget *child) const;

    /*!
     * Returns the pointer to Style object used to draw this Widget. By default,
     * same Style object is shared by all Widgets within a Screen.
     *
     * \sa setPropagatesStyle, propagateStyleToChild
     */
    StylePointer style() const;

    /*!
     * Sets current \a overshoot of the contents of this Widget.
     */
    void setWidgetOvershoot(const SizeOvershoot overshoot);

    /*!
     * Sets \a timer object which controls how long pressed elements (buttons,
     * scroll bar arrows, etc.) look different (pressed).
     *
     * \warning This method does not take ownership of the \a timer
     *
     * \sa Button, ScrollBar
     */
    void setupPressTimer(QTimer *timer) const;

    /*!
     * Forces Widget to lay out its children according to layoutType().
     *
     * \sa layoutType
     */
    void doLayout();

protected slots:
    /*!
     * Instructs Screen that full redraw of entire Screen area should be
     * performed.
     *
     * \warning Calling this method often can cause flicker!
     */
    void scheduleFullRedraw() const;

    /*!
     * Instructs Screen to redraw this Widget only, at its current position.
     *
     * \sa position, size
     */
    void schedulePartialRedraw() const;

    /*!
     * Instructs Screen to redraw the area previously occupied by this Widget.
     * This is necessary to "clean up" the are of Screen where Widget used to be
     * before it has been moved.
     *
     * \sa previousGlobalPosition, previousSize
     */
    void schedulePreviousPositionRedraw() const;

private:
    bool canRedraw() const;
    void updatePreviousBoundingRect();

    const int _borderWidth = 1;
    bool _resizableByMouse = true;

    QPointer<Screen> _screen;
    QPointer<Widget> _parentWidget;
    StylePointer _style;
    // TODO: smart pointer
    Layout *_layout = nullptr;
    SizeOvershoot _layoutOvershoot = Overshoot::None;
    SizeOvershoot _widgetOvershoot = Overshoot::None;

    QPoint _position = { 0, 0 };
    QPoint _previousGlobalPosition = { 0, 0 };
    QSize _size = { 1, 1 };
    QSize _previousSize = { 1, 1 };
    int _z = 0;

    Tg::Color _backgroundColor;
    Tg::Color _textColor;
    Tg::Color _borderTextColor;
    Tg::Color _borderBackgroundColor;

    bool _visible = false;
    bool _borderVisible = true;
    bool _acceptsFocus = false;
    bool _hasFocus = false;
    bool _verticalArrowsMoveFocus = false;
    bool _propagatesStyle = true;
    QChar _backgroundCharacter;
    QString _title;
};
}
