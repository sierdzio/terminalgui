#include <QCoreApplication>
#include <QDebug>

#include <tgterminal.h>
#include <tgscreen.h>
#include <widgets/tgwidget.h>
#include <widgets/tglabel.h>
#include <widgets/tglineedit.h>
#include <widgets/tgbutton.h>
#include <widgets/tgcheckbox.h>
#include <widgets/tgradiobutton.h>
#include <layouts/tglayout.h>

#include <styles/tgstyle.h>
#include <styles/tgtableborderstyle.h>

void addCheckBox(Tg::Widget *parent, const int number)
{
    auto radio = new Tg::CheckBox(QObject::tr("CheckBox %1").arg(number),
                                     parent);
    radio->show();
}

void addRadioButton(Tg::Widget *parent, const int number)
{
    auto radio = new Tg::RadioButton(QObject::tr("RadioButton %1").arg(number),
                                     parent);
    radio->show();
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    Tg::RawTerminalLocker locker;

    Tg::Screen screen;
    Tg::Widget widget(&screen);
    widget.setObjectName("widget");
    widget.setPosition(QPoint(1, 1));
    widget.setSize(QSize(45, 30));
    widget.setLayoutType(Tg::Layout::Type::Column);
    widget.show();

    Tg::Button quitButton(QObject::tr("Quit"), &widget);
    quitButton.setObjectName("quitButton");
    quitButton.show();

    Tg::Label label(QObject::tr("Some example text ąęłóœą ☐ ☒"), &widget);
    label.show();

    int i = 1;
    addCheckBox(&widget, i++);
    addCheckBox(&widget, i);

    i = 1;
    addRadioButton(&widget, i++);
    addRadioButton(&widget, i++);
    addRadioButton(&widget, i++);
    addRadioButton(&widget, i);

    Tg::LineEdit lineEdit(QObject::tr("Placeholder text"), &widget);
    lineEdit.show();

    CHECK(QObject::connect(&quitButton, &Tg::Button::clicked,
                           &app, &QCoreApplication::quit));

    return app.exec();
}
