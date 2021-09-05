#pragma once

#include "menuitem.h"

namespace Tg {
class Widget;
class ListMenuItem;

class ActionMenuItem : public MenuItem
{
public:
    ActionMenuItem(const QString &title, ListMenuItem *parent = nullptr);
    virtual ~ActionMenuItem();

    virtual bool trigger(Tg::Widget *displayWidget) const;

    bool isList() const override;
    bool isAction() const override;

protected:
    void showPopup(Tg::Widget *parent, const QString &message) const;
    void runProcess(Tg::Widget *parent,
                    const QString &question,
                    const QString &program,
                    const QStringList &arguments) const;
    void runScript(Tg::Widget *parent,
                   const QString &question,
                   const QString &script) const;
};
}
