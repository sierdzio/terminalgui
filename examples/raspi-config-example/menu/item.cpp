#include "item.h"

#include <QDebug>

Item::Item(const QString &title, Item *parent) : _title(title), _parent(parent)
{
}

Item::~Item()
{
}

Item *Item::parent() const
{
    return _parent;
}

bool Item::isList() const
{
    return false;
}

bool Item::isAction() const
{
    return false;
}

ListItem::ListItem(const QString &title, Item *parent)
    : Item(title, parent)
{
}

ListItem::~ListItem()
{
    qDeleteAll(_items);
}

bool ListItem::isList() const
{
    return true;
}

bool ListItem::isAction() const
{
    return false;
}

Items ListItem::items() const
{
    return _items;
}

void ListItem::addItem(Item *item)
{
    // TODO: check for duplicates!
    _items.append(item);
}

ActionItem::ActionItem(const QString &title, ListItem *parent)
    : Item(title, parent)
{
    if (parent) {
        parent->addItem(this);
    }
}

ActionItem::~ActionItem()
{
}

bool ActionItem::trigger()
{
    qDebug() << "Base ActionItem::trigger()";

    return true;
}

bool ActionItem::isList() const
{
    return false;
}

bool ActionItem::isAction() const
{
    return true;
}
