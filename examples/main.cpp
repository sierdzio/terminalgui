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

    Tg::Label labelAbove(QObject::tr("Block!"), &label);
    labelAbove.setPosition(QPoint(40, 0));
    labelAbove.setTextColor(Terminal::Color::Cyan);
    labelAbove.show();

    Tg::ReversibleAnimation animation(&label, "position");
    animation.setDuration(5000);
    animation.setStartValue(QPoint(0, 0));
    //qDebug() << "Screen size" << screen.size();
    const int endX = screen.size().width() - label.text().size();
    animation.setEndValue(QPoint(endX, 0));
    animation.start();

    return app.exec();
}
