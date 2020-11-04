#include "tglistview.h"

#include <QAbstractItemModel>

Tg::ListView::ListView(Tg::Widget *parent) : Tg::ScrollArea(parent)
{
    init();
}

Tg::ListView::ListView(Tg::Screen *screen) : Tg::ScrollArea(screen)
{
    init();
}

QString Tg::ListView::drawAreaContents(const QPoint &pixel) const
{
    if (model() == nullptr) {
        return {};
    }

    const QPoint childPx = childPixel(pixel);
    const int rowCount = model()->rowCount();

    if (childPx.y() >= rowCount) {
        return {};
    }

    const QModelIndex index = model()->index(childPx.y(), 0);
    const QString line = model()->data(index, Qt::ItemDataRole::DisplayRole).toString();

    if (childPx.x() >= line.length()) {
        return {};
    }

    return line.at(childPx.x());
}

QAbstractItemModel *Tg::ListView::model() const
{
    return _model;
}

void Tg::ListView::setModel(QAbstractItemModel *model)
{
    _model = model;
}

bool Tg::ListView::wrapRows() const
{
    return _wrapRows;
}

void Tg::ListView::setWrapRows(const bool wrapRows)
{
    if (_wrapRows == wrapRows)
        return;

    _wrapRows = wrapRows;
    emit wrapRowsChanged(_wrapRows);
}

void Tg::ListView::init()
{
    ScrollArea::init();
}

void Tg::ListView::consumeKeyboardBuffer(const QString &keyboardBuffer)
{
    ScrollArea::consumeKeyboardBuffer(keyboardBuffer);
}
