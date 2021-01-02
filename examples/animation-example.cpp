#include <QCoreApplication>
#include <QPropertyAnimation>
#include <QDebug>

#include <tgterminal.h>
#include <tgscreen.h>
#include <utils/tgreversibleanimation.h>
#include <utils/tghelpers.h>
#include <widgets/tgwidget.h>
#include <widgets/tglabel.h>
#include <widgets/tgbutton.h>
#include <widgets/tglineedit.h>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    Tg::RawTerminalLocker locker;

    Tg::Screen screen;
    Tg::Label labelBelow(QObject::tr("Below with some extra text!"), &screen);
    labelBelow.setPosition(QPoint(20, 1));
    labelBelow.setSize(QSize(6, 5));
    labelBelow.setTextColor(Tg::Color::Predefined::Red);
    labelBelow.setBackgroundColor(Tg::Color::Predefined::Black);
    labelBelow.setBorderVisible(false);
    labelBelow.show();

    Tg::Label label(QObject::tr("Hello world!"), &screen);
    label.setPosition(QPoint(1, 1));
    label.setTextColor(Tg::Color::Predefined::Green);
    label.setBackgroundColor(Tg::Color::Predefined::Black);
    label.setBorderVisible(false);
    label.show();

    Tg::Label labelAbove(QObject::tr("Above"), &screen);
    labelAbove.setPosition(QPoint(40, 5));
    labelAbove.setTextColor(Tg::Color::Predefined::Cyan);
    labelAbove.setBackgroundColor(Tg::Color::Predefined::Black);
    labelAbove.setBorderVisible(false);
    labelAbove.show();

    Tg::Label labelNotOnFirstRow(QObject::tr("Detached with some extra text!"), &screen);
    labelNotOnFirstRow.setPosition(QPoint(1, 6));
    labelNotOnFirstRow.setSize(QSize(8, 7));
    labelNotOnFirstRow.setTextColor(Tg::Color::Predefined::Blue);
    labelNotOnFirstRow.show();

    Tg::Widget widget(&screen);
    widget.setPosition(QPoint(18, 6));
    widget.setSize(QSize(18, 10));
    widget.setBackgroundCharacter('x');
    widget.show();

    Tg::Button button(QObject::tr("Hide widget"), &widget);
    button.setPosition(QPoint(0, 1));
    button.setSize(QSize(12, 2));
    button.show();

    CHECK(QObject::connect(&button, &Tg::Button::clicked,
                           &labelNotOnFirstRow, &Tg::Label::hide));

    Tg::Button quitButton(QObject::tr("Quit"), &widget);
    quitButton.setPosition(QPoint(1, 4));
    quitButton.show();

    CHECK(QObject::connect(&quitButton, &Tg::Button::clicked,
                           &app, &QCoreApplication::quit));

    Tg::LineEdit lineEdit(QObject::tr("Placeholder"), &widget);
    lineEdit.setPosition(QPoint(2, 6));
    lineEdit.show();

    Tg::ReversibleAnimation animation(&label, "position");
    animation.setDuration(5000);
    animation.setStartValue(QPoint(1, 1));
    const int endX = screen.size().width() - label.text().size();
    animation.setEndValue(QPoint(endX, 7));
    animation.start();

    return app.exec();
}
