#include "tgscreen.h"
#include "widgets/tgwidget.h"

#include <backend/backend.h>

#include <QPoint>
#include <QRect>
#include <QDebug>

Tg::Screen::Screen(QObject *parent) : QObject(parent)
{
    _style = StylePointer::create();

    const Terminal::Size size = Terminal::updateSize();
    _size.setWidth(size.width);
    _size.setHeight(size.height);
    emit sizeChanged(_size);

    //qDebug() << "TgScreen info:" << _size.width() << _size.height();

    _keyboardTimer.setInterval(100);
    _keyboardTimer.setSingleShot(false);

    CHECK(connect(&_keyboardTimer, &QTimer::timeout,
                  this, &Screen::checkKeyboard));

    _redrawTimer.setInterval(32);
    _redrawTimer.setSingleShot(true);

    CHECK(connect(&_redrawTimer, &QTimer::timeout,
                  this, &Screen::redrawImmediately));
}

Tg::Screen::~Screen()
{
}

QSize Tg::Screen::size() const
{
    return _size;
}

void Tg::Screen::registerWidget(Tg::Widget *widget)
{
    _widgets.append(widget);
    widget->setStyle(_style, true);

    CHECK(connect(widget, &Widget::moveFocusToPreviousWidget,
                  this, &Screen::moveFocusToPreviousWidget));
    CHECK(connect(widget, &Widget::moveFocusToNextWidget,
                  this, &Screen::moveFocusToNextWidget));

    if (widget->acceptsFocus() && _activeFocusWidget.isNull()) {
        _activeFocusWidget = widget;
        widget->setHasFocus(true);

        if (_keyboardTimer.isActive() == false) {
            _keyboardTimer.start();
        }
    }
}

void Tg::Screen::deregisterWidget(Tg::Widget *widget)
{
    _widgets.removeOne(widget);
}

Tg::StylePointer Tg::Screen::style() const
{
    return _style;
}

void Tg::Screen::onNeedsRedraw(const RedrawType type, const Widget *widget)
{
    updateRedrawRegions(type, widget);
    compressRedraws();
}

void Tg::Screen::moveFocusToPreviousWidget()
{
    QListIterator<WidgetPointer> iterator(_widgets);
    const bool result = iterator.findNext(_activeFocusWidget);
    if (result == false) {
        _activeFocusWidget->setHasFocus(false);
        _activeFocusWidget = nullptr;
        return;
    }

    // Search from current focus widget backward
    while (iterator.hasPrevious()) {
        const WidgetPointer widget = iterator.previous();
        if (widget != _activeFocusWidget && widget->acceptsFocus()) {
            _activeFocusWidget->setHasFocus(false);
            _activeFocusWidget = widget;
            _activeFocusWidget->setHasFocus(true);
            return;
        }
    }

    // Search from back up to current focus widget
    iterator.toBack();

    while (iterator.hasPrevious()) {
        const WidgetPointer widget = iterator.previous();
        if (widget == _activeFocusWidget) {
            return;
        } else if (widget->acceptsFocus()) {
            _activeFocusWidget->setHasFocus(false);
            _activeFocusWidget = widget;
            _activeFocusWidget->setHasFocus(true);
            return;
        }
    }
}

void Tg::Screen::moveFocusToNextWidget()
{
    QListIterator<WidgetPointer> iterator(_widgets);
    const bool result = iterator.findNext(_activeFocusWidget);
    if (result == false) {
        _activeFocusWidget->setHasFocus(false);
        _activeFocusWidget = nullptr;
        return;
    }

    // Search from current focus widget forward
    while (iterator.hasNext()) {
        const WidgetPointer widget = iterator.next();
        if (widget != _activeFocusWidget && widget->acceptsFocus()) {
            _activeFocusWidget->setHasFocus(false);
            _activeFocusWidget = widget;
            _activeFocusWidget->setHasFocus(true);
            return;
        }
    }

    // Search from root up to current focus widget
    iterator.toFront();

    while (iterator.hasNext()) {
        const WidgetPointer widget = iterator.next();
        if (widget == _activeFocusWidget) {
            return;
        } else if (widget->acceptsFocus()) {
            _activeFocusWidget->setHasFocus(false);
            _activeFocusWidget = widget;
            _activeFocusWidget->setHasFocus(true);
            return;
        }
    }
}

void Tg::Screen::redrawImmediately()
{
    QTextStream stream(stdout);

    QVector<QPoint> points;
    for (const QRect &region : qAsConst(_redrawRegions)) {
        for (int y = region.y(); y < (region.y() + region.height()); ++y) {
            for (int x = region.x(); x < (region.x() + region.width()); ++x) {
                const QPoint pixel(x, y);

                if (points.contains(pixel)) {
                    continue;
                }

                bool drawn = false;
                // TODO: sort by Z value...
                QList<WidgetPointer> affectedWidgets;
                for (const WidgetPointer &widget : qAsConst(_widgets)) {
                    if (widget->visible() && widget->clipped() == false
                            && widget->globalBoundingRectangle().contains(pixel))
                    {
                        affectedWidgets.append(widget);
                    }
                }

                // TODO: properly handle Z value...
                if (affectedWidgets.isEmpty() == false) {
                    WidgetPointer widget = affectedWidgets.last();
                    if (widget.isNull() == false) {
                        const QPoint localPixel(widget->mapFromGlobal(pixel));
                        // TODO: consider using Terminal::currentPosition() to
                        // prevent move operation if it's not needed. This could
                        // speed things up (or slow them down...)
                        stream << Terminal::Command::moveToPosition(x, y);
                        stream << widget->drawPixel(localPixel);
                        drawn = true;
                    }
                }

                if (drawn == false) {
                    stream << Terminal::colorEnd();
                } else {
                    points.append(pixel);
                }
            }
        }
    }

    _redrawRegions.clear();
}

void Tg::Screen::checkKeyboard()
{
    const int bufferSize = Terminal::keyboardBufferSize();
    if (bufferSize > 0 && _activeFocusWidget) {
        QString characters;
        for (int i = 0; i < bufferSize; ++i) {
            characters.append(Terminal::getChar());
        }

        if (const QString command(Terminal::Key::tab);
            characters.contains(command)) {
            // Move to next input
            moveFocusToNextWidget();
            characters.remove(command);
        }

        if (_activeFocusWidget->verticalArrowsMoveFocus()) {
            // Up Arrow
            if (const QString command(Terminal::Key::up);
                characters.contains(command)) {
                moveFocusToPreviousWidget();
                characters.remove(command);
            }

            // Down Arrow
            if (const QString command(Terminal::Key::down);
                characters.contains(command)) {
                moveFocusToNextWidget();
                characters.remove(command);
            }
        }

        _activeFocusWidget->consumeKeyboardBuffer(characters);
    }
}

void Tg::Screen::updateRedrawRegions(const Tg::RedrawType type,
                                     const Tg::Widget *widget)
{
     if (type == RedrawType::Full) {
         //const Terminal::Size size = Terminal::updateSize();
         //_size.setWidth(size.width);
         //_size.setHeight(size.height);
         //emit sizeChanged(_size);
         _redrawRegions.clear();
         const QRect region(QPoint(0, 0), size());
         _redrawRegions.append(region);
     } else {
         bool update = true;
         const QRect region(widget->globalBoundingRectangle());
         const auto originalRegions = _redrawRegions;
         for (const QRect &current : originalRegions) {
             if (current.contains(region, true)) {
                 update = false;
                 break;
             }

             // TODO: add more fine-grained control and optimisation of
             // intersecting draw regions
         }

         if (update) {
             _redrawRegions.append(region);
         }
     }
}

void Tg::Screen::compressRedraws()
{
    if (_redrawTimer.isActive() == false) {
        _redrawTimer.start();
    }
}
