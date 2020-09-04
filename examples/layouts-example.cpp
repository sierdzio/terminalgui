#include <QCoreApplication>
#include <QDebug>

#include <widgets/tgscreen.h>
#include <widgets/tgwidget.h>
#include <widgets/tglabel.h>
#include <widgets/tgbutton.h>
#include <widgets/tglayout.h>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    Terminal::RawTerminalLocker locker;

    const QSize size(10, 5);

    Tg::Screen screen;
    Tg::Widget widget(&screen);
    widget.setObjectName("widget");
    widget.setPosition(QPoint(1, 1));
    widget.setSize(size);
    widget.setLayoutType(Tg::Layout::Type::None);
    widget.show();

    Tg::Button quitButton(QObject::tr("Quit"), &widget);
    quitButton.setObjectName("quitButton");
    quitButton.show();    

    Tg::Widget widgetFill(&screen);
    widgetFill.setObjectName("widgetFill");
    widgetFill.setLayoutType(Tg::Layout::Type::ChildFillsParent);
    widgetFill.setPosition(QPoint(13, 1));
    widgetFill.setSize(size);
    widgetFill.show();

    Tg::Button quitButton2(QObject::tr("Quit"), &widgetFill);
    quitButton2.setObjectName("quitButton2");
    quitButton2.show();

    Tg::Widget widgetColumn(&screen);
    widgetColumn.setObjectName("widgetColumn");
    widgetColumn.setLayoutType(Tg::Layout::Type::Column);
    widgetColumn.setPosition(QPoint(1, 7));
    widgetColumn.setSize(size);
    widgetColumn.show();

    Tg::Label l1("a", &widgetColumn);
    l1.show();

    Tg::Label l2("ab", &widgetColumn);
    l2.show();

    Tg::Label l3("c", &widgetColumn);
    l3.show();

    Tg::Label l4("d", &widgetColumn);
    l4.show();

    CHECK(QObject::connect(&quitButton, &Tg::Button::clicked,
                           &app, &QCoreApplication::quit));
    CHECK(QObject::connect(&quitButton2, &Tg::Button::clicked,
                           &app, &QCoreApplication::quit));

    return app.exec();
}
