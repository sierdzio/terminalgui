#include "tgscreen.h"
#include "tgwidget.h"
#include "textstream.h"

#include <backend/backend.h>

#include <QPoint>
#include <QRect>
#include <QDebug>

Tg::Screen::Screen(QObject *parent) : QObject(parent)
{
    const Terminal::Size size = Terminal::updateSize();
    _size.setWidth(size.width);
    _size.setHeight(size.height);
    emit sizeChanged(_size);

    //qDebug() << "TgScreen info:" << _size.width() << _size.height();

    _keyboardTimer.setInterval(1000);
    _keyboardTimer.setSingleShot(false);

    connect(&_keyboardTimer, &QTimer::timeout,
            this, &Screen::checkKeyboard);

    _redrawTimer.setInterval(100);
    _redrawTimer.setSingleShot(true);

    connect(&_redrawTimer, &QTimer::timeout,
            this, &Screen::redrawImmediately);
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

void Tg::Screen::needsRedraw()
{
    compressRedraws();
}

void Tg::Screen::redrawImmediately() const
{
    Tg::TextStream stream(stdout);
    // TODO: do not clear everything. Make only partial redraws!
    stream << Commands::clear;

    for (int y = 1; y < size().width(); ++y) {
        for (int x = 1; x < size().width(); ++x) {
            const QPoint pixel(x, y);

            bool drawn = false;
            // TODO: sort by Z value...
            // TODO: "bundle" pixels from same widget to prevent
            // multiple loop passes for the same widget
            for (const Widget *widget : qAsConst(_widgets)) {
                if (widget->visible() && widget->boundingRectangle().contains(pixel)) {
                    stream << Commands::moveToPosition(x, y);
                    stream << widget->drawPixel(pixel);
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
        QByteArray characters;
        for (int i = 0; i < bufferSize; ++i) {
            const char c = getchar();
            characters.append(c);
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
