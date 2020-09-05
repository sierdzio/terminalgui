#include <QCoreApplication>
#include <QDebug>

#include <widgets/tgscreen.h>
#include <widgets/tgwidget.h>
#include <widgets/tglabel.h>
#include <widgets/tgbutton.h>
#include <widgets/tglayout.h>

#include <widgets/tgstyle.h>
#include <widgets/tgtableborderstyle.h>

void populateWidget(Tg::Widget *parent) {
    auto w1 = new Tg::Label("a", parent);
    w1->show();

    auto w2 = new Tg::Button("bc", parent);
    w2->show();

    auto w3 = new Tg::Label("d", parent);
    w3->show();

    auto w4 = new Tg::Label("ef", parent);
    w4->show();
}

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
    auto style = Tg::StylePointer::create();
    style->setBorderStyleValues(Tg::TableBorderStyle());
    style->border->backgroundColor = Terminal::Color4Bit::Green;
    style->backgroundColor = Terminal::Color4Bit::LightGreen;
    style->inactiveBackgroundColor = Terminal::Color4Bit::LightMagenta;
    widgetColumn.setStyle(style, true);

    widgetColumn.setObjectName("widgetColumn");
    widgetColumn.setLayoutType(Tg::Layout::Type::Column);
    widgetColumn.setPosition(QPoint(1, 7));
    widgetColumn.setSize(size);
    widgetColumn.show();

    populateWidget(&widgetColumn);

    Tg::Widget widgetRow(&screen);
    widgetRow.setObjectName("widgetRow");
    widgetRow.setLayoutType(Tg::Layout::Type::Row);
    widgetRow.setPosition(QPoint(13, 7));
    widgetRow.setSize(size);
    widgetRow.show();

    populateWidget(&widgetRow);

    Tg::Widget widgetGrid(&screen);
    widgetGrid.setObjectName("widgetGrid");
    widgetGrid.setLayoutType(Tg::Layout::Type::Grid);
    widgetGrid.setPosition(QPoint(1, 14));
    widgetGrid.setSize(size);
    widgetGrid.show();

    populateWidget(&widgetGrid);

    CHECK(QObject::connect(&quitButton, &Tg::Button::clicked,
                           &app, &QCoreApplication::quit));
    CHECK(QObject::connect(&quitButton2, &Tg::Button::clicked,
                           &app, &QCoreApplication::quit));

    return app.exec();
}
