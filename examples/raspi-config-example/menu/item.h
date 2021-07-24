#ifndef ITEM_H
#define ITEM_H

#include <QString>
#include <QList>

class Item
{
public:
    Item(const QString &title, Item *parent = nullptr);

    Item *parent() const;

    virtual bool isMenu() const;
    virtual bool isAction() const;

private:
    const QString _title;
    Item *_parent = nullptr;
};

using Items = QList<Item*>;

class MenuItem : public Item
{
    MenuItem(const QString &title, Item *parent = nullptr);

    Items items() const;

private:
    Items _items;
};

#endif // ITEM_H
