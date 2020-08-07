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
    Tg::Label labelBelow(QObject::tr("Below"), &screen);
    labelBelow.setPosition(QPoint(20, 0));
    labelBelow.setTextColor(Terminal::Color::Red);
    labelBelow.show();

    Tg::Label label(QObject::tr("Hello world!"), &labelBelow);
    label.setPosition(QPoint(0, 0));
    label.setTextColor(Terminal::Color::Green);
    label.show();

    Tg::Label labelAbove(QObject::tr("Above"), &label);
    labelAbove.setPosition(QPoint(40, 0));
    labelAbove.setTextColor(Terminal::Color::Cyan);
    labelAbove.show();

    Tg::ReversibleAnimation animation(&label, "position");
    animation.setDuration(5000);
    animation.setStartValue(QPoint(0, 0));
    const int endX = screen.size().width() - label.text().size();
    animation.setEndValue(QPoint(endX, 0));
    animation.start();

    return app.exec();
}
