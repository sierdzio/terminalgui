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
            const QPoint contentsPixel(pixel - contentsPosition());

            // TODO: sort by Z value...
            QList<WidgetPointer> affectedWidgets;
            for (const WidgetPointer &widget : qAsConst(children)) {
                // Only draw direct children
                if (widget->parentWidget() != this) {
                    continue;
                }

                if (widget->visible() /*&& widget->clipped() == false*/
                        && widget->boundingRectangle().contains(contentsPixel))
                {
                    affectedWidgets.append(widget);
                }
            }

            // TODO: properly handle Z value...
            if (affectedWidgets.isEmpty() == false) {
                WidgetPointer widget = affectedWidgets.last();
                if (widget.isNull() == false) {
                    const QPoint childPixel(mapToChild(widget, pixel));
                    result.append(widget->drawPixel(childPixel));
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
    return contentsRectangle().topLeft();
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
        if (currentX > 0) {
            QPoint pos = contentsPosition();
            pos.setX(currentX - 1);
            setContentsPosition(pos);
        }
    }

    if (keyboardBuffer.contains(Terminal::Key::right)) {
        const int currentX = contentsPosition().x();
        const int visibleContents = contentsRectangle().width() - currentX;
        if (visibleContents > size().width()) {
            QPoint pos = contentsPosition();
            pos.setX(currentX + 1);
            setContentsPosition(pos);
        }
    }

    if (keyboardBuffer.contains(Terminal::Key::up)) {
        const int currentY = contentsPosition().y();
        if (currentY > 0) {
            QPoint pos = contentsPosition();
            pos.setY(currentY - 1);
            setContentsPosition(pos);
        }
    }

    if (keyboardBuffer.contains(Terminal::Key::down)) {
        const int currentY = contentsPosition().y();
        const int visibleContents = contentsRectangle().height() - currentY;
        if (visibleContents > size().height()) {
            QPoint pos = contentsPosition();
            pos.setY(currentY + 1);
            setContentsPosition(pos);
        }
    }
}
