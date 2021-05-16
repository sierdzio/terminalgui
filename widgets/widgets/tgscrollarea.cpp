#include "tgscrollarea.h"
#include "tgscrollbar.h"

#include <tgkey.h>

#include <QRect>

Tg::ScrollArea::ScrollArea(Tg::Widget *parent) : Tg::Widget(parent)
{
    ScrollArea::init();
}

Tg::ScrollArea::ScrollArea(Tg::Screen *screen) : Tg::Widget(screen)
{
    ScrollArea::init();
}

QString Tg::ScrollArea::drawPixel(const QPoint &pixel) const
{
    if (isBorder(pixel)) {
        return drawBorderPixel(pixel);
    } else {
        const QRect contents = contentsRectangle();
        const int right = contents.right();
        const int bottom = contents.bottom();
        if (pixel.x() > right || pixel.y() > bottom) {
            return {};
        }

        const bool isCorner = (pixel == contents.bottomRight());
        if (isCorner == false) {
            if (_verticalScrollBar->visible()
                    && _verticalScrollBarPolicy != ScrollBarPolicy::NeverShow
                    && pixel.x() == right) {
                const int borderWidth = effectiveBorderWidth();
                const QPoint adjustedPixel(pixel - QPoint(borderWidth, borderWidth));
                return _verticalScrollBar->drawPixel(adjustedPixel);
            }

            if (_horizontalScrollBar->visible()
                    && _horizontalScrollBarPolicy != ScrollBarPolicy::NeverShow
                    && pixel.y() == bottom) {
                const int borderWidth = effectiveBorderWidth();
                const QPoint adjustedPixel(pixel - QPoint(borderWidth, borderWidth));
                return _horizontalScrollBar->drawPixel(adjustedPixel);
            }
        }

        const auto children = childrenWidgets();
        const WidgetPointer widget = Helpers::topWidget(children, pixel, WidgetType::All);
        if (widget.isNull() == false && widget->visible()) {
            const QPoint childPx(childPixel(pixel));
            const QPoint childPos(widget->position());
            return widget->drawPixel(childPx - childPos);
        }

        const QString result = drawAreaContents(pixel);
        if (result.isEmpty() == false) {
            return result;
        }
    }

    // Draw default widget background
    QString result;
    result.append(Tg::Color::code(Tg::Color::Predefined::Empty,
                                        backgroundColor()));
    result.append(backgroundCharacter());
    return result;
}

QString Tg::ScrollArea::drawAreaContents(const QPoint &pixel) const
{
    Q_UNUSED(pixel);
    return {};
}

QPoint Tg::ScrollArea::contentsPosition() const
{
    return _contentsPosition;
}

void Tg::ScrollArea::setContentsPosition(const QPoint &contentsPosition)
{
    if (_contentsPosition == contentsPosition)
        return;

    _contentsPosition = contentsPosition;
    updateScrollBarPositions();
    emit contentsPositionChanged(_contentsPosition);
}

void Tg::ScrollArea::init()
{
    _verticalScrollBar = new ScrollBar(this);
    _verticalScrollBar->setOrientation(Qt::Orientation::Vertical);
    _verticalScrollBar->setAcceptsFocus(false);

    _horizontalScrollBar = new ScrollBar(this);
    _horizontalScrollBar->setOrientation(Qt::Orientation::Horizontal);
    _horizontalScrollBar->setAcceptsFocus(false);

    setAcceptsFocus(true);

    Widget::init();

    CHECK(connect(this, &ScrollArea::contentsPositionChanged,
                  this, &ScrollArea::schedulePartialRedraw));

    CHECK(connect(this, &ScrollArea::childAdded,
                  this, &ScrollArea::connectChild));
    CHECK(connect(this, &ScrollArea::childAdded,
                  this, &ScrollArea::updateChildrenDimensions));
    CHECK(connect(this, &ScrollArea::childRemoved,
                  this, &ScrollArea::updateChildrenDimensions));

    QTimer::singleShot(1, this, [=](){
        updateChildrenDimensions();
    });
}

bool Tg::ScrollArea::consumeKeyboardBuffer(const QString &keyboardBuffer)
{
    if (keyboardBuffer.contains(Tg::Key::right)) {
        const int currentX = contentsPosition().x();
        const int hiddenLength = std::abs(currentX);
        const int contentsWidth = scrollableArea().width();
        const int childrenW = childrenWidth();
        if ((hiddenLength + contentsWidth) < childrenW) {
            QPoint pos = contentsPosition();
            pos.setX(currentX - 1);
            setContentsPosition(pos);
        }

        return true;
    }

    if (keyboardBuffer.contains(Tg::Key::left)) {
        const int currentX = contentsPosition().x();
        if (currentX < 0) {
            QPoint pos = contentsPosition();
            pos.setX(currentX + 1);
            setContentsPosition(pos);
        }

        return true;
    }

    if (keyboardBuffer.contains(Tg::Key::down)) {
        const int currentY = contentsPosition().y();
        const int hiddenLength = std::abs(currentY);
        const int contentsHeight = scrollableArea().height();
        const int childrenH = childrenHeight();
        if ((hiddenLength + contentsHeight) < childrenH) {
            QPoint pos = contentsPosition();
            pos.setY(currentY - 1);
            setContentsPosition(pos);
        }

        return true;
    }

    if (keyboardBuffer.contains(Tg::Key::up)) {
        const int currentY = contentsPosition().y();
        if (currentY < 0) {
            QPoint pos = contentsPosition();
            pos.setY(currentY + 1);
            setContentsPosition(pos);
        }

        return true;
    }

    return false;
}

void Tg::ScrollArea::updateChildrenDimensions()
{
    const int oldWidth = _childrenWidth;
    const int oldHeight = _childrenHeight;

    _childrenWidth = 0;
    _childrenHeight = 0;

    const auto widgets = findChildren<Widget *>();
    for (const Widget *widget : widgets) {
        if (widget == _verticalScrollBar || widget == _horizontalScrollBar) {
            continue;
        }

        if (widget) {
            const QRect rect = widget->boundingRectangle();
            _childrenWidth = std::max(_childrenWidth, rect.x() + rect.width());
            _childrenHeight = std::max(_childrenHeight, rect.y() + rect.height());
        }
    }

    if (oldWidth != _childrenWidth || oldHeight != _childrenHeight) {
        updateScrollBarStates();
        schedulePartialRedraw();
    }
}

void Tg::ScrollArea::connectChild(Tg::Widget *child)
{
    CHECK(connect(child, &Widget::positionChanged,
                  this, &ScrollArea::updateChildrenDimensions));
    CHECK(connect(child, &Widget::sizeChanged,
                  this, &ScrollArea::updateChildrenDimensions));
}

QPoint Tg::ScrollArea::childPixel(const QPoint &pixel) const
{
    const int borderWidth = effectiveBorderWidth();
    const QPoint adjustedPixel(pixel - QPoint(borderWidth, borderWidth));
    const QPoint reversed(contentsPosition() * -1);
    const QPoint result(reversed + adjustedPixel);
    return result;
}

int Tg::ScrollArea::childrenWidth() const
{
    return _childrenWidth;
}

int Tg::ScrollArea::childrenHeight() const
{
    return _childrenHeight;
}

QRect Tg::ScrollArea::scrollableArea() const
{
    QRect result = contentsRectangle();
    if (_horizontalScrollBar->visible() && _horizontalScrollBarPolicy != ScrollBarPolicy::NeverShow) {
        result.setHeight(result.height() - _horizontalScrollBar->size().height());
    }

    if (_verticalScrollBar->visible() && _verticalScrollBarPolicy != ScrollBarPolicy::NeverShow) {
        result.setWidth(result.width() - _verticalScrollBar->size().width());
    }

    return result;
}

void Tg::ScrollArea::updateScrollBarStates()
{
    const QSignalBlocker vBlock(_verticalScrollBar);
    const QSignalBlocker hBlock(_horizontalScrollBar);

    if (_verticalScrollBarPolicy == ScrollBarPolicy::NeverShow
            && _horizontalScrollBarPolicy == ScrollBarPolicy::NeverShow) {
        _verticalScrollBar->setVisible(false);
        _horizontalScrollBar->setVisible(false);
        return;
    }

    _verticalScrollBar->setVisible(true);
    _horizontalScrollBar->setVisible(true);

    const QRect contents = contentsRectangle();
    _verticalScrollBar->setPosition(QPoint(contents.right(), 0));
    _verticalScrollBar->setSize(QSize(1, contents.height()));

    _horizontalScrollBar->setPosition(QPoint(0, contents.bottom()));
    _horizontalScrollBar->setSize(QSize(contents.width(), 1));

    if (_verticalScrollBarPolicy == ScrollBarPolicy::AlwaysShow) {
        _verticalScrollBar->setVisible(true);
    }

    if (_horizontalScrollBarPolicy == ScrollBarPolicy::AlwaysShow) {
        _horizontalScrollBar->setVisible(true);
    }

    if (_horizontalScrollBarPolicy == ScrollBarPolicy::NeverShow) {
            _horizontalScrollBar->setVisible(false);
    } else if (childrenWidth() >= (contents.width() - 1)
            && _horizontalScrollBarPolicy != ScrollBarPolicy::NeverShow) {
        _horizontalScrollBar->setVisible(true);
    }

    if (_verticalScrollBarPolicy == ScrollBarPolicy::NeverShow) {
             _verticalScrollBar->setVisible(false);
    } else if (childrenHeight() >= (contents.height() - 1)
            && _verticalScrollBarPolicy != ScrollBarPolicy::NeverShow) {
        _verticalScrollBar->setVisible(true);
    }

    const QRect scrollable = scrollableArea();

    if (_horizontalScrollBar->visible()) {
        _horizontalScrollBar->setMinimum(0);
        _horizontalScrollBar->setMaximum(childrenWidth() - scrollable.width());
    }

    if (_verticalScrollBar->visible()) {
        _verticalScrollBar->setMinimum(0);
        _verticalScrollBar->setMaximum(childrenHeight() - scrollable.height());
    }

    updateScrollBarPositions();
}

void Tg::ScrollArea::updateScrollBarPositions()
{
    _horizontalScrollBar->setSliderPosition(std::abs(contentsPosition().x()));
    _verticalScrollBar->setSliderPosition(std::abs(contentsPosition().y()));
}

Tg::ScrollArea::ScrollBarPolicy Tg::ScrollArea::horizontalScrollBarPolicy() const
{
    return _horizontalScrollBarPolicy;
}

void Tg::ScrollArea::setHorizontalScrollBarPolicy(const ScrollBarPolicy newHorizontalScrollBarPolicy)
{
    if (_horizontalScrollBarPolicy == newHorizontalScrollBarPolicy) {
        return;
    }

    _horizontalScrollBarPolicy = newHorizontalScrollBarPolicy;
    emit horizontalScrollBarPolicyChanged(newHorizontalScrollBarPolicy);
    updateScrollBarStates();
    schedulePartialRedraw();
}

Tg::ScrollArea::ScrollBarPolicy Tg::ScrollArea::verticalScrollBarPolicy() const
{
    return _verticalScrollBarPolicy;
}

void Tg::ScrollArea::setVerticalScrollBarPolicy(const ScrollBarPolicy newVerticalScrollBarPolicy)
{
    if (_verticalScrollBarPolicy == newVerticalScrollBarPolicy) {
        return;
    }

    _verticalScrollBarPolicy = newVerticalScrollBarPolicy;
    emit verticalScrollBarPolicyChanged(newVerticalScrollBarPolicy);
    updateScrollBarStates();
    schedulePartialRedraw();
}
