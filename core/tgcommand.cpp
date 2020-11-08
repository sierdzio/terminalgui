#include "tgcommand.h"

QString Tg::Command::moveToPosition(const int x, const int y)
{
    return Command::ansiEscape + QString::number(y)
            + Command::positionSeparator + QString::number(x)
            + Command::ansiPositionEnd;
}
