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

QAbstractItemModel *Tg::ListView::model() const
{
    return _model;
}

void Tg::ListView::setModel(QAbstractItemModel *model)
{
    _model = model;
}

void Tg::ListView::init()
{
    ScrollArea::init();
}

void Tg::ListView::consumeKeyboardBuffer(const QString &keyboardBuffer)
{
    ScrollArea::consumeKeyboardBuffer(keyboardBuffer);
}
