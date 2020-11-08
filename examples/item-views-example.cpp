#include <QCoreApplication>
#include <QStringListModel>
#include <QDebug>

#include <tgterminal.h>
#include <tgscreen.h>
#include <widgets/tgwidget.h>
#include <widgets/tglabel.h>
#include <widgets/tgbutton.h>
#include <widgets/tgscrollbar.h>
#include <widgets/tgscrollarea.h>
#include <widgets/tglistview.h>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    Tg::RawTerminalLocker locker;

    Tg::Screen screen;
    Tg::Widget widget(&screen);
    widget.setObjectName("widget");
    widget.setPosition(QPoint(1, 1));
    widget.setSize(QSize(20, 10));
    widget.setLayoutType(Tg::Layout::Type::Column);
    widget.show();

    Tg::Button quitButton(QObject::tr("Quit"), &widget);
    quitButton.setObjectName("quitButton");
    quitButton.show();

    CHECK(QObject::connect(&quitButton, &Tg::Button::clicked,
                           &app, &QCoreApplication::quit));

    const QString sizeText("%1 x %2");
    Tg::Label sizeLabel(&widget);
    sizeLabel.show();

    auto setter = [&sizeLabel, &sizeText](const QSize &size) {
        sizeLabel.setText(sizeText.arg(size.width()).arg(size.height()));
    };

    setter(screen.size());

    CHECK(QObject::connect(&screen, &Tg::Screen::sizeChanged,
                  &sizeLabel, setter));

    Tg::ScrollArea scrollArea(&widget);
    // TODO: fix layouts here - leaving size to default completely destroys
    // the UI!
    scrollArea.setSize(QSize(18, 7));
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
    tallLabel.setTextColor(Tg::Color::Predefined::Yellow);
    tallLabel.show();

    Tg::ListView listView(&screen);
    listView.setPosition(QPoint(22, 1));
    listView.setSize(QSize(20, 10));
    listView.setWrapRows(true);
    listView.setAlternatingRowColors(true);

    auto model = new QStringListModel(
                {
                    "Some",
                    "strings",
                    "in this long, very, very, very, long",
                    "model",
                    "are",
                    "simply",
                    "fabulous!",
                    "Be sure",
                    "to read them",
                    "all"
                },
                &listView);

    listView.setModel(model);
    listView.show();

    return app.exec();
}
