#pragma once

#include <QChar>
#include <QString>

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
const QString ansiEscape = "\033[";

/*!
 * Common ending character for many ANSI codes.
 */
const QChar ansiEscapeEnd = 'm';

/*!
 * Ending character when specifying cursor position.
 */
const QChar ansiPositionEnd = 'H';

/*!
 * Up arrow code.
 *
 * \todo Move to Tg::Key?
 */
const QString up = ansiEscape + "1A";

/*!
 * Down arrow code.
 *
 * \todo Move to Tg::Key?
 */
const QString down = ansiEscape + "1B";

/*!
 * Right arrow code.
 *
 * \todo Move to Tg::Key?
 */
const QString forward = ansiEscape + "1C";

/*!
 * Left arrow code.
 *
 * \todo Move to Tg::Key?
 */
const QString backward = ansiEscape + "1D";

/*!
 * Clears whole terminal screen.
 */
const QString clear = ansiEscape + "2J";

/*!
 * Clears whole terminal screen (?).
 */
const QString erase = ansiEscape + 'K';

/*!
 * Saves terminal state.
 */
const QString save = ansiEscape + 's';

/*!
 * Restores terminal state.
 */
const QString restore = ansiEscape + 'u';

/*!
 * Ends ANSI Color definition.
 */
const QString colorEnd = ansiEscape + '0' + ansiEscapeEnd;

/*!
 * Common separator between ANSI sequence parts.
 */
const QChar separator = ';';

/*!
 * Set font weight to bold (on some terminals).
 */
const QString bold = ansiEscape + '1' + ansiEscapeEnd;

/*!
 * Resets font settings.
 */
const QString resetFontSettings = colorEnd;

// Mouse support
// https://stackoverflow.com/questions/5966903/how-to-get-mousemove-and-mouseclick-in-bash

/*!
 * Sets some bit to "high" ("enabled" or "on").
 */
const QChar on = 'h';

/*!
 * Sets some bit to "low" ("disabled", or "off");
 */
const QChar off = 'l';

/*!
 * Sequence which enables mouse click reporting (but not mouse move).
 */
const QString mouseClickReporting = ansiEscape + "?1000" + on;

/*!
 * Enables extended mouse coordinates (for terminals bigger than ~120 columns).
 */
const QString mouseExtendedCoordinates = ansiEscape + "?1006" + on;

/*!
 * Enables extended mouse reporting (hover tracking).
 */
const QString mouseMovementReporting = ansiEscape + "?1003" + on;

/*!
 * End mouse state reporting.
 */
const QString mouseEndReporting = ansiEscape + "?1000" + off;

/*!
 * Beginning of a mouse event.
 */
const QString mouseEventBegin = ansiEscape + '<';

/*!
 * Indicates a mouse press.
 */
const QChar mousePressSuffix = 'M';

/*!
 * Indicates a mouse release.
 */
const QChar mouseReleaseSuffix = 'm';

/*!
 * Indicates a mouse click.
 */
const QString mouseClick = mouseEventBegin + "0" + separator;

/*!
 * Indicates a mouse wheel up event.
 */
const QString mouseWheelUp = mouseEventBegin + "64" + separator;

/*!
 * Indicates a mouse wheel down event.
 */
const QString mouseWheelDown = mouseEventBegin + "65" + separator;

/*!
 * Indicates a mouse wheel down event.
 */
const QString mouseMoveEvent = mouseEventBegin + "35" + separator;

/*!
 * Returns terminal command which will move the cursor to position \a x, \a y.
 *
 * \warning \a x and \a y start in top left corner of the screen and they both
 * start with `1` (one), not zero!
 */
QString moveToPosition(const int x, const int y);
}
}
