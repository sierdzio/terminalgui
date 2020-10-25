#include "tgscrollarea.h"

#include <QRect>

Tg::ScrollArea::ScrollArea(Tg::Widget *parent) : Tg::Widget(parent)
{
    init();
}

Tg::ScrollArea::ScrollArea(Tg::Screen *screen) : Tg::Widget(screen)
{
    init();
}

QString Tg::ScrollArea::drawPixel(const QPoint &pixel) const
{
    QString result;

    if (isBorder(pixel)) {
        return drawBorderPixel(pixel);
    } else {
        const auto children = findChildren<Widget *>();
        if (children.isEmpty() == false) {
            // TODO: sort by Z value...
            QList<WidgetPointer> affectedWidgets;
            for (const WidgetPointer &widget : qAsConst(children)) {
                // Only draw direct children
                if (widget->parentWidget() != this) {
                    continue;
                }

                if (widget->visible() && widget->boundingRectangle().contains(
                            childPixel(widget, pixel)))
                {
                    affectedWidgets.append(widget);
                }
            }

            // TODO: properly handle Z value...
            if (affectedWidgets.isEmpty() == false) {
                WidgetPointer widget = affectedWidgets.last();
                if (widget.isNull() == false) {
                    result.append(widget->drawPixel(childPixel(widget, pixel)));
                    return result;
                }
            }
        }
    }

    // Draw default widget background
    result.append(Terminal::Color::code(Terminal::Color::Predefined::Empty,
                                        backgroundColor()));
    result.append(backgroundCharacter());
    return result;
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
    emit contentsPositionChanged(_contentsPosition);
}

void Tg::ScrollArea::init()
{
    setAcceptsFocus(true);

    Widget::init();

    CHECK(connect(this, &ScrollArea::contentsPositionChanged,
                  this, &ScrollArea::schedulePartialRedraw));
}

void Tg::ScrollArea::consumeKeyboardBuffer(const QString &keyboardBuffer)
{
    if (keyboardBuffer.contains(Terminal::Key::left)) {
        const int currentX = contentsPosition().x();
        const int hiddenLength = std::abs(currentX);
        const int contentsWidth = contentsRectangle().width();
        const int childrenW = childrenWidth();
        if ((hiddenLength + contentsWidth) < childrenW) {
            QPoint pos = contentsPosition();
            pos.setX(currentX - 1);
            setContentsPosition(pos);
        }
    }

    if (keyboardBuffer.contains(Terminal::Key::right)) {
        const int currentX = contentsPosition().x();
        if (currentX < 0) {
            QPoint pos = contentsPosition();
            pos.setX(currentX + 1);
            setContentsPosition(pos);
        }
    }

    if (keyboardBuffer.contains(Terminal::Key::up)) {
        const int currentY = contentsPosition().y();
        const int hiddenLength = std::abs(currentY);
        const int contentsHeight = contentsRectangle().height();
        const int childrenH = childrenHeight();
        if ((hiddenLength + contentsHeight) < childrenH) {
            QPoint pos = contentsPosition();
            pos.setY(currentY - 1);
            setContentsPosition(pos);
        }
    }

    if (keyboardBuffer.contains(Terminal::Key::down)) {
        const int currentY = contentsPosition().y();
        if (currentY < 0) {
            QPoint pos = contentsPosition();
            pos.setY(currentY + 1);
            setContentsPosition(pos);
        }
    }
}

int Tg::ScrollArea::childrenWidth() const
{
    int result = 0;

    // TODO: cache this
    const auto widgets = findChildren<Widget *>();
    for (const Widget *widget : widgets) {
        if (widget) {
            result = std::max(result, widget->boundingRectangle().right());
        }
    }

    return result;
}

int Tg::ScrollArea::childrenHeight() const
{
    int result = 0;

    // TODO: cache this
    const auto widgets = findChildren<Widget *>();
    for (const Widget *widget : widgets) {
        if (widget) {
            result = std::max(result, widget->boundingRectangle().bottom());
        }
    }

    return result;
}

QPoint Tg::ScrollArea::childPixel(Tg::Widget *widget, const QPoint &pixel) const
{
    const int borderWidth = effectiveBorderWidth();
    const QPoint adjustedPixel(pixel - QPoint(borderWidth, borderWidth));
    const QPoint childPos(widget->position());
    const QPoint reversed(contentsPosition() * -1);
    const QPoint result(reversed - childPos + adjustedPixel);
    return result;
}
