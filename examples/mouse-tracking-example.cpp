#include <QCoreApplication>
#include <QDebug>

#include <tgterminal.h>
#include <tgscreen.h>
#include <widgets/tgbutton.h>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    Tg::RawTerminalLocker locker;

    Tg::Screen screen;

    Tg::Button label(QObject::tr("Drag me!"), &screen);
    label.setPosition(QPoint(5, 5));
    label.setSize(QSize(15, 3));
    label.show();

    return app.exec();
}
