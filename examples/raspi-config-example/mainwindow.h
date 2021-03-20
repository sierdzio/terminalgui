#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <widgets/tgwidget.h>

namespace Tg {
class Button;
class ListView;
}

class MainWindow : public Tg::Widget
{
    Q_OBJECT

public:
    MainWindow(Tg::Screen *screen);

private:
    Tg::ListView *_listView = nullptr;
    Tg::Button *_finishButton = nullptr;

    const QStringList _mainMenuLabels = {
        tr("System Options"),
        tr("Display Options"),
        tr("Interface Options"),
        tr("Performance Options"),
        tr("Localisation Options"),
        tr("Advanced Options"),
        tr("Update"),
        tr("About raspi-config-tg")
    };
};

#endif // MAINWINDOW_H
