#pragma once

#include "tgcommand.h"

#include <QByteArray>

namespace Tg {
/*!
 * Characters and escape sequences which can be found in keyboard buffer
 * (see Terminal::getChar()).
 */
namespace Key {
/*!
 * Up arrow key.
 */
const QByteArray up = Command::ansiEscape + "A";

/*!
 * Down arrow key.
 */
const QByteArray down = Command::ansiEscape + "B";

/*!
 * Right arrow key.
 */
const QByteArray right = Command::ansiEscape + "C";

/*!
 * Left arrow key.
 */
const QByteArray left = Command::ansiEscape + "D";

/*!
 * Tab key.
 */
const QByteArray tab = "\t";

/*!
 * Enter key.
 */
const QByteArray enter = "\n";

/*!
 * Return key.
 */
const QByteArray ret = "\r";

/*!
 * Backspace key.
 */
const QByteArray backspace = QByteArray(1, 0x007f);

/*!
 * Escape key.
 */
const QByteArray escape = QByteArray(1, 0x001b);

/*!
 * Delete key.
 */
const QByteArray del = Command::ansiEscape + "3~";

/*!
 * Space key.
 */
const QByteArray space = " ";

/*!
 * Ctrl+C
 */
const QByteArray ctrlC = "\003";

/*!
 * Ctrl+D
 */
const QByteArray ctrlD = "\004";
}
}
