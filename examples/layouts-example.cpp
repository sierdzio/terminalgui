#include <QCoreApplication>
#include <QPropertyAnimation>
#include <QDebug>

#include <widgets/tgscreen.h>
#include <widgets/tgwidget.h>
#include <widgets/tgbutton.h>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    Terminal::RawTerminalLocker locker;

    Tg::Screen screen;
    Tg::Widget widget(&screen);
    widget.setPosition(QPoint(1, 1));
    widget.setSize(QSize(18, 10));
    widget.show();

    Tg::Button quitButton(QObject::tr("Quit"), &widget);
    quitButton.setFillsParent(true);
    quitButton.show();

    CHECK(QObject::connect(&quitButton, &Tg::Button::clicked,
                           &app, &QCoreApplication::quit));

    return app.exec();
}
