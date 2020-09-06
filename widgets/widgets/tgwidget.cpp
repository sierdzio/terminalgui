#include "tgwidget.h"
#include "tgscreen.h"
#include "layouts/tgchildfillsparentlayout.h"
#include "layouts/tgcolumnlayout.h"
#include "layouts/tgrowlayout.h"
#include "layouts/tggridlayout.h"

#include <QRect>
#include <QDebug>

Tg::Widget::Widget(Widget *parent)
    : QObject(parent),
      _screen(parent->screen()),
      _parentWidget(parent)
{
    init();
}

Tg::Widget::Widget(Tg::Screen *parentScreen)
    : QObject(parentScreen),
      _screen(parentScreen),
      _parentWidget(nullptr)
{
    init();
}

Tg::Widget::~Widget()
{
    if (_screen) {
        _screen->deregisterWidget(this);
    }
}

QPoint Tg::Widget::position() const
{
    return _position;
}

QSize Tg::Widget::size() const
{
    return _size;
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

Terminal::Color4Bit Tg::Widget::backgroundColor() const
{
    if (isColorEmpty(_backgroundColor)) {
        return style()->backgroundColor;
    } else {
        return _backgroundColor;
    }
}

Terminal::Color4Bit Tg::Widget::textColor() const
{
    if (isColorEmpty(_textColor)) {
        return style()->textColor;
    } else {
        return _textColor;
    }
}

Terminal::Color4Bit Tg::Widget::borderTextColor() const
{
    if (isColorEmpty(_borderTextColor)) {
        return style()->border->textColor;
    } else {
        return _borderTextColor;
    }
}

Terminal::Color4Bit Tg::Widget::borderBackgroundColor() const
{
    if (isColorEmpty(_borderBackgroundColor)) {
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

void Tg::Widget::setAcceptsFocus(const bool acceptsFocus)
{
    if (_acceptsFocus != acceptsFocus) {
        _acceptsFocus = acceptsFocus;
        emit acceptsFocusChanged(acceptsFocus);
    }
}

void Tg::Widget::setHasFocus(const bool hasFocus)
{
    if (_hasFocus != hasFocus) {
        _hasFocus = hasFocus;
        emit hasFocusChanged(hasFocus);
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

std::string Tg::Widget::drawBorderPixel(const QPoint &pixel) const
{
    std::string result;

    result.append(Terminal::colorCode(borderTextColor(),
                                      borderBackgroundColor()));

    const QRect rect(QPoint(0, 0), size());
    // https://en.wikipedia.org/wiki/Geometric_Shapes
    // TODO: allow full customization of border styles!
    if (pixel == rect.topLeft()) {
        result.append(style()->border->topLeft);
    } else if (pixel == rect.topRight()) {
        result.append(style()->border->topRight);
    } else if (pixel == rect.bottomLeft()) {
        result.append(style()->border->bottomLeft);
    } else if (pixel == rect.bottomRight()) {
        result.append(style()->border->bottomRight);
    } else if (pixel.y() == rect.top() || pixel.y() == rect.bottom()) {
        result.append(style()->border->horizontal);
    } else if (pixel.x() == rect.left() || pixel.x() == rect.right()) {
        result.append(style()->border->vertical);
    } else {
        result.push_back('x');
    }

    return result;
}

std::string Tg::Widget::drawPixel(const QPoint &pixel) const
{
    std::string result;
    if (isBorder(pixel)) {
        return drawBorderPixel(pixel);
    } else {
        result.append(Terminal::colorCode(Terminal::Color4Bit::Empty,
                                          backgroundColor()));
    }
    result.push_back(' ');
    return result;
}

bool Tg::Widget::isBorder(const QPoint &pixel) const
{
    if (borderVisible() == false) {
        return false;
    }

    const QRect rect(QPoint(0, 0), size());
    if (pixel.x() == rect.left() || pixel.x() == rect.right()) {
        return true;
    }

    if (pixel.y() == rect.top() || pixel.y() == rect.bottom()) {
        return true;
    }

    return false;
}

bool Tg::Widget::verticalArrowsMoveFocus() const
{
    return _verticalArrowsMoveFocus;
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
    return _layout->type;
}

void Tg::Widget::setLayoutType(const Tg::Layout::Type type)
{
    if (_layout) {
        if (_layout->type == type) {
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
    case Layout::Type::Column:
        _layout = new ColumnLayout;
        break;
    case Layout::Type::Row:
        _layout = new RowLayout;
        break;
    case Layout::Type::Grid:
        _layout = new GridLayout;
        break;
    }

    _layout->parent = this;
    _layout->doLayout();
}

void Tg::Widget::doLayout()
{
    if (_layout) {
        _layout->doLayout();
    }
}

void Tg::Widget::setPosition(const QPoint &position)
{
    if (_position == position)
        return;

    if (parentWidget() == nullptr) {
        if (position.x() == 0) {
            qWarning() << "Minimal x coordinate on terminal is 1, not 0";
        }

        if (position.y() == 0) {
            qWarning() << "Minimal y coordinate on terminal is 1, not 0";
        }
    }

    _position = position;
    emit positionChanged(_position);
}

void Tg::Widget::setSize(const QSize &size)
{
    if (_size == size)
        return;

    _size = size;
    emit sizeChanged(_size);

    if (_layout) {
        _layout->doLayout();
    }
}

void Tg::Widget::setBackgroundColor(const Terminal::Color4Bit backgroundColor)
{
    if (_backgroundColor == backgroundColor)
        return;

    _backgroundColor = backgroundColor;
    emit backgroundColorChanged(_backgroundColor);
}

void Tg::Widget::setTextColor(const Terminal::Color4Bit textColor)
{
    if (_textColor == textColor)
        return;

    _textColor = textColor;
    emit textColorChanged(_textColor);
}

void Tg::Widget::setBorderTextColor(Terminal::Color4Bit borderColor)
{
    if (_borderTextColor == borderColor)
        return;

    _borderTextColor = borderColor;
    emit borderTextColorChanged(_borderTextColor);
}

void Tg::Widget::setBorderBackgroundColor(
        const Terminal::Color4Bit borderBackgroundColor)
{
    if (_borderBackgroundColor == borderBackgroundColor)
        return;

    _borderBackgroundColor = borderBackgroundColor;
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
}

void Tg::Widget::show()
{
    setVisible(true);
}

void Tg::Widget::hide()
{
    setVisible(false);
}

void Tg::Widget::setBorderVisible(const bool borderVisible)
{
    if (_borderVisible == borderVisible)
        return;

    _borderVisible = borderVisible;
    emit borderVisibleChanged(_borderVisible);
}

int Tg::Widget::effectiveBorderWidth() const
{
    if (borderVisible()) {
        return _borderWidth;
    }

    return 0;
}

bool Tg::Widget::isColorEmpty(const Terminal::Color4Bit color) const
{
    return color == Terminal::Color4Bit::Empty;
}

void Tg::Widget::init()
{
    CHECK(connect(this, &Widget::positionChanged,
                  this, &Widget::scheduleRedraw));
    CHECK(connect(this, &Widget::sizeChanged,
                  this, &Widget::scheduleRedraw));
    CHECK(connect(this, &Widget::backgroundColorChanged,
                  this, &Widget::scheduleRedraw));
    CHECK(connect(this, &Widget::textColorChanged,
                  this, &Widget::scheduleRedraw));
    CHECK(connect(this, &Widget::borderTextColorChanged,
                  this, &Widget::scheduleRedraw));
    CHECK(connect(this, &Widget::visibleChanged,
                  this, &Widget::scheduleRedraw));
    CHECK(connect(this, &Widget::borderVisibleChanged,
                  this, &Widget::scheduleRedraw));
    CHECK(connect(this, &Widget::hasFocusChanged,
                  this, &Widget::scheduleRedraw));
    CHECK(connect(this, &Widget::styleChanged,
                  this, &Widget::scheduleRedraw));

    if (_screen) {
        CHECK(connect(this, &Widget::needsRedraw,
                      _screen, &Screen::onNeedsRedraw));
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
    }

    setLayoutType(Layout::Type::None);
}

void Tg::Widget::consumeKeyboardBuffer(const QString &keyboardBuffer)
{
    Q_UNUSED(keyboardBuffer)
}

void Tg::Widget::setVerticalArrowsMoveFocus(const bool verticalArrowsMoveFocus)
{
    _verticalArrowsMoveFocus = verticalArrowsMoveFocus;
}

void Tg::Widget::setPropagatesStyle(const bool propagatesStyle)
{
    if (propagatesStyle != _propagatesStyle) {
        _propagatesStyle = propagatesStyle;
        emit propagatesStyleChanged(propagatesStyle);
    }
}

void Tg::Widget::propagateStyleToChild(Tg::Widget *child) const
{
    if (child) {
        child->setStyle(style(), true);
    }
}

Tg::StylePointer Tg::Widget::style() const
{
    return _style;
}

void Tg::Widget::scheduleRedraw() const
{
    if (visible() == true) {
        emit needsRedraw();
    }
}
