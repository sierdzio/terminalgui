#pragma once

#include <QByteArray>

namespace Tg {
/*!
 * Various ANSI code commands.
 *
 * For more information, take a look at:
 * \li http://www.tldp.org/HOWTO/Bash-Prompt-HOWTO/x361.html
 * \li https://en.wikipedia.org/wiki/ANSI_escape_code
 */
namespace Command {
/*!
 * This string begins all ASCI controll sequences.
 */
const QByteArray ansiEscape = "\033[";

/*!
 * Common ending character for many ANSI codes.
 */
const QByteArray ansiEscapeEnd = "m";

/*!
 * Ending character when specifying cursor position.
 */
const QByteArray ansiPositionEnd = "H";

/*!
 * Up arrow code.
 *
 * \todo Move to Tg::Key?
 */
const QByteArray up = ansiEscape + "1A";

/*!
 * Down arrow code.
 *
 * \todo Move to Tg::Key?
 */
const QByteArray down = ansiEscape + "1B";

/*!
 * Right arrow code.
 *
 * \todo Move to Tg::Key?
 */
const QByteArray forward = ansiEscape + "1C";

/*!
 * Left arrow code.
 *
 * \todo Move to Tg::Key?
 */
const QByteArray backward = ansiEscape + "1D";

/*!
 * Clears whole terminal screen.
 */
const QByteArray clear = ansiEscape + "2J";

/*!
 * Clears whole terminal screen (?).
 */
const QByteArray erase = ansiEscape + "K";

/*!
 * Saves terminal state.
 */
const QByteArray save = ansiEscape + "s";

/*!
 * Restores terminal state.
 */
const QByteArray restore = ansiEscape + "u";

/*!
 * Ends ANSI Color definition.
 */
const QByteArray colorEnd = ansiEscape + "0" + ansiEscapeEnd;

/*!
 * Common separator between ANSI sequence parts.
 */
const QByteArray separator = ";";

/*!
 * Set font weight to bold (on some terminals).
 */
const QByteArray bold = ansiEscape + "1" + ansiEscapeEnd;

/*!
 * Resets font settings.
 */
const QByteArray resetFontSettings = colorEnd;

// Mouse support
// https://stackoverflow.com/questions/5966903/how-to-get-mousemove-and-mouseclick-in-bash

/*!
 * Sets some bit to "high" ("enabled" or "on").
 */
const QByteArray on = "h";

/*!
 * Sets some bit to "low" ("disabled", or "off");
 */
const QByteArray off = "l";

/*!
 * Sequence which enables mouse click reporting (but not mouse move).
 */
const QByteArray mouseClickReporting = ansiEscape + "?1000" + on;

/*!
 * Enables extended mouse coordinates (for terminals bigger than ~120 columns).
 */
const QByteArray mouseExtendedCoordinates = ansiEscape + "?1006" + on;

/*!
 * Enables extended mouse reporting (hover tracking).
 */
const QByteArray mouseMovementReporting = ansiEscape + "?1003" + on;

/*!
 * End mouse state reporting.
 */
const QByteArray mouseEndReporting = ansiEscape + "?1000" + off;

/*!
 * Beginning of a mouse event.
 */
const QByteArray mouseEventBegin = ansiEscape + "<";

/*!
 * Indicates a mouse press.
 */
const QByteArray mousePressSuffix = "M";

/*!
 * Indicates a mouse release.
 */
const QByteArray mouseReleaseSuffix = "m";

/*!
 * Indicates a mouse click.
 */
const QByteArray mouseClick = mouseEventBegin + "0" + separator;

/*!
 * Indicates a mouse wheel up event.
 */
const QByteArray mouseWheelUp = mouseEventBegin + "64" + separator;

/*!
 * Indicates a mouse wheel down event.
 */
const QByteArray mouseWheelDown = mouseEventBegin + "65" + separator;

/*!
 * Indicates a mouse wheel down event.
 */
const QByteArray mouseMoveEvent = mouseEventBegin + "35" + separator;

/*!
 * Returns terminal command which will move the cursor to position \a x, \a y.
 *
 * \warning \a x and \a y start in top left corner of the screen and they both
 * start with `1` (one), not zero!
 */
QByteArray moveToPosition(const int x, const int y);
}
}
