#include <QCoreApplication>

#include <tgterminal.h>
#include <tgscreen.h>
#include <widgets/tglabel.h>
#include <styles/tgstyle.h>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    Tg::RawTerminalLocker locker;

    const auto background = Tg::Color::Predefined::Blue;

    Tg::Screen screen;
    screen.style()->screenBackgroundColor = background;

    Tg::Label model(QObject::tr("Raspberry Pi X Model Y Rev Z.Ż"), &screen);
    model.setBorderVisible(false);
    model.setBackgroundColor(background);
    model.setPosition(QPoint(1, 1));
    model.setSize(QSize(30, 1));
    model.show();

    MainWindow mainWindow(&screen);
    mainWindow.setBorderBackgroundColor(background);
    mainWindow.setPosition(QPoint(10, 6));
    mainWindow.setSize(QSize(80, 30));

    return app.exec();
}

