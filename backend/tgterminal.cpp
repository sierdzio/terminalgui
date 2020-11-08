#include "tgterminal.h"

Tg::Terminal::Terminal(QObject *parent) : QObject(parent)
{
    _size = updateSize();
}

QSize Tg::Terminal::size() const
{
    return _size;
}


