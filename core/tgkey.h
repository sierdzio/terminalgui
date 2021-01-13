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
/*!
 * Up arrow key.
 */
const QString up = Command::ansiEscape + 'A';

/*!
 * Down arrow key.
 */
const QString down = Command::ansiEscape + 'B';

/*!
 * Right arrow key.
 */
const QString right = Command::ansiEscape + 'C';

/*!
 * Left arrow key.
 */
const QString left = Command::ansiEscape + 'D';

/*!
 * Tab key.
 */
const QChar tab = '\t';

/*!
 * Enter key.
 */
const QChar enter = '\n';

/*!
 * Return key.
 */
const QChar ret = '\r';

/*!
 * Backspace key.
 */
const int backspace = 0x007f;

/*!
 * Delete key.
 */
const QString del = Command::ansiEscape + "3~";

/*!
 * Space key.
 */
const QChar space = ' ';

/*!
 * Ctrl+C
 */
const QChar ctrlC = '\003';

/*!
 * Ctrl+D
 */
const QChar ctrlD = '\004';
}
}