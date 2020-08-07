#include <QCoreApplication>
#include <QPropertyAnimation>
#include <QDebug>

#include <backend/backend.h>
#include <widgets/reversibleanimation.h>
#include <widgets/tgscreen.h>
#include <widgets/tgwidget.h>
#include <widgets/tglabel.h>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    Tg::Screen screen;
    Tg::Label labelBelow(QObject::tr("Below with some extra text!"), &screen);
    labelBelow.setPosition(QPoint(20, 1));
    labelBelow.setSize(QSize(6, 4)); // 6 characters per line, 3 lines
    labelBelow.setTextColor(Terminal::Color::Red);
    labelBelow.show();

    Tg::Label label(QObject::tr("Hello world!"), &labelBelow);
    label.setPosition(QPoint(1, 1));
    label.setTextColor(Terminal::Color::Green);
    label.show();

    Tg::Label labelAbove(QObject::tr("Above"), &label);
    labelAbove.setPosition(QPoint(40, 4));
    labelAbove.setTextColor(Terminal::Color::Cyan);
    labelAbove.show();

    Tg::Label labelNotOnFirstRow(QObject::tr("Detached with some extra text!"), &screen);
    labelNotOnFirstRow.setPosition(QPoint(1, 6));
    labelNotOnFirstRow.setSize(QSize(6, 5)); // 6 characters per line, 5 lines
    labelNotOnFirstRow.setTextColor(Terminal::Color::Blue);
    labelNotOnFirstRow.show();

    Tg::Widget widget(&screen);
    widget.setPosition(QPoint(18, 5));
    widget.setSize(QSize(8, 9));
    widget.show();

    Tg::ReversibleAnimation animation(&label, "position");
    animation.setDuration(5000);
    animation.setStartValue(QPoint(1, 1));
    const int endX = screen.size().width() - label.text().size();
    animation.setEndValue(QPoint(endX, 7));
    animation.start();

    return app.exec();
}
