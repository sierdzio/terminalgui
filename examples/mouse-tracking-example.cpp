#include <QCoreApplication>
#include <QDebug>

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
    button.setPosition(QPoint(5, 5));
    button.setSize(QSize(15, 3));
    button.show();

    CHECK(QObject::connect(&button, &Tg::Button::clicked,
                           &app, &QCoreApplication::quit));

    Tg::Label label(QObject::tr("Drag me 2!"), &screen);
    label.setPosition(QPoint(25, 5));
    label.setSize(QSize(15, 3));
    label.show();

    Tg::Widget widget(&screen);
    widget.setPosition(QPoint(5, 10));
    widget.setSize(QSize(15, 3));
    widget.show();

    return app.exec();
}
