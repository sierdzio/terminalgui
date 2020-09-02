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
    widget.setPosition(QPoint(1, 1));
    widget.setSize(size);
    widget.show();

    Tg::Button quitButton(QObject::tr("Quit"), &widget);
    quitButton.setFillsParent(true);
    quitButton.show();    

    Tg::Widget widgetWithFillLayout(&screen);
    widgetWithFillLayout.setLayoutType(Tg::Layout::Type::ChildFillsParent);
    widgetWithFillLayout.setPosition(QPoint(13, 1));
    widgetWithFillLayout.show();

    Tg::Button quitButton2(QObject::tr("Quit"), &widgetWithFillLayout);
    // TODO: make sure size can be called at any point!
    // TODO: make sure layout is redone when child widget is added!
    widgetWithFillLayout.setSize(size);
    quitButton2.show();

    CHECK(QObject::connect(&quitButton, &Tg::Button::clicked,
                           &app, &QCoreApplication::quit));

    return app.exec();
}
