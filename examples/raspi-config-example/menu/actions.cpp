#include "actions.h"

#include <QObject>
#include <widgets/tgpopup.h>

AboutItem::AboutItem(ListItem *parent)
    : ActionItem(QObject::tr("About raspi-config-tg"), parent)
{
}

bool AboutItem::trigger(Tg::Widget *displayWidget) const
{
    showPopup(displayWidget, QObject::tr(
        "This tool provides a straightforward way of "
        "doing initial configuration of the Raspberry Pi. Although it can be "
        "run at any time, some of the options may have difficulties if you "
        "have heavily customised your installation."));

    return true;
}

UpdateItem::UpdateItem(ListItem *parent)
    : ActionItem(QObject::tr("Update"), parent)
{
}

bool UpdateItem::trigger(Tg::Widget *displayWidget) const
{
    runProcess(displayWidget, QObject::tr("Update will be performed!"),
               "ls", { "-aGl" });

    return true;
}
