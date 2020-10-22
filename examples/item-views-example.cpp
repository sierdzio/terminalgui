#include <QCoreApplication>
#include <QDebug>

#include <tgscreen.h>
#include <widgets/tgwidget.h>
#include <widgets/tglabel.h>
#include <widgets/tgbutton.h>
#include <widgets/tgscrollbar.h>
#include <widgets/tgscrollarea.h>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    Terminal::RawTerminalLocker locker;

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

    CHECK(QObject::connect(&quitButton, &Tg::Button::clicked,
                           &app, &QCoreApplication::quit));

    Tg::ScrollBar scrollBar(&widget);
    scrollBar.setOrientation(Qt::Orientation::Horizontal);
    scrollBar.show();

    // TODO: add example scroll bar, scroll area, list view etc.

    Tg::Widget widgetV(&screen);
    widgetV.setObjectName("widgetV");
    widgetV.setPosition(QPoint(size.width() + 1, 1));
    widgetV.setSize(size);
    widgetV.setLayoutType(Tg::Layout::Type::Row);
    widgetV.show();

    Tg::ScrollBar scrollBarV(&widgetV);
    scrollBarV.setOrientation(Qt::Orientation::Vertical);
    scrollBarV.show();

    Tg::ScrollArea scrollArea(&screen);
    scrollArea.setPosition(QPoint(5, 18));
    scrollArea.setSize(QSize(18, 10));
    scrollArea.show();

    Tg::Label longLabel(&scrollArea);
    longLabel.setText(QObject::tr("Very long text which will DEFINITELY not fit the widget's width!"));
    longLabel.setPosition(QPoint(-3, 0));
    longLabel.show();

    return app.exec();
}
