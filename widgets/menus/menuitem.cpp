#include "menuitem.h"

Tg::MenuItem::MenuItem(const QString &title, MenuItem *parent) : _title(title), _parent(parent)
{
}

Tg::MenuItem::~MenuItem()
{
}

Tg::MenuItem *Tg::MenuItem::parent() const
{
    return _parent;
}

bool Tg::MenuItem::hasParent() const
{
    return _parent != nullptr;
}

QString Tg::MenuItem::title() const
{
    return _title;
}

bool Tg::MenuItem::isList() const
{
    return false;
}

bool Tg::MenuItem::isAction() const
{
    return false;
}

void Tg::MenuItem::setParent(MenuItem *item)
{
    _parent = item;
}
