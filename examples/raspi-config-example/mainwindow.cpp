#include "mainwindow.h"

#include <widgets/tgbutton.h>

#include <QCoreApplication>

MainWindow::MainWindow(Tg::Screen *screen) : Tg::Widget(screen)
{
    setTitle(QObject::tr("Raspberry Pi Configuration Tool (raspi-config-tg)"));

    _button = new Tg::Button(tr("Button"), this);

    CHECK(connect(_button, &Tg::Button::clicked,
                  QCoreApplication::instance(), &QCoreApplication::quit));

    show();
}
