#include <QCoreApplication>
#include <QDebug>

#include <backend/backend.h>
#include <widgets/tgscreen.h>
#include <widgets/tglabel.h>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    TgScreen screen;
    TgLabel label(QObject::tr("Hello world!"), &screen);
    label.setPosition(QPoint(5, 0));
    label.setTextColor(Terminal::Color::Green);
    label.show();

    QObject::connect(&screen, &TgScreen::end,
                     &app, &QCoreApplication::quit);

    return app.exec();
}
