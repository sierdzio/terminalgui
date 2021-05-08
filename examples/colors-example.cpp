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

    const QSize size(20, 15);

    Tg::Screen screen;
    Tg::Widget widget(&screen);
    widget.setObjectName("widget");
    widget.setPosition(QPoint(1, 1));
    widget.setSize(size);
    widget.setLayoutType(Tg::Layout::Type::Column);
    widget.show();

    Tg::Button quitButton(QObject::tr("Quit"), &widget);
    quitButton.setObjectName("quitButton");
    quitButton.show();

    auto w1 = new Tg::Label("abcd", &widget);
    w1->setTextColor(Tg::Color(153, 204, 0));
    w1->show();

    auto w2 = new Tg::Label("bcde", &widget);
    w2->setBackgroundColor(Tg::Color(153, 204, 0));
    w2->show();

    auto w3 = new Tg::Label("defg", &widget);
    w3->setBackgroundCharacter("Z");
    w3->show();

    auto w4 = new Tg::Label("efgh", &widget);
    w4->setTextColor(Tg::Color(22, 22, 204));
    w4->setBackgroundColor(Tg::Color(204, 153, 0));
    w4->show();

    auto w5 = new Tg::Label("ghij", &widget);
    w5->show();

    auto w6 = new Tg::Label("klmn", &widget);
    w6->show();

    CHECK(QObject::connect(&quitButton, &Tg::Button::clicked,
                           &app, &QCoreApplication::quit));

    return app.exec();
}
