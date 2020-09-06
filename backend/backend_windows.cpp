#include "backend.h"

// For reading terminal size
// https://stackoverflow.com/questions/6812224/getting-terminal-size-in-c-for-windows
#include <windows.h>
#include <conio.h>

Terminal::Size Terminal::updateSize()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    Terminal::Size result;
    result.width = columns;
    result.height = rows;
    return result;
}

Terminal::Position Terminal::currentPosition()
{
//    winsize w;
//    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    Terminal::Position result;
//    result.x = w.ws_xpixel;
//    result.y = w.ws_ypixel;
    return result;
}

int Terminal::keyboardBufferSize()
{
    //https://docs.microsoft.com/en-us/cpp/c-runtime-library/console-and-port-i-o?redirectedfrom=MSDN&view=vs-2019
    return _kbhit();
}

int Terminal::getChar()
{
    // https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/getch-getwch?view=vs-2019
    return _getch();
}

// TODO: use termios! Right?
//#include <termios.h>

Terminal::RawTerminalLocker::RawTerminalLocker()
{
    //struct termios term;
    //tcgetattr(standardInputIndex, &term);
    //term.c_lflag &= ~ICANON;
    //tcsetattr(standardInputIndex, TCSANOW, &term);
    //setbuf(stdin, NULL);

    system("stty raw -echo");
}

Terminal::RawTerminalLocker::~RawTerminalLocker()
{
    system("stty cooked echo");
}
