#include "tgterminal.h"
#include "tgcommand.h"

#include <QTextStream>

// For reading terminal size
// https://stackoverflow.com/questions/6812224/getting-terminal-size-in-c-for-windows
#include <windows.h>
#include <conio.h>

QSize Tg::Terminal::terminalWindowSize() const
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    return QSize(columns, rows);
}

int Tg::Terminal::keyboardBufferSize()
{
    //https://docs.microsoft.com/en-us/cpp/c-runtime-library/console-and-port-i-o?redirectedfrom=MSDN&view=vs-2019
    return _kbhit();
}

int Tg::Terminal::getChar()
{
    // https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/getch-getwch?view=vs-2019
    return _getch();
}

void Tg::Terminal::registerSignalHandler()
{
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

#include <iostream>
Tg::RawTerminalLocker::RawTerminalLocker()
{
    // This is Windowese for "UTF-8, sorta where we feel like it"
    system("chcp 65001");
    system("cls");
}

Tg::RawTerminalLocker::~RawTerminalLocker()
{
    system("cls");
}
