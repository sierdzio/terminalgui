#include "tgscreen.h"
#include "tgwidget.h"
#include "textstream.h"
#include "tghelpers.h"

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

    _keyboardTimer.setInterval(200);
    _keyboardTimer.setSingleShot(false);

    CHECK(connect(&_keyboardTimer, &QTimer::timeout,
                  this, &Screen::checkKeyboard));

    _redrawTimer.setInterval(60);
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

void Tg::Screen::onNeedsRedraw()
{
    compressRedraws();
}

void Tg::Screen::moveFocusToPreviousWidget()
{
    QVectorIterator<WidgetPointer> iterator(_widgets);
    const bool result = iterator.findNext(_activeFocusWidget);
    if (result == false) {
        _activeFocusWidget->setHasFocus(false);
        _activeFocusWidget = nullptr;
        return;
    }

    // Search from current focus widget backward
    while (iterator.hasPrevious()) {
        const WidgetPointer widget = iterator.previous();
        if (widget != _activeFocusWidget and widget->acceptsFocus()) {
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
    QVectorIterator<WidgetPointer> iterator(_widgets);
    const bool result = iterator.findNext(_activeFocusWidget);
    if (result == false) {
        _activeFocusWidget->setHasFocus(false);
        _activeFocusWidget = nullptr;
        return;
    }

    // Search from current focus widget forward
    while (iterator.hasNext()) {
        const WidgetPointer widget = iterator.next();
        if (widget != _activeFocusWidget and widget->acceptsFocus()) {
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

void Tg::Screen::redrawImmediately() const
{
    Tg::TextStream stream(stdout);
    // TODO: do not clear everything. Make only partial redraws!
    stream << Terminal::Command::clear;

    for (int y = 1; y < size().width(); ++y) {
        for (int x = 1; x < size().width(); ++x) {
            const QPoint pixel(x, y);

            bool drawn = false;
            // TODO: sort by Z value...
            // TODO: "bundle" pixels from same widget to prevent
            // multiple loop passes for the same widget
            for (const Widget *widget : qAsConst(_widgets)) {
                if (widget->visible() && widget->globalBoundingRectangle().contains(pixel))
                {
                    const QPoint localPixel(widget->mapFromGlobal(pixel));
                    stream << Terminal::Command::moveToPosition(x, y);
                    stream << widget->drawPixel(localPixel);
                    drawn = true;
                    continue;
                }
            }

            if (drawn == false) {
                stream << Terminal::colorEnd();
            }
        }
    }
}

void Tg::Screen::checkKeyboard()
{
    const int bufferSize = Terminal::keyboardBufferSize();
    if (bufferSize > 0 && _activeFocusWidget) {
        QString characters;
        for (int i = 0; i < bufferSize; ++i) {
            characters.append(getchar());
        }

        if (const QString command(Helpers::toString(Terminal::Key::tab));
            characters.contains(command)) {
            // Move to next input
            moveFocusToNextWidget();
            characters.remove(command);
        }

        if (_activeFocusWidget->verticalArrowsMoveFocus()) {
            // Up Arrow
            if (const QString command(Helpers::toString(Terminal::Key::up));
                characters.contains(command)) {
                moveFocusToPreviousWidget();
                characters.remove(command);
            }

            // Down Arrow
            if (const QString command(Helpers::toString(Terminal::Key::down));
                characters.contains(command)) {
                moveFocusToNextWidget();
                characters.remove(command);
            }
        }

        _activeFocusWidget->consumeKeyboardBuffer(characters);
    }
}

void Tg::Screen::compressRedraws()
{
    if (_redrawTimer.isActive() == false) {
        _redrawTimer.start();
    }
}
