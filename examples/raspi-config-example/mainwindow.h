#pragma once

#include <widgets/tgwidget.h>

#include "menu/item.h"

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
        PowerLed,
        // Display options
        Resolution,
        Underscan,
        PixelDoubling,
        ScreenBlanking,
        // Interface options
        Camera,
        Ssh,
        Vnc,
        Spi,
        I2c,
        SerialPort,
        OneWire,
        RemoteGpio,
        // Performance options
        Overclock,
        GpuMemory,
        OverlayFileSystem,
        Fan,
        // Localisation options
        Locale,
        Timezone,
        Keyboard,
        WlanCountry,
        // AdvancedOptions
        ExpandFilesystem,
        GlDriver,
        Compositor,
        NetworkInterfaceNames,
        NetworkProxySettings,
        BootOrder,
        BootloaderVersion,
        HdmiComposite
    };

    MainWindow(Tg::Screen *screen);

signals:
    void update();

protected:
    bool consumeKeyboardBuffer(const QString &keyboardBuffer) override;

private slots:
    void updateSpacerHeight();
    void onIndexPressed(const QModelIndex &index);
    void quit();

private:
    int spacerHeight() const;
    void showPopup(const QString &message) const;

    Tg::ListView *_listView = nullptr;
    Tg::Widget *_spacer = nullptr;
    Tg::Button *_finishButton = nullptr;

    bool _isDirty = false;
    MenuItem _currentMenuItem = MenuItem::Root;

    ListItem *_menu = new ListItem {
        "Main menu",

        {
            new ListItem { "System options", {}, nullptr }
        },

        nullptr
    };

    // QMap because order matters
    const QMap<MenuItem, QString> _mainMenuLabels = {
        { MenuItem::SystemOptions, tr("System Options") },
        { MenuItem::DisplayOptions, tr("Display Options") },
        { MenuItem::InterfaceOptions, tr("Interface Options") },
        { MenuItem::PerformanceOptions, tr("Performance Options") },
        { MenuItem::LocalisationOptions, tr("Localisation Options") },
        { MenuItem::AdvancedOptions, tr("Advanced Options") },
        { MenuItem::Update, tr("Update") },
        { MenuItem::About, tr("About raspi-config-tg") }
    };

    // QMap because order matters
    const QMap<MenuItem, QString> _systemOptionsLabels = {
        { MenuItem::WirelessLan, tr("Wireless LAN") },
        { MenuItem::Audio, tr("Audio") },
        { MenuItem::Password, tr("Password") },
        { MenuItem::Hostname, tr("Hostname") },
        { MenuItem::BootAutoLogin, tr("Boot / Auto Login") },
        { MenuItem::NetworkAtBoot, tr("Network At Boot") },
        { MenuItem::SplashScreen, tr("Splash Screen") },
        { MenuItem::PowerLed, tr("Power LED") }
    };

    // QMap because order matters
    const QMap<MenuItem, QString> _displayOptionsLabels = {
        { MenuItem::Resolution, tr("Resolution") },
        { MenuItem::Underscan, tr("Underscan") },
        { MenuItem::PixelDoubling, tr("Pixel Doubling") },
        { MenuItem::ScreenBlanking, tr("Screen Blanking") }
    };

    // QMap because order matters
    const QMap<MenuItem, QString> _interfaceOptionsLabels = {
        { MenuItem::Camera, tr("Camera") },
        { MenuItem::Ssh, tr("SSH") },
        { MenuItem::Vnc, tr("VNC") },
        { MenuItem::Spi, tr("SPI") },
        { MenuItem::I2c, tr("I2C") },
        { MenuItem::SerialPort, tr("Serial Port") },
        { MenuItem::OneWire, tr("1-Wire") },
        { MenuItem::RemoteGpio, tr("Remote GPIO") },
    };

    // QMap because order matters
    const QMap<MenuItem, QString> _performanceOptionsLabels = {
        { MenuItem::Overclock, tr("Overclock") },
        { MenuItem::GpuMemory, tr("GPU Memory") },
        { MenuItem::OverlayFileSystem, tr("Overlay File System") },
        { MenuItem::Fan, tr("Fan") }
    };

    // QMap because order matters
    const QMap<MenuItem, QString> _localisationOptionsLabels = {
        { MenuItem::Locale, tr("Locale") },
        { MenuItem::Timezone, tr("Timezone") },
        { MenuItem::Keyboard, tr("Keyboard") },
        { MenuItem::WlanCountry, tr("WLAN Country") }
    };

    // QMap because order matters
    const QMap<MenuItem, QString> _advancedOptionsLabels = {
        { MenuItem::ExpandFilesystem, tr("ExpandFilesystem") },
        { MenuItem::GlDriver, tr("GL Driver") },
        { MenuItem::Compositor, tr("Compositor") },
        { MenuItem::NetworkInterfaceNames, tr("Network Interface Names") },
        { MenuItem::NetworkProxySettings, tr("Network Proxy Settings") },
        { MenuItem::BootOrder, tr("Boot Order") },
        { MenuItem::BootloaderVersion, tr("Bootloader Version") },
        { MenuItem::HdmiComposite, tr("Hdmi / Composite") }
    };

    const QString _aboutText = tr("This tool provides a straightforward way of "
        "doing initial configuration of the Raspberry Pi. Although it can be "
        "run at any time, some of the options may have difficulties if you "
        "have heavily customised your installation.");
};

uint qHash(const MainWindow::MenuItem item);
