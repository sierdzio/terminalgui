#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <widgets/tgwidget.h>

namespace Tg {
class Button;
}

class MainWindow : public Tg::Widget
{
    Q_OBJECT

public:
    MainWindow(Tg::Screen *screen);

private:
    Tg::Button *_button = nullptr;
};

#endif // MAINWINDOW_H
