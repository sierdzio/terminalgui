#pragma once

#include <QChar>
#include <QString>

namespace Tg {
// http://www.tldp.org/HOWTO/Bash-Prompt-HOWTO/x361.html
// https://en.wikipedia.org/wiki/ANSI_escape_code
namespace Command {
const QString ansiEscape = "\e[";
const QChar ansiEscapeEnd = 'm';
const QChar ansiPositionEnd = 'H';

const QString up = ansiEscape + "1A";
const QString down = ansiEscape + "1B";

const QString forward = ansiEscape + "1C";
const QString backward = ansiEscape + "1D";

const QString clear = ansiEscape + "2J";
const QString erase = ansiEscape + 'K';

const QString save = ansiEscape + 's';
const QString restore = ansiEscape + 'u';

const QString colorEnd = ansiEscape + '0' + ansiEscapeEnd;

const QChar separator = ';';

const QString bold = ansiEscape + '1' + ansiEscapeEnd;
const QString resetFontSettings = colorEnd;

// Mouse support
// https://stackoverflow.com/questions/5966903/how-to-get-mousemove-and-mouseclick-in-bash

const QChar on = 'h';
const QChar off = 'l';
const QString mouseClickReporting = ansiEscape + "?1000" + on;
//ansiEscape + "1015" + on
const QString mouseExtendedCoordinates = ansiEscape + "?1006" + on;
const QString mouseEndReporting = ansiEscape + "?1000" + off;

const QString mouseEventBegin = ansiEscape + '<';
const QChar mousePressSuffix = 'M';
const QChar mouseReleaseSuffix = 'm';

const QString mouseClick = mouseEventBegin + "0" + separator;
const QString mouseWheelUp = mouseEventBegin + "64" + separator;
const QString mouseWheelDown = mouseEventBegin + "65" + separator;

/*!
 * Returns terminal command which will move the cursor to position \a x, \a y.
 *
 * \warning \a x and \a y start in top left corner of the screen and they both
 * start with `1` (one), not zero!
 */
QString moveToPosition(const int x, const int y);
}
}
