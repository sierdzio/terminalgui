#include <QCoreApplication>
#include <QDebug>

#include <tgscreen.h>
#include <widgets/tgwidget.h>
#include <widgets/tglabel.h>
#include <widgets/tglineedit.h>
#include <widgets/tgbutton.h>
#include <widgets/tgcheckbox.h>
#include <layouts/tglayout.h>

#include <styles/tgstyle.h>
#include <styles/tgtableborderstyle.h>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    Terminal::RawTerminalLocker locker;

    Tg::Screen screen;
    Tg::Widget widget(&screen);
    widget.setObjectName("widget");
    widget.setPosition(QPoint(1, 1));
    widget.setSize(QSize(50, 35));
    widget.setLayoutType(Tg::Layout::Type::Column);
    widget.show();

    Tg::Button quitButton(QObject::tr("Quit"), &widget);
    quitButton.setObjectName("quitButton");
    quitButton.show();

    Tg::Label label(QObject::tr("Some example text ąęłóœą ☐ ☒"), &widget);
    label.show();

    Tg::CheckBox checkBox(QObject::tr("This is a checkbox"), &widget);
    checkBox.show();

    Tg::LineEdit lineEdit(QObject::tr("Placeholder text"), &widget);
    lineEdit.show();

    CHECK(QObject::connect(&quitButton, &Tg::Button::clicked,
                           &app, &QCoreApplication::quit));

    return app.exec();
}
