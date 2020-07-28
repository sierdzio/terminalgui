#include "consolescreen.h"

#include <ncursesw/ncurses.h>

#include <QDebug>

ConsoleScreen::ConsoleScreen(QObject *parent) : ConsoleWidget(parent)
{
    initscr();

    setPosition(QPoint(0, 0));
    setSize(QSize(COLS, LINES));

    _timer.setInterval(1000);
    _timer.setSingleShot(false);
    _timer.setTimerType(Qt::TimerType::VeryCoarseTimer);

    connect(&_timer, &QTimer::timeout,
            this, &ConsoleScreen::checkIfQuit);

    qDebug() << "ConsoleScreen info:" << position() << size();
}

ConsoleScreen::~ConsoleScreen()
{
    endwin();
}

void ConsoleScreen::show()
{
    // Console screen is not shown
    //ConsoleWidget::show();
}

void ConsoleScreen::waitForQuit()
{
    _timer.start();
}

void ConsoleScreen::checkIfQuit()
{
    noecho();
    const int character = getch();
    if (character == 'q') {
        emit end();
    }
}
