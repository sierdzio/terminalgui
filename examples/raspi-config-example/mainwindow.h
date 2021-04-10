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
    enum class MenuItem {
        // Main menu
        SystemOptions,
        DisplayOptions,
        InterfaceOptions,
        PerformanceOptions,
        LocalisationOptions,
        AdvancedOptions,
        Update,
        About
    };

    MainWindow(Tg::Screen *screen);

private slots:
    void updateSpacerHeight();
    void onIndexPressed(const QModelIndex &index);

private:
    Tg::ListView *_listView = nullptr;
    Tg::Widget *_spacer = nullptr;
    Tg::Button *_finishButton = nullptr;

    int spacerHeight() const;

    const QHash<MenuItem, QString> _mainMenuLabels = {
        { MenuItem::SystemOptions, tr("System Options") },
        { MenuItem::DisplayOptions, tr("Display Options") },
        { MenuItem::InterfaceOptions, tr("Interface Options") },
        { MenuItem::PerformanceOptions, tr("Performance Options") },
        { MenuItem::LocalisationOptions, tr("Localisation Options") },
        { MenuItem::AdvancedOptions, tr("Advanced Options") },
        { MenuItem::Update, tr("Update") },
        { MenuItem::About, tr("About raspi-config-tg") }
    };
};

#endif // MAINWINDOW_H
