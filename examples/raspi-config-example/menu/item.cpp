#include "item.h"

#include <widgets/tgpopup.h>
#include <widgets/tglabel.h>
#include <widgets/tgbutton.h>

#include <QObject>

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

bool Item::hasParent() const
{
    return _parent != nullptr;
}

QString Item::title() const
{
    return _title;
}

bool Item::isList() const
{
    return false;
}

bool Item::isAction() const
{
    return false;
}

void Item::setParent(Item *item)
{
    _parent = item;
}

ListItem::ListItem(const QString &title, Item *parent)
    : Item(title, parent)
{
}

ListItem::ListItem(const QString &title, const Items &children, Item *parent)
    : Item(title, parent), _items(children)
{
    for (Item *item : qAsConst(_items)) {
        item->setParent(this);
    }
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

QStringList ListItem::listTitles() const
{
    QStringList result;

    for (auto item : qAsConst(_items)) {
        result.append(item->title());
    }

    return result;
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

bool ActionItem::trigger(Tg::Widget *displayWidget) const
{
    qDebug() << "Base ActionItem::trigger()" << displayWidget;

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

void ActionItem::showPopup(Tg::Widget *parent, const QString &message) const
{
    auto *popup = new Tg::Popup(QSize(55, 9), parent->screen());
    popup->setLayoutType(Tg::Layout::Type::Column);
    auto label = new Tg::Label(message, popup);
    label->setSize(QSize(53, 6));
    auto ok = new Tg::Button(QObject::tr("OK"), popup);
    popup->show();
    ok->setActiveFocus();

    CHECK(QObject::connect(ok, &Tg::Button::clicked,
                           popup, &Tg::Widget::hide));
    CHECK(QObject::connect(ok, &Tg::Button::clicked,
                           popup, &Tg::Widget::deleteLater));
}
