#include "tgterminal.h"
#include "tgcommand.h"

#include <QCoreApplication>
#include <QTextStream>

// For reading terminal size
// https://stackoverflow.com/questions/1022957/getting-terminal-width-in-c
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

static void linuxSignalHandler(const int signal)
{
    const auto terminal = Tg::Terminal::globalTerminal();
    if (terminal == nullptr) {
        return;
    }

    if (signal == SIGWINCH) {
        const auto newSize = terminal->updateSize();
        terminal->setSize(newSize);
    }
    else
    if (signal == SIGQUIT || signal == SIGTERM || signal == SIGKILL) {
        QCoreApplication::instance()->quit();
    }
}

QSize Tg::Terminal::updateSize()
{
    winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return QSize(w.ws_col, w.ws_row);
}

QPoint Tg::Terminal::currentPosition()
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
    if (signal(SIGWINCH, linuxSignalHandler) == SIG_ERR) {
        fputs("An error occurred while setting a signal handler.\n", stderr);
        return;
    }
}

void Tg::Terminal::enableMouseTracking()
{
    QTextStream stream(stdout);
    stream << Command::mouseClickReporting << Command::mouseExtendedCoordinates;
    _isMouseReporting = true;
}

void Tg::Terminal::disableMouseTracking()
{
    QTextStream stream(stdout);
    stream << Command::mouseEndReporting;
    _isMouseReporting = false;
}

// TODO: use termios! Right?
//#include <termios.h>

Tg::RawTerminalLocker::RawTerminalLocker()
{
    //struct termios term;
    //tcgetattr(standardInputIndex, &term);
    //term.c_lflag &= ~ICANON;
    //tcsetattr(standardInputIndex, TCSANOW, &term);
    //setbuf(stdin, NULL);

    system("stty raw -echo");
}

Tg::RawTerminalLocker::~RawTerminalLocker()
{
    system("stty cooked echo");
}
