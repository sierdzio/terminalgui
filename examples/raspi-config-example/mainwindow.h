#pragma once

#include <widgets/tgwidget.h>
#include <menus/menuitem.h>
#include <menus/listmenuitem.h>
#include <menus/actionmenuitem.h>

#include "menu/actions.h"

namespace Tg {
class Button;
class ListView;
}

class MainWindow : public Tg::Widget
{
    Q_OBJECT

public:
    MainWindow(Tg::Screen *screen);

signals:
    void update();

protected:
    bool consumeKeyboardBuffer(const QString &keyboardBuffer) override;

private slots:
    void updateSpacerHeight();
    void onIndexPressed(const QModelIndex &index);
    void quit();
    const Tg::ListMenuItem *currentMenu() const;

private:
    int spacerHeight() const;

    Tg::ListView *_listView = nullptr;
    Tg::Widget *_spacer = nullptr;
    Tg::Button *_finishButton = nullptr;

    bool _isDirty = false;

    // https://github.com/RPi-Distro/raspi-config/blob/master/raspi-config

    const Tg::ListMenuItem *_menu = new Tg::ListMenuItem
    {
        tr("Main menu"),
        {
            new Tg::ListMenuItem { tr("System options"),
            {
                new Tg::ListMenuItem { tr("Wireless LAN"), {} },
                new Tg::ListMenuItem { tr("Audio"), {} },
                new Tg::ListMenuItem { tr("Password"), {} },
                new Tg::ListMenuItem { tr("Hostname"), {} },
                new Tg::ListMenuItem { tr("Boot / Auto Login"), {} },
                new Tg::ListMenuItem { tr("Network At Boot"), {} },
                new Tg::ListMenuItem { tr("Splash Screen"), {} },
                new Tg::ListMenuItem { tr("Power LED"), {} }
            }},
            new Tg::ListMenuItem { tr("Display Options"),
            {
                new Tg::ListMenuItem { tr("Resolution"), {} },
                new Tg::ListMenuItem { tr("Underscan"), {} },
                new Tg::ListMenuItem { tr("Pixel Doubling"), {} },
                new Tg::ListMenuItem { tr("Screen Blanking"), {} }
            }},
            new Tg::ListMenuItem { tr("Interface Options"),
            {
                new Tg::ListMenuItem { tr("Camera"), {} },
                new Tg::ListMenuItem { tr("SSH"), {} },
                new Tg::ListMenuItem { tr("VNC"), {} },
                new Tg::ListMenuItem { tr("SPI"), {} },
                new Tg::ListMenuItem { tr("I2C"), {} },
                new Tg::ListMenuItem { tr("Serial Port"), {} },
                new Tg::ListMenuItem { tr("1-Wire"), {} },
                new Tg::ListMenuItem { tr("Remote GPIO"), {} }
            }},
            new Tg::ListMenuItem { tr("Performance Options"),
            {
                new Tg::ListMenuItem { tr("Overclock"), {} },
                new Tg::ListMenuItem { tr("GPU Memory"), {} },
                new Tg::ListMenuItem { tr("Overlay File System"), {} },
                new Tg::ListMenuItem { tr("Fan"), {} }
            }},
            new Tg::ListMenuItem { tr("Localisation Options"),
            {
                new Tg::ListMenuItem { tr("Locale"), {} },
                new Tg::ListMenuItem { tr("Timezone"), {} },
                new Tg::ListMenuItem { tr("Keyboard"), {} },
                new Tg::ListMenuItem { tr("WLAN Country"), {} }
            }},
            new Tg::ListMenuItem { tr("Advanced Options"),
            {
                new Tg::ListMenuItem { tr("Expand Filesystem"), {} },
                new Tg::ListMenuItem { tr("GL Driver"), {} },
                new Tg::ListMenuItem { tr("Compositor"), {} },
                new Tg::ListMenuItem { tr("Network Interface Names"), {} },
                new Tg::ListMenuItem { tr("Network Proxy Settings"), {} },
                new Tg::ListMenuItem { tr("Boot Order"), {} },
                new Tg::ListMenuItem { tr("Bootloader Version"), {} },
                new Tg::ListMenuItem { tr("Hdmi / Composite"), {} }
            }},
            new UpdateItem,
            new AboutItem,
            new ProcessTestItem
        },
        nullptr
    };

    const Tg::MenuItem *_currentMenuItem = _menu;
};
