#include <QCoreApplication>
#include <QDebug>

#include <widgets/tgscreen.h>
#include <widgets/tgwidget.h>
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

    Tg::Widget widgetColumn(&screen);
    widgetColumn.setObjectName("widgetColumn");
    widgetColumn.setLayoutType(Tg::Layout::Type::ChildFillsParent);
    widgetColumn.setPosition(QPoint(13, 1));
    widgetColumn.setSize(size);
    widgetColumn.show();

    Tg::Button quitButton2(QObject::tr("Quit"), &widgetColumn);
    quitButton2.setObjectName("quitButton2");
    quitButton2.show();

    CHECK(QObject::connect(&quitButton, &Tg::Button::clicked,
                           &app, &QCoreApplication::quit));
    CHECK(QObject::connect(&quitButton2, &Tg::Button::clicked,
                           &app, &QCoreApplication::quit));

    return app.exec();
}
