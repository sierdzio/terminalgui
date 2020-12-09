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
 * \list
 * \li one taking Screen pointer - used when subclass is a top-level widget
 * \li one taking Widget pointer - used when subclass is not a top-level widget
 * \endlist
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
 */
class Widget : public QObject
{
    Q_OBJECT

    /*!
     * Position of Widget - either on the Screen or within it's parent Widget.
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
    explicit Widget(Widget *parent);
    explicit Widget(Screen *parentScreen);
    ~Widget();

    QPoint position() const;
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
     * Returns globalBoundingRectangle() recorded last time when widget was
     * moved or its size has been changed.
     */
    QRect globalPreviousBoundingRectangle() const;

    /*!
     * Returns the rectangle which holds Widget interior. It is similar to
     * boundingRectangle() but with Widget border removed.
     */
    QRect contentsRectangle() const;

    Tg::Color backgroundColor() const;
    QChar backgroundCharacter() const;
    Tg::Color textColor() const;
    Tg::Color borderTextColor() const;
    Tg::Color borderBackgroundColor() const;

    bool visible() const;
    bool borderVisible() const;
    bool acceptsFocus() const;
    bool hasFocus() const;

    void setAcceptsFocus(const bool acceptsFocus);
    void setHasFocus(const bool hasFocus);

    /*!
     * Returns the Screen on which this Widget is being drawn.
     */
    Screen *screen() const;

    /*!
     * Returns the parent Widget. If returned pointer is a `nullptr`, it means
     * this Widget is a top level Widget, usually drawn with border (unless
     * setBorderVisible() has overriden the default behavior).
     *
     * \sa setBorderVisible()
     */
    Widget *parentWidget() const;

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

signals:
    void needsRedraw(const RedrawType type, const Widget *widget) const;
    void positionChanged(const QPoint &position) const;
    void sizeChanged(const QSize &size) const;
    void backgroundColorChanged(const Tg::Color &backgroundColor) const;
    void backgroundCharacterChanged(const QChar &backgroundCharacter) const;
    void textColorChanged(const Tg::Color &textColor) const;
    void borderTextColorChanged(const Tg::Color &borderColor) const;
    void borderBackgroundColorChanged(const Tg::Color &borderBackgroundColor) const;
    void visibleChanged(const bool visible) const;
    void borderVisibleChanged(const bool borderVisible) const;
    void acceptsFocusChanged(const bool acceptsFocus) const;
    void hasFocusChanged(const bool hasFocus) const;
    void moveFocusToPreviousWidget() const;
    void moveFocusToNextWidget() const;
    void propagatesStyleChanged(const bool propagatesStyle) const;
    void styleChanged() const;
    void layoutOvershootChanged(const SizeOvershoot overshoot) const;
    void widgetOvershootChanged(const SizeOvershoot overshoot) const;
    void childAdded(Widget *child);
    void childRemoved();

public slots:
    void setPosition(const QPoint &position);
    void setSize(const QSize &size);
    void setBackgroundColor(const Tg::Color &backgroundColor);
    void setBackgroundCharacter(const QChar &backgroundCharacter);
    void setTextColor(const Tg::Color &textColor);
    void setBorderTextColor(const Tg::Color &borderColor);
    void setBorderBackgroundColor(const Tg::Color &borderBackgroundColor);
    void setVisible(const bool visible);
    void show();
    void hide();
    void setBorderVisible(const bool borderVisible);

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
     * Called when Widget accepts focus and \a keyboardBuffer is not empty.
     *
     * \sa acceptsFocus
     */
    virtual void consumeKeyboardBuffer(const QString &keyboardBuffer);

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

    QPoint previousGlobalPosition() const;
    QSize previousSize() const;

    int effectiveBorderWidth() const;

    void setVerticalArrowsMoveFocus(const bool verticalArrowsMoveFocus);

    void setPropagatesStyle(const bool propagatesStyle);
    void propagateStyleToChild(Widget *child) const;
    StylePointer style() const;

    void setWidgetOvershoot(const SizeOvershoot overshoot);

    void setupPressTimer(QTimer *timer) const;

    void doLayout();

protected slots:
    void scheduleFullRedraw() const;
    void schedulePartialRedraw() const;
    void schedulePreviousPositionRedraw() const;

private:
    bool canRedraw() const;
    void updatePreviousBoundingRect();

    const int _borderWidth = 1;

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
};
}
