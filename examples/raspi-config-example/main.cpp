#include <QCoreApplication>

#include <tgterminal.h>
#include <tgscreen.h>
#include <widgets/tgwidget.h>
#include <widgets/tglabel.h>
#include <widgets/tgbutton.h>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    Tg::RawTerminalLocker locker;

    Tg::Screen screen;

    Tg::Button button(QObject::tr("Drag me!"), &screen);
    button.setTitle(QObject::tr("Title!"));
    button.setPosition(QPoint(5, 5));
    button.setSize(QSize(15, 3));
    button.show();

    CHECK(QObject::connect(&button, &Tg::Button::clicked,
                           &app, &QCoreApplication::quit));

    return app.exec();
}

