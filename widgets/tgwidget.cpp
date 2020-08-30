#include "tgwidget.h"
#include "tgscreen.h"
#include "tgstyle.h"

#include <QRect>
#include <QDebug>

Tg::Widget::Widget(Widget *parent)
    : QObject(parent),
      _screen(parent->screen()),
      _parentWidget(parent)
{
    // TODO: when parenting under a Widget, make sure position() and size()
    // are adjusted to fit the parent. And that the two will now move together

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
        return _style->backgroundColor;
    } else {
        return _backgroundColor;
    }
}

Terminal::Color4Bit Tg::Widget::textColor() const
{
    if (isColorEmpty(_textColor)) {
        return _style->textColor;
    } else {
        return _textColor;
    }
}

Terminal::Color4Bit Tg::Widget::borderTextColor() const
{
    if (isColorEmpty(_borderTextColor)) {
        return _style->borderTextColor;
    } else {
        return _borderTextColor;
    }
}

Terminal::Color4Bit Tg::Widget::borderBackgroundColor() const
{
    if (isColorEmpty(_borderBackgroundColor)) {
        return _style->borderBackgroundColor;
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
                                      Terminal::Color4Bit::Empty));

    const QRect rect(QPoint(0, 0), size());
    // https://en.wikipedia.org/wiki/Geometric_Shapes
    // TODO: allow full customization of border styles!
    if (pixel == rect.topLeft()) {
        result.append("\u25E2");
    } else if (pixel == rect.topRight()) {
        result.append("\u25E3");
    } else if (pixel == rect.bottomLeft()) {
        result.append("\u25E5");
    } else if (pixel == rect.bottomRight()) {
        result.append("\u25E4");
    } else if (pixel.y() == rect.top() or pixel.y() == rect.bottom()) {
        result.append("\u25AA");
    } else if (pixel.x() == rect.left() or pixel.x() == rect.right()) {
        result.append("\u25AA");
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
    if (pixel.x() == rect.left() or pixel.x() == rect.right()) {
        return true;
    }

    if (pixel.y() == rect.top() or pixel.y() == rect.bottom()) {
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
    _style = style;
    setPropagatesStyle(propagate);

    if (propagate) {
        const auto children = findChildren<Tg::Widget*>();
        for (const Tg::Widget *child : children) {
            if (child) {
                setStyle(style, true);
            }
        }
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

void Tg::Widget::setBorderBackgroundColor(const Terminal::Color4Bit borderBackgroundColor)
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

    if (_screen) {
        CHECK(connect(this, &Widget::needsRedraw,
                      _screen, &Screen::onNeedsRedraw));
        _screen->registerWidget(this);
    } else {
        qCritical() << "Screen is missing, can't draw the widget!" << this;
    }

    if (_parentWidget) {
        setBorderVisible(false);
        setBackgroundColor(Terminal::Color4Bit::Black);
    }
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
