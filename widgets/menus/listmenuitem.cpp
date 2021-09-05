#include "listmenuitem.h"

Tg::ListMenuItem::ListMenuItem(const QString &title, MenuItem *parent)
    : MenuItem(title, parent)
{
}

Tg::ListMenuItem::ListMenuItem(const QString &title, const Items &children, MenuItem *parent)
    : MenuItem(title, parent), _items(children)
{
    for (MenuItem *item : qAsConst(_items)) {
        item->setParent(this);
    }
}

Tg::ListMenuItem::~ListMenuItem()
{
    qDeleteAll(_items);
}

bool Tg::ListMenuItem::isList() const
{
    return true;
}

bool Tg::ListMenuItem::isAction() const
{
    return false;
}

Tg::Items Tg::ListMenuItem::items() const
{
    return _items;
}

QStringList Tg::ListMenuItem::listTitles() const
{
    QStringList result;

    for (auto item : qAsConst(_items)) {
        result.append(item->title());
    }

    return result;
}

void Tg::ListMenuItem::addItem(MenuItem *item)
{
    // TODO: check for duplicates!
    _items.append(item);
}
