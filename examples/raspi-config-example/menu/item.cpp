#include "item.h"

Item::Item(const QString &title, Item *parent) : _title(title), _parent(parent)
{
}

Item *Item::parent() const
{
    return _parent;
}

bool Item::isMenu() const
{
    return false;
}

bool Item::isAction() const
{
    return false;
}

MenuItem::MenuItem(const QString &title, Item *parent)
    : Item(title, parent)
{
}

Items MenuItem::items() const
{
    return _items;
}
