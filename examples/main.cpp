#include <QCoreApplication>
#include <QDebug>

#include <widgets/tgscreen.h>
#include <widgets/tglabel.h>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    TgScreen screen;
    TgLabel label(QObject::tr("Hello world!"), &screen);
    label.show();

    QObject::connect(&screen, &TgScreen::end,
                     &app, &QCoreApplication::quit);

    return app.exec();
}
