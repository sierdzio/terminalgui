#pragma once

#include <QChar>
#include <QString>

namespace Tg {
// http://www.tldp.org/HOWTO/Bash-Prompt-HOWTO/x361.html
// https://en.wikipedia.org/wiki/ANSI_escape_code
namespace Command {
const QString ansiEscape = "\033[";
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

const QChar positionSeparator = ';';

const QString bold = ansiEscape + '1' + ansiEscapeEnd;
const QString resetFontSettings = colorEnd;

/*!
 * Returns terminal command which will move the cursor to position \a x, \a y.
 *
 * \warning \a x and \a y start in top left corner of the screen and they both
 * start with `1` (one), not zero!
 */
QString moveToPosition(const int x, const int y);
}
}
