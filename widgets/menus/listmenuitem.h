#pragma once

#include "menuitem.h"

#include <QStringList>

namespace Tg {
class Widget;

class ListMenuItem : public MenuItem
{
public:
    ListMenuItem(const QString &title, MenuItem *parent = nullptr);
    ListMenuItem(const QString &title, const Items &children, MenuItem *parent = nullptr);
    virtual ~ListMenuItem();

    bool isList() const override;
    bool isAction() const override;

    Items items() const;
    // Consider returning built-in, static QStringListModel!
    QStringList listTitles() const;

    friend class ActionMenuItem;

protected:
    void addItem(MenuItem *item);

private:
    Items _items;
};
}
