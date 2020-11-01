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

    Tg::ScrollArea scrollArea(&screen);
    scrollArea.setPosition(QPoint(23, 1));
    scrollArea.setSize(QSize(18, 10));
    scrollArea.show();

    Tg::Label longLabel(&scrollArea);
    longLabel.setText(QObject::tr("Very long text which will DEFINITELY not fit the widget's width!"));
    longLabel.setPosition(QPoint(1, 0));
    longLabel.setSize(QSize(longLabel.text().length(), 1));
    longLabel.show();

    Tg::Label tallLabel(&scrollArea);
    tallLabel.setText(QObject::tr("Very long text which will DEFINITELY not fit the widget's height!"));
    tallLabel.setPosition(QPoint(0, 1));
    tallLabel.setSize(QSize(10, 7));
    tallLabel.setTextColor(Terminal::Color::Predefined::Yellow);
    tallLabel.show();

    return app.exec();
}
