#include <QCoreApplication>
#include <QDebug>

#include <tgterminal.h>
#include <tgscreen.h>
#include <widgets/tglabel.h>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    Tg::RawTerminalLocker locker;

    Tg::Screen screen;

    Tg::Label label(QObject::tr("Drag me!"), &screen);
    label.setPosition(QPoint(5, 5));
    label.setSize(QSize(15, 3));
    label.show();

    return app.exec();
}
