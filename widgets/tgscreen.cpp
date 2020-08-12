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

    qDebug() << "TgScreen info:" << _size.width() << _size.height();
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
    }
}

void Tg::Screen::deregisterWidget(Tg::Widget *widget)
{
    _widgets.removeOne(widget);
}

void Tg::Screen::onNeedsRedraw()
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
