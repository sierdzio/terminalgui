#pragma once

#include <widgets/tgwidget.h>

#include "menu/item.h"
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
    const ListItem *currentMenu() const;

private:
    int spacerHeight() const;
    //void showPopup(const QString &message) const;

    Tg::ListView *_listView = nullptr;
    Tg::Widget *_spacer = nullptr;
    Tg::Button *_finishButton = nullptr;

    bool _isDirty = false;

    const ListItem *_menu = new ListItem
    {
        tr("Main menu"),
        {
            new ListItem { tr("System options"),
            {
                new ListItem { tr("Wireless LAN"), {} },
                new ListItem { tr("Audio"), {} },
                new ListItem { tr("Password"), {} },
                new ListItem { tr("Hostname"), {} },
                new ListItem { tr("Boot / Auto Login"), {} },
                new ListItem { tr("Network At Boot"), {} },
                new ListItem { tr("Splash Screen"), {} },
                new ListItem { tr("Power LED"), {} }
            }},
            new ListItem { tr("Display Options"),
            {
                new ListItem { tr("Resolution"), {} },
                new ListItem { tr("Underscan"), {} },
                new ListItem { tr("Pixel Doubling"), {} },
                new ListItem { tr("Screen Blanking"), {} }
            }},
            new ListItem { tr("Interface Options"),
            {
                new ListItem { tr("Camera"), {} },
                new ListItem { tr("SSH"), {} },
                new ListItem { tr("VNC"), {} },
                new ListItem { tr("SPI"), {} },
                new ListItem { tr("I2C"), {} },
                new ListItem { tr("Serial Port"), {} },
                new ListItem { tr("1-Wire"), {} },
                new ListItem { tr("Remote GPIO"), {} }
            }},
            new ListItem { tr("Performance Options"),
            {
                new ListItem { tr("Overclock"), {} },
                new ListItem { tr("GPU Memory"), {} },
                new ListItem { tr("Overlay File System"), {} },
                new ListItem { tr("Fan"), {} }
            }},
            new ListItem { tr("Localisation Options"),
            {
                new ListItem { tr("Locale"), {} },
                new ListItem { tr("Timezone"), {} },
                new ListItem { tr("Keyboard"), {} },
                new ListItem { tr("WLAN Country"), {} }
            }},
            new ListItem { tr("Advanced Options"),
            {
                new ListItem { tr("Expand Filesystem"), {} },
                new ListItem { tr("GL Driver"), {} },
                new ListItem { tr("Compositor"), {} },
                new ListItem { tr("Network Interface Names"), {} },
                new ListItem { tr("Network Proxy Settings"), {} },
                new ListItem { tr("Boot Order"), {} },
                new ListItem { tr("Bootloader Version"), {} },
                new ListItem { tr("Hdmi / Composite"), {} }
            }},
            new UpdateItem,
            new AboutItem
        },
        nullptr
    };

    const Item *_currentMenuItem = _menu;
};
