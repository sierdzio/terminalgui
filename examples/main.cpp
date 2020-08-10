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
    labelBelow.setSize(QSize(6, 4));
    labelBelow.setTextColor(Terminal::Color4Bit::Red);
    labelBelow.setBackgroundColor(Terminal::Color4Bit::Black);
    labelBelow.setBorderVisible(false);
    labelBelow.show();

    Tg::Label label(QObject::tr("Hello world!"), &labelBelow);
    label.setPosition(QPoint(1, 1));
    label.setTextColor(Terminal::Color4Bit::Green);
    label.show();

    Tg::Label labelAbove(QObject::tr("Above"), &label);
    labelAbove.setPosition(QPoint(40, 4));
    labelAbove.setTextColor(Terminal::Color4Bit::Cyan);
    labelAbove.show();

    // TODO: fix issue with label trying to draw on border and segfaulting.
//    Tg::Label labelNotOnFirstRow(QObject::tr("Detached with some extra text!"), &screen);
//    labelNotOnFirstRow.setPosition(QPoint(1, 6));
//    labelNotOnFirstRow.setSize(QSize(8, 7));
//    labelNotOnFirstRow.setTextColor(Terminal::Color4Bit::Blue);
//    labelNotOnFirstRow.show();

    Tg::Widget widget(&screen);
    widget.setPosition(QPoint(18, 6));
    widget.setSize(QSize(18, 9));
    widget.show();

    Tg::ReversibleAnimation animation(&label, "position");
    animation.setDuration(5000);
    animation.setStartValue(QPoint(1, 1));
    const int endX = screen.size().width() - label.text().size();
    animation.setEndValue(QPoint(endX, 7));
    animation.start();

    return app.exec();
}
