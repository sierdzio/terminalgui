#include "tgwidget.h"
#include "tgscreen.h"
#include "layouts/tgchildfillsparentlayout.h"
#include "layouts/tgcolumnlayout.h"
#include "layouts/tgrowlayout.h"
#include "layouts/tggridlayout.h"
#include "styles/tgstyle.h"

#include <QRect>
#include <QDebug>

Tg::Widget::Widget(Widget *parent)
    : QObject(parent),
      _screen(parent->screen()),
      _parentWidget(parent)
{
    Widget::init();
}

Tg::Widget::Widget(Tg::Screen *screen)
    : QObject(screen),
      _screen(screen),
      _parentWidget(nullptr)
{
    Widget::init();
}

Tg::Widget::~Widget()
{
    if (_screen) {
        if (hasFocus()) {
            blockSignals(true);
            _screen->moveFocusToPreviousWidget();
            blockSignals(false);
        }
        _screen->deregisterWidget(this);
        _screen->deregisterCurrentModalWidget(this);
    }
}

QPoint Tg::Widget::position() const
{
    return _position;
}

QPoint Tg::Widget::previousGlobalPosition() const
{
    return _previousGlobalPosition;
}

QSize Tg::Widget::size() const
{
    return _size;
}

QSize Tg::Widget::previousSize() const
{
    return _previousSize;
}

QRect Tg::Widget::boundingRectangle() const
{
    return QRect(position(), size());
}

QRect Tg::Widget::globalBoundingRectangle() const
{
    if (parentWidget()) {
        const int border = parentWidget()->effectiveBorderWidth();
        return QRect(mapToGlobal(QPoint(border, border)), size());
    } else {
        return QRect(mapToGlobal(QPoint(0, 0)), size());
    }
}

QRect Tg::Widget::globalPreviousBoundingRectangle() const
{
    if (parentWidget()) {
        const int border = parentWidget()->effectiveBorderWidth();
        return QRect(previousGlobalPosition() + QPoint(border, border),
                     previousSize());
    } else {
        return QRect(previousGlobalPosition(), previousSize());
    }
}

QRect Tg::Widget::contentsRectangle() const
{
    const int borderWidth = effectiveBorderWidth();
    const QPoint pos(borderWidth, borderWidth);

    QSize siz = size();
    const int twiceBorderWidth = 2 * borderWidth;
    siz.setWidth(siz.width() - twiceBorderWidth);
    siz.setHeight(siz.height() - twiceBorderWidth);
    return QRect(pos, siz);
}

Tg::Color Tg::Widget::backgroundColor() const
{
    if (_backgroundColor.isEmpty()) {
        return style()->backgroundColor;
    } else {
        return _backgroundColor;
    }
}

QByteArray Tg::Widget::backgroundCharacter() const
{
    if (_backgroundCharacter.isNull()) {
        return style()->backgroundCharacter;
    } else {
        return _backgroundCharacter;
    }
}

Tg::Color Tg::Widget::textColor() const
{
    if (_textColor.isEmpty()) {
        return style()->textColor;
    } else {
        return _textColor;
    }
}

QString Tg::Widget::title() const
{
    return _title;
}

Tg::Color Tg::Widget::borderTextColor() const
{
    if (_borderTextColor.isEmpty()) {
        return style()->border->textColor;
    } else {
        return _borderTextColor;
    }
}

Tg::Color Tg::Widget::borderBackgroundColor() const
{
    if (_borderBackgroundColor.isEmpty()) {
        return style()->border->backgroundColor;
    } else {
        return _borderBackgroundColor;
    }
}

bool Tg::Widget::visible() const
{
    return _visible;
}

bool Tg::Widget::borderVisible() const
{
    return _borderVisible;
}

bool Tg::Widget::acceptsFocus() const
{
    return _acceptsFocus;
}

bool Tg::Widget::hasFocus() const
{
    return _hasFocus;
}

void Tg::Widget::setActiveFocus()
{
    if (acceptsFocus() && hasFocus() == false) {
        screen()->setActiveFocusWidget(this);
    }
}

void Tg::Widget::setAcceptsFocus(const bool accept)
{
    if (_acceptsFocus != accept) {
        _acceptsFocus = accept;
        emit acceptsFocusChanged(accept);
    }
}

void Tg::Widget::setHasFocus(const bool active)
{
    if (_hasFocus != active) {
        _hasFocus = active;
        emit hasFocusChanged(active);
    }
}

Tg::Screen *Tg::Widget::screen() const
{
    return _screen;
}

Tg::Widget *Tg::Widget::parentWidget() const
{
    return _parentWidget;
}

Tg::Widget *Tg::Widget::topLevelParentWidget() const
{
    Widget *current = const_cast<Widget *>(this);
    while (current->isTopLevel() == false) {
        current = current->parentWidget();
    }

    return current;
}

bool Tg::Widget::isTopLevel() const
{
    return _parentWidget.isNull();
}

QString Tg::Widget::drawBorderPixel(const QPoint &pixel) const
{
    QString result;

    const auto color = Tg::Color::code(borderTextColor(), borderBackgroundColor());
    // TODO: add property to make overshoot color customizable
    const auto overshootColor = Tg::Color::code(style()->border->overshootTextColor,
                                                      style()->border->overshootBackgroundColor);

    const QRect rect(QPoint(0, 0), size());
    if (pixel == rect.topLeft()) {
        result.append(color);
        result.append(style()->border->topLeft);
    } else if (pixel == rect.topRight()) {
        result.append(color);
        result.append(style()->border->topRight);
    } else if (pixel == rect.bottomLeft()) {
        result.append(color);
        result.append(style()->border->bottomLeft);
    } else if (pixel == rect.bottomRight()) {
        if (_resizableByMouse) {
            result.append(color);
            result.append(style()->border->resizableCorner);
        } else {
            result.append(color);
            result.append(style()->border->bottomRight);
        }
    } else if (pixel.y() == rect.top()) {
        result.append(color);

        const auto border = style()->border->horizontal;
        if (title().isEmpty()) {
            result.append(border);
        } else {
            const int width = rect.width() - (2 * _borderWidth);
            const int textWidth = title().size();
            const int margin = (width - textWidth) / 2;
            // TODO: handle case where margin < 0
            const int x = pixel.x() - _borderWidth;

            if (x < margin || x >= (margin + textWidth)) {
                result.append(border);
            } else {
                result.append(title().at(x - margin));
            }
        }
    } else if (pixel.y() == rect.bottom()) {
        if (widgetOvershoot().testFlag(Overshoot::Vertical)
                || layoutOvershoot().testFlag(Overshoot::Vertical)) {
            result.append(overshootColor);
            result.append(style()->border->horizontalOvershoot);
        } else {
            result.append(color);
            result.append(style()->border->horizontal);
        }
    } else if (pixel.x() == rect.left()) {
        result.append(color);
        result.append(style()->border->vertical);
    } else if (pixel.x() == rect.right()) {
        if (widgetOvershoot().testFlag(Overshoot::Horizontal)
                || layoutOvershoot().testFlag(Overshoot::Horizontal)) {
            result.append(overshootColor);
            result.append(style()->border->verticalOvershoot);
        } else {
            result.append(color);
            result.append(style()->border->vertical);
        }
    } else {
        result.append(Tg::Key::space);
    }

    return result;
}

QString Tg::Widget::drawPixel(const QPoint &pixel) const
{
    QString result;

    if (isBorder(pixel)) {
        return drawBorderPixel(pixel);
    } else {
        const auto children = childrenWidgets();
        if (children.isEmpty() == false) {
            const QPoint contentsPixel(pixel - contentsRectangle().topLeft());
            const WidgetPointer widget = Helpers::topWidget(children, contentsPixel, WidgetType::All);
            if (widget.isNull() == false) {
                const QPoint childPixel(mapToChild(widget, pixel));
                result.append(widget->drawPixel(childPixel));
                return result;
            }
        }
    }

    // Draw default widget background
    result.append(Tg::Color::code(Tg::Color::Predefined::Empty,
                                        backgroundColor()));
    result.append(backgroundCharacter());
    return result;
}

bool Tg::Widget::isBorder(const QPoint &pixel) const
{
    if (borderVisible() == false) {
        return false;
    }

    const QRect rect(QPoint(0, 0), size());
    if (pixel.x() == rect.left() || (pixel.x() == rect.right())) {
        return true;
    }

    if (pixel.y() == rect.top() || (pixel.y() == rect.bottom())) {
        return true;
    }

    return false;
}

bool Tg::Widget::verticalArrowsMoveFocus() const
{
    return _acceptsFocus == false || (_acceptsFocus && _verticalArrowsMoveFocus);
}

QPoint Tg::Widget::mapFromGlobal(const QPoint &position) const
{
    const QPoint result(position - this->position());

    if (parentWidget()) {
        const int border = parentWidget()->effectiveBorderWidth();
        return parentWidget()->mapFromGlobal(result) -
            QPoint(border, border);
    }

    return result;
}

QPoint Tg::Widget::mapToGlobal(const QPoint &position) const
{
    const QPoint result(position + this->position());

    if (parentWidget()) {
        return parentWidget()->mapToGlobal(result);
    }

    return result;
}

QPoint Tg::Widget::mapToChild(const Tg::WidgetPointer &child,
                              const QPoint &position) const
{
    const QPoint childPos(child->position());
    const QPoint topLeft(contentsRectangle().topLeft());
    const QPoint result(position - childPos - topLeft);
    return result;
}

bool Tg::Widget::propagatesStyle() const
{
    return _propagatesStyle;
}

void Tg::Widget::setStyle(const Tg::StylePointer &style, const bool propagate)
{
    if (style == _style && propagatesStyle() == propagate) {
        return;
    }

    _style = style;
    setPropagatesStyle(propagate);

    if (propagate) {
        for (auto child : children()) {
            auto widget = qobject_cast<Widget*>(child);
            if (widget) {
                propagateStyleToChild(widget);
            }
        }
    }

    emit styleChanged();
}

Tg::Layout::Type Tg::Widget::layoutType() const
{
    return _layout->type();
}

void Tg::Widget::setLayoutType(const Tg::Layout::Type type)
{
    if (_layout) {
        if (_layout->type() == type) {
            return;
        } else {
            delete _layout;
        }
    }

    switch (type) {
    case Layout::Type::None:
        _layout = new Layout;
        break;
    case Layout::Type::ChildFillsParent:
        _layout = new ChildFillsParentLayout;
        break;
    case Layout::Type::Row:
        _layout = new RowLayout;
        break;
    case Layout::Type::Column:
        _layout = new ColumnLayout;
        break;
    case Layout::Type::Grid:
        _layout = new GridLayout;
        break;
    }

    _layout->setParent(this);
    doLayout();
}

void Tg::Widget::doLayout()
{
    if (_layout) {
        _layout->doLayout();

        const auto overshoot = _layout->overshoot();
        if (overshoot != _layoutOvershoot) {
            _layoutOvershoot = overshoot;
            _widgetOvershoot = overshoot;
            emit layoutOvershootChanged(_layoutOvershoot);
            emit widgetOvershootChanged(_widgetOvershoot);
        }
    }
}

Tg::WidgetList Tg::Widget::childrenWidgets() const
{
    WidgetList result;
    for (QObject *child : qAsConst(children())) {
        Widget *childWidget = qobject_cast<Widget *>(child);
        if (childWidget) {
            result.append(WidgetPointer(childWidget));
        }
    }
    return result;
}

Tg::WidgetList Tg::Widget::allFocusableChildrenWidgets() const
{
    WidgetList result;
    for (QObject *child : qAsConst(children())) {
        Widget *childWidget = qobject_cast<Widget *>(child);
        if (childWidget) {
            if (childWidget->acceptsFocus()) {
                result.append(WidgetPointer(childWidget));
            }

            result.append(childWidget->allFocusableChildrenWidgets());
        }
    }
    return result;
}

Tg::SizeOvershoot Tg::Widget::layoutOvershoot() const
{
    return _layoutOvershoot;
}

Tg::SizeOvershoot Tg::Widget::widgetOvershoot() const
{
    return _widgetOvershoot;
}

int Tg::Widget::z() const
{
    return _z;
}

void Tg::Widget::setPosition(const QPoint &position)
{
    if (_position == position)
        return;

    if (isTopLevel()) {
        if (position.x() == 0) {
            qWarning() << "Minimal x coordinate on terminal is 1, not 0";
        }

        if (position.y() == 0) {
            qWarning() << "Minimal y coordinate on terminal is 1, not 0";
        }
    }

    updatePreviousBoundingRect();
    _position = position;
    emit positionChanged(_position);
}

void Tg::Widget::setSize(const QSize &size)
{
    if (_size == size)
        return;

    updatePreviousBoundingRect();
    _size = size;
    emit sizeChanged(_size);

    doLayout();
}

void Tg::Widget::setBackgroundColor(const Tg::Color &color)
{
    if (_backgroundColor == color)
        return;

    _backgroundColor = color;
    emit backgroundColorChanged(_backgroundColor);
}

void Tg::Widget::setBackgroundCharacter(const QByteArray &character)
{
    if (_backgroundCharacter == character)
        return;

    _backgroundCharacter = character;
    emit backgroundCharacterChanged(_backgroundCharacter);
}

void Tg::Widget::setTextColor(const Tg::Color &color)
{
    if (_textColor == color)
        return;

    _textColor = color;
    emit textColorChanged(_textColor);
}

void Tg::Widget::setTitle(const QString &title)
{
    if (_title == title)
        return;

    _title = title;
    emit titleChanged(_title);
}

void Tg::Widget::setBorderTextColor(const Tg::Color &color)
{
    if (_borderTextColor == color)
        return;

    _borderTextColor = color;
    emit borderTextColorChanged(_borderTextColor);
}

void Tg::Widget::setBorderBackgroundColor(const Tg::Color &color)
{
    if (_borderBackgroundColor == color)
        return;

    _borderBackgroundColor = color;
    emit borderBackgroundColorChanged(_borderBackgroundColor);
}

void Tg::Widget::setVisible(const bool visible)
{
    if (_visible == visible)
        return;

    _visible = visible;

    emit visibleChanged(_visible);

    if (visible && parentWidget()) {
        parentWidget()->doLayout();

        if (parentWidget()->propagatesStyle()) {
            parentWidget()->propagateStyleToChild(this);
        }
    }

    for (const auto &child : childrenWidgets()) {
        child->setVisible(visible);
    }
}

void Tg::Widget::show()
{
    setVisible(true);
}

void Tg::Widget::hide()
{
    setVisible(false);
}

void Tg::Widget::setBorderVisible(const bool visible)
{
    if (_borderVisible == visible)
        return;

    _borderVisible = visible;
    emit borderVisibleChanged(_borderVisible);
}

void Tg::Widget::setZ(const int z)
{
    if (_z == z)
        return;

    _z = z;
    emit zChanged(_z);
}

int Tg::Widget::effectiveBorderWidth() const
{
    if (borderVisible()) {
        return _borderWidth;
    }

    return 0;
}

void Tg::Widget::init()
{
    CHECK(connect(this, &Widget::positionChanged,
                  this, &Widget::schedulePreviousPositionRedraw));
    CHECK(connect(this, &Widget::sizeChanged,
                  this, &Widget::schedulePreviousPositionRedraw));

    CHECK(connect(this, &Widget::backgroundColorChanged,
                  this, &Widget::schedulePartialRedraw));
    CHECK(connect(this, &Widget::backgroundCharacterChanged,
                  this, &Widget::schedulePartialRedraw));
    CHECK(connect(this, &Widget::textColorChanged,
                  this, &Widget::schedulePartialRedraw));
    CHECK(connect(this, &Widget::borderTextColorChanged,
                  this, &Widget::schedulePartialRedraw));
    CHECK(connect(this, &Widget::visibleChanged,
                  this, &Widget::schedulePartialRedraw));
    CHECK(connect(this, &Widget::borderVisibleChanged,
                  this, &Widget::schedulePartialRedraw));
    CHECK(connect(this, &Widget::hasFocusChanged,
                  this, &Widget::schedulePartialRedraw));
    CHECK(connect(this, &Widget::styleChanged,
                  this, &Widget::schedulePartialRedraw));
    CHECK(connect(this, &Widget::layoutOvershootChanged,
                  this, &Widget::schedulePartialRedraw));
    CHECK(connect(this, &Widget::widgetOvershootChanged,
                  this, &Widget::schedulePartialRedraw));

    if (_screen) {
        CHECK(connect(this, &Widget::needsRedraw,
                      _screen, &Screen::scheduleRedraw));
        _screen->registerWidget(this);
    } else {
        qCritical() << "Screen is missing, can't draw the widget!" << this;
    }

    if (_parentWidget) {
        setBorderVisible(false);

        _parentWidget->doLayout();
        if (_parentWidget->propagatesStyle()) {
            _parentWidget->propagateStyleToChild(this);
        }

        emit _parentWidget->childAdded(this);

        CHECK(connect(this, &Widget::destroyed,
                      _parentWidget, &Widget::childRemoved));

        setVisible(_parentWidget->visible());
    }

    setLayoutType(Layout::Type::None);
}

bool Tg::Widget::consumeKeyboardBuffer(const QString &keyboardBuffer)
{
    Q_UNUSED(keyboardBuffer)
    return false;
}

void Tg::Widget::setVerticalArrowsMoveFocus(const bool enable)
{
    _verticalArrowsMoveFocus = enable;
}

void Tg::Widget::setPropagatesStyle(const bool propagate)
{
    if (_propagatesStyle != propagate) {
        _propagatesStyle = propagate;
        emit propagatesStyleChanged(propagate);
    }
}

void Tg::Widget::propagateStyleToChild(Widget *child) const
{
    if (child) {
        child->setStyle(style(), true);
    }
}

Tg::StylePointer Tg::Widget::style() const
{
    return _style;
}

void Tg::Widget::setWidgetOvershoot(const SizeOvershoot overshoot)
{
    if (_widgetOvershoot != overshoot) {
        _widgetOvershoot = overshoot;
        emit widgetOvershootChanged(overshoot);
    }
}

void Tg::Widget::setupPressTimer(QTimer *timer) const
{
    timer->setInterval(500);
    timer->setSingleShot(true);
}

void Tg::Widget::scheduleFullRedraw() const
{
    emit needsRedraw(RedrawType::Full, this);
}

void Tg::Widget::schedulePartialRedraw() const
{
    emit needsRedraw(RedrawType::Partial, this);
}

void Tg::Widget::schedulePreviousPositionRedraw() const
{
    emit needsRedraw(RedrawType::PreviousPosition, this);
}

bool Tg::Widget::canRedraw() const
{
    if (visible() == true) {
        return true;
    }

    return false;
}

void Tg::Widget::updatePreviousBoundingRect()
{
    _previousGlobalPosition = _position;
    _previousSize = _size;
}

bool Tg::Widget::isModal() const
{
    return _isModal;
}

void Tg::Widget::setIsModal(const bool newIsModal)
{
    if (_isModal != newIsModal) {
        if (newIsModal) {
            _screen->registerCurrentModalWidget(this);
        } else {
            _screen->deregisterCurrentModalWidget(this);
        }

        _isModal = newIsModal;
        emit isModalChanged(newIsModal);
    }
}
