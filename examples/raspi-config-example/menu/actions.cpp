#include "actions.h"

#include <widgets/tgpopup.h>
#include <menus/listmenuitem.h>

#include <QObject>
#include <QCoreApplication>

AboutItem::AboutItem(Tg::ListMenuItem *parent)
    : Tg::ActionMenuItem(QObject::tr("About raspi-config-tg"), parent)
{
}

bool AboutItem::trigger(Tg::Widget *displayWidget) const
{
    showPopup(displayWidget, QObject::tr(
        "This tool provides a straightforward way of "
        "doing initial configuration of the Raspberry Pi. Although it can be "
        "run at any time, some of the options may have difficulties if you "
        "have heavily customised your installation.\nVersion: %1")
              .arg(QCoreApplication::applicationVersion()));

    return true;
}

UpdateItem::UpdateItem(Tg::ListMenuItem *parent)
    : Tg::ActionMenuItem(QObject::tr("Update"), parent)
{
}

bool UpdateItem::trigger(Tg::Widget *displayWidget) const
{
    runScript(displayWidget, QObject::tr("Update will be performed!"),
              "apt-get update &&"
              "apt-get install raspi-config &&"
              "printf 'Sleeping 5 seconds before reloading raspi-config\n' &&"
              "sleep 5 &&"
              "exec raspi-config"
              );

    return true;
}

ProcessTestItem::ProcessTestItem(Tg::ListMenuItem *parent)
    : Tg::ActionMenuItem(QObject::tr("Process test"), parent)
{
}

bool ProcessTestItem::trigger(Tg::Widget *displayWidget) const
{
    runProcess(displayWidget, QObject::tr("Testing QProcess!"),
               "ls", { "-aGl" });

    return true;
}
