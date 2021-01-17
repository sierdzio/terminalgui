#include "tgterminal.h"
#include "tgcommand.h"

#include <QCoreApplication>
#include <QTextStream>
#include <QDebug>

// For reading terminal size
// https://stackoverflow.com/questions/1022957/getting-terminal-width-in-c
#include <sys/ioctl.h>
#include <unistd.h>
#include <signal.h>
#include <termios.h>

static struct sigaction sigIntHandler;
struct termios previousTermios;

static void linuxSignalHandler(const int signal)
{
    const auto terminal = Tg::Terminal::globalTerminal();
    if (terminal == nullptr) {
        return;
    }

    if (signal == SIGWINCH) {
        const auto newSize = terminal->terminalWindowSize();
        terminal->setSize(newSize);
    }
    else
    if (signal == SIGQUIT || signal == SIGTERM || signal == SIGKILL) {
        QCoreApplication::instance()->quit();
    }
}

QSize Tg::Terminal::terminalWindowSize() const
{
    winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return QSize(w.ws_col, w.ws_row);
}

QPoint Tg::Terminal::cursorPosition()
{
    winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return QPoint(w.ws_xpixel, w.ws_ypixel);
}

int Tg::Terminal::keyboardBufferSize()
{
    int i;
    ioctl(standardInputIndex, FIONREAD, &i);
    return i;
}

int Tg::Terminal::getChar()
{
    return getchar();
}

void Tg::Terminal::registerSignalHandler()
{
    sigIntHandler.sa_handler = linuxSignalHandler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;

    sigaction(SIGWINCH, &sigIntHandler, NULL);
    sigaction(SIGQUIT, &sigIntHandler, NULL);
    sigaction(SIGTERM, &sigIntHandler, NULL);
    sigaction(SIGKILL, &sigIntHandler, NULL);
}

void Tg::Terminal::enableMouseTracking()
{
    QTextStream stream(stdout);
    stream << Command::mouseClickReporting
           << Command::mouseMovementReporting
           << Command::mouseExtendedCoordinates;
    _isMouseReporting = true;
}

void Tg::Terminal::disableMouseTracking()
{
    QTextStream stream(stdout);
    stream << Command::mouseEndReporting;
    _isMouseReporting = false;
}

// Adapted from https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html
void disableRawMode()
{
    const int result = tcsetattr(STDIN_FILENO, TCSAFLUSH, &previousTermios);
    if (result != 0) {
        qWarning() << Q_FUNC_INFO << "could not unlock the terminal" << result;
    }
}

Tg::RawTerminalLocker::RawTerminalLocker()
{
    tcgetattr(STDIN_FILENO, &previousTermios);
    //atexit(disableRawMode);

    struct termios raw = previousTermios;
    raw.c_lflag &= ~(ECHO | ICANON);

    const int result = tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    if (result != 0) {
        qWarning() << Q_FUNC_INFO << "could not lock the terminal" << result;
    }
}

Tg::RawTerminalLocker::~RawTerminalLocker()
{
    disableRawMode();
}

