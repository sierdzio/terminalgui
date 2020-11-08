#include "tgterminal.h"

Tg::Terminal *Tg::Terminal::_globalTerminal = nullptr;

Tg::Terminal::Terminal(QObject *parent) : QObject(parent)
{
    _globalTerminal = this;
    _size = updateSize();
    registerSignalHandler();
}

Tg::Terminal *Tg::Terminal::globalTerminal()
{
    return _globalTerminal;
}

QSize Tg::Terminal::size() const
{
    return _size;
}

void Tg::Terminal::setSize(const QSize &newSize)
{
    if (_size != newSize) {
        _size = newSize;
        emit sizeChanged(newSize);
    }
}


