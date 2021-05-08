#include "tgcommand.h"

QByteArray Tg::Command::moveToPosition(const int x, const int y)
{
    return Command::ansiEscape + QByteArray::number(y)
            + Command::separator + QByteArray::number(x)
            + Command::ansiPositionEnd;
}
