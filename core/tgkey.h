#pragma once

#include "tgcommand.h"

#include <QChar>
#include <QString>

namespace Tg {
/*!
 * Characters and escape sequences which can be found in keyboard buffer
 * (see Terminal::getChar()).
 */
namespace Key {
const QString up = Command::ansiEscape + 'A';
const QString down = Command::ansiEscape + 'B';
const QString right = Command::ansiEscape + 'C';
const QString left = Command::ansiEscape + 'D';

const QChar tab = '\t';
const QChar enter = '\n';
const QChar ret = '\r';
const int backspace = 0x007f;
const QString del = Command::ansiEscape + "3~";
const QChar space = ' ';
}
}
