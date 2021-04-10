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
        Root,
        // Main menu
        SystemOptions,
        DisplayOptions,
        InterfaceOptions,
        PerformanceOptions,
        LocalisationOptions,
        AdvancedOptions,
        Update,
        About,
        // System options
        WirelessLan,
        Audio,
        Password,
        Hostname,
        BootAutoLogin,
        NetworkAtBoot,
        SplashScreen,
        PowerLed
    };

    MainWindow(Tg::Screen *screen);

private slots:
    void updateSpacerHeight();
    void onIndexPressed(const QModelIndex &index);

private:
    Tg::ListView *_listView = nullptr;
    Tg::Widget *_spacer = nullptr;
    Tg::Button *_finishButton = nullptr;

    MenuItem _currentMenuItem = MenuItem::Root;

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

    const QHash<MenuItem, QString> _systemOptionsLabels = {
        { MenuItem::WirelessLan, tr("Wireless LAN") },
        { MenuItem::Audio, tr("Audio") },
        { MenuItem::Password, tr("Password") },
        { MenuItem::Hostname, tr("Hostname") },
        { MenuItem::BootAutoLogin, tr("Boot / Auto Login") },
        { MenuItem::NetworkAtBoot, tr("Network At Boot") },
        { MenuItem::SplashScreen, tr("Splash Screen") },
        { MenuItem::PowerLed, tr("Power LED") }
    };
};

uint qHash(const MainWindow::MenuItem item);

#endif // MAINWINDOW_H
