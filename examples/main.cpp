#include <QCoreApplication>
#include <QPropertyAnimation>
#include <QDebug>

#include <backend/backend.h>
#include <widgets/reversibleanimation.h>
#include <widgets/tgscreen.h>
#include <widgets/tglabel.h>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    Tg::Screen screen;
    Tg::Label label(QObject::tr("Hello world!"), &screen);
    label.setPosition(QPoint(5, 0));
    label.setTextColor(Terminal::Color::Green);
    label.show();

    QPropertyAnimation animation(&label, "position");
    animation.setDuration(5000);
    animation.setStartValue(QPoint(0, 0));
    animation.setEndValue(QPoint(screen.size().width()/* - label.text().size()*/, 0));
    animation.start();

    QObject::connect(&screen, &Tg::Screen::end,
                     &app, &QCoreApplication::quit);

    return app.exec();
}
